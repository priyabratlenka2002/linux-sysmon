#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "sysmon.h"

#define DEVICE_NAME "sysmonitor"

static int major;
static struct class *sysmon_class;
static struct cdev sysmon_cdev;

static int dev_open(struct inode *inode, struct file *file)
{
    pr_info("sysmon: device opened\n");
    return 0;
}

static int dev_release(struct inode *inode, struct file *file)
{
    pr_info("sysmon: device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    struct sysmon_data data;

    if (*offset > 0)
        return 0;

    data.cpu_load = 42;
    data.mem_total = 1000000;
    data.mem_free = 500000;
    data.uptime = 12345;

    if (len < sizeof(data))
        return -EINVAL;

    if (copy_to_user(buf, &data, sizeof(data)))
        return -EFAULT;

    *offset += sizeof(data);
    return sizeof(data);
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
};

static int __init sysmon_init(void)
{
    dev_t dev;

    if (alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME) < 0)
        return -1;

    major = MAJOR(dev);
    cdev_init(&sysmon_cdev, &fops);

    if (cdev_add(&sysmon_cdev, dev, 1) < 0) {
        unregister_chrdev_region(dev, 1);
        return -1;
    }

    sysmon_class = class_create(DEVICE_NAME);
    if (IS_ERR(sysmon_class)) {
        cdev_del(&sysmon_cdev);
        unregister_chrdev_region(dev, 1);
        return PTR_ERR(sysmon_class);
    }

    device_create(sysmon_class, NULL, dev, NULL, DEVICE_NAME);
    pr_info("sysmon: driver loaded, major=%d\n", major);
    return 0;
}

static void __exit sysmon_exit(void)
{
    dev_t dev = MKDEV(major, 0);

    device_destroy(sysmon_class, dev);
    class_destroy(sysmon_class);
    cdev_del(&sysmon_cdev);
    unregister_chrdev_region(dev, 1);
    pr_info("sysmon: driver unloaded\n");
}

module_init(sysmon_init);
module_exit(sysmon_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("System monitor character device driver");
