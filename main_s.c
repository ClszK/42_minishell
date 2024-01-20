#include "minishell.h"

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
		// cmdline_init(&cmdline);
		// analyze_init(&alz);
		rline = readline("minishell$ ");
		cmd.cmd_argv = ft_split(rline, ' ');
		// token_cmdline(rline, &cmdline);
		// dlst_print(&cmdline, test_printf_token);
		// // analyze_start(&alz, &cmdline);
		// dlst_print(&alz, test_printf_parse);
		// dlst_del_all(&cmdline, token_elem_free);
		// dlst_del_all(&alz, parse_elem_free);
		// builtin_echo(&cmd);
		// builtin_pwd();
		// builtin_env(&env_c);
		// builtin_exit(&cmd);
		if (!ft_strcmp(cmd.cmd_argv[0], "ex"))
			builtin_export(&cmd, &env_c);
		else if (!ft_strcmp(cmd.cmd_argv[0], "un"))
			builtin_unset(&cmd, &env_c);
		else
			builtin_cd(&cmd, &env_c);
		free(rline);
    }
	return (0);
}
