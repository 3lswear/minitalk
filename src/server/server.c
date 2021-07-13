#include "minitalk.h"

/* void	save_byte(char *c, char *str, size_t *i, unsigned int *len) */
/* { */


/* } */

void end_transfer(char *str, size_t *i, unsigned int *len, pid_t pid)
{
	printf("len is %u\n", *len);
	ft_putstr_fd(str, 1);
	ft_putendl_fd("", 1);
	free(str);
	/* exit(0); */
	*i = 0;
	*len = 0;
	kill(pid, SIGUSR2);
}

void sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static size_t i = 0; // received bit number
	static char c = 0; //assembled byte
	static unsigned int len = 0; // string length
	static char *str; // assembled string
	(void)ucontext;

	i++;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	if (i % 8 == 0) //read a byte
	{
		if (i <= 32) // receiving len
		{
			len = (len << 8) | (c & 0xFF);
			if (i == 32)
				str = ft_calloc(len + 1, sizeof(char));
		}
		else
		{
			if (str)
				str[(i - 40) / 8] = c;
			else
			{
				ft_putendl_fd("\n[x] malloc error", 2);
				exit(-1);
			}
			/* ft_putchar_fd(c, 1); */
			if (!c) //if transfer ended
				end_transfer(str, &i, &len, info->si_pid);
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
