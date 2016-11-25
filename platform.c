#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <my_global.h>
#include <mysql.h>

int create_database(char* n);

int main(){
int port = 9777;
char db_name[20];
MYSQL *con = mysql_init(NULL);
if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
} 

printf("Configuring Platform...\n");
printf("Creating Database...\n");
printf("Enter Database name: ");
scanf("%s",db_name);
int db_op = create_database(db_name);
printf("Database creation :");

if(db_op==-1){
printf("Failed, check logs\n");
return -1;
}

printf("Successful\n");


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

if (mysql_real_connect(con, "localhost", "root", "", 
          db_name, 0, NULL, 0) == NULL) 
{
	fprintf(stderr, "%s\n", mysql_error(con));
      	printf("Error in real connect\n");
	return -1;
}

printf("Listening on PORT : %d\n", port);

char create_qry[200];
char* c_qry_1= "CREATE TABLE IF NOT EXISTS device_";
char* c_qry_2="(ID int NOT NULL AUTO_INCREMENT PRIMARY KEY,Sensor_1 INT, Sensor_2 INT, Sensor_3 INT)";
char insert_qry[300];

char d_id[4];
char s1[3];
char s2[3];
char s3[3];
int s1_val;
int s2_val;
int s3_val;
int id_val;

while(1){
	uint8_t rcvfrm[20];
	int slen = sizeof(udp_rcv);	
	recvfrom(udp_rcvfd, rcvfrm, 19, 0, (struct sockaddr *)&udp_rcv, &slen);		
	strncpy(d_id,rcvfrm,3);
	d_id[3]='\0';
	id_val = atoi(d_id);	
	strncpy(s1,rcvfrm+3,2);
	s1[3]='\0';
	strncpy(s2,rcvfrm+5,2);
	s2[3]='\0';
	strncpy(s3,rcvfrm+7,2);
	s3[3]='\0';
	
	s1_val= atoi(s1);
	s2_val= atoi(s2);
	s3_val= atoi(s3);
	
	sprintf(insert_qry,"INSERT INTO device_%d VALUES(NULL,%d,%d,%d)",id_val,s1_val,s2_val,s3_val);
	printf("Insert qry : %s", insert_qry);	
	strcpy(create_qry,c_qry_1);
	strcat(create_qry,d_id);
	strcat(create_qry,c_qry_2);
	if (mysql_query(con, create_qry)) {
		fprintf(stderr, "%s\n", mysql_error(con));      
      		printf("Error creating table\n");
  		}
	
	if (mysql_query(con, insert_qry)) {
		fprintf(stderr, "%s\n", mysql_error(con));      
      		printf("Error inserting values\n");
  		}
	
	}

return 0;
}

int create_database(char* name){
MYSQL *con = mysql_init(NULL);  
if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      return -1;
  }
  if (mysql_real_connect(con, "localhost", "root", "root_pswd", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      return -1;
  }  
char* qry = "CREATE DATABASE ";
char full_qry[30];

strcpy(full_qry,qry);
strcat(full_qry,name);
 
  if (mysql_query(con, full_qry)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      return -1;
  }
return 1;
}

