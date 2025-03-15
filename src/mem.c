#include <mem.h>
#include <common.h>
#include <efi.h>
#include <fbcon.h>

long long cur_size = 0;
long long page_cnt = 0;
long long physical_start = 0;

void mem_init(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size) {
    struct EFI_MEMORY_DESCRIPTOR *p = (struct EFI_MEMORY_DESCRIPTOR *)ptr;
	unsigned int i;
    for (i = 0; i < mem_desc_num; i++) {
		if (p->Type == EfiConventionalMemory) {
            physical_start = p->PhysicalStart;
            puts("\r\n");
            puts("physical start: ");
            puth(p->PhysicalStart, 16);
            puts("\r\nnumberOfPages: ");
            puth(p->NumberOfPages, 16);
            page_cnt = p->NumberOfPages;
            break;
		}
    }
}

void* alloc_pages(long long n) {
    if (page_cnt <= cur_size + n) {
        return NULL;
    }
    void* ret = (void*) (physical_start + PAGE_SIZE * cur_size);
    cur_size += n;
    return ret;
}

void dump_memmap(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size)
{
    puth(mem_desc_num, 16);
	struct EFI_MEMORY_DESCRIPTOR *p = (struct EFI_MEMORY_DESCRIPTOR *)ptr;
	unsigned int i;

	for (i = 0; i < mem_desc_num; i++) {
		if (p->Type == EfiConventionalMemory) {
			puth(p->NumberOfPages, 16);
			putc(' ');
		}
		// puth((unsigned long long)p, 16);
		// putc(' ');
		// puth(p->Type, 2);
		// putc(' ');
		// puth(p->PhysicalStart, 16);
		// putc(' ');
		// puth(p->VirtualStart, 16);
		// putc(' ');
		// puth(p->NumberOfPages, 16);
		// putc(' ');
		// puth(p->Attribute, 16);
		// puts("\r\n");

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + mem_desc_unit_size);
	}
}

struct EFI_MEMORY_DESCRIPTOR *get_allocatable_area(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size, unsigned long long size)
{
	struct EFI_MEMORY_DESCRIPTOR *p =
		(struct EFI_MEMORY_DESCRIPTOR *)ptr;
	unsigned long long i;

	for (i = 0; i < mem_desc_num; i++) {
		if ((p->Type == EfiConventionalMemory) &&
		    ((p->NumberOfPages * PAGE_SIZE) >= size))
			break;

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + mem_desc_unit_size);
	}

	return p;
}
