#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	
	char buffer[256] = "GET /hello.txt HTTP/1.1User-Agent: Wget/1.19.4 (darwin17.3.0)Accept: Accept-Encoding: identityHost: 127.0.0.1:3035 Connection: Keep-Alive";
	char *str = strtok(buffer, " ");

	printf("%s\n",str);


	return 0;
}