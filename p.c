/* A simple server in the internet domain using TCP
The port number is passed as an argument 


 To compile: gcc server.c -o server 
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






void * response(void  * client_info);

char * DIRECTORY;

void * response(void   * client_info){
	printf("\nhere111\n");
	int * client_in= (int *)client_info;
		printf("\nhere111\n");
	int x = 0; 
	char *str;	
	char *file_read;
	char *requested ;
	FILE *html_data ;
	int rcvd; 
	char send_buf[1024];
	int fd;
	int size;
	int bytes_read;
	char data_to_send[1024];
	// int BYTES=1024;
	char temp_file[1024];
	char buffer[1024];
	int n;
	printf("\nhere1\n");
	// bzero(buffer, 256);
	printf("\n%d\n",n);
	n = (recv(*client_in, buffer,sizeof(buffer),0));

	printf("\n%d\n",n);
	if(strncmp(buffer,"GET ",4)!=0){
		send(*client_in,"Invalid request",16,0);
		exit(errno);
	}
	else
{

		
	str = strtok(buffer, " ");
    x = 1;
	
	while (str != NULL){

	    //printf ("%s\n",str);
	    if(x == 1){
	    	str = strtok (NULL, " ");
	    	printf("\nstr====%s\n",str);
	    	  	printf("\ndir====%s\n",DIRECTORY);
	    	strcpy(temp_file,DIRECTORY);
	    	strcat(temp_file,str);
	    	printf("\nsize of tem file = %lu and file = %s\n",sizeof(temp_file),temp_file );
	    	requested=malloc(sizeof(temp_file));
	    	strcpy(requested,temp_file);
	    	  printf("\nstr_req====%s\n",requested);
	    	break;
		}
	  }
 	 printf("\nfile name reuqwested=== %s\n",requested);

  

  	if((html_data = fopen(requested, "r")) != NULL){
  		printf("file exists %s\n", requested);
  		if(strstr(requested,".html")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/html\n\n");
  		}
  		if(strstr(requested,".css")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/css\n\n");
  		}
  		if(strstr(requested,".jpeg")||strstr(requested,".jpg")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: image/jpeg\n\n");
  		}
  		if(strstr(requested,".js")){
  				sprintf(send_buf,"HTTP/1.0 200 OK\nContent-Type: text/javascript\n\n");
  		}

  		
  		/*read(file_read,8000,1,html_data);
  		write(*client_in, file_read,8000);*/
  		
  		fseek(html_data, 0L, SEEK_END); // seek to end of file
		size = ftell(html_data); // get current file pointer
		fseek(html_data, 0L, SEEK_SET); // seek back to beginning of file
		printf("size of file resd is %d \n",size );
  		file_read = (char *)(malloc(size+1));
  		fread(file_read,size,1,html_data);
  		file_read[size]='\0';
		write (*client_in,file_read, size);

		free(file_read);
		fclose(html_data);
  		
  	}
  	else{
  		send(*client_in,"HTTP/1.1 404 Not Found\n\n",24,0);
  	}

	}
	close(*client_in);
	fflush(stdout);
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	printf("\ndfrg\n");
	int sockfd, newsockfd, portno;// clilen;
	int clients[1000];
	char buffer[256];
	struct sockaddr_in serv_addr;
	
	int n;
	


	pthread_t threads[100];
	DIRECTORY=getenv("PWD");
	int x; 
	int j;
	int read_data;
	char *str;

	int thread_count = 0;
	printf("wefrgt");
	//char *requested[3];
	char *requested ;

 
	 /* Create TCP socket */
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		perror("ERROR opening socket");
		exit(1);
	}

	portno = atoi(argv[1]);

	printf("%d\n",portno);
	printf("\n%s\n",argv[2]);
	strcpy(DIRECTORY, argv[2]);

	
	// if(strcpy(DIRECTORY, (argv[2])) == NULL){
	// 	perror("Not file DIRECTORY provided");
	// }
	// else{

	// 	printf("\n file name :%s\n", DIRECTORY);
	// 	//read_data = recv()
	// }
	


	bzero((char *) &serv_addr, sizeof(serv_addr));

	
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
	
	/* Listen on socket - means we're ready to accept connections - 
	 incoming connection requests will be queued */
	while(thread_count<100){
		if(listen(sockfd,5)!=0){
			return (errno);
		}

	

	
		clients[thread_count] = accept(	sockfd, NULL,NULL);
		printf("thread_count is %d \n", thread_count);
			if (clients[thread_count] < 0) 
		{
			perror("ERROR on accept");
			exit(1);
		}
		else{
		
			
				// printf("\n buffer = %s\n",buffer );
				printf("ok");
				pthread_create(&threads[thread_count],NULL,response,&clients[thread_count]);
				thread_count++;
				thread_count++;
				// response(buffer, clients[thread_count], DIRECTORY);
			
			//printf("Here is the message:\n%s\n",buffer);

		}
		
	}
	return 0; 
}

