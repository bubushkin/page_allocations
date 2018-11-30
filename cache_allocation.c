/*
===============================================================================
Driver Name		:		page_alloc
Author			:		ISKANDAR, NAVYA, SONALE
License			:		GPL
Description		:		LINUX DEVICE DRIVER PROJECT
===============================================================================
*/

#include "page_allocation.h"

#define PAGE_ALLOC_N_MINORS 1
#define PAGE_ALLOC_FIRST_MINOR 0
#define PAGE_ALLOC_BUFF_SIZE 1024



MODULE_LICENSE("GPL");
MODULE_AUTHOR("ISKANDAR, NAVYA, SONALE");

static int maobjnum = -0xFF;
static int count = 0x0;
static unsigned int current_cpu;
static unsigned int page_order;

static struct kmem_cache *p_mcache;

static unsigned int get_order_by_size(unsigned int asize);

struct _timer{

	unsigned int usec_start;
	unsigned int usec_end;

} t_timer;

int (*pf_page_allocation)(void *);
struct task_struct *p_kthread;



static struct _rdata{
	int xdata[0x8];
};

int page_allocation(void *unused){

	PINFO(CLASS_INFO "INIT\n");
	PINFO(CLASS_INFO AUTHOR_INFO "\n");


	if(maobjnum < 0x0){
		maobjnum = 2000;
		PINFO(CLASS_INFO "Setting objnum to default value: %d \n", maobjnum);
	}
	PINFO(CLASS_INFO "Page size: %d\n", PAGE_SIZE);
	PINFO(CLASS_INFO "Size of struct _rdata: %lu\n", sizeof(struct _rdata));
	PINFO(CLASS_INFO "Max allowed instances per page: %d\n", PAGE_SIZE / sizeof(struct _rdata));

	PINFO(CLASS_INFO "maobjnum: %lu\n", maobjnum);

	page_order = get_order(maobjnum);

	PINFO(CLASS_INFO "order for alloc_pages: %d\n", page_order);
	t_timer.usec_start = jiffies_to_nsecs(jiffies);
	void *p_data = kmem_cache_alloc(p_mcache, GFP_KERNEL);
	if(!p_mcache){
		PERR(CLASS_INFO "Memory allocation failed\n");
		return -ENOMEM;
	} else{
		PINFO(CLASS_INFO "Memory allocation successful\n");
	}
	kmem_cache_free(p_mcache, p_data);
	t_timer.usec_end = jiffies_to_nsecs(jiffies);
	PINFO(CLASS_INFO "Time took %lu nsec\n", t_timer.usec_end - t_timer.usec_start);

	while(!kthread_should_stop()){
		ssleep(0x1);
		count++;
	}



	PINFO(CLASS_INFO "Exiting page_allocator\n");
	return 0x0;
}

static int __init page_allocation_init(void){

	pf_page_allocation = &page_allocation;
	p_mcache = kmem_cache_create("p_mcache", maobjnum, 0x0, SLAB_HWCACHE_ALIGN|SLAB_PANIC, NULL);

	p_kthread = kthread_create(pf_page_allocation, NULL, "page_alloc/%u");
	current_cpu = get_cpu();
	PDEBUG(CLASS_INFO "Current CPU: %d", current_cpu);
	kthread_bind(p_kthread, 0x1);

	if(IS_ERR(p_kthread)){
		PERR(CLASS_INFO "kernel thread error\n");
		return PTR_ERR(p_kthread);
	} else
		wake_up_process(p_kthread);
	return 0;
}

static void __exit page_allocation_exit(void){

	PINFO(CLASS_INFO "EXIT\n");
	kmem_cache_destroy(p_mcache);
	if(p_kthread){
		int kret = kthread_stop(p_kthread);
		if(kret != -EINTR){
			PINFO(CLASS_INFO "kernel thread stopped");
		}
	}
}

static unsigned int get_order_by_size(unsigned int asize){

	unsigned int order;

	if(PAGE_SIZE >= asize){
		order = 0x0;
	} else{
		order = PAGE_SIZE / asize;
	}
	return order;
}

module_init(page_allocation_init);
module_exit(page_allocation_exit);

module_param(maobjnum, int, S_IRUGO);

MODULE_PARM_DESC(maobjnum, "(int) length in bytes");

