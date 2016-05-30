#include <types.h>
#include <copyinout.h>
#include <syscall.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <lib.h>
#include <current.h>
#include <syscall.h>


void sys_exit(int code) {
  curthread->exitCode = code;
  thread_exit();
}
