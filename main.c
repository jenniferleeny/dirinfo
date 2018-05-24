#include "main.h"

void create(char *name, char *arg) { //char* name, char* arg) {
  if (strcmp(arg, "-c") == 0) {
    int fd1 = open("story", O_CREAT | O_RDONLY | O_TRUNC, 0644);
    key_t key = ftok("story", 40);
    int shmid = shmget(key, sizeof(int), IPC_CREAT);
    /*printf("shmid: %d\n", shmid);
    if (shmid < 0) 
      printf("Error in creating shared memory! Error: %d %s\n", errno, strerror(errno));
    printf("shared memory created: %d\n", shmid);
    */
    int *shmidvar = (int *)shmat(shmid, 0, 0);
    struct shmid_ds *buf;
    shmctl(shmid, IPC_STAT, buf);
    //printf("BUFFER:\nsize_t: %zu time_t: %zu, pid_t: %d\n", buf->shm_segsz, buf->shm_atime, buf->shm_cpid);
    int semid = semget(key, 1, 0644 | IPC_CREAT);
    union semun su;
    su.val = 1;
    int semadd = semctl(semid, 0, SETVAL, su);
    /*if (semadd < 0) 
      printf("Error in creating semaphore!\nerror: %d strrerno: %s\n", errno, strerror(errno));    
      printf("semaphore created: %d\n", semadd);
    */
    close(fd1);
  }
}

void remove_all(char* name, char* arg) {
  if (strcmp(arg, "-r") == 0) {  
    //printf("REMOVE_ALL:\n\n");
    key_t key = ftok("story", 40);
    int semid = semget(key, 1, IPC_EXCL);//get access to a semaphore
    int shmid = shmget(key, sizeof(int), IPC_CREAT);
    
    int sem_rm = semctl(semid, 0, IPC_RMID);//remove the semaphore
    /*if (sem_rm < 0)
      printf("Error in removing semaphore!\nerror: %d strrerno: %s\n", errno, strerror(errno));
    printf("Detaching semaphore: %d\n", sem_rm);
    */
    int shm_rm = shmctl(shmid, IPC_RMID, NULL);
    /*if (shm_rm < 0) 
      printf("Error in removing semaphore!\nerror: %d strrerno: %s\n", errno, strerror(errno));
    printf("shared memory detached: %d\n", shm_rm);
    */
    int fd1 = open("story", O_RDONLY, 0644);
    /*
    if (fd1 == -1)
      printf("Error in reading file: Error: %d %s\n", errno, strerror(errno));
    else 
      printf("File successfully opened!\n");    
    */
    struct stat sb;
    stat("story" , &sb);
    char *story = (char *)malloc(sizeof(char *));
    int fd2 = read(fd1, story, 100*sizeof(char));
    printf("content of file displayed: %s\n", story);
    close(fd1);
    close(fd2);
  }
}

int main(int argc, char **argv) {
  /* if(strcmp(argv[1], "-c") == 0) {
    create("story",argv[1]);
  }
  else if(strcmp(argv[1], "-r") == 0) {
    remove_all("story", "-r");
  }
  else {
    printf("ERROR\n");
    }*/
  create("story" , "-c");  
  remove_all("story", "-r");

  key_t key = ftok("story", 40);
  
  int semid = semget( key, 1, IPC_CREAT);
  int shmid = shmget( key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
  
  int file = open("story", O_APPEND | O_RDONLY);
  
  char* last_line;
  int new_size;
  char* new_size_addr = shmat(shmid,0,0);
  memcpy(&new_size, new_size_addr, sizeof(int));
  int e = read(file, last_line, new_size);
  if (e < 0)
    printf("First line added\n");
  else
    printf("Last line added to the file: %s\n", last_line);

  special_access();
  
  return 0;
}

//EXTRA CODE
/*
struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    int semop_val = semop(semid, &sb, 1);
    if (semop_val != 0) {
      printf("Error in using semop!\nerror: %d strrerno: %s\n", errno, strerror(errno));
      }
*/
