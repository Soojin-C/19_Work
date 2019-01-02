#include "pipe_networking.h"

static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove("main");
        printf("Removed main\n");
        exit(0);
    }
}

int main() {
  signal(SIGINT, sighandler);

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

//  while(1){
    char input[BUFFER_SIZE] = "message recieved";
    char output[BUFFER_SIZE];

    int reading = read(from_client, output, BUFFER_SIZE);
    printf("%c", output[0]);

    int counter = 0;
    while (counter < strlen(output)){

      char curr = output[counter];
      if(!strcmp(&curr, "\n")){
        output[counter] = 0;
        //printf("%s\n", output);
      }

      output[counter] = curr + 3;
      counter ++;

    }
    printf("output: %s\n", output);

    int writing = write(to_client, output, BUFFER_SIZE);

    close(to_client);
    close(from_client);
  //}
}
