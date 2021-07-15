#include "minitalk.h"

/* void	end_tranfer(char **str, size_t *i, unsigned int *len, pid_t pid) */
/* { */

/* } */

void sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static size_t bitn = 0; // received bit number
	static char c = 0; //assembled byte
	static unsigned int len = 0; // string length
	static char *str; // assembled string

	(void)ucontext;
	bitn++;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	if (bitn % 8 == 0) //read a byte
	{
		if (bitn <= 32)
		{
			len = (len << 8) | (c & 0xFF);
			if (bitn == 32)
				str = ft_calloc(len + 1, sizeof(char));
		}
		else
		{
			if (str)
				str[(bitn - 40) / 8] = c;
			else
				print_err(-1, "malloc error");
			if (!c)
			{
				ft_putstr_fd(str, 1);
				ft_putendl_fd("", 1);
				free(str);
				kill(info->si_pid, SIGUSR2);
				/* exit(0); */
				bitn = 0;
				c = 0;
				len = 0;
				return;
			}
			/* ft_putchar_fd(c, 1); */
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
	/* sigaddset(&new_action.sa_mask, SIGUSR1); */
	/* sigaddset(&new_action.sa_mask, SIGUSR2); */
	new_action.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);

	ft_putstr_fd("[i] Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);

	while(1)
		pause();

	return (0);
}
