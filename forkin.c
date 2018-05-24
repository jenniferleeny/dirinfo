#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

//Methods

int random_num(int s, int f) {
  int randomread = open("/dev/random", O_RDONLY);
  if (randomread == -1) {
    printf("error in populating: %s\n", strerror(errno));
    return -1;
  }
  else {
    int i;
    read(randomread, &i, 4);
    close(randomread);
    return (abs(i)%15) + 5;
  }
}

int main() {
  printf("[PARENT] data:\n");
  printf("[PARENT] pid: %d\n", getpid());
  printf("Fork #1:\n");
  int f1, f2, status;
  
  f1 = fork();//fork first child
  printf("f1: %d\n", f1);
  if (f1 != 0) {
    printf("[CHILD] pid#1: %d\n", getpid());  
    printf("Fork #2:\n");
    f2 = fork();//fork second child
    if (f2 != 0) {
      printf("[CHILD] pid#2: %d\n", getpid());
      //wait...
      int pid = wait(&status);
      int sec = WEXITSTATUS(status);
      printf("A child just exited after %d secs\n", sec);
      printf("pid of completed child: %d\n", pid);
    }
  }
  //sleeping
  if (f1 == 0 || f2 == 0) {
    printf("child pid: %d\n", getpid());
    int sleep_num = random_num(5, 21);
    sleep(sleep_num);
    printf("finished sleeping! Pid = %d", getpid());
    return sleep_num;
  }
  exit(33);
  return 0;
}
