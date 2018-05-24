#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

static void sighandler(int signo) {
  if (signo == SIGUSR1) {    
    char *filename = "who.txt";
    
    int f = fork();
    if (!f) {
      int fopen = open(filename, O_APPEND | O_CREAT, 0755);
      if (fopen == -1)
	printf("error %d: %s\n", errno, strerror(errno));
      dup2(fopen,STDOUT_FILENO);
      execlp("who", "who", NULL);
      int fclose = close(fopen);
      if (fclose == -1) 
	printf("error %d: %s\n", errno, strerror(errno));
      exit(0);
    }
  }
  else if (signo == SIGUSR2) {
    char *filename = "ps.txt";
    int f = fork();
    if (!f) {
      int fopen = open(filename, O_APPEND | O_CREAT, 0755);
      if (fopen == -1)
        printf("error %d: %s\n", errno, strerror(errno));
      dup2(fopen,STDOUT_FILENO);
      execlp("ps", "ps", NULL);
      int fclose = close(fopen);
      if (fclose == -1)
        printf("error %d: %s\n", errno, strerror(errno));
      exit(0);
    }
  }
  else if (signo == SIGINT) {
    printf("Interrupted... RUDE\n");
    
    printf("Content of whofile \n");
    int fwho = open("whofile", O_RDONLY);
    char buffer[1000];
    read(fwho, buffer, sizeof(buffer));
    close(fwho);
    printf("%s\n", buffer);
    printf("Content of psfile: \n");
    int fps =open("psfile", O_RDONLY);
    read(fps, buffer, sizeof(buffer));
    close(fps);
    printf("%s\n", buffer);
    exit(0);
  }
}



int main() {
  int i = 0;
  
  signal(SIGUSR1, sighandler);
  signal(SIGUSR2, sighandler);
  signal(SIGINT, sighandler);

  printf("HELLO WELCOME TO TERMINAL\tPID#\tNUM\n");
  while(10) {
    printf("HELLO WELCOME TO TERMINAL\t%d\t%d\n", getpid(), i);
    i++;  
    sleep(1);
  }
  return 0;
}
