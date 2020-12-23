/*
    **CLIENT SIDE**

Name: Marco Aguilera

Class: Computer Networking 3550

COMPILATION RULES:

    1.   touch client.c
    2.   make
    3.   ./client cse02.cse.unt.edu <PORT NUMBER>
    4.   ****PLAY WITH THE WORDS****
    5.   Type "quit" when you want to end the program.



*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {

    /* Make sure a port was specified. */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    int portNUM = atoi(argv[1]);
    //printf("numnum: %d\n", portNUM );

    int sockfd;
    struct sockaddr_in servaddr; //Transporting the address
    char message[2000] = {'\0'}, serverMessage[2000]= {'\0'}; //size message for the client & server

    char wordCount[30] = {'\0'}; int netClientNum; int alphaNetNum; int numOFalpha; int netNUMvowels;

    sockfd=socket(AF_INET, SOCK_STREAM, 0); //stream socket with the TCP protocol providing the underlying communication
    bzero(&servaddr,sizeof(servaddr));

    if(sockfd == -1){printf("Could not create socket");} //message incase the socket failed
    puts("Socket Successful"); //Delete later (for checking to see if connected)

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(portNUM); // Server port number

    inet_pton(AF_INET,"129.120.151.94",&(servaddr.sin_addr));

    //Connect to remote server
	if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("Connection Failed. Try Again"); //Incase the server never connected
        return 1;
    }
    puts("Server Connected\n"); //Delete Later (for checking to see if connected)

    while(1){

        // memset (serverMessage,'\0',sizeof(serverMessage)); //clearing the char string that sends to the server
        // memset (message,'\0',sizeof(message));
        bzero(message, sizeof(message));
        bzero(serverMessage, sizeof(serverMessage));

        printf("\nInput: ");
        // gets(message);
         fgets(message, 2000, stdin);

         // if(strcmp(message, "quit") == 1)
         // {
         // puts("CYA!");
         // break;
         // }
         if(message[0]=='q' && message[1]=='u' && message[2]=='i' && message[3]=='t')
         {
              puts("CYA!");
             break;
         }

        if( send(sockfd , message , strlen(message) , 0) < 0)
		{
			puts("Send failed"); //Failed message incase nothing sent
			return 1;
		}

        if(recv(sockfd , serverMessage , sizeof(serverMessage) , 0) < 0)
		{
			puts("Recieveing failed");
			break;
		}

        //strcpy(wordCount, WordParse(serverMessage));

        char * token = strtok(serverMessage,"#");
        int count = 0;
        printf("============================");
        while( token != NULL ) {
            if(count == 0){printf("\nOutput: ");}
            if(count == 1){printf("Words: ");}
            if(count == 2){printf("\nAlphabet: ");}
            if(count == 3){printf("\nVowels: ");}
             printf( " %s\n", token ); //printing each token
             token = strtok(NULL, "#");
             count++;
          }
          printf("============================");
         //printf("what is this: %s\n", token);





    }

    close(sockfd);
    return 0;
}
