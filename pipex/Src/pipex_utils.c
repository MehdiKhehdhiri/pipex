/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhedhir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:32:06 by mkhedhir          #+#    #+#             */
/*   Updated: 2022/05/24 20:32:12 by mkhedhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	bad_argument(void)
{
	ft_putstr_fd("\tError: Bad argument\n", 2);
	ft_putstr_fd("\tEx: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("\t./pipex \"here_doc\" <LIMITER> ", 1);
	ft_putstr_fd("<cmd> <cmd1> <cmdn> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

int	open_file(char *ag, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(ag, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(ag, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(ag, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		rd;
	char	c;

	i = 0;
	rd = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	rd = read(0, &c, 1);
	while (rd && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		rd = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (rd);
}
