/*
 *                               POK header
 *
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team
 *
 * Created by julien on Thu Jan 15 23:34:13 2009
 */


#ifndef __POK_PPC_MSR_H__
#define __POK_PPC_MSR_H__

#define MSR_DR (1 << 4)
#define MSR_IR (1 << 5)
#define MSR_IP (1 << 6)

#define MSR_PR (1 << 14)
#define MSR_EE (1 << 15)
#define MSR_WE (1 << 18)

#ifndef __ASM__
static inline unsigned int get_msr (void)
{
   unsigned int res;
   asm ("mfmsr %0\n" : "=r" (res));
   return res;
}

static inline void set_msr (unsigned int val)
{
   asm volatile ("mtmsr %0\n" : : "r" (val));
}

#define HID0_POW   0x00E00000
#define SPR_HID0   0x3f0

#define __set_spr(_s_, _v_)				\
   asm volatile ("mtspr " # _s_ ", %0\n" : :"r" (_v_));

#define set_spr(_sPr_, _vAl_) __set_spr(_sPr_,_vAl_)

#endif // __ASM__

#endif

