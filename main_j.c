#include "minishell.h"

int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN"};

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
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN"};

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
	char	*test;
	char	*test2;
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
		test = expand_str_alloc(rline, &env_c);
		test2 = expand_str_cpy(rline, test, &env_c);
		printf("%s\n", test);
		free(test);
		// if (rline && *rline != '\n')
		// {
		// 	token_cmdline(rline, &cmdline);
		// 	if (cmdline.lst_size != 0)
		// 		analyze_start(&alz, &cmdline);
		// 	dlst_print(&cmdline, test_printf_token);
		// 	dlst_print(&alz, test_printf_parse);
		// }
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
