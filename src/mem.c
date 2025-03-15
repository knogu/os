#include <mem.h>
#include <common.h>
#include <efi.h>
#include <fbcon.h>

void dump_memmap(void* ptr, unsigned long long mem_desc_num, unsigned long long mem_desc_unit_size)
{
    putc('D');
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
