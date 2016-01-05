##Build rt preempt kernel
Here we use kernel 3.12.12 as the example. <br>
1. Download Linux Kernel 3.12.12: <br>
`wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.12.12.tar.gz`<br>
2. Unzip the kernel: <br>
`tar -zxvf linux-3.12.12.tar.gz`<br>
3. Download rt preempt patch for Linux kernel 3.12.12:<br>
`wget https://www.kernel.org/pub/linux/kernel/projects/rt/3.12/older/patch-3.12.12-rt19.patch.gz`<br>
4. Patch the kernel:<br>
`gzip -d patch-3.12.12-rt19.patch.gz`<br>
`cd linux-3.12.12`<br>
`patch -p1 < ../patch-3.12.12-rt19.patch`<br>
5. Before building the kernel, make sure you have installed libncurses5-dev and kernel-package. If not, type:<br>
`apt-get install libncurses5-dev kernel-package`<br>
6. Config the kernel: <br>
First type: <br>
`make menuconfig`<br>
Then in the GUI, select “Fully Preemptible Kernel (RT)” under “Processor type and features” -> “Preemption Model” module<br>
7. Build the kernel:<br>
`make-kpkg clean`<br>
`make-kpkg --initrd --revision=1.0 kernel_image`<br>
`dpkg -i ../linux-image-3.12.12-rt19_1.0_i386.deb`<br>
