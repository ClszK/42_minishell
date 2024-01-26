/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:29:34 by ljh               #+#    #+#             */
/*   Updated: 2024/01/27 03:20:16 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN", "PIPE_IN", "PIPE_OUT"};

	token = (t_token *)elem;
	if (token == NULL)
		return (1);
	printf("		TYPE : %s%%\n", str[token->type]);
	printf("		STR  : %s%%\n", token->str);
	printf("\n");
	return (0);
}

int	test_printf_parse(void *elem)
{
	t_parse	*parse;

	parse = (t_parse *)elem;
	printf("\n	CMD_PATH : %s\n", parse->cmd_path);
	printf("\n	CMD_ARGV\n\n");
	for (int i = 0; parse->cmd_argv[i] ; i++)
		printf("		%s%%\n", parse->cmd_argv[i]);
	printf("\n	HERE_DOC\n\n");
	dlst_print(parse->here_doc_lst, test_printf_token);
	printf("\n	STD_LST\n\n");
	dlst_print(parse->std_lst, test_printf_token);
	printf("\n");
	return (0);
}

void	test_leak(void)
{
	char	*test;
	char	*pid;
	char	*str = "leaks -quiet ";

	pid = ft_itoa(getpid());
	test = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(pid) + 1));
	ft_strcpy(test, str);
	ft_strlcat(test, pid, 1000);
	system(test);
	free(pid);
	free(test);
}

int main(int argc, char **argv, char **envp)
{
	t_shinfo	sh;
	// char		*line;

	(void)argc;
	(void)argv;
	envp_init(envp, &sh.env_c);
	while (1)
	{
		errno = 0;
		
		shinfo_init(&sh);
		// if (isatty(fileno(stdin)))
		// 	sh.rline = readline("minishell$ ");
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// 	sh.rline = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		sh.rline = readline("minishell$ ");
		if (sh.rline == NULL)
			exit (sh.env_c.last_stat);
		add_history(sh.rline);
		if (sh.rline && !command_preprocessing(&sh))
			command_excute(&sh.alz, &sh.env_c);
		shinfo_free(&sh, NULL);
		delete_heredoc();
    }
	set_terminal(0);
	return (0);
}


// dlst_print(&sh->cmdline, test_printf_token);

// bash: maximum here-document count exceeded