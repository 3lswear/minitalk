#include "minitalk.h"

void sig_handler(int signum)
{
static int i = 0;
	static char c = 0;

	if (signum == SIGUSR1)
	{
		i++;
		c = c << 1;
		/* ft_putstr_fd("0", 1); */
	}
	else if (signum == SIGUSR2)
	{
		i++;
		c = c << 1;
		c = c | 1;
		/* ft_putstr_fd("1", 1); */
	}
	else
		ft_putstr_fd("received something else\n", 1);

	if (i % 8 == 0)
	{
		if (!c)
			/* exit(0); */
			ft_putendl_fd("", 1);
		/* ft_putstr_fd("	", 1); */
		ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
		/* ft_putendl_fd("", 1); */
	}
}

int main(void)
{
	static char *art = "\n\
   ________  ______   _____  _____\n\
  / ___/ _ \\/ ___/ | / / _ \\/ ___/\n\
 (__  )  __/ /   | |/ /  __/ /    \n\
/____/\\___/_/    |___/\\___/_/     \n\n";

	struct sigaction new_action;

	new_action.sa_handler = sig_handler;
	sigemptyset(&new_action.sa_mask);
	/* sigemptyset(&new_action.sa_mask); */
	/* sigaddset(&new_action.sa_mask, SIGUSR1); */
	/* sigaddset(&new_action.sa_mask, SIGUSR2); */
	new_action.sa_flags = 0;

	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);

	printf("%s", art);
	printf("[i] My pid is: %d\n", getpid());

	while(1)
		pause();

	return (0);
}
