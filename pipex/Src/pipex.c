/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhedhir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:31:40 by mkhedhir          #+#    #+#             */
/*   Updated: 2022/05/24 20:31:45 by mkhedhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*right_path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		right_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(right_path, F_OK) == 0)
			return (right_path);
		free(right_path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

void	child_process(char *ag, char **cmd1)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(ag, cmd1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc(char *ag)
{
	pid_t	read;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error();
	read = fork();
	if (read == -1)
		error();
	if (read == 0)
	{
		while (get_next_line(&line))
		{
			if (strncmp(line, ag, ft_strlen(ag)) == 0)
				exit(0);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **ag, char **envp)
{
	int	f1;
	int	f2;
	int	i;

	if (ac < 5)
		bad_argument();
	if (ft_strncmp(ag[1], "here_doc", 6) == 0)
	{
		i = 3;
		f2 = open_file(ag[ac - 1], 0);
		here_doc(ag[2]);
	}
	else
	{
		i = 2;
		f1 = open_file(ag[1], 2);
		f2 = open_file(ag[ac - 1], 1);
		dup2(f1, STDIN_FILENO);
	}
	while (i < ac - 2)
		child_process(ag[i++], envp);
	dup2(f2, STDOUT_FILENO);
	execute(ag[ac - 2], envp);
	bad_argument();
}
