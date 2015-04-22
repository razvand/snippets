/*
 * Print bvec information in bio. Add 4 bvecs (pages) in a bio and then print
 * information on bvecs: bvec index and bvec data length.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>

MODULE_AUTHOR("SO2");
MODULE_DESCRIPTION("Test case for printing information on bvecs in bio");
MODULE_LICENSE("GPL");

#define KERN_LOG_LEVEL		KERN_ALERT

#define PHYSICAL_DISK_NAME	"/dev/sdb"
#define KERNEL_SECTOR_SIZE	512

/* pointer to physical device structure */
static struct block_device *phys_bdev;

static struct bio *construct_bio(struct block_device *bdev)
{
	struct bio *bio = bio_alloc(GFP_NOIO, 4);
	struct page *page;
	size_t i;
	size_t size;

	bio->bi_bdev = bdev;

	/*
	 * We don't care about the disk sector or direction. Initialize
	 * to 0.
	 */
	bio->bi_sector = 0;
	bio->bi_rw = 0;

	/* Add 4 pages (bvecs) to bio, each using a different size. */
	for (i = 0; i < 4; i++) {
		page = alloc_page(GFP_NOIO);
		size = (i + 1) * KERNEL_SECTOR_SIZE;
		bio_add_page(bio, page, size, 0);
	}
	/* Use all bvecs in bio: start (bi_idx) is 0. */
	bio->bi_idx = 0;

	return bio;
}

static void print_info_bio(struct bio *bio)
{
	size_t idx;
	struct bio_vec *bvec;

	pr_alert("bio uses %u bvecs\n", bio->bi_vcnt);
	bio_for_each_segment(bvec, bio, idx) {
		pr_alert("bvec %u uses %u bytes starting from offset %u\n",
				idx, bvec->bv_len, bvec->bv_offset);
		pr_alert("bio_cur_bytes is %u\n", bio_cur_bytes(bio));
	}
}

static void destroy_bio(struct bio *bio)
{
	size_t idx;
	struct bio_vec *bvec;

	bio_for_each_segment(bvec, bio, idx) {
		__free_page(bvec->bv_page);
	}
	bio_put(bio);
}

static struct block_device *open_disk(char *name)
{
	struct block_device *bdev;

	bdev = blkdev_get_by_path(name, FMODE_READ | FMODE_WRITE | FMODE_EXCL, THIS_MODULE);
	if (IS_ERR(bdev)) {
		printk(KERN_ERR "blkdev_get_by_path\n");
		return NULL;
	}

	return bdev;
}

static int __init bio_bvec_init(void)
{
	struct bio *bio;

	phys_bdev = open_disk(PHYSICAL_DISK_NAME);
	if (phys_bdev == NULL) {
		printk(KERN_ERR "[relay_init] No such device\n");
		return -EINVAL;
	}

	bio = construct_bio(phys_bdev);
	print_info_bio(bio);
	destroy_bio(bio);

	return 0;
}

static void close_disk(struct block_device *bdev)
{
	blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
}

static void __exit bio_bvec_exit(void)
{
	close_disk(phys_bdev);
}

module_init(bio_bvec_init);
module_exit(bio_bvec_exit);
