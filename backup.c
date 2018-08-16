/* A simple server in the internet domain using TCP
The port number is passed as an argument 


 To compile: gcc server.c -o server 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

void *accept_clients(void *args);




int main(int argc, char **argv)
{
	int sockfd, newsockfd, portno;// clilen;
	int clients[1000];
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	int n;
	FILE *html_data = NULL;
	char directory[256];
	pthread_t threads[10];
	size_t i = 0; 
	int x; 
	int j;
	int read_data;
	char *str;
	char *test = "test/index.html";
	FILE *html_data_test = NULL;
	int slot = 0;

	//char *requested[3];
	char *requested = NULL;

 
	 /* Create TCP socket */
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}

	if(strcpy(directory, (argv[2])) == NULL){
		perror("Not file directory provided");
	}
	else{
		printf("\n file name :%s\n", directory);
		//read_data = recv()
	}
	


	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	printf("%d\n",portno);

	
	/* Create address we're going to listen on (given port number)
	 - converted to network byte order & any IP address for 
	 this machine */
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);  // store in machine-neutral format

	 /* Bind address to the socket */
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0) 
	{
		perror("ERROR on binding");
		exit(1);
	}
	
	/* Listen on socket - means we're ready to accept connections - 
	 incoming connection requests will be queued */
	
	/*listen(sockfd,5);

	while(1){

		clilen = sizeof(cli_addr);
		clients[slot] = accept(	sockfd, (struct sockaddr *) &cli_addr, 
						&clilen);
			if (clients[slot] < 0) 
		{
			perror("ERROR on accept");
			exit(1);
		}
		else{
			bzero(buffer, 256);
			n = read(clients[slot], buffer,255);
			if(n < 0){
				perror("ERROR reading from socket");
				exit(1);
			}
		}

	}*/
	listen(sockfd,5);
	
	clilen = sizeof(cli_addr);

	 /*Accept a connection - block until a connection is ready to
	 be accepted. Get back a new file descriptor to communicate on. */

	newsockfd = accept(	sockfd, (struct sockaddr *) &cli_addr, 
						&clilen);


	if (newsockfd < 0) 
	{
		perror("ERROR on accept");
		exit(1);
	}
	
	bzero(buffer,256);

	/*Read characters from the connection,
		then process */
	
	n = read(newsockfd,buffer,255);

	if (n < 0) 
	{
		perror("ERROR reading from socket");
		exit(1);
	}


	
	printf("Here is the message: %s\n",buffer);

  
    str = strtok (buffer, " ");
    x = 1;
	while (str != NULL)
  {

    //printf ("%s\n",str);
    if(x == 1){
    	str = strtok (NULL, " ");
    	//printf("%s\n",str);
    	requested = strcat(directory, str);
    	break;
	}
  }
  printf("%s\n",requested);

  

  if(html_data = fopen(requested, "r") != NULL){
  	printf("file exists\n");
  }
  else{
  	printf("no such file\n");
  }

  




	//strtok(buffer, "\n");

	//printf("%s\n",buffer);

	/*strcpy(str,strtok(buffer, " "));
	printf("\n %s \n",buffer);
	printf("str : %s\n",str);
*/


	n = write(newsockfd,"I got your message",18);
	
	if (n < 0) 
	{
		perror("ERROR writing to socket");
		exit(1);
	}

	/*while(i < 10){
		pthread_create(&threads[i], NULL, accept_clients, NULL);
		i++;
	}
	while(j < 10){
		printf("here\n");
		pthread_join(threads[j], NULL);
		j++;	
	}*/

	
	//newsockfd[thread_count] = accept(sockfd, NULL, NULL);//accept gives the new socket file descriptor for new clinet connected.
	printf(stderr, 'Hello world');
	
	return 0; 
}

/*void *accept_clients(void *args){

	printf("thread created\n");

}

connfd[thread_count] = accept(sfd, NULL, NULL);//accept gives the new socket file descriptor for new clinet connected.

    if (connfd[thread_count] < 0) {
      perror("Accept Error");
      return (errno);
    }*.

    pthread_create(&threads[thread_count], NULL, connection, &connfd[thread_count]);		//create a thread and receive data
    pthread_join(threads[thread_count], NULL);												//join the finished thread and continue
    thread_count++;


    if (newsockfd[i] < 0) {
      perror("Accept Error");
      return (errno);
    }

    while( i < 10){
    
    pthread_create(&threads[i], NULL, accept_clients, NULL);	
   	//create a thread and receive data
    i++;
}


	while(j < 10){
		pthread_join(threads[i], NULL);
		j++;
	}
	
	/* close socket *
	close(sockfd);
  }*/