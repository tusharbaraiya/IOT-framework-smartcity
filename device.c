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
char msg[9];
char* timberlake_ip = "128.205.36.8";
char* my_ip = "128.205.163.14";
struct sockaddr_in udp;
int send_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
memset(&udp,0,sizeof(udp));
udp.sin_family=AF_INET;
inet_aton(my_ip, &udp.sin_addr);
udp.sin_port=htons(port);

char id[3];
char device_name[20];
char s1[2];
char s2[2];
char s3[2];

printf("Create an IOT Device...\n");
printf("Enter Device ID: ");
scanf("%s",id);
printf("Enter Device Name: ");
scanf("%s",device_name);
printf("Successfuly created devide, now you may start sending sensor data to the platform... ");

while(1){
	printf("\nEnter sensor_1 value : ");
	scanf("%s",s1);
	printf("Enter sensor_2 value : ");
	scanf("%s",s2);
	printf("Enter sensor_3 value : ");
	scanf("%s",s3);
	strcpy(msg,id);
	strcat(msg,s1);
	strcat(msg,s2);
	strcat(msg,s3);	
	printf("msg : %s \n",msg);	
	//sendto(send_udp_fd, msg, 5, 0, (struct sockaddr *)&udp, sizeof(udp));
	printf("Succsessfuly sent the data to the platform");
}
}
