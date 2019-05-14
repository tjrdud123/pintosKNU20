#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  int *p = f->esp;
  int syscall_number = *p++;
  
  // verify address

//  printf("\n\n\n%d\n\n\n", syscall_number);

  switch(syscall_number)
  {
    case SYS_HALT: // 0
      break;
    case SYS_EXIT: // 1
      break;
    case SYS_EXEC: // 2
      break;
    case SYS_WAIT: // 3
      break;
    case SYS_CREATE: // 4
      break;
    case SYS_REMOVE: // 5
      break;
    case SYS_OPEN: // 6
      break;
    case SYS_FILESIZE: // 7
      break;
    case SYS_READ: // 8
      break;
    case SYS_WRITE: // 9
      break;
    case SYS_SEEK: // 10
      break;
    case SYS_TELL: // 11
      break;
    case SYS_CLOSE: // 12
      break;
    default:
      //exit
      break;
  }









  thread_exit ();
}
