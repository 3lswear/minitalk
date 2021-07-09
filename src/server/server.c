#include "minitalk.h"

void sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static int i = 0;
	static char c = 0;
	(void)ucontext;

	if (signum == SIGUSR1)
	{
		i++;
		c = c << 1;
		/* ft_putstr_fd("0", 1); */
		usleep(100);
		kill(info->si_pid, SIGUSR1);
	}
	else if (signum == SIGUSR2)
	{
		i++;
		c = c << 1;
		c = c | 1;
		/* ft_putstr_fd("1", 1); */
		usleep(100);
		kill(info->si_pid, SIGUSR1);
	}
	else
		ft_putstr_fd("received something else\n", 1);

	if (i % 8 == 0)
	{
		if (!c)
		{
			ft_putendl_fd("", 1);
			exit(0);
		}
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

	(void)art;
	struct sigaction new_action;

	new_action.sa_sigaction = sig_handler;
	sigemptyset(&new_action.sa_mask);
	/* sigaddset(&new_action.sa_mask, SIGUSR1); */
	/* sigaddset(&new_action.sa_mask, SIGUSR2); */
	new_action.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);

	/* printf("%s", art); */
	/* printf("[i] My pid is: %d\n", getpid()); */

	while(1)
		pause();

	return (0);
}
