/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:29:34 by ljh               #+#    #+#             */
/*   Updated: 2024/01/29 01:08:48 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shinfo	sh;

	if (argc != 1)
	{
		print_builtin_error(argv[1], "Usage", "./minishell\n");
		exit(1);
	}
	envp_init(envp, &sh.env_c);
	set_signal();
	while (1)
	{
		shinfo_init(&sh);
		errno = 0;
		sh.rline = readline("minishell$ ");
		if (sh.rline == NULL && !errno)
		{
			restore_signal();
			set_sigterm();
		}
		add_history(sh.rline);
		if (sh.rline && !command_preprocessing(&sh))
			command_excute(&sh.alz, &sh.env_c, &sh.heredoc);
		shinfo_free(&sh, NULL);
		delete_heredoc();
	}
}

/*
int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", \
				"INPUT", "HEREDOC", "NEWLN", "PIPE_IN", "PIPE_OUT"};

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
	printf("\n	STD_LST\n\n");
	dlst_print(parse->std_lst, test_printf_token);
	printf("\n");
	return (0);
}
*/