/* client.c using TCP */

/* Client for connecting to Internet stream server waiting on port 1040 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#define port "1040"	 /* socket file name */
#define BLOCK_SIZE 1024

/* 
The first 4 bytes (in network byte order) will contain
the number of bytes in the file to follow. Use functions 
like htonl, ntohl, htons, and ntohs to achieve appropriate
byte order conversion. The next 20 bytes will contain the name of the file
*/

/* client program called with host name where server is run */
main(int argc, char *argv[])
{
	int sock;										 /* initial socket descriptor */
	int	rval;										/* returned value from a read */
	struct sockaddr_in sin_addr; /* structure for socket name 
																 * setup */
	char buf[1024];		 /* message to set to server */
	bzero(buf,1024);
	struct hostent *hp;

	FILE *fin = fopen( argv[2], "r" );
	if (!fin) {
		printf("the first file is invalid\n");
		exit(-1);
	}

	if(argc < 2) {
		printf("usage: cli remote_host\n");
		exit(1);
	}
	
	/* initialize socket connection in unix domain */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error openting datagram socket");
		exit(1);
	}

	hp = gethostbyname(argv[1]);
	if(hp == 0) {
		fprintf(stderr, "%s: unknown host\n", argv[1]);
		exit(2);
	}

	/* construct name of socket to send to */
	bcopy((void *)hp->h_addr, (void *)&sin_addr.sin_addr, hp->h_length);
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(atoi(port)); /* fixed by adding htons() */
	
	/* establish connection with server */
	if(connect(sock, (struct sockaddr *)&sin_addr, sizeof(struct sockaddr_in)) < 0) {
		close(sock);
		perror("error connecting stream socket");
		exit(1);
	}
	int count = 1;
	fseek(fin, 0L, SEEK_END);
	int sz = ftell(fin);
	fseek(fin, 0L, SEEK_SET);
	int size;

	// wtire file size
	memcpy(buf, sz, sizeof(sz));
	if(write(sock, buf, sizeof(sz)) < 0) {
		perror("error writing on stream socket");
		exit(1);
	}

	// write filename
	memcpy(buf, argv[2], sizeof(argv[2]));
	if(write(sock, buf, sizeof(argv[2])) < 0) {
		perror("error writing on stream socket");
		exit(1);
	}

	while( !feof( fin ))
	{
		/* write buf to sock */
		size = fread(buf, BLOCK_SIZE, 1, fin);
		printf("size %d\n", size);
		if(write(sock, buf, BLOCK_SIZE) < 0) {
			perror("error writing on stream socket");
			exit(1);
		}
		printf("Client sent %d part", count++);	
	}

	if(read(sock, buf, BLOCK_SIZE) < 0) {
		perror("error reading on stream socket");
		exit(1);
	}
	printf("Client receives: %s\n", buf);

}
