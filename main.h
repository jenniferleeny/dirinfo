#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "write.h"
#endif

union north {
  int val;
  struct semid_ds *buf; // Buffer for IPC_STAT, IPC_SET
  unsigned short *array; // Array for GETALL, SETALL
  struct seminfo *_buf; // Buffer for IPC_INFO
  };

void create(char *, char *);

void remove_all(char *, char *);
