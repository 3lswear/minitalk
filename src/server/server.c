#include "minitalk.h"

void sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static size_t i = 0; // received bit number
	static char c = 0; //assembled byte
	static unsigned int len = 0; // string length
	static char *str; // assembled string
	(void)ucontext;

	if (signum == SIGUSR1)
	{
		i++;
		c = c << 1;
	}
	else if (signum == SIGUSR2)
	{
		i++;
		c = c << 1;
		c = c | 1;
	}
	else
		ft_putstr_fd("received something else\n", 1);


	//read a byte
	if (i % 8 == 0)
	{
		if (i <= 32)
		{
			/* printf("i = %2lu, c = %02X\n", i, c); */
			len = len << 8;
			len = len | (c & 0xFF);
			/* printf("len is %02X\n", len); */
			if (i == 32)
				str = ft_calloc(len + 1, sizeof(char));
		}
		else
		{
			if (!c)
			{
				/* ft_putstr_fd(str, 1); */
				ft_putendl_fd("", 1);
				free(str);
				kill(info->si_pid, SIGUSR2);
				exit(0);
				i = 0;
				c = 0;
				len = 0;
				return;
			}
			ft_putchar_fd(c, 1);
			if (!str)
			{
				ft_putendl_fd("\n[x] STR IS FUCKING NULL", 2);
				exit(-1);
			}
			str[(i - 40) / 8] = c;
		}
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
	sigaddset(&new_action.sa_mask, SIGUSR1);
	sigaddset(&new_action.sa_mask, SIGUSR2);
	new_action.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);

	/* printf("%s", art); */
	/* printf("[i] My pid is: %d\n", getpid()); */

	while(1)
		/* sleep(1); */
		pause();

	return (0);
}
