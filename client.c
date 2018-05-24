#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int client_handshake(int *msg) {
  int to_server;
  char output[100];

  sprintf(output, "%d\n", getpid()); //takes getpid into buffer
  mkfifo(output, 0644);

  to_server = open("WKP", O_WRONLY);
  write(to_server, output, sizeof(output));

  *msg = open(output, O_RDONLY); // when this returns a value, we know the server has connected to the pipe
  remove(output); //removes named pipe so connection can't get high-jacked
  read(*msg, output, sizeof(output));
  printf("<client> connection established: [%s]\n", output);

  return to_server;
}


int main() {
  int to_server, from_server;
  char buffer[100];
  
  to_server = client_handshake(&from_server);
  while (1) {
    printf("<client> Please enter something:\n");
    fgets(buffer, sizeof(buffer), stdin);
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer,sizeof(buffer) );
    printf("<client> received: [%s]\n", buffer);
  }
  close (to_server);
  close(from_server);
  return 0;
}
