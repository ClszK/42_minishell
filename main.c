#include "minishell.h"

int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC"};

	token = (t_token *)elem;
	if (token == NULL)
		return (0);
	printf("TYPE : %s%%\n", str[token->type]);
	printf("STR  : %s%%\n", token->str);
	printf("\n");
	return (0);
}

int	test_printf_parse(void *elem)
{
	t_parse	*parse;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC"};

	parse = (t_parse *)elem;
	printf("\nParse\n");
	for (int i = 0; parse->cmd_argv[i] ; i++)
		printf("%d	%s\n", parse->cmd_argc, parse->cmd_argv[i]);
	if (parse->stdin_token)
	{
		printf("	\nstdin_token\n");
		printf("		TYPE : %s\n", str[parse->stdin_token->type]);
		printf("		STR  : %s\n", parse->stdin_token->str);
	}
	if (parse->stdout_token)
	{
		printf("	\nstdout_token\n");
		printf("		TYPE : %s\n", str[parse->stdout_token->type]);
		printf("		STR  : %s\n", parse->stdout_token->str);
	}
	printf("\n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*rline;
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
		token_cmdline(rline, &cmdline);
		dlst_print(&cmdline, test_printf_token);
		analyze_start(&alz, &cmdline);
		dlst_print(&alz, test_printf_parse);
		dlst_del_all(&cmdline, token_elem_free);
		dlst_del_all(&alz, parse_elem_free);
		// builtin_echo(&cmd);
		// builtin_pwd();
		// builtin_env(&env_c);
		// builtin_exit(&cmd);
		// builtin_export(&cmd, &env_c);
		// dlst_delete(&env_c, map_elem_free, map_del_find, "OLDPWD");
		free(rline);
    }
	return (0);
}
