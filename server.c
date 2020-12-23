/*
    **SERVER SIDE**

Name: Marco Aguilera

Class: Computer Networking 3550

COMPILATION RULES:

    1.   touch server.c
    2.   make
    3.   ./server cse01.cse.unt.edu <PORT NUMBER>
    4.   ****HEAD TO THE CLIENT SIDE****

*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


/*
Funtion that will take
a string in and Capatilize the
first letter of each word in a sentence
*/
char * CapFirstLetter(char * clientString){
    int i;
    for(i=0; clientString[i]!='\0'; i++) /* Going through the whole string that the client entered */
	{
		if(i==0) //starting with the first letter and then coming back after skipping spaces
		{
			if((clientString[i]>='a' && clientString[i]<='z'))
				clientString[i]=clientString[i]-32; //subtract 32 to make it capital
			continue; //continue to the same iteration
		}
		if(clientString[i]==' ')//Only will make a stop here when a space is found
		{
			++i;
			//after the space we will check the next character that will need to become capatilized
			if(clientString[i]>='a' && clientString[i]<='z')
			{
				clientString[i]=clientString[i]-32; //subtract 32 to make it capital
				continue;
			}
		}
	}
    return clientString;
}

int NumberOfWords(char * clientString){

    int somenumber; int count; int j;
    count = 0;

    for(j=0; clientString[j]!='\0'; j++) /* Going through the whole string that the client entered */
    {
        if(clientString[j]==' ')//Only will make a stop here when a space is found
        { ++count; }
    }
    int addone = count + 1;
    // printf("Word Count is ::: %d\n", addone );

    //somenumber = htonl(addone);

    return addone;
}

 int AlphabetCount(char * clientString){
    int len = 0; int countCHAR = 0; int alphanum = 0;

    len = strlen(clientString);
    for( int i = 0; i < len; i++){
        if(clientString[i] >= 'a' && clientString[i] <= 'z' || clientString[i] >= 'A' && clientString[i] <= 'Z'){
            countCHAR++;
        }
    }
     alphanum = countCHAR;
     //printf("Alpha Number: %d\n", alphanum );
     return alphanum;
 }

 int Vowels(char * clientString){
     int len = 0; int countVOWEL = 0; int vowelNum = 0;

     len = strlen(clientString);
     for( int i = 0; i < len; i++){
         if(clientString[i] == 'a' || clientString[i] == 'A' || clientString[i] == 'e' || clientString[i] == 'E' || clientString[i] == 'i' || clientString[i] == 'I' || clientString[i] == 'o' || clientString[i] == 'O' || clientString[i] == 'u' || clientString[i] == 'U'){
             countVOWEL++;
         }
     }
      vowelNum = countVOWEL;
     // printf("Alpha Number: %d\n", vowelNum );
      return vowelNum;
 }

int main(int argc , char *argv[])
{

    /* Make sure a port was specified. */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    int portNUM = atoi(argv[1]);
    //printf("numnum: %d\n", portNUM );

    char clientMessage[2000] = {'\0'};
    int listen_fd, conn_fd, c, read_size;
    struct sockaddr_in servaddr, client;
    int j; int count;
    int netNUM; int netNUMalpha; int netVowels;
    char Warr[100] = {'\0'};
    char Aarr[100] = {'\0'};
    char Varr[100] = {'\0'};


    //Creating Socket
    listen_fd = socket(AF_INET , SOCK_STREAM , 0);
    if(listen_fd == -1){ printf("Could not create socket"); } //later remove
    puts("Socket Successful"); //later remove only for connecting

    bzero(&servaddr, sizeof(servaddr)); //not sure what this does

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(portNUM);

    //Binding
    if( bind(listen_fd,(struct sockaddr *)&servaddr , sizeof(servaddr)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("Bind Successful");

    //listening for incoming traffic
    listen(listen_fd, 10);


    puts("Waiting for incoming connections..."); //later remove (only for checking if we are listening)
	// c = sizeof(struct sockaddr_in);

    //accepting connection from incoming client
    conn_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    if (conn_fd < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");

    //Receive a message from client
	// while( (read_size = recv(conn_fd , clientMessage , 2000 , 0)) > 0 )
    while(1)
	{
        bzero(clientMessage, sizeof(clientMessage));

        if(read_size = recv(conn_fd , clientMessage , 2000 , 0) > 0)
        {
                //netNUM = 0; netNUMalpha = 0; len = 0;
                puts("Checking Client Message: ");
                puts(clientMessage);

                strcpy(clientMessage,CapFirstLetter(clientMessage)); //uses the function as the source and clientmessage as the destination
                // puts("(AFTER STR CPY)Checking Client Message: ");
                // puts(clientMessage);

                netNUM = NumberOfWords(clientMessage); //finds the number of words
                // puts("(AFTER NUMBER OF WRDS:  ");
                // printf("%d\n", netNUM);
                sprintf(Warr, "#%d",netNUM);

                netNUMalpha = AlphabetCount(clientMessage);    /* Alphabets */
                // puts("(AFTER NUMBER OF APLPHA:  ");
                // printf("%d\n", netNUMalpha);
                sprintf(Aarr, "#%d",netNUMalpha);

                netVowels = Vowels(clientMessage);
                // puts("(AFTER NUMBER OF VOWELS: ");
                // printf("%d\n", netVowels);
                sprintf(Varr,"#%d" ,netVowels);

                strcat(clientMessage,Warr);
                strcat(clientMessage,Aarr);
                strcat(clientMessage,Varr);
                //printf("Concatinated String: %s\n", clientMessage );



        	   send(conn_fd , clientMessage , strlen(clientMessage),0); //Send the message back to client
               puts("clientMessage SENT");
               // sleep(1);

               // send(conn_fd, (const char*)&netNUM, 4 ,0);
               // puts("numWORDs SENT");
               // sleep(1);
               //
               // send(conn_fd, (const char*)&netNUMalpha, 4 ,0);
               // puts("APLPHA SENT");
               // sleep(1);
               //
               // send(conn_fd, (const char*)&netVowels, 4 ,0);
               // puts("vowels SENT");
               // sleep(1);

       }
       // memset (clientMessage,'\0',sizeof(clientMessage)); // clearing the message sent back to the client ready for the next word


    }

    if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

    return 0;
}
