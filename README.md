# page_allocations

Compare and contrast the results you saw for each of the module parameter values, and for
each of the memory allocation and deallocation approaches. As the answer to this exercise,
please describe briefly any trends you saw as the number of objects to allocate memory for
increased, and/or as the memory allocation approach changed.


All page allocations were gained from ZONE_NORMAL. alloc_page and kmalloc works with buddy allocator and provides physically contigious
buffer layout. We have also created additional cache in kernel's slab area and allocated memory portion. 
We used jiffies to measure memory allocations. Our delta shows 0ns for allocations. 
