#include "minitalk.h"

void	print_err(int code, char *msg)
{
	ft_putstr_fd("[x] Error! 😰", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	exit(code);
}
