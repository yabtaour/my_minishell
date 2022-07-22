#include "minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	last;
	char	*ptr;

	ptr = NULL;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		last = strlen(s1);
		while (s1[start] != '\0' && strchr(set, s1[start]))
			start++;
		while (strchr(set, s1[last - 1]) && last > start)
			last--;
		ptr = (char *)malloc(sizeof(char) * (last - start + 1));
		if (ptr)
			strlcpy(ptr, s1 + start, last - start + 1);
	}
	return (ptr);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.env = env;
	data.first_export = NULL;
	ft_env(&data);
	while (69)
	{
		init_signals(&data);
		data.lst_lexer = NULL;
		data.lst_cmd = NULL;
		data.error = 0;
		data.her_doc = 0;
		data.cmd = readline("minishell-1.0 > ");
		if (!data.cmd || !strcmp(data.cmd, "exit"))
			exit(1);
		if (data.cmd && data.cmd[0] != '\0')
		{
			data.cmd = ft_strtrim(data.cmd, " ");
			add_history(data.cmd);
			ft_lexer(&data);
			free(data.cmd);
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
			{
				ft_free_lexer(data.lst_lexer);
				continue;
			}
			ft_expanding(&data);
			// ft_print_lexer(data.lst_lexer);
			ft_parsing(&data);
			ft_delete_quotes(&data);
			int i = 0;
			// printf("her_doc %d\n", data.her_doc);
			// while (data.eof[i])
			// {
			// 	printf("%s\n", data.eof[i]);
			// 	i++;
			// }
			// ft_print_cmd(data.lst_cmd);
			ft_herdoc(&data);
			execution(&data);
			ft_free_lexer(data.lst_lexer);
			ft_free_cmd(data.lst_cmd);
		}
	}
	return (0);
}