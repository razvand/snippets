#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define IP_ADDRESS	0x01020304

static int pton_init(void)
{
	char buf[128];
	unsigned int address = IP_ADDRESS;

	sprintf(buf, "%d.%d.%d.%d", HIPQUAD(address));

	printk("buf is #%s#\n", buf);

	printk("enter\n");
	return 0;
}

static void pton_exit(void)
{
	printk("exit\n");
}

module_init(pton_init);
module_exit(pton_exit);
