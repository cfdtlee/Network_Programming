/*************************************************************************
 > File Name: web_client.c
 > Author: Eric
 > Mail: cfdtlee@gmail.com 
 > Created Time: Thu Jun 12 14:55:05 2014
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#define W3PORT 80
int main(int argc, char* argv[])
{
    int n;
    char buf[32768];
    struct hostent host;
    int sockfd;
    struct sockaddr_in addr;
    if(argc != 2) {
        printf("Please input a valid hostname.");
        exit(1);
    }
    bzero(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(W3PORT);
    if(inet_aton(argv[1], &addr.sin_addr) == 0) {
        if( (host = gethostbyname(argv[1])) == NULL) { 
        //获取服务器地址
            printf("Please input a valid hostname.");
            exit(1);
        }
        addr.sin_addr = *(struct in_addr *)(host->h_addr_list[0]);
    }
    printf("Tring host");
    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))<0) {
    	//尝试连接
        printf("Connect Failed.");
        close(sockfd);
        exit(1);
    }
    printf("Sending msg.");
    strcpy(buf, "GET /20050419/3134630/shtml \r\n\r\n");
    write(sockfd, buf, strlen(buf));
    for( ; ; )
    {
        n = read(sockfd, buf, 32768);
        if(n == EINTR)
            continue;
        else if(n<0) {
            fprintf("Read error");
            exit(1);
        }
        else {
            printf("OK");
            break;
        }
    }
    close(sockfd);
}
