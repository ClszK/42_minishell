/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:19:42 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/22 13:55:23 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tmpfile_create(char **tmp_name)
{
	char	*itoa_str;
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	tmp = "here_doc_tmp";
	errno = 0;
	while (++i < 2147483647)
	{
		itoa_str = ft_itoa(i);
		*tmp_name = ft_strjoin(tmp, itoa_str);
		if (*tmp_name == NULL)
			exit(EXIT_FAILURE);
		free(itoa_str);
		fd = open(*tmp_name, O_EXCL | O_CREAT | O_RDWR, 0644);
		if (fd != -1)
			return (fd);
		free(*tmp_name);
		if (errno != EEXIST)
			perror_exit("minishell");
	}
	return (-1);
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
