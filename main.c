#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char		*rline;
	t_envp		env_c;
	t_cmdline	cmdline;

	envp_init(envp, &env_c);
	cmdline_init(&cmdline);
	while (1)
	{
		rline = readline("minishell$ ");
		// cmd.cmd_argv = ft_split(cmdline, ' ');
		// builtin_echo(&cmd);s
		// builtin_pwd();
		builtin_env(&env_c);
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