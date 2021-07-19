#include "gtypes.h"
#include <types.h>
#include "deployment.h"
#include <core/thread.h>
#include <middleware/port.h>
#include <assert.h>
#include <core/time.h>
#include <core/partition.h>

uint32_t pok_threads[POK_CONFIG_NB_THREADS];
uint8_t pr1_pdataout_id;

/*
 * NOP sled for insn injection. We should let room for ~1MB but
 * BIOS_SIZE in Qemu is 1MB max and POK is loaded as a BIOS image
 *
 * So we reduce space here to simplify. The full story is that
 * partitions are packed as ELF files in one "partitions.bin" which is
 * injected in the POK.elf file in the .archive2 section.
 *
 * The PPC relocation of POK starts @ 0xfff00000 until 4GB (the last
 * 1MB) because of the assumption it is loaded as a BIOS image by
 * Qemu. QEMU maps memory region of 1MB in last 4GB for the BIOS.
 * cf. hw/pci-host/prep.c (raven PCI controller)
 *
 * However, 0x20000 insn should be enough to trigger crash cases :)
 */
void thr_job (void)
{
    asm volatile (
                  "bl 1f         \n"
                  "1:            \n\t"
                  ".rept 0x20000 \n\t"
                  "nop           \n\t"
                  ".endr         \n\t"
                  "blr"
                  );
}

int main (void)
{
    /* single thread scenario */
    thr_job();

    /* pok_thread_attr_t tattr; */
    /* pok_ret_t ret; */

    /* /\* ret = pok_port_queueing_create ( *\/ */
    /* /\*    "pr1_pdataout", *\/ */
    /* /\*    2 * sizeof (int), POK_PORT_DIRECTION_OUT, *\/ */
    /* /\*    POK_PORT_QUEUEING_DISCIPLINE_FIFO, *\/ */
    /* /\*    &(pr1_pdataout_id)); *\/ */

    /* ret = pok_thread_attr_init (&(tattr)); */
    /* ASSERT_RET(ret); */
    /* tattr.stack_size = 4096; */
    /* tattr.entry = thr_job; */

    /* tattr.period = pok_time_milliseconds (1900); */
    /* tattr.time_capacity = -1; */
    /* //tattr.deadline = pok_time_milliseconds (1900); */

    /* ret = pok_thread_create (&(pok_threads[1]), &(tattr)); */
    /* ASSERT_RET(ret); */
    /* pok_partition_set_mode (POK_PARTITION_MODE_NORMAL); */
    return (0);
}
