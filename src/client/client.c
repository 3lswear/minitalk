#include "minitalk.h"

void client_handler(int signum)
{
	if (signum == SIGUSR2)
		ft_putendl_fd("[i] Message was received.", 1);
	else
		usleep(1);
}

void	send_byte(char byte, int pid)
{
	int i;
	int err;

	i = 8;
	err = 0;
	while (i-- >= 1)
	{
		if ((byte >> i) & 1)
			err = kill(pid, SIGUSR2);
		else
			err = kill(pid, SIGUSR1);
		usleep(40000);
		if (err)
		{
			ft_putendl_fd("[x] Server is dead :(", 2);
			exit(-1);
		}
	}
}

void	send_str(char *str, int pid)
{
	unsigned int len;
	size_t i;

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

int		main(int argc ,char **argv)
{
	int pid;
	char *str;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
	}
	else 
	{
		ft_putendl_fd("Usage: client PID STRING", 2);
		return(-1);
	}

	struct sigaction client_action;
	client_action.sa_handler = client_handler;
	sigemptyset(&client_action.sa_mask);
	client_action.sa_flags = 0;
	sigaction(SIGUSR1, &client_action, NULL);
	sigaction(SIGUSR2, &client_action, NULL);
	send_str(str, pid);
	return (0);
}
