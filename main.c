/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhedhir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:26:26 by mkhedhir          #+#    #+#             */
/*   Updated: 2022/03/02 16:47:35 by mkhedhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	child1_process(int f1, char *cmd)
{
	dup2(f1
}

void	pipex(int f1, int f2)
{
	int	end[2];
	int	status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child1_process(f1,cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child2_process(f2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);	
}

int	main(int ac, char **ag, char **envp)
{
	int	f1;
	int	f2;

	f1 = open (ag[1], O_RDONLY);
	f2 = open (ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	pipex(f1, f2 , ag, envp);
	return (0);
}
