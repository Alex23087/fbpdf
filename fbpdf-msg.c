#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/fbpdf.sock"

int sock_descriptor = -1;
struct sockaddr_un sock_addr;

int main(){
	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sun_family = AF_UNIX;
	strncpy(sock_addr.sun_path, SOCK_PATH, strlen(SOCK_PATH)+1);

	sock_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock_descriptor < 0){
		fprintf(stderr, "Error while opening the socket");
		return -1;
	}

	connect(sock_descriptor, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
	char msg[] = {'q'};
	write(sock_descriptor, msg, 1);
	close(sock_descriptor);
	//sendto(sock_descriptor, msg, 1, 0, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
	return 0;
}
