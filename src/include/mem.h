#ifndef _MEM_H_
#define _MEM_H_

#define PAGE_SIZE	4096
#define MEM_DESC_SIZE	4800

void dump_memmap(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size);
struct EFI_MEMORY_DESCRIPTOR *get_allocatable_area(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size, unsigned long long size);
void mem_init(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size);
void* alloc_pages(long long n);

#endif
