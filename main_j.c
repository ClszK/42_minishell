#include "minishell.h"

int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN"};

	token = (t_token *)elem;
	if (token == NULL)
		return (0);
	printf("	TYPE : %s%%\n", str[token->type]);
	printf("	STR  : %s%%\n", token->str);
	printf("\n");
	return (0);
}

int	test_printf_parse(void *elem)
{
	t_parse	*parse;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN"};

	parse = (t_parse *)elem;
	printf("\nParse\n");
	for (int i = 0; parse->cmd_argv[i] ; i++)
		printf("%d	%s%%\n", parse->cmd_argc, parse->cmd_argv[i]);
	printf("\nSTDIN_LST\n\n");
	dlst_print(parse->stdin_lst, test_printf_token);
	printf("\nSTDOUT_LST\n\n");
	dlst_print(parse->stdout_lst, test_printf_token);
	printf("\n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*rline;
	char	*test;
	pid_t	child_pid;
	t_envp	env_c;
	t_parse	cmd;
	t_cmdline cmdline;
	t_analyze alz;

	envp_init(envp, &env_c);
	while (1)
	{
		cmdline_init(&cmdline);
		analyze_init(&alz);
		rline = readline("minishell$ ");
		add_history(rline);
		if (rline && *rline != '\n')
		{
			token_cmdline(rline, &cmdline);
			if (cmdline.lst_size != 0)
			{
				analyze_start(&alz, &cmdline);
				expand_start(&alz, &env_c);
			}
			dlst_print(&alz, test_printf_parse);
		}
		dlst_del_all(&cmdline, token_elem_free);
		dlst_del_all(&alz, parse_elem_free);
		// builtin_echo(&cmd);s
		// builtin_pwd();
		// builtin_env(&env_c);
		// builtin_exit(&cmd);
		// builtin_export(&cmd, &env_c);
		free(rline);
    }
	return (0);
}
