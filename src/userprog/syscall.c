#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

static uint32_t *esp;

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
//	printf("syscall : %d %d\n", *(uint32_t *)(f->esp),f->eax);
	//hex_dump(f->esp, f->esp, 100, 1);
	esp = f->esp;

  switch (*(uint32_t *)(f->esp)) {
    case SYS_HALT:  // 0
	break;
    case SYS_EXIT:  // 1
	exit(*(esp+1));
	//exit(*(uint32_t *)(f->esp + 4));
	break;
    case SYS_EXEC:  // 2
	break;
    case SYS_WAIT:  // 3
	break;
    case SYS_CREATE:// 4
	break;
    case SYS_REMOVE:// 5
	break;
    case SYS_OPEN:  // 6
	break;
    case SYS_FILESIZE: // 7
	break;
    case SYS_READ:  // 8
	break;
    case SYS_WRITE: // 9
	//f->eax = write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp+8), (unsigned)*((uint32_t *)(f->esp+12)));
	f->eax = write(*(esp+1), (void*) *(esp+2), *(esp+3));
	break;
    case SYS_SEEK:  // 10
	break;
    case SYS_TELL:  // 11
	break;
    case SYS_CLOSE: // 12
	break;

  }

  //printf ("system call!\n");
  //thread_exit ();
}

void halt(void) {
	shutdown_power_off();
}

void exit(int status) {
	printf("%s: exit(%d)\n",thread_name(),status);
	thread_exit();
}

pid_t exec (const char *cmd_line) {
	return process_execute(cmd_line);
}

int wait (pid_t pid) {
	return process_wait(pid);
}

int read (int fd, void* buffer, unsigned size) {
	int i;
	if(!fd) {
		for(i =0; i < size; i++) {
			if(((char *)buffer)[i] == '\0') {
				break;
			}
		}
	}
	return i;
}

int write(int fd, const void *buffer, unsigned size) {
	if (fd == 1) {
		putbuf(buffer,size);
		return size;
	}
	return -1;
}
