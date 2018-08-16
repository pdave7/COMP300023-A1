/*
Name : Parnak.Niranjan.Dave
Login ID: pdave

Simple HTTP server designed to handle multiple client requests to serve

	*HTML FILES
	*MIME FILES

The structure of starting the server has been borrowed from the server.c provided in labs. 	
*/


#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define total_threads 100
#define buffer_size 2048
#define max_clients 999
#define max_connections 100
#define max_args 3




void * response(void  * client_info);
char * DIRECTORY;


int main(int argc, char **argv)
{
	int sockfd, portno;
	int clients[max_clients];
	struct sockaddr_in serv_addr;
	int thread_join = 0;;
	

	pthread_t threads[100];
	DIRECTORY=getenv("PWD");

	int thread_count = 0;

 
	 /* Create TCP socket */
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}

	
	if(argc != max_args){
		printf("\nNot enough arguments passed to start the server\n");
	}

	else{
		portno = atoi(argv[1]);	
		strcpy(DIRECTORY, argv[2]);
	}


	
	/* Create address we're going to listen on (given port number)
	 - converted to network byte order & any IP address for 
	 this machine */
	memset(&serv_addr.sin_zero,0,sizeof(serv_addr.sin_zero));
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
	
	/* Here we can accpet the incoming connection 
	to accept the client requests on multiple threads */
	while(thread_count<total_threads){
		if(listen(sockfd,max_connections)!=0){
			return (errno);
		}
			clients[thread_count] = accept(	sockfd, NULL,NULL);
			if (clients[thread_count] < 0) 
		{
			perror("ERROR on accept");
			exit(1);
		}
		else{
		
			pthread_create(&threads[thread_count],NULL,response,&clients[thread_count]);
			thread_count++;

		}
		
	}
/*Join the threads in order to receieve multiple request from the client*/
	while (thread_join < total_threads){
		pthread_join(threads[thread_join],NULL);
	}
	return 0; 
}

void * response(void   * client_info){
	int * client_in= (int *)client_info;
	int x = 0; 
	char *str;	
	char *file_read;
	char *requested;
	FILE *html_data;
	int recieved; 
	char send_buf[buffer_size];
	int size;
	char temp_file[buffer_size];
	char buffer[buffer_size];

	recieved = (recv(*client_in, buffer,sizeof(buffer),0));

/*Check if the client sent any data, and if it did send it to buffer*/
	if(recieved < 0){
		printf("error on recieving data from client\n");
	}

	if(strncmp(buffer,"GET ",4)!=0){
		send(*client_in,"Invalid request",16,0);
		exit(errno);
	}
	else{

/*simple string manipulation to fetch the 
second part of the get request and join to the direcgtory path */
		
	str = strtok(buffer, " ");
    x = 1;
	
	while (str != NULL){
/*If the string is the second on break the loop 
as all get requests come in the same format */
	    if(x == 1){
	    	str = strtok (NULL, " ");
	    	strcpy(temp_file,DIRECTORY);
	    	strcat(temp_file,str);
	    	requested=malloc(sizeof(temp_file));
	    	strcpy(requested,temp_file);
	    	break;
		}
	  }

  
/*Check for the MIME type that comes in to check on what files to send to the client*/
  	if((html_data = fopen(requested, "r")) != NULL){
  		if(strstr(requested,".html")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/html\n\n");
  		}
  		if(strstr(requested,".css")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/css\n\r\n");
  		}
  		if(strstr(requested,".jpeg")||strstr(requested,".jpg")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: image/jpeg\n\r\n");
  		}
  		if(strstr(requested,".js")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/javascript\n\r\n");
  		}
  		
  		/*Getting the size of the file that needs to be sent to the client*/
  		fseek(html_data, 0, SEEK_END); 
		size = ftell(html_data); 
		fseek(html_data, 0, SEEK_SET); 
  		file_read = (char *)(malloc(size+1));
  		send(*client_in, send_buf, strlen(send_buf),0);
  		if(fread(file_read,size,1,html_data) == 0){
  			printf("error in reading the file date\n");
  		}
  		file_read[size]='\0';
		if(write (*client_in,file_read, size) == 0){
			printf("error in writing to the client\n");
		}

		free(file_read);
		fclose(html_data);
  		
  	}
  	else{/*Send the data that no such file exists*/
  		send(*client_in,"HTTP/1.1 404 Not Found\n\n",24,0);
  	}

}
	close(*client_in);
	fflush(stdout);
	pthread_exit(NULL);

}


