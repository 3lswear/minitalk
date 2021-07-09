#include "minitalk.h"

void	send_byte(char byte, int pid)
{
	int i = 7;
	int bit;

	while (i >= 0)
	{
		bit = (byte >> i) & 1;
		if (bit)
		{
			kill(pid, SIGUSR2);
			/* ft_putstr_fd("1", 1); */
		}
		else
		{
			kill(pid, SIGUSR1);
			/* ft_putstr_fd("0", 1); */
		}
		i--;
		usleep(400);
	}
	/* ft_putstr_fd("	", 1); */
	/* ft_putchar_fd(byte, 1); */
	/* ft_putendl_fd("", 1); */
}

void	send_str(char *str, int pid)
{
	while (*str)
	{
		send_byte(*str++, pid);
		/* usleep(1000); */
	}
	send_byte(0, pid);
	/* usleep(1000); */
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

	send_str(str, pid);

	return (0);
}
