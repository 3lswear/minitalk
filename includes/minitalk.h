#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# include <stdio.h>

void	send_byte(char byte, int pid);
void	print_err(int code, char *msg);

#endif
