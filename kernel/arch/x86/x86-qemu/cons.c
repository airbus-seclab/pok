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


#include <errno.h>

#include <arch/x86/ioports.h>
#include <libc.h>
#include <core/debug.h>
#include <core/cons.h>

#include "cons.h"

#ifdef POK_NEEDS_CONSOLE

static const int     screen_w = 80;
static const int     screen_h = 25;
static const int     tab_size = 8;
static char *const   vga_base = (char *)0xb8000;
struct s_cons        g_cons;


void pok_cons_print_char (const char c)
{
   char*                ptr;
   static struct s_cons local_curs; /* Local copy of the curent cursor position */
   int                  i;

   local_curs = g_cons;

   if (c == '\r')
   {
      local_curs.col = 0;
   }

   if (c == '\n')
   {
      local_curs.col = 0;
      ++local_curs.row;
   }

   if (c == '\t')
   {
      local_curs.col += tab_size - local_curs.col % tab_size;
   }

   if (c != '\r' && c != '\n' && c != '\t')
   {
      ptr = vga_base + 2 * screen_w * local_curs.row + 2 * local_curs.col++;
      *ptr = c;
      ++ptr;
      *ptr = local_curs.cur_attr;
   }

   if (local_curs.col >= screen_w)
   {
      local_curs.col = 0;
      ++local_curs.row;
   }

   if (local_curs.row >= screen_h)
   {
      memcpy (vga_base, vga_base + 2 * screen_w, (screen_h - 1) * screen_w * 2);
      for (i = 0; i < screen_w; ++i)
      {
         *(vga_base + 2 * screen_w * (screen_h - 1) + 2 * i) = 0;
         *(vga_base + 2 * screen_w * (screen_h - 1) + 2 * i + 1) = local_curs.cur_attr;
      }
      local_curs.row = screen_h - 1;
   }

   // Reset the global cursor to the new position
   g_cons = local_curs;
}

void pok_cons_attr (uint8_t attr)
{
   g_cons.cur_attr = attr;
}

void pok_cons_clear (void)
{
   int   i;
   int   j;
   char  *ptr;
   static struct s_cons		local_curs; /* local copy of the current cursor position */

   ptr = vga_base;
   local_curs = g_cons;

   for (i = 0 ; i < screen_h ; ++i)
   {
      for (j = 0 ; j < screen_w ; ++j)
      {
         *ptr = 0;
         ++ptr;
         *ptr = g_cons.cur_attr;
         ++ptr;
      }
   }

   local_curs.row = 0;
   local_curs.col = 0;

   g_cons = local_curs; /* reset the global cursor to the new position */
}

pok_bool_t pok_cons_write (const char *s, size_t length)
{
   int    res;
   size_t i;

   res = 0;
   i   = 0;

   while (i < length)
   {
      if ((const unsigned char)s[i] == CONS_ESCAPE)
      {
         ++i;
         switch (s[i])
         {
            case CONS_CLEAR:
               pok_cons_clear();
               break;
            case CONS_COLOR:
               ++i;
               pok_cons_attr((const unsigned char)s[i]);
               break;
            case CONS_SETY:
               ++i;
               g_cons.row = (const unsigned char)s[i] % screen_h;
               break;
            case CONS_SETX:
               ++i;
               g_cons.col = (const unsigned char)s[i] % screen_w;
               break;
            default:
               pok_cons_print_char(s[i]);
               ++res;
         }
      }
      else
      {
         pok_cons_print_char(s[i]);
         ++res;
      }
      ++i;
   }
   return res;
}

void pok_cons_disable_cursor (void)
{
   char tmp;
   int  base_port;

   if (inb(0x3cc) & 0x01)
   {
      base_port = 0x3d4;
   }
   else
   {
      base_port = 0x3b4;
   }

   tmp = inb (base_port);
   outb (base_port, 0x0a);
   outb (base_port + 1, inb (base_port + 1) | 0x20);
   outb (base_port, tmp);
}

int pok_cons_init (void)
{
   g_cons.cur_attr = CONS_FRONT (CONS_WHITE) | CONS_BACK (CONS_BLACK);
   pok_cons_clear ();
   pok_cons_disable_cursor ();
   pok_print_init (pok_cons_print_char, pok_cons_attr);
   return 0;
}

#else // ! NEEDS_CONSOLE


#if defined (POK_NEEDS_DEBUG) ||                \
    defined (POK_NEEDS_INSTRUMENTATION) ||      \
    defined (POK_NEEDS_COVERAGE_INFOS)

#define COM1 0x3F8

int is_transmit_empty() {
    return inb(COM1 + 5) & 0x20;
}

void write_serial(char a) {
    while (is_transmit_empty() == 0);
    outb(COM1,a);
}

int pok_cons_init (void)
{
    /* To be fixed : init serial */
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00);    //                  (hi byte)
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    return 0;
}

void pok_cons_print_char (const char c)
{
    write_serial (c);
}

pok_bool_t pok_cons_write (const char *s, size_t length)
{
    int    res = 0;
    size_t i   = 0;

    while (i < length) {
        if ((const unsigned char)s[i] == CONS_ESCAPE) {
            ++i;
            switch (s[i]) {
            case CONS_CLEAR:
                break;
            case CONS_COLOR:
                ++i;
                break;
            case CONS_SETY:
                ++i;
                break;
            case CONS_SETX:
                ++i;
                break;
            default:
                pok_cons_print_char(s[i]);
                ++res;
            }
        } else {
            pok_cons_print_char(s[i]);
            ++res;
        }
        ++i;
    }
    return res;
}
#else
int pok_cons_init (void){}
#endif

#endif // CONSOLE
