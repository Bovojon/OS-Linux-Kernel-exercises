/*
Run `gcc -o main collatz_conjecture.c`
Then run `./main`
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int n = 0;
	int i = 0;
	pid_t pid;
	while (i <= 0) {
		printf("Enter a positive integer (not 0):\n");
		scanf("%d", &i);
	}
	pid = fork();
	if (pid == 0) {
		printf("%d\n",i);
		while (i != 1) {
			if (i%2 == 0) {
				i = i/2;
			}
			else if (i%2 == 1) {
				i = 3*(i)+1;
			}
			printf("%d\n",i);
		}
	}
	else {
		wait();
		printf("All processes are done. wait() is called to wait for the child process to complete now.\n");
	}
	return 0;
}
