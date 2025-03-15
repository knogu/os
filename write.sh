cp ./fs/kernel.bin /Volumes/OS/
cp ./fs/poiboot.conf /Volumes/OS/
cp ./fs/fs.img /Volumes/OS/
mkdir -p /Volumes/OS/EFI/BOOT
cp ./fs/EFI/BOOT/BOOTX64.EFI /Volumes/OS/EFI/BOOT/
diskutil unmount /Volumes/OS
