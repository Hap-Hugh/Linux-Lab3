/***************************
Name：p12
Programmer:修海博 3160105286
***************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main()
{
	pid_t firstResult, secondResult, thirdResult;
	int ret;
	firstResult = fork();
	secondResult = fork();
	int firstRead;
	int secondRead;
	int fd[2];
	char* s1 = "Child process p1 is sending a message!";
	char* s2 = "Child process p2 is sending a message!";
	/*Child process 1*/
	if (firstResult == 0 && secondResult != 0)
	{
		thirdResult = fork();
		if (thirdResult == 0)
		{
			printf("===\n");
			printf("I am child process p3\n");
			printf("My PID is: %d\n", getpid());
			execl("/bin/ls", "ls", "-rl", NULL);
			printf("===\n");
			exit(0);
		}
		else{	
		write(fd[1], s1, strlen(s1));
		firstRead = read(fd[0], s2, strlen(s2));
		printf("===\n");
		printf("Here is p1\n");
		printf("My PID is: %d\n", getpid());
		printf("%s\n", s2);
		printf("===\n");
		close(fd[0]);
		close(fd[1]);
		waitpid(thirdResult, NULL, 0);
		exit(0);
		}
	}
	/*Child process 2*/
	else if (secondResult == 0 && firstResult != 0)
	{
		write(fd[0], s2, strlen(s2));
		secondRead = read(fd[1], s1, strlen(s1));
		printf("===\n");
		printf("Here is p2\n");
		printf("My PID is: %d\n", getpid());
		printf("%s\n",s1);
		printf("===\n");
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else if(secondResult != 0 && firstResult != 0)
	{
		printf("===\n");
		printf("I am main process\n");
		printf("My PID is: %d\n", getpid());
		printf("===\n");
		waitpid(firstResult, NULL, 0);
		waitpid(secondResult, NULL, 0);
		exit(0);
	}

}

