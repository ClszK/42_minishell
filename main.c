#include "minishell.h"

int main(int argc, char **argv, char* envp[])
{
	char	*cmdline;
	pid_t	child_pid;
	t_envp	shell;
	t_parse	cmd;

	set_envp(envp, &shell);

	while (1)
	{
		cmdline = readline("minishell$ ");
		cmd.cmd_argv = ft_split(cmdline, ' ');
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