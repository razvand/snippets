/*
 * Test whether user space data is accessible from kernel thread.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <asm/uaccess.h>

MODULE_DESCRIPTION("Access user space data from kernel thread");
MODULE_AUTHOR("So2rul Esforever");
MODULE_LICENSE("GPL");

#define BUSYBOX_TEXT_START_ADDRESS	0x08048000

static unsigned char buffer[64];

static int access_userspace_data(void *data)
{
	size_t i;

	pr_alert("Thread will read from address 0x%08x\n", BUSYBOX_TEXT_START_ADDRESS);

	if (copy_from_user(buffer, (void *) BUSYBOX_TEXT_START_ADDRESS, 64) != 0) {
		pr_alert("Unable to read from address 0x%08x\n", BUSYBOX_TEXT_START_ADDRESS);
		return -1;
	}

	pr_alert("Data has been read. Dumping hex:\n");
	for (i = 0; i < 64; i++)
		printk("\\x%02x", buffer[i]);
	pr_alert("\n");

	return 0;
}

static int kthread_user_init(void)
{
	struct task_struct *thread;
	
	thread = kthread_run(access_userspace_data, NULL, "access_user_thread");
	pr_alert("Thread has been created.\n");

	return 0;
}

static void kthread_user_exit(void)
{
}

module_init(kthread_user_init);
module_exit(kthread_user_exit);
