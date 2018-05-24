#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  
  char input[256];
  char *s1[256];
  //char *s2;
  
  printf("What would you like to do?\n");
  fgets(input, sizeof(input), stdin);
  printf("input: %s\n", input);
  
  input[strlen(input) - 1] = 0;

  char *s2 = input;
  
  printf("input: %s\n", input);
  s1[0] = strsep(&s2, " "); //parse
  printf("s1[0]: %s\n", s1[0]);
  s1[1] = strsep(&s2, " ");
  printf("s1[1]: %s\n", s1[1]);
  s1[2] = 0;
  
  execvp(input, s1);
  
  return 0;
}
