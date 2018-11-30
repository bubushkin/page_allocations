
#define DRIVER_NAME "page_allocation2"
#define KTHREAD_NAME  "pagealloc/%u"
#define PDEBUG(fmt,args...) printk(KERN_DEBUG"%s:"fmt,DRIVER_NAME, ##args)
#define PERR(fmt,args...) printk(KERN_ERR"%s:"fmt,DRIVER_NAME,##args)
#define PINFO(fmt,args...) printk(KERN_INFO"%s:"fmt,DRIVER_NAME, ##args)
#define AUTHOR_INFO "Iskandar, Navya, Sonale"
#define CLASS_INFO "CS630: "
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/mmzone.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
