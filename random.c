#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int random_pop() {
  int randomread = open("/dev/random", O_RDONLY);
  //srand(time(NULL));                                                                                                                              
  if (randomread == -1) {
    printf("error in populating: %s\n", strerror(errno));
    return -1;
  }
  else {
    int i;
    read(randomread, &i, 4);
    close(randomread);
    return i;
  }
}


int main() {
  int array[10];
  printf("Generating random numbers:\n");
  int i;
  for (i = 0; i < 10; i++) {
    array[i] = random_pop();
    printf("index %d = %d\n", i, array[i]);
  }

  printf("\n");
  printf("Creating a file:\n");
  int fd1;
  fd1 = creat("fd", 0644);
  if (fd1 == -1)
    printf("error %d: %s\n", errno, strerror(errno));
  else
    printf("File created. fd1 = %d\n", fd1);

  printf("\n");
  printf("Write to a file:\n");
  int fd2;
  fd2 = write(fd1, array, 40);
  if (fd2 == -1)
    printf("error %d: %s\n", errno, strerror(errno));
  else
    printf("File written to. fd2 = %d\n", fd2);

  printf("\n");
  printf("Reading a file:\n");
  int fd3;
  int array2[10];

  fd3 = open("fd", O_RDONLY);

  read(fd3, array2, 40);
  int close_now = close(fd3);
  if (close_now == -1)
    printf("error %d: %s\n", errno, strerror(errno));

  int j;
  for (j = 0; j < 10;j++)
    printf("index %d = %d\n", j, array2[j]);

  }

