#include "../minishell.h"

int	pwd(t_data *data, t_cmd *lst_cmd, int fd)
{
	char	*curr_wd;

	curr_wd = NULL;
	if (lst_cmd)
	{
		if (lst_cmd->cmd[0])
		{
			curr_wd = getcwd(curr_wd, 0);
			if (!curr_wd)
				ft_putstr_fd(ft_get_env(data, "OLDPWD"), 1);
			else
				ft_putstr_fd(curr_wd, fd);
			write(fd, "\n", 1);
		}
		else
			return (printf("pwd: too many arguments\n"), 1);
	}
	return (0);
}

// change the PWD : /Users/rsaf/Desktop/2.0shell/t1/t2/..
// and OLD PWD to : /Users/rsaf/Desktop/2.0shell/t1/t2