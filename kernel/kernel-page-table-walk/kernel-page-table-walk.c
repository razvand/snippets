/*
 * Go through addresses in kernel space virtual memory from PAGE_OFFSET to
 * high_memory (where low-mem physical memory is mapped) and then from
 * high_memory to VMALLOC_START (a virtual memory "hole" for catchig
 * out-of-bound memory accesses).
 */

#include <linux/module.h>
#include <linux/init.h>

MODULE_DESCRIPTION("Walk kernel space virtual memory");
MODULE_AUTHOR("So2rul Esforever");
MODULE_LICENSE("GPL");

extern void *high_memory;

/*
 * Go through each page in kernel virtual address space, extract first byte
 * and do a dumb XOR operation with it. Print the final result and the number
 * of pages walked.
 */

static void walk_pages(void *start, void *end)
{
	void *walk_address;
	unsigned char first_byte, result = 0;
	size_t walk_count = 0;

	pr_alert("Read first byte of each page starting from address %p to address %p\n",
			 start, end);
	for (walk_address = start; walk_address < end; walk_address += PAGE_SIZE) {
		first_byte = * (unsigned char *) walk_address;
		result = result ^ first_byte;
		walk_count++;
	}

	pr_alert("Walked through %zu pages. Kernel page walking result is %02x.\n",
			walk_count, result);
}

/*
 * Walk through the kernel virtual address space mapping the low-mem physical
 * memory. Stop at the start of the high memory map.
 */

static int kpg_walk_init(void)
{
	walk_pages((void *) PAGE_OFFSET, high_memory);
	return 0;
}

/*
 * Walk through the "hole" separate the low-mem mapping to the high memory
 * mapping. This should result in an oops, as that area is not valid.
 */

static void kpg_walk_exit(void)
{
	walk_pages(high_memory, (void *) VMALLOC_START);
}

module_init(kpg_walk_init);
module_exit(kpg_walk_exit);
