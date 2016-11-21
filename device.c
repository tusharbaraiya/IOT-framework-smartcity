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
int port = 9887;
char msg[5] ="12345";
char* timberlake_ip = "128.205.36.8";
char* my_ip = "128.205.163.14";
struct sockaddr_in udp;
int send_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
memset(&udp,0,sizeof(udp));
udp.sin_family=AF_INET;
inet_aton(my_ip, &udp.sin_addr);
udp.sin_port=htons(port);
sendto(send_udp_fd, msg, 5, 0, (struct sockaddr *)&udp, sizeof(udp));
}
