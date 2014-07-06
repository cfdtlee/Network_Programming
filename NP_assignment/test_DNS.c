/*************************************************************************
 > File Name: test_DNS.c
 > Author: Eric
 > Mail: cfdtlee@gmail.com 
 > Created Time: Thu Jul  3 21:03:17 2014
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<stdlib.h>
int main()
{
    int i;
    struct hostent *he = gethostbyname("www.baidu.com");
    if(he != NULL) {
        printf("h_name:%s\n", he->h_name);
        printf("h_length:%d\n", he->h_length);
        printf("h_addrtype:%d", he->h_addrtypr);
        for(i = 0; he->h_aliases[i] != NULL; i++)
            printf("h_aliases%d:%s\n", i+1, he->h_aliases[i]);
        for(i = 0; he->h_addr_list[i] != NULL; i++)
        {
            struct in_addr *addr;
            addr = (struct in_addr *)he->h_addr_list[i];
            printf("ip%d:%s\n", (i+1), inet_ntoa(*addr));
        }
    }
    else
        printf("gethostbyname error:%s\n", hstrerror(h_errno));
}
