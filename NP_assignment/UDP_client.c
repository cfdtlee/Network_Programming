/*************************************************************************
 > File Name: UDP_client.c
 > Author: Eric
 > Mail: cfdtlee@gmail.com 
 > Created Time: Tue Jul 5 15:37:45 2014
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define SERVER_PORT 8080

/*处理数据通信的函数*/
void udpc_requ(int sockfd, const struct sockaddr_in* addr, int len)
{
	char buf[1024];
	int n;

	for( ; fgets(buf, 1024, stdin) != NULL; )
	{
		/*send data gram to server*/
		sendto(sockfd, buf, strlen(buf), 0, addr, len);
		/*receive from server*/
		n = recvfrom(sockfd, buf, 1024, 0, NULL, NULL);
		buf[n] = '\0';
		fputs(buf, stdout);
	}
}

int main(int argc, char* argv[])
{
	int sockfd;
	struct sockaddr_in addr;
	if(argc != 3)
	{
		fprintf(stderr, "usafe:client ipaddr port");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		fprintf(stderr, "Socket error");
		exit(1);
	}
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	if(inet_aton(argv[1], &addr.sin_addr) < 0)
	{
		fprintf(stderr, "Inet_aton error");
		exit(1);
	}
	udpc_requ(sockfd, &addr, sizeof(addr));
	close(sockfd);
}