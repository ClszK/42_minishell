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
	printf("\n	STD_LST\n\n");
	dlst_print(parse->std_lst, test_printf_token);
	printf("\n");
	return (0);
}

void	test_leak(void)
{
	char	*test;
	char	*pid;
	char	*str = "leaks -quiet --list ";

	pid = ft_itoa(getpid());
	test = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(pid) + 1));
	ft_strcpy(test, str);
	ft_strlcat(test, pid, 1000);
	system(test);
	free(pid);
	free(test);
}

/* 	명령어 전처리.
	token화, 구문 분석, 변수 확장, 파일 확장.
	Error 처리 미구현 */
int	command_preprocessing(t_shinfo *sh)
{
	int		error_token;

	if (sh->rline && *(sh->rline) != '\0')
	{
		error_token = valid_quote(sh->rline);
		if (error_token)
		{
			sh->env_c.last_stat = 258;
			print_syntax_error(error_token);
			return  (1);
		}
		token_cmdline(sh->rline, &(sh->cmdline));
		// dlst_print(&sh->cmdline, test_printf_token);
		if (sh->cmdline.lst_size != 0)
		{
			error_token = analyze_start(&sh->alz, &sh->cmdline);
			if (error_token)
			{
				sh->env_c.last_stat = 258;
				print_syntax_error(error_token);
				return (1);
			}
			expand_start(&sh->alz, &sh->env_c);
			path_insert_in_parse(&sh->alz, &sh->env_c);
			dlst_print(&sh->alz, test_printf_parse);
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
		shinfo_init(&sh);
		sh.rline = readline("minishell$ ");
		if (sh.rline == NULL)
			exit(EXIT_FAILURE);
		add_history(sh.rline);
		if (!command_preprocessing(&sh))
			command_excute(&sh.alz, &sh.env_c);
		shinfo_free(&sh, NULL);
    }
	return (0);
}


// dlst_print(&sh->cmdline, test_printf_token);

// bash: maximum here-document count exceeded