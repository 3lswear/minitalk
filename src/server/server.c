#include "minitalk.h"

void a_handler(int signum)
{
	printf("signal handled ! signum = %d\n", signum);
}

int main(int argc, char **argv)
{
	static char *art = "\n\
   ________  ______   _____  _____\n\
  / ___/ _ \\/ ___/ | / / _ \\/ ___/\n\
 (__  )  __/ /   | |/ /  __/ /    \n\
/____/\\___/_/    |___/\\___/_/     \n\n";

	struct sigaction new_action;

	new_action.sa_handler = a_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	sigaction(SIGUSR1, )

	(void)argc;
	(void)argv;

	printf("%s", art);
	printf("My pid is: %d\n", getpid());
	pause();

	return (0);
}
