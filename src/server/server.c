#include "minitalk.h"

void	recv_len(char c, int bitn, char **str)
{
	static unsigned int	len = 0;

	len = (len << 8) | (c & 0xFF);
	if (bitn == 32)
	{
		*str = ft_calloc(len + 1, sizeof(char));
		len = 0;
	}
}

void	end_tranfer(char **str, size_t *bitn, pid_t pid)
{
	int	err;

	err = 0;
	ft_putstr_fd(*str, 1);
	ft_putendl_fd("", 1);
	free(*str);
	err = kill(pid, SIGUSR2);
	if (err)
		print_err(-1, "Client is dead.");
	*bitn = 0;
}

void	sig_handler(int signum, siginfo_t *info, void *ucontext)
{
	static size_t	bitn = 0;
	static char		c = 0;
	static char		*str;

	(void)ucontext;
	bitn++;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	if (bitn % 8 == 0)
	{
		if (bitn <= 32)
			recv_len(c, bitn, &str);
		else
		{
			if (str)
				str[(bitn - 40) / 8] = c;
			else
				print_err(-1, "Malloc error");
			if (!c)
				end_tranfer(&str, &bitn, info->si_pid);
		}
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	static char			*art = "\n\
   ________  ______   _____  _____\n\
  / ___/ _ \\/ ___/ | / / _ \\/ ___/\n\
 (__  )  __/ /   | |/ /  __/ /    \n\
/____/\\___/_/    |___/\\___/_/     \n\n";
	struct sigaction	new_action;

	(void)art;
	new_action.sa_sigaction = sig_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &new_action, NULL);
	sigaction(SIGUSR2, &new_action, NULL);
	ft_putstr_fd("[i] Server pid: ", 2);
	ft_putnbr_fd(getpid(), 2);
	ft_putendl_fd("", 2);
	while (1)
		pause();
	return (0);
}
