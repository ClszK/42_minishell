#include "minishell.h"

int	test_printf(void *param)
{
	t_token *token;

	token = (t_token *)param;
	if (token->type == WORD)
		printf("TYPE : WORD\n");
	else if (token->type == PIPE)
		printf("TYPE : PIPE\n");
	else if (token->type == REDIRECT)
		printf("TYPE : REDIRECT\n");
	printf("STR  : %s%%\n", token->str);
	printf("\n");
	return (0);
}

void	test_del(void *param)
{
	t_token	*token;

	token = (t_token *)param;
	free(token->str);
}

int main(int argc, char **argv, char **envp)
{
	char		*rline;
	t_envp		env_c;
	t_cmdline	cmdline;
	t_parse		cmd;

	envp_init(envp, &env_c);
	while (1)
	{
		rline = readline("minishell$ ");
		cmd.cmd_argv = ft_split(rline, ' ');
		// cmdline_init(&cmdline);
		builtin_export(&cmd, &env_c);
		for(int x = 0;cmd.cmd_argv[x]; x++)
			free(cmd.cmd_argv[x]);
		free(cmd.cmd_argv);
		// token_cmdline(rline, &cmdline);
		// dlst_print(&cmdline, test_printf);
		// dlst_del_all(&cmdline, test_del);
		// cmd.cmd_argv = ft_split(cmdline, ' ');
		// builtin_echo(&cmd);s
		// builtin_pwd();
		// builtin_env(&env_c);
		// builtin_exit(&cmd);
		free(rline);
    }
	return (0);
}

    //  int 
    //  main (int argc, char **argv)
    //  {
	// while (1){
	// 	int childPid;
	// 	char * cmdLine;

	//         printPrompt();

	//         cmdLine= readCommandLine(); //or GNU readline("");
		
	// 	cmd = parseCommand(cmdLine);

	// 	record command in history list (GNU readline history ?)
 
	// 	if ( isBuiltInCommand(cmd)){
	// 	    executeBuiltInCommand(cmd);
	// 	} else {		
	// 	     childPid = fork();
	// 	     if (childPid == 0){
	// 		executeCommand(cmd); //calls execvp  
			
	// 	     } else {
	// 		if (isBackgroundJob(cmd)){
	// 		        record in list of background jobs
	// 		} else {
	// 			waitpid (childPid);

	// 		}		
	// 	    }
	//         }
    //  }