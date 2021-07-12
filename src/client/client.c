#include "minitalk.h"

void client_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		/* ft_putendl_fd("SIGUSR1 recieved", 1); */
		ft_putendl_fd("[i] Message was received.", 1);
	}
	else
		usleep(1);
		/* ft_putendl_fd("received something else", 1); */
}

void	send_byte(char byte, int pid)
{
	int i = 7;
	short err;

	err = 0;
	while (i >= 0)
	{
		if ((byte >> i) & 1)
			err = kill(pid, SIGUSR2);
		else
			err = kill(pid, SIGUSR1);
		usleep(40000);
		i--;
		if (err)
		{
			ft_putendl_fd("Server died :(", 2);
			return;
		}
	}
}

void	send_str(char *str, int pid)
{
	unsigned int len;
	int i;

	len = ft_strlen(str);
	i = 0;

	while (i < 4)
	{
		send_byte((len & 0xFF000000) >> 24, pid);
		len = len << 8;
		i++;
	}

	while (*str)
	{
		send_byte(*str++, pid);
	}
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
		return(-1);

	printf("pid is %d\n", pid);

	struct sigaction client_action;

	client_action.sa_handler = client_handler;
	sigemptyset(&client_action.sa_mask);
	/* sigaddset(&client_action.sa_mask, SIGUSR1); */
	client_action.sa_flags = 0;

	sigaction(SIGUSR1, &client_action, NULL);
	sigaction(SIGUSR2, &client_action, NULL);

	send_str(str, pid);

	return (0);
}
