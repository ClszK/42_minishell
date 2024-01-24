#include "minishell.h"

int	test_printf_token(void *elem)
{
	t_token	*token;
	char	*str[] = {"NONE", "WORD", "PIPE", "OUTPUT", "APPEND", "INPUT", "HEREDOC", "NEWLN"};

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
	printf("\n	STDIN_LST\n\n");
	dlst_print(parse->stdin_lst, test_printf_token);
	printf("\n");
	return (0);
}

/* 명령어 전처리(token화, 구문 분석, 변수 확장, 파일 확장)
	Error 처리 미구현 */
int	command_preprocessing(t_shinfo *sh)
{
	int	error_token;

	if (sh->rline && *(sh->rline) != '\0')
	{
		error_token = valid_quote(sh->rline);
		if (error_token)
		{
			print_syntax_error(error_token);
			return  (1);
		}
		token_cmdline(sh->rline, &(sh->cmdline));
		if (sh->cmdline.lst_size != 0)
		{
			error_token = analyze_start(&sh->alz, &sh->cmdline);
			if (error_token)
			{
				print_syntax_error(error_token);
				return (1);
			}
			expand_start(&sh->alz, &sh->env_c);
			path_insert_in_parse(&sh->alz, &sh->env_c);
		}
		return (0);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_shinfo	sh;

	(void)argc;
	(void)argv;
	envp_init(envp, &sh.env_c);

	while (1)
	{
		set_signal();
		shinfo_init(&sh);
		sh.rline = readline("minishell$ ");
		if (sh.rline == NULL)
		{
			set_sigterm();
			exit(0);
		}
		add_history(sh.rline);
		if (command_preprocessing(&sh))
			continue ;
		else
			command_excute(&sh);
		shinfo_free(&sh, NULL);
    }
	return (0);
}


		// dlst_print(&sh->cmdline, test_printf_token);
		// dlst_print(&sh->alz, test_printf_parse);