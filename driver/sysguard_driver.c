#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "sysguard"

static dev_t dev_number;
static struct cdev sysguard_cdev;
static struct class *sysguard_class;

static int sysguard_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "SysGuard: device opened\n");
    return 0;
}

static int sysguard_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "SysGuard: device closed\n");
    return 0;
}

static ssize_t sysguard_read(struct file *file,
                             char __user *buffer,
                             size_t length,
                             loff_t *offset)
{
    char message[] = "SysGuard driver active\n";
    size_t message_len = sizeof(message) - 1;

    if (*offset >= message_len)
        return 0;

    if (copy_to_user(buffer, message, message_len))
        return -EFAULT;

    *offset += message_len;

    return message_len;
}

static const struct file_operations sysguard_fops = {
    .owner = THIS_MODULE,
    .open = sysguard_open,
    .read = sysguard_read,
    .release = sysguard_release
};

static int __init sysguard_init(void)
{
    int result;

    printk(KERN_INFO "SysGuard: initializing driver\n");

    result = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);

    if (result < 0) {
        printk(KERN_ERR "SysGuard: failed to allocate device number\n");
        return result;
    }

    cdev_init(&sysguard_cdev, &sysguard_fops);

    result = cdev_add(&sysguard_cdev, dev_number, 1);

    if (result < 0) {
        unregister_chrdev_region(dev_number, 1);
        printk(KERN_ERR "SysGuard: failed to add cdev\n");
        return result;
    }

    sysguard_class = class_create(DEVICE_NAME);

    if (IS_ERR(sysguard_class)) {
        cdev_del(&sysguard_cdev);
        unregister_chrdev_region(dev_number, 1);
        printk(KERN_ERR "SysGuard: failed to create class\n");
        return PTR_ERR(sysguard_class);
    }

    if (IS_ERR(device_create(sysguard_class,
                             NULL,
                             dev_number,
                             NULL,
                             DEVICE_NAME))) {

        class_destroy(sysguard_class);
        cdev_del(&sysguard_cdev);
        unregister_chrdev_region(dev_number, 1);

        printk(KERN_ERR "SysGuard: failed to create device\n");
        return -1;
    }

    printk(KERN_INFO "SysGuard: /dev/sysguard created\n");

    return 0;
}

static void __exit sysguard_exit(void)
{
    device_destroy(sysguard_class, dev_number);
    class_destroy(sysguard_class);

    cdev_del(&sysguard_cdev);
    unregister_chrdev_region(dev_number, 1);

    printk(KERN_INFO "SysGuard: driver unloaded\n");
}

module_init(sysguard_init);
module_exit(sysguard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SysGuard Project");
MODULE_DESCRIPTION("SysGuard Linux monitoring character device driver");
MODULE_VERSION("1.0");
