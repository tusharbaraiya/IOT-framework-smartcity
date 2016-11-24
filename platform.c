#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(){
int port = 9777;
printf("Creating UDP socket... ");
int udp_rcvfd=socket(AF_INET, SOCK_DGRAM, 0);
if(udp_rcvfd == -1){
printf("sockfd failed\n");
return 0;
}

struct sockaddr_in udp_rcv;
memset(&udp_rcv,0,sizeof(udp_rcv));
udp_rcv.sin_family=AF_INET;
udp_rcv.sin_addr.s_addr=htonl(INADDR_ANY);
udp_rcv.sin_port=htons(port);
printf(": Successful\n");
printf("Binding ... ");
int bnd = bind(udp_rcvfd, (struct sockaddr *)&udp_rcv, sizeof(udp_rcv));
if(bnd == -1){
printf("bind failed\n");
return 0;
}
printf(": Successful\n");
printf("Listening on PORT : %d\n", port);


while(1){
	uint8_t rcvfrm[200];
	int slen = sizeof(udp_rcv);
	recvfrom(udp_rcvfd, rcvfrm, 199, 0, (struct sockaddr *)&udp_rcv, &slen);
	printf("recieved %s\n ",rcvfrm);
	}

return 0;
}
