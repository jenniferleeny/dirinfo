//Code still in progress
#include "write.h"

/*
int main() {
  key_t key = ftok("story", 40);
  int shmid = shmget(key, sizeof(int), IPC_CREAT);
  int semid = semget(key, 1, IPC_CREAT);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;                                                                                                             
  int semop_val = semop(semid, &sb, 1);
  if (semop_val != 0) {
    printf("Error in using semop!\nerror: %d strrerno: %s\n", errno, strerror(errno));
  }  
  int *shmidvar = (int *)shmat(shmid, 0, 0);
  
  return 0;
}
*/

void special_access() {
  key_t key = ftok("story", 40);
  
  int semid = semget( key, 1, IPC_CREAT);
  int shmid = shmget( key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);

  int file = open("story", O_APPEND | O_RDONLY);

  //Prompt
  printf("What is the next line?");

  char* add_line = malloc( 256 * sizeof(char) );
  add_line = fgets( add_line, 256, stdin );
  
  int e = write(file, add_line, sizeof(add_line));
  if(e < 0)
    printf("Error: %s\n", strerror(errno));

  //Stores size of add_line for future reference with last_line
  char* stored_address = shmat( shmid, 0, 0);
  int size = sizeof(add_line);
  memcpy(stored_address, &size, sizeof(int));
  
  e = close(file);
  if(e < 0)
    printf("Error: %s\n", strerror(errno));
}
