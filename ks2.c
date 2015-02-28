#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){

	int pipefd[2];
    char buf_r[4] = {'\0'};
	char buf_w[4] = {'\0'};
 	pid_t pid_r;

	if(pipe(pipefd) == -1){	
		perror("pipe");
		exit(-1);
	}	
	pid_r = fork();
	if(pid_r == -1 ) {
		perror("fork");
		exit(-1);
	}
	while(1){
		if(pid_r == 0){
			close(pipefd[1]);
			read(pipefd[0], &buf_r, 1);
			if(buf_r[0] == 'q'){
				close(pipefd[1]);
				break;
			}
			printf("%s \n",buf_r);
		}else{
			close(pipefd[0]);
			scanf("%s",buf_w);			
			write(pipefd[1], &buf_w, 1);
			if(buf_w[0] == 'q'){
				close(pipefd[1]);
				break;
			}
		}
	}
	wait(NULL);
    exit(0);	
    return 0;
}
