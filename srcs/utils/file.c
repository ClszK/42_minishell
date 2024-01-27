/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeholee <jeholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:19:42 by jeholee           #+#    #+#             */
/*   Updated: 2024/01/28 02:54:40 by jeholee          ###   ########.fr       */
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
void	child_heredoc_process(char *end_id, int tmp_fd)
{
	char	*rline;
	size_t	len;

	errno = 0;
	signal(SIGINT, heredoc_handler);
	len = ft_strlen(end_id);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		rline = get_next_line(STDIN_FILENO);
		if (rline == NULL && errno != 0)
			perror_exit("minishell");
		if (rline == NULL || 
			(len == ft_strlen(rline) - 1 && \
			!ft_strncmp(rline, end_id, len)))
		{
			free(rline);
			exit(0);
		}
		write(tmp_fd, rline, ft_strlen(rline));
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
		errno = 0;
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (errno)
		{
			print_strerror(filename, NULL);
			return (-1);
		}
	}
	if (errno == EACCES || errno == ENAMETOOLONG)
		return (-1);
	return (fd);
}

void	delete_heredoc(void)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;
	char			tmp_path[255];
	size_t			tmp_size;

	dir_info = opendir("/Users/jeholee/Documents/42_minishell/tmp/");
	if (!dir_info)
		return ;
	dir_entry = readdir(dir_info);
	while (dir_entry)
	{
		ft_strcpy(tmp_path, "/Users/jeholee/Documents/42_minishell/tmp/");
		if (!ft_strncmp("here_doc_tmp", dir_entry->d_name, 12))
		{
			tmp_size = ft_strlen(tmp_path) + ft_strlen(dir_entry->d_name) + 1;
			ft_strlcat(tmp_path, dir_entry->d_name, tmp_size);
			unlink(tmp_path);
		}
		dir_entry = readdir(dir_info);
	}
	closedir(dir_info);
}
