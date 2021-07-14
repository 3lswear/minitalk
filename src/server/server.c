#include "minitalk.h"

/* void	put_char() */

void	recv_len(int bitn, char c, char **str)
{
	static unsigned int	len;

	len = (len << 8) | (c & 0xFF);
	if (bitn == 32)
	{
		printf("len is %u\n", len);
		ft_putendl_fd("allocing", 1);
		*str = ft_calloc(len + 1, sizeof(char));
		len = 0;
	}

}

void	end_transfer(char **str, size_t *bitn, pid_t pid)
{
	int	err;

	err = 0;
	ft_putstr_fd(*str, 1);
	ft_putendl_fd("", 1);
	free(*str);
	/* exit(0); */
	*bitn = 0;
	err = kill(pid, SIGUSR2);
	if (err)
		ft_putendl_fd("[w] Client didn\'t receive acknowledgment :(", 2);
}

void	sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static size_t	bitn = 0; // received bit number
	static char		c = 0; //assembled byte
	static char 	*str; // assembled string
	/* int 			err; */

	(void)ucontext;
	/* err = 0; */
	bitn++;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	if (bitn % 8 == 0) //read a byte
	{
		if (bitn <= 32) // receiving len
			recv_len(bitn, c, &str);
		else
		{
			if (str)
				str[(bitn - 40) / 8] = c;
			else
				print_err(-1, "malloc error");
			/* ft_putchar_fd(c, 1); */
			if (!c) //if transfer ended
				end_transfer(&str, &bitn, info->si_pid);
		}
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
	/* if (err) */
	/* { */
	/* 	ft_putendl_fd("[x] Client is dead", 2); */
	/* 	end_transfer(&str, &bitn, info->si_pid); */
	/* } */
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
	ft_putstr_fd("[i] My pid is: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);
	while(1)
		pause();

	return (0);
}
