/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljh <ljh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:19:42 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/27 00:57:09 by ljh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	tmp 디렉토리에 임시파일 생성.
*/
int	tmpfile_create(char **tmp_name)
{
	char	*itoa_str;
	char	*tmp;
	int		i;
	int		fd;

	i = 0;
	tmp = "./tmp/here_doc_tmp";
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

/*
	mode에 따라 쓰기 파일인지 읽기 파일인지 파악.
	파악 이후 해당 파일을 open한 후 fd값을 반환함.
*/
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

/*
	임시 파일 생성된 fd를 통해 표준 입력으로 받아온 값을 파일에 작성.
*/
void	stdin_heredoc(char *end_id, int tmp_fd)
{
	char	*rline;
	char	*line;
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

/*
	파일이 존재하는 경우 해당 파일에다가 덮어씌우는 open 함수.
*/
int	open_append(char *filename, int fd)
{
	errno = 0;
	if (is_file_access(filename, W_OK))
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (errno)
			print_strerror(filename, NULL);
	}
	if (errno == EACCES)
		return (-1);
	return (fd);
}

//heredoc 환경변수 해석해야하는지.
		// if (isatty(fileno(stdin)))
		// 	rline = readline("> ");
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// 	rline = ft_strtrim(line, "\n");
		// 	free(line);
		// }