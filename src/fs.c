#include <fs.h>
#include <fbcon.h>
#include <common.h>

#define END_OF_FS	0x00

struct file *fs_start;

void fs_init(void *_fs_start)
{
	fs_start = _fs_start;
}

struct file *open(char *name)
{
	struct file *f = fs_start;
	while (f->name[0] != END_OF_FS) {
		if (!strcmp(f->name, name)) {
			puts("FOUND\r\n");
			putd(f->size, 10);
			return f;
		}
		f = (struct file *)((unsigned long long)f + sizeof(struct file)
				    + f->size);
	}

	return NULL;
}

unsigned long long get_files(struct file *files[])
{
	struct file *f = fs_start;
	unsigned int num;

	for (num = 0; f->name[0] != END_OF_FS; num++) {
		files[num] = f;
		f = (struct file *)((unsigned long long)f + sizeof(struct file)
				    + f->size);
	}

	return num;
}

void add_file(struct file newfile) {
	struct file *f = fs_start;
	unsigned int num;

	for (num = 0; f->name[0] != END_OF_FS; num++) {
		f = (struct file *)((unsigned long long)f + sizeof(struct file)
				    + f->size);
	}
	puts(newfile.data);
	*f = newfile;
	f = f + sizeof(struct file) + newfile.size;
	memcpy(f->name, END_OF_FS, 1);
}
