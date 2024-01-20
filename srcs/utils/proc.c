/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:43:21 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/21 07:15:25 by jeholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *filename, int mode);

void	wait_child(t_pinfo *info)
{
	int	status;
	int	i;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		info->pid = wait(&status);
		if (info->last_pid == info->pid)
			info->last_status = status;
	}
}

void	child_process(t_parse *parse, t_envp *env_c, int i)
{
	char	**envp;

	// dup_std_fd(argv[0], info, i);
	execve(parse->cmd_path, parse->cmd_argv, envp);
	exit(EXIT_FAILURE);
}

void	pinfo_set(t_pinfo *info, int argc, char *argv[], char *envp[])
{
	// info->fd[0] = open_file(argv[0], argv[1], R_OK);
	// info->fd[1] = open_file(argv[0], argv[argc - 1], W_OK);
	// if (info->fd[1] == -1)
	// 	print_strerror(argv[0], argv[argc -1]);
	info->pfd = pipe_init(argv[0], info->cmd_cnt - 1);
}


void	pipe_close(int **pfd, int std_fd, int i, int pipe_cnt)
{
	if (i == 0 || i == pipe_cnt - 1)
	{
		close(pfd[i % 2][!std_fd]);
		close(pfd[(i + 1) % 2][std_fd]);
	}
}



void	stdin_heredoc(char *end_id, int tmp_fd)
{
	char	*readline;
	size_t	len;

	errno = 0;
	len = ft_strlen(end_id);
	while (1)
	{
		ft_printf("> ");
		readline = get_next_line(STDIN_FILENO);
		if (readline == NULL && errno != 0)
			perror_exit("minishell");
		if (len == ft_strlen(readline) - 1 && \
			!ft_strncmp(readline, end_id, len))
		{
			free(readline);
			return ;
		}
		write(tmp_fd, readline, ft_strlen(readline));
		free(readline);
	}
}

int	std_to_fd(t_stdio *std_lst, int i, int std_fd, t_pinfo *info)
{
	t_node	*std_node;
	t_token	*token;	
	char	*tmp_name;
	int		fd;

	std_node = std_lst->head->next;
	fd = 0;
	while (std_node->elem)
	{
		if (fd)
			close(fd);
		token = std_node->elem;
		if (!ft_strcmp(token->type, "APPEND"))
			fd = open(token->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (!ft_strcmp(token->type, "OUTPUT"))
			fd = open_file(token->str, W_OK);
		else if (!ft_strcmp(token->type, "HEREDOC"))
		{
			fd = tmpfile_create(&tmp_name);
			stdin_heredoc(token->str, fd);
			close(fd);
			fd = open_file(tmp_name, R_OK);
		}
		else if (!ft_strcmp(token->type, "INPUT"))
			fd = open_file(token->str, R_OK);
		else if (!ft_strcmp(token->type, "PIPE"))
			fd = info->pfd[i % 2][std_fd];
		if (dup2(fd, std_fd) < 0)
			exit(EXIT_FAILURE);
		std_node = std_node->next;
	}
	if (info->is_pipe)
		pipe_close(info->pfd, std_fd, i);
}

void	dup_std_fd(t_pinfo *info, t_stdio *stdin_lst, t_stdio *stdout_lst, int i)
{
	std_to_fd(stdin_lst, i, STDIN_FILENO, info);
	std_to_fd(stdout_lst, i, STDOUT_FILENO, info);
}

int	is_file_access(char *progname, char *filename, int mode)
{
	errno = 0;
	if (access(filename, mode) == 0)
		return (1);
	if (errno != 0)
		print_strerror(progname, filename);
	return (0);
}

int	open_file(char *filename, int mode)
{
	int	omode;
	int	rfd;

	if (mode == R_OK)
		omode = O_RDONLY;
	else
		omode = O_WRONLY | O_TRUNC | O_CREAT;
	if (mode != R_OK || is_file_access("minishell", filename, mode))
	{
		errno = 0;
		if (mode == R_OK)
			rfd = open(filename, omode);
		else
			rfd = open(filename, omode, 0666);
		if (rfd == -1 && errno != 0)
		{
			error_exit("minishell", filename, strerror(errno), EXIT_FAILURE);
			return (-1);
		}
		return (rfd);
	}
	return (-1);
}
