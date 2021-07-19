# POK system for GUSTAVE x86 (c) Airbus 2020

Should be built from GUSTAVE repository. However you can git it a try
manually.

Part1 is attacker partition. We use single thread model. EFLAGS is off
into part1 context so that nothing is scheduled (at best).

We might have preempt_enable() during execution of a syscall.  However
this should enhance AFL stability, preventing IRQ0 from updating the
coverage bitmap.

## Build POK firmware

```
T> make
```

## Run it to get some runtime info

Logs go to the terminal (from serial)
```
T> qemu-system-i386 -nographic -kernel pok.elf
T> <ctl-a> x
```
