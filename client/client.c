#include <stdio.h>                   // Client – fileClent.c 
#include <stdlib.h>                  // gcc fileClient.c -o fileClient -lunp
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
int main(void){
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    char fname[20];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;
    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6690); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    /* Create file where data will be stored */
    FILE *fp;
    if (bytesReceived = read(sockfd, fname, sizeof(fname)) < 0){
        printf("\n Error: Recive File Name Error \n");
        return 1;
    }
    fp = fopen(fname, "wb"); 
    if(NULL == fp)     {
        printf("Error opening file");
        return 1;
    }
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sockfd, recvBuff, 256)) > 0) {
        // printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }
    if(bytesReceived < 0)    {
        printf("\n Read Error \n");
    }

    return 0;
}

