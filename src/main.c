#include <x86.h>
#include <intr.h>
#include <pic.h>
#include <acpi.h>
#include <fb.h>
#include <kbc.h>
#include <fbcon.h>
#include <fs.h>
#include <hpet.h>
#include <common.h>
#include <sched.h>
#include <syscall.h>
#include <proc.h>
#include <mem.h>
#include <pci.h>
#include <nic.h>

struct __attribute__((packed)) platform_info {
	struct framebuffer fb;
	void *rsdp;
	void *mem;
	unsigned long long mem_desc_num;
	unsigned long long mem_desc_unit_size;
};

void do_taskA(void);

void start_kernel(void *_t __attribute__((unused)), struct platform_info *pi,
		  void *_fs_start)
{
	/* フレームバッファ周りの初期化 */
	fb_init(&pi->fb);
	set_fg(255, 255, 255);
	set_bg(0, 70, 250);
	clear_screen();

	/* ACPIの初期化 */
	acpi_init(pi->rsdp);

	/* CPU周りの初期化 */
	gdt_init();
	intr_init();

	/* 周辺ICの初期化 */
	pic_init();
	hpet_init();
	kbc_init();

	dump_vid_did(NIC_BUS_NUM, NIC_DEV_NUM, NIC_FUNC_NUM);
	while (1)
		cpu_halt();

	syscall_init();	
	
	fs_init(_fs_start);
	// struct file newfile;
	// memcpy(newfile.name, "NEW\0", 4);
	// memcpy(newfile.data, "THISISNEWFILE\0", 14);
	// puts(newfile.data);
	// newfile.size = 14;
	// add_file(&newfile);
	// struct file* ptr = open("NEW");
	// puts((char *)ptr->data);

	mem_init(pi->mem, pi->mem_desc_num, pi->mem_desc_unit_size);
	char* p = alloc_pages(1);
	p = "TESTTEST";
	puts(p);

	exec(open("test"));

	while (1)
		cpu_halt();

	/* スケジューラの初期化 */
	sched_init();

	/* CPUの割り込み有効化 */
	enable_cpu_intr();

	/* スケジューラの開始 */
	sched_start();

	do_taskA();

	/* haltして待つ */
	while (1)
		cpu_halt();
}

void do_taskA(void)
{
	while (1) {
		putc('A');
		volatile unsigned long long wait = 10000000;
		while (wait--);
	}
}
