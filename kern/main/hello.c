// this file will be only included if option hello is enabled

#include <types.h>
#include <lib.h>

void hello(void); // prototype

void hello(void) {
  kprintf("Hello from me!\n");
}
