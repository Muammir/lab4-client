#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server; 
	struct sockaddr_in Baruclient;
        char *message, server_reply[2000];
	char buffer[2000], msg[2000];
	
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
		exit(1);
	}
	memset(&server, '\0', sizeof(server));		
	server.sin_addr.s_addr = inet_addr("192.168.1.32"); //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		exit(1);
	}
	
	puts("Connected \n");
	
	while(1){
		printf("Client: \t");
		scanf("%s", &buffer[0]);
		send(socket_desc, buffer, strlen(buffer), 0);

		if(strcmp(buffer, ":exit") == 0){
			close(socket_desc);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(socket_desc, server_reply, 2000, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}
		printf("Server :%s\n",server_reply);
//		else{
//			printf("Server: \t%s\n", buffer);
//		}
	}
	close(socket_desc);
	return 0;
}
