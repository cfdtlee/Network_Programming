/*************************************************************************
 > File Name: TCP_client.c
 > Author: Eric
 > Mail: cfdtlee@gmail.com 
 > Created Time: Tue Jun 10 15:37:45 2014
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define SERVER_PORT 8080

 void udp_respon(int sockfd)
 {
 	int n;
 	char msg[1024] = "hello world!";
 	int addrlen;
 	struct sockaddr_in addr;

 	for( ; ; )
 	{
 		//int n=recvfrom(sockfd,buf,16,0,(struct sockaddr *)&client_addr,&addr_len);
 		//sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&client_addr,sizeof(client_addr));
 		n = recvfrom(sockfd, msg, 1024, 0, (struct sockaddr*)&addr, &addrlen);
 		sendto(sockfd, msg, n, 0, (struct sockaddr*)&addr, addrlen);
 	}
 }

 int main(int argc, char* argv[])
 {
 	int sockfd;
 	struct sockaddr_in addr;
 	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 	if(sockfd < 0)
 	{
 		fprintf(stderr, "Socket error");
 		exit(1);
 	}

 	bzero(&addr, sizeof(addr));
 	addr.sin_family = AF_INET;
 	addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	addr.sin_port = htons(SERVER_PORT);

 	if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
 	{
 		fprintf(stderr, "Bind error");
 		exit(1);
 	}

 	udp_respon(sockfd);
 	close(sockfd);
 }