#include "minitalk.h"

int g_ready = 1;

void wait_for_ready()
{
	while (!g_ready)
		pause();
}

void client_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		/* ft_putendl_fd("SIGUSR1 recieved", 1); */
		g_ready = 1;
	}
	else
		ft_putendl_fd("recieved something else", 1);

}

void	send_byte(char byte, int pid)
{
	int i = 7;
	int bit;

	while (i >= 0)
	{
		wait_for_ready();
		usleep(100);
		bit = (byte >> i) & 1;
		if (bit)
		{
			kill(pid, SIGUSR2);
		}
		else
		{
			kill(pid, SIGUSR1);
		}
		g_ready = 0;
		i--;
		/* usleep(400); */
	}
}

void	send_str(char *str, int pid)
{
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
	sigaddset(&client_action.sa_mask, SIGUSR1);
	client_action.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &client_action, NULL);

	send_str(str, pid);

	return (0);
}
