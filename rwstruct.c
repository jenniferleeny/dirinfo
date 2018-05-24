//I could not complete the assignment due to college apps. Please give me another day to complete
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

typedef struct {
  int n;
  char string[50];
} rwstruct;

rwstruct create_rwstruct(char name[], int pwsd) {
  rwstruct rw1;
  rw1.n = pwsd;
  strncpy(rw1.string, name, sizeof(rw1.string));
  //rw1.string = name;                                                                                                                                     
  return rw1;
}

void write_to(rwstruct *person, char filename[]) {
  int op = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  int file2 = write(op, person, sizeof(person));
  if (file2 == -1)
    printf("error %d: %s\n", errno, strerror(errno));
  else
    printf("File written to. file2 = %d\n", file2);
  
  close(file2);
  
}

void main() {
  printf("Creating 10 instances to a file:\n");

  rwstruct users[10];
  users[1] = create_rwstruct("jennifer lee", 1);
  users[2] = create_rwstruct("Bob", 64);
  users[3] = create_rwstruct("Beyonce", 50);
  users[4] = create_rwstruct("Hello everyone", 10);
  users[5] = create_rwstruct("Nicole Ng", 52);
  users[6] = create_rwstruct("Vicki Chen", 13);
  users[7] = create_rwstruct("James Chin", 25);
  users[8] = create_rwstruct("Aritri Dutta", 91);
  users[9] = create_rwstruct("Ian McDowall", 10);
  users[0] = create_rwstruct("Pie", 41);

   printf("Writing these variables to a file:\n");
  int file = creat("file", 0644);
  if (file == -1)
    printf("error %d: %s\n", errno, strerror(errno));
  else
    printf("File created. file = %d\n", file);

  write_to(users, "file");
  /*
  int i;
  int file2;
  for (i = 0; i < 10; i++) {                                                                                                                             
    file2 = write(file, users, sizeof(users[i]));
    if (file2 == -1)
      printf("error %d: %s\n", errno, strerror(errno));
    else
      printf("File written to. file2 = %d\n", file2);
  }                                                                                                                                                   
  close(file2);
  */
  printf("\n");
  printf("Read from a file:\n");
  rwstruct rw3[10];
  int op = open("file", O_RDONLY);
  
  read(op, rw3, 10*sizeof(users[0]));
    int close_now = close(op);
    if (close_now == -1)
      printf("error %d: %s\n", errno, strerror(errno));

    int j;
    for (j = 0; j < 10;j++)
      printf("index %d: name = %s, pswd = %d\n", j, rw3[j].string, rw3[j].n);
}
