#include "minitalk.h"

void	client_handler(int signum, siginfo_t *info, void *ucontext)
{
	static pid_t	server;

	(void)ucontext;
	if (signum == SIGUSR2)
	{
		ft_putendl_fd("[i] Message was received.", 1);
		exit(0);
	}
	else if (signum == SIGUSR1)
		server = info->si_pid;
	else
	{
		if (server)
		{
			send_byte(0, server);
			send_byte(0, server);
		}
	}
}

void	send_byte(char byte, int pid)
{
	int	i;
	int	err;

	i = 8;
	err = 0;
	while (i-- >= 1)
	{
		if ((byte >> i) & 1)
			err = kill(pid, SIGUSR2);
		else
			err = kill(pid, SIGUSR1);
		if (err)
			print_err(-1, "Server is dead");
		usleep(20000);
	}
}

void	send_str(char *str, int pid)
{
	unsigned int	len;
	size_t			i;

	len = ft_strlen(str);
	i = 0;
	printf("len is %u\n", len);
	while (i < 4)
	{
		send_byte(((len & 0xFF000000) >> 24) & 0xFF, pid);
		len = len << 8;
		i++;
	}
	while (*str)
		send_byte(*str++, pid);
	send_byte(0, pid);
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*str;
	struct sigaction	client_action;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
	}
	else
	{
		ft_putendl_fd("Usage: client PID STRING", 2);
		return (-1);
	}
	client_action.sa_sigaction = client_handler;
	sigemptyset(&client_action.sa_mask);
	client_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &client_action, NULL);
	sigaction(SIGUSR2, &client_action, NULL);
	sigaction(SIGINT, &client_action, NULL);
	send_str(str, pid);
	return (0);
}
