/* server.c using TCP */

/* Server for accepting an Internet stream connection on port 1040 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


#define port "1040"	 /* socket file name */

/* server program called with no argument */
main(void)
{
	int sock;			/* initial socket descriptor */
	int msgsock;		/* accepted socket descriptor,
						 * each client connection has a
						 * unique socket descriptor*/
	int rval=1;		 	/* returned value from a read */	
	struct sockaddr_in sin_addr; /* structure for socket name setup */
	char buf[1024];							 /* buffer for holding read data */
	char buf2[1024] = "Hello back in TCP from server";
	FILE *fout;

	printf("TCP server waiting for remote connection from clients ...\n");

	/*initialize socket connection in unix domain*/
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	perror("error openting datagram socket");
	exit(1);
	}
	
	/* construct name of socket to send to */
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_addr.s_addr = INADDR_ANY;
	sin_addr.sin_port = htons(atoi(port));

	/* bind socket name to socket */
	if(bind(sock, (struct sockaddr *)&sin_addr, sizeof(struct sockaddr_in)) < 0) {
		perror("error binding stream socket");
		exit(1);
	}
	
	/* listen for socket connection and set max opened socket connetions to 5 */
	listen(sock, 5);

	/* accept a (1) connection in socket msgsocket */
		if((msgsock = accept(sock, (struct sockaddr *)NULL, (int *)NULL)) == -1) {
			perror("error connecting stream socket");
		exit(1);
	}

	
	int count = 1, size, fileSize, remainSize;
	char fileName[20];

	if( (size = read(msgsock, buf, sizeof(int))) < 0) {
		perror("error reading on stream socket");
		exit(1);
	}
	memcpy(fileSize, buf, sizeof(int));

	if( (size = read(msgsock, buf, sizeof(int))) < 0) {
		perror("error reading on stream socket");
		exit(1);
	}
	memcpy(fileName, buf, size);
	fout = fopen( "test.jpg", "w" );
	remainSize = fileSize;
	while(1)
	{
		/* put all zeros in buffer (clear) */
		bzero(buf,1024);
		int neededSize = 1024 > remainSize ? remainSize : 1024;
		/* read from msgsock and place in buf */
		if( (size = read(msgsock, buf, neededSize)) < 0) {
			perror("error reading on stream socket");
			exit(1);
		}
		if( size == 0 ) {
			break;
		}
		printf("%d part has been recieved(%d)", count++, size);
		fwrite(buf, 1, size, fout);
	}

	/* write message back to client */
	if(write(msgsock, buf2, 1024) < 0) {
		perror("error writing on stream socket");
		exit(1);
	}
	printf("Server sends:%s\n", buf2);

	/* close all connections and remove socket file */
	close(msgsock);
	close(sock);
}
