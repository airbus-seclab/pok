#ifndef __OCARINA_GENERATED_DEPLOYMENT_H_
#define __OCARINA_GENERATED_DEPLOYMENT_H_

#include <core/schedvalues.h>

#define POK_NEEDS_GETTICK             1
#define POK_NEEDS_THREADS             1
#define POK_NEEDS_PARTITIONS          1
#define POK_NEEDS_SCHED               1
#define POK_NEEDS_SCHED_RR            1
#define POK_NEEDS_DEBUG               1
//#define POK_NEEDS_DEBUG_MMU           1
#define POK_NEEDS_THREAD_SUSPEND      1
#define POK_NEEDS_THREAD_SLEEP        1
#define POK_NEEDS_THREAD_SLEEP_UNTIL  1
/* #define POK_NEEDS_CONSOLE             1 */
#define POK_NEEDS_LOCKOBJECTS         1
#define POK_NEEDS_PORTS_QUEUEING      1
#define POK_NEEDS_PORTS_SAMPLING      1
#define POK_NEEDS_PORTS_VIRTUAL       1
//#define POK_NEEDS_COVERAGE_INFOS

#define POK_CONFIG_LOCAL_NODE 0
#define POK_GENERATED_CODE 1

#define POK_CONFIG_NB_PARTITIONS 2
#define POK_CONFIG_NB_THREADS 6
#define POK_CONFIG_PARTITIONS_NTHREADS {2,2}

#define POK_CONFIG_NB_LOCKOBJECTS 2
#define POK_CONFIG_PARTITIONS_NLOCKOBJECTS {1,1}

#define POK_CONFIG_PARTITIONS_SIZE {1100000, 50000}
#define POK_CONFIG_PARTITIONS_SCHEDULER {POK_SCHED_RR,POK_SCHED_RR}

#define POK_CONFIG_SCHEDULING_SLOTS {1900, 100}
#define POK_CONFIG_SCHEDULING_SLOTS_ALLOCATION {0,1}
#define POK_CONFIG_SCHEDULING_NBSLOTS 2
#define POK_CONFIG_SCHEDULING_MAJOR_FRAME 2000

#define POK_CONFIG_STACKS_SIZE 16384
#define POK_CONFIG_PARTITIONS_PORTS {0,1}
#define POK_CONFIG_NB_PORTS 2
#define POK_CONFIG_NB_GLOBAL_PORTS 2

typedef enum
{
  pr2_pdatain = 0,
  pr1_pdataout = 1,
  invalid_local_port = 2
} pok_port_local_identifier_t;

typedef enum
{
  cpu = 0
} pok_node_identifier_t;

typedef enum
{
  pr2_pdatain_global = 0,
  pr1_pdataout_global = 1
} pok_port_identifier_t;

#define POK_CONFIG_NB_BUSES 0

typedef enum
{
  invalid_bus = 0
} pok_bus_identifier_t;

#define POK_CONFIG_NB_NODES 1

#endif
