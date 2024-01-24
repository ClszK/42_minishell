/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:19:42 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/25 00:07:59 by jeholee          ###   ########.fr       */
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
	tmp = ".here_doc_tmp";
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
			perror("minishell: ");
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
	if (is_file_access(filename, mode))
	{
		errno = 0;
		if (mode == R_OK)
			rfd = open(filename, omode);
		else
			rfd = open(filename, omode, 0666);
		if (rfd == -1 && errno)
		{
			print_strerror(NULL, filename);
			return (-1);
		}
		return (rfd);
	}
	return (-1);
}

void	stdin_heredoc(char *end_id, int tmp_fd)
{
	char	*rline;
	size_t	len;

	errno = 0;
	len = ft_strlen(end_id);
	while (1)
	{
		rline = readline("> ");
		if (rline == NULL && errno != 0)
			perror_exit("minishell");
		if (len == ft_strlen(rline) && \
			!ft_strncmp(rline, end_id, len))
		{
			free(rline);
			return ;
		}
		write(tmp_fd, rline, ft_strlen(rline));
		write(tmp_fd, "\n", 1);
		free(rline);
	}
}

int	open_append(char *filename)
{
	int	fd;

	fd = 0;
	if (is_file_access(filename, W_OK))
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		return (-1);
	return (fd);
}
