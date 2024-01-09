#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*cmdline;
	pid_t	child_pid;
	t_envp	env_c;
	t_parse	cmd;

	envp_init(envp, &env_c);
	// for (int i = 0; envp[i];i++)
	// 	printf("%p %s\n", &envp[i], envp[i]);
	while (1)
	{
		cmdline = readline("minishell$ ");
		// cmd.cmd_argv = ft_split(cmdline, ' ');
		// builtin_echo(&cmd);s
		// builtin_pwd();
		builtin_env(&env_c);
		free(cmdline);
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