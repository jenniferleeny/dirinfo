#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  /* 
  if ((dir = opendir (path)) != NULL) {
   //print all the files and directories within directory 
    while ((ent = readdir (dir)) != NULL) {
      printf ("%s\n", ent->d_name);
    }
    closedir (dir);
  } else {
  // could not open directory
    perror ("");
    return EXIT_FAILURE;

*/

  char *name = (char *)malloc(256);
  if (argc > 1){
    name = argv[1];
  }
  else {
    name = ".";
  }

  printf("Statistics for directory:\n");

  DIR *dir = opendir(name);
  struct stat sb;
  struct dirent *files = readdir(dir);
  int size = 0;

  if ((dir = opendir(name)) != NULL) { 
    //print all the files within directory
    char *filepath = (char *)malloc(512);
    while (files){
      filepath = "./";
      if (files->d_type == 4 | !files->d_type){
	printf("Directory Name: %s\n",files->d_name);
      }
      if (files->d_type == 8){
	stat(files->d_name,&sb);
	printf("File Name: %s\n",files->d_name);
	size += sb.st_size;
      }
      files = readdir(dir);
    }
    //print size
    printf("The size of the directory: %d bytes\n", size);
  }
  else {
    perror ("");
    return EXIT_FAILURE;      
  }
  closedir(dir);
  return 0;
}
