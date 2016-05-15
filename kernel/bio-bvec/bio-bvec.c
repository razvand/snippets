/*
 * Print bio_vec information in bio. Add 4 bio_vecs (pages) in a bio and
 * then print information about bio_vecs: bio_vec index and bio_vec data
 * length. At the end destroy bio by freeing pages.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/blkdev.h>

MODULE_AUTHOR("SO2");
MODULE_DESCRIPTION("Test case for printing information about bvecs");
MODULE_LICENSE("GPL");

#define PHYSICAL_DISK_NAME	"/dev/sdb"
#define KERNEL_SECTOR_SIZE	512

/* pointer to physical device structure */
static struct block_device *phys_bdev;

static struct bio *construct_bio(struct block_device *bdev)
{
	struct bio *bio = bio_alloc(GFP_NOIO, 4);
	size_t i;
	struct page *page;
	size_t size;
	size_t offset;

	bio->bi_bdev = bdev;

	/*
	 * We don't care about the disk sector or direction. Initialize
	 * both to 0: read first sector. First sector is index 0 and read
	 * operation is 0 for bi_rw field.
	 */
	bio->bi_sector = 0;
	bio->bi_rw = 0;

	/*
	 * Add 4 pages (bio_vecs) to bio. For diversity make each bio_vec
	 * use a different data size and a different offset.
	 */
	for (i = 0; i < 4; i++) {
		page = alloc_page(GFP_NOIO);
		size = (i + 1) * KERNEL_SECTOR_SIZE;
		offset = (4 - i) * KERNEL_SECTOR_SIZE;
		bio_add_page(bio, page, size, offset);
		pr_info("Add page (bio_vec) in bio: bio_vec idx %u, %u bytes"
				" starting from offset %u\n",
				i, size, offset);
	}
	/* Use all bio_vecs in bio: start (bi_idx) is 0. */
	bio->bi_idx = 0;

	return bio;
}

static void print_info_bio(struct bio *bio)
{
	size_t idx;
	struct bio_vec *bvec;

	pr_alert("bio uses %u bio_vecs\n", bio->bi_vcnt);
	bio_for_each_segment(bvec, bio, idx) {
		pr_alert("bio_vec %u uses %u bytes starting from offset %u\n",
				idx, bvec->bv_len, bvec->bv_offset);
		pr_alert("bio_cur_bytes is %u\n", bio_cur_bytes(bio));
	}
}

static void destroy_bio(struct bio *bio)
{
	size_t idx;
	struct bio_vec *bvec;

	/* Free bio pages. Start from the beginning (bi_idx = 0). */
	bio->bi_idx = 0;
	bio_for_each_segment(bvec, bio, idx) {
		__free_page(bvec->bv_page);
		pr_info("Free bio page for bio_vec %u\n", idx);
	}
	bio_put(bio);
}

static struct block_device *open_disk(char *name)
{
	struct block_device *bdev;

	bdev = blkdev_get_by_path(name, FMODE_READ | FMODE_WRITE | FMODE_EXCL, THIS_MODULE);
	if (IS_ERR(bdev))
		return NULL;

	return bdev;
}

static int __init bio_bvec_init(void)
{
	struct bio *bio;

	phys_bdev = open_disk(PHYSICAL_DISK_NAME);
	if (phys_bdev == NULL) {
		pr_err("Error opening device %s\n", PHYSICAL_DISK_NAME);
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
