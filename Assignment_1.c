#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



/*Structure for sockaddr_in 
struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
};
*/

void error(char *msg){
	perror(msg);
	exit(1);
}


int main(int argc, char const *argv[])
{
	/*Sockfd and newsockfd are file descriptors where these two store the values returned by the socket system call and the accpet system call*/
	/*portno stores the port number on which the server accpets connections*/
	/*clilen stores the size of the address of the client. This is needed for the accpet system call*/
	/*n is the return calue for the read and write calls, which contains the no of chars read or written*/

	int sockfd, newsockfd, portno, clilen, n;

	/*server reads characters from the socket connection into this buffer*/

	char buffer[256]

	/*sockaddr_in contains internet address. Structure is defined in netinet/in.h. serv_addr will contain address of the server and cli_addr will contain address of the client server*/
	struct sockaddr_in serv_addr, cli_addr

	if(argc < 2){
		fprintf(stderr, "ERROR, no port provided\n");/*Error message if the user fails to pass in the port number*/
		exit(1);
	}

	/*socket() system call createssa new socket.First arg is the address domain of the socket, second argument is the type of the socket. The streams can be sent as characters in continuous stream or chunks;  SOCKSTREAM OR SOCKDGRAM. Third argument is protocol, if argument is zero the OS will choose the appropriate protocol. TCP for stream socket and UDP for datagram sockets. */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		error("ERROR opening socket");
	}
	/*bzero sets all values in a buffer to zero, it takes two args where first is pointer to the biuffer and the second is the size of the buffer*/
	bzero((char*) &serv_addr, sizeof(serv_addr));

	/*portno that server will listen for connections will be passsed in as an argument and this statement uses atoi to convert this from string of digit to integer*/
	portno = atoi(argv[1]);

	/*variable serv_addr is a structure of type struct sockaddr_in. the structure has hour fields, where the first field is short sin_family, which contains a code for the address family. It should always be set to the symbolic constant AF_INET.*/
	serv_addr.sin_family = AF_INET; 

	/*The second field of serv_addr is unsigned short sin_port, which contains port number*/
	serv_addr.sin_port = htons(portno);
	/*The third field is a structure of type struct in_addr which contains only a single field unsigned long s_addr which contains the IP address of the host. For server code this will the IP address of the machine on which the server is running.
	*/
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	/* the bind system calls binds a soncket to an address, in this case the address of the current host and port number on which the server will run. It takes three arguments; socket file descriptor, address to which is bound and the size of the
	 address to which it is bound. The second argument is a pointer to a structure of type sockaddr, but what is passed in is a structure of type sockaddr_in and so must be casted correctly. It can fail if the socket is already in use
	 */
	if(bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr)){
		error("Error on binding");
	}

	listen(sockfd,5);

	clilen = sizeof(cli_addr);
	newsockfd = accpet(sockfd, (Struct sockaddr*)&cli_addr, &clilen);
	if(newsockfd < 0){
		error("Error on accept");
	}
	/* */

	bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);

	 
	 n = write(newsockfd,"I got your message",18);

	 return 0;
	


