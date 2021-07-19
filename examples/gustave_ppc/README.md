# POK system for GUSTAVE ppc (c) Airbus 2020

Fixed POK PPC support for QEMU, with IDLE using PPC Power mode. It prevents
"hogging cpu" anytime idle is called for instance.

However you still have to take care of thread time setting, port
reading mode etc. POK offers timeout for some system calls.

## Build out of GUSTAVE

Should be built from GUSTAVE repository. However you can git it a try manually.

### Build QEMU with simplified PREP board (no GUSTAVE instrumentation)
```
T> git clone git@github.cert.corp:sduverger/qemu.git -b pok-ppc-nopci-novga qemu-git
T> mkdir qemu-git/build && cd qemu-git/build
T> ./configure --target-list=ppc-softmmu --disable-user --disable-sdl \
--disable-tpm --disable-libxml2 --disable-cap-ng --disable-curses \
--disable-vnc --disable-blobs --disable-kvm --disable-guest-agent
```

### Build POK firmware

You need a PowerPC cross compiler. The following pkgs might be useful:

```
T> sudo apt install binutils-powerpc-linux-gnu gcc-powerpc-linux-gnu
T> cd <HERE> ; make
```
### Run

```
T> qemu-git/build/ppc-softmmu -M prep -cpu 7400 -nographic -bios rom.bin
```
