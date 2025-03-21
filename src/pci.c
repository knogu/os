#include <x86.h>
#include <pci.h>
#include <fbcon.h>

#define CONFIG_ADDRESS	0x0cf8
#define CONFIG_DATA	0x0cfc

union pci_config_address {
	unsigned int raw;
	struct __attribute__((packed)) {
		unsigned int reg_addr:8;
		unsigned int func_num:3;
		unsigned int dev_num:5;
		unsigned int bus_num:8;
		unsigned int _reserved:7;
		unsigned int enable_bit:1;
	};
};

unsigned int get_pci_conf_reg(unsigned char bus, unsigned char dev, unsigned char func, unsigned char reg) {
    union pci_config_address conf_addr;
	conf_addr.raw = 0;
	conf_addr.bus_num = bus;
	conf_addr.dev_num = dev;
	conf_addr.func_num = func;
	conf_addr.reg_addr = reg;
	conf_addr.enable_bit = 1;
    io_write32(CONFIG_ADDRESS, conf_addr.raw);

	/* CONFIG_DATAを読み出す */
	return io_read32(CONFIG_DATA);
}

void dump_vid_did(unsigned char bus, unsigned char dev, unsigned char func) {
    unsigned int conf_data = get_pci_conf_reg(bus, dev, func, PCI_CONF_DID_VID);

    unsigned short vendor_id = conf_data & 0x0000ffff;
	unsigned short device_id = conf_data >> 16;

    puts("VENDOR ID ");
	puth(vendor_id, 4);
	puts("\r\n");
	puts("DEVICE ID ");
	puth(device_id, 4);
	puts("\r\n");
}
