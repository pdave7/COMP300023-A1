#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <fcntl.h> // for open
#include <unistd.h> // for close

int main(int argc, char const *argv[])
{
	
	char response_data[1024];

	fgets(response_data, 1024,  html_files);

	char http_header[2048] = "HTTP/1.1/ 200  OK\r\n\n";
	strcat(http_header, response_data); 

	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the address
	struct sockaddr_in server_address; 
	server_address.sin_family = AF_INET; 
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	while(1){
			client_socket = accept(server_socket, NULL,NULL);
			send(client_socket, http_header, sizeof(http_header),0);
			close(client_socket);
}

	// open a file to serve
	FILE *html_data = NULL;
	//html_data =  fopen("/files/index.html", "r");
	
	int Port_number = 0; 
	char directory[100];

    if (argc == 3 ){
    	Port_number = atoi(argv[1]);
    	strcpy(directory, (argv[2]));
    	//directory = argv[3];
    	if((html_data = fopen(directory, "r")) != NULL){
    		printf("File exists \n");
    		printf("%d\n", Port_number);
    		printf("%s\n",directory);
    	}
   		else{
			printf("Not here\n");
			printf("%s\n",directory);
			printf("%d\n",Port_number);
    	}
	}
  
	return 0;
}
  
	/*char response_data[1024];
	fgets(response_data, 1024, html_data);

	char http_header[2048] = "HTTP/1.1 200 OK \n\n\n";
	strcat(http_header, response_data);
	

	if(argc == 3){

		Port_number = atoi((argv[1]));
		strcpy(directory,argv[2]);
	}


	printf("%d\n", Port_number);
	printf("%s\n", directory);

	// create a socket 
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(Port_number);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	while(1) {
		client_socket = accept(server_socket, NULL, NULL);
		send(client_socket, http_header, sizeof(http_header), 0);
		close(client_socket);

	*/

