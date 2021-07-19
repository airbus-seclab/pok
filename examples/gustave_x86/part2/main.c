#include "activity.h"
#include "gtypes.h"
#include <types.h>
#include "deployment.h"
#include <core/thread.h>
#include <middleware/port.h>
#include <assert.h>
#include <core/time.h>
#include <core/partition.h>

uint32_t pok_threads[POK_CONFIG_NB_THREADS];
uint8_t pr2_pdatain_id;

/* void* thr_job (void) */
/* { */
/*     while(1) { */
/*     } */
/* } */

int main (void)
{
    /* single thread scenario */
    printf("p2");
    while(1) {
        pok_thread_suspend ();
    }


    /* pok_thread_attr_t tattr; */
    /* pok_ret_t ret; */

    /* /\* ret = pok_port_queueing_create ( *\/ */
    /* /\*                                 "pr2_pdatain", *\/ */
    /* /\*                                 2 * sizeof (int), *\/ */
    /* /\*                                 POK_PORT_DIRECTION_IN, *\/ */
    /* /\*                                 POK_PORT_QUEUEING_DISCIPLINE_FIFO, *\/ */
    /* /\*                                 &(pr2_pdatain_id)); *\/ */

    /* ret = pok_thread_attr_init (&(tattr)); */
    /* ASSERT_RET(ret); */
    /* tattr.entry = thr_job; */
    /* tattr.stack_size = 4096; */

    /* /\* tattr.period = pok_time_milliseconds (100); *\/ */
    /* tattr.period = pok_time_milliseconds (1900); */
    /* tattr.time_capacity = -1; //pok_time_milliseconds (1900); */
    /* tattr.deadline = pok_time_milliseconds (1900); */

    /* ret = pok_thread_create (&(pok_threads[1]), &(tattr)); */
    /* ASSERT_RET(ret); */
    /* pok_partition_set_mode (POK_PARTITION_MODE_NORMAL); */
    /* return (0); */
}
