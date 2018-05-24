#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int server_handshake(int *msg) {
  int to_client;
  char input[100];

  mkfifo("WKP", 0644);  
  *msg = open("WKP", O_RDONLY);
  remove("WKP");

  read(*msg, input, sizeof(input));
  
  to_client = open(input, O_WRONLY);
  strncpy(input, "Well Known Pipe... We Kan Party? ;)\n", sizeof(input));
  write(to_client, input, sizeof(input));
  return to_client;
}

void process(char *line) {
  while (*line) {
    *line = (*line - 'a' + 13)%26 + 'a';
    printf("This is what the processed message looks like: %c\n", *line);
  }
}

int main() {
  int to_client, from_client;
  char buffer[100];
  
  printf("waiting for a connection...");
  to_client = server_handshake(&from_client);//returns file descriptor of pipe?
  printf("return value of server_handshake: %d\n", to_client);
  while(1) {
    printf("<server> received [%s]\n", buffer);
    read(from_client, buffer, sizeof(buffer));
    process(buffer);
    write (to_client, buffer, sizeof(buffer));
    strncpy(buffer, "", sizeof(buffer));
  }
  close(to_client);
  close(from_client);
  return 0;

}
