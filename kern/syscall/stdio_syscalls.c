#include <types.h>
#include <copyinout.h>
#include <syscall.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <lib.h>
#include <current.h>
#include <syscall.h>


ssize_t sys_write(int fd, const void *buf, size_t nbytes) {
  (void)fd;
  if(buf == NULL) {
    // no data to write
    return -1;
  }
  char* temp_buffer=kmalloc(sizeof(char)*(nbytes+1));
  if (temp_buffer == NULL) {
    // no space for malloc
    return -1;
  }
  //copy to my buffer
  copyin((const_userptr_t)buf,temp_buffer,nbytes);

  // terminate the string
  temp_buffer[nbytes]='\0';

  // print using kprintf
  kprintf("%s",temp_buffer);

	return nbytes;
}

ssize_t sys_read(int fd, const void *buf, size_t buflen) {
  (void)fd;
  int result;
 
  if (!buflen)
    return 0;
  if(buf == NULL) {
    // no buffer to store data
    return -1;
  }
  //Create a temporary array in the kernel to store buffer
  char* temp_buffer=kmalloc((buflen+1)*sizeof(char));

  if (temp_buffer == NULL) {
    // no space for malloc
    return -1;
  }
  // read from STDIN  

  size_t i;
  for(i = 0;i<buflen; i++ ){
    // TODO need to test that
	  temp_buffer[i] = getch();
  }
  temp_buffer[buflen] = '\0';

  //kgets(temp_buffer, buflen);


  //copy stored input to the user buffer
  result = copyout(temp_buffer,(userptr_t)buf,sizeof(buf));

  return result;
}

int sys_exit(int code) {
  (void)code;
  thread_exit();
  return 0;
}
