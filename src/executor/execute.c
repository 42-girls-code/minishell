/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingrid <ingrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:12:41 by ilemos-c          #+#    #+#             */
/*   Updated: 2026/03/02 20:46:05 by ingrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	test_hard_code(void)
{
	//test ls -l | wc -l
	t_ast	*root;

	root = create_node(NODE_PIPE);
	root->left = create_node(NODE_CMD);
	root->left->args = ft_split("ls -l", ' ');
	root->right = create_node(NODE_CMD);
	root->right->args = ft_split("wc -l", ' ');
}

t_ast	*create_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return ;
	node->type = type;
	node->left = " ";
	node->right = " ";
}

int	execute_ast(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return(handle_pipe(node));
	if (node->type == NODE_CMD)
		return (handle_command(node));
	return (0);
}

// int	handle_pipe(t_ast *node)
// {

// }

int	handle_command(t_ast *node)
{
	if (is_builtin(node->args[0]) && !node->has_pipe)
		return (execute_builtin(node));
	else
		return	(execute_binary(node));
}

// int	is_builtin(char	*cmd)
// {
// 	if (ft_strcmp(cmd, "echo", 4) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "cd", 2) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "pwd", 3) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "export", 5) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "unset", 5) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "env", 3) == 0)
// 		return (1);
// 	if (ft_strcmp(cmd, "exit", 4) == 0)
// 		return (1);
// 	return (0);
// }

int	execute_builtin(t_ast *node)
{
	char	*cmd;

	cmd = node->args[0];
	if (ft_strcmp(cmd, "echo", 4) == 0)
		return (ft_echo(node->args));
	if (ft_strcmp(cmd, "cd", 2) == 0)
		return (ft_cd(node->args));
	if (ft_strcmp(cmd, "pwd", 3) == 0)
		return (ft_pwd());
	// if (ft_strcmp(cmd, "export", 5) == 0)
	// 	return (ft_export(node->args));
	// if (ft_strcmp(cmd, "unset", 5) == 0)
	// 	return (ft_unset(node->args));
	// if (ft_strcmp(cmd, "env", 3) == 0)
	// 	return (ft_env(g_minishell.env_list));
	// if (ft_strcmp(cmd, "exit", 4) == 0)
	// 	return (ft_exit());
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

// char	*ft_getenv(char *envp[])
// {
// 	int		i;
// 	char	*path_key;

// 	i = 0;
// 	path_key = "PATH=";
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], path_key, ft_strlen(path_key)))
// 			return (envp[i] + ft_strlen(path_key));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	execute_cmd(char *cmd_str, char *envp[])
// {
// 	char	**cmd_array;
// 	char	*full_path;

// 	cmd_array = ft_split(cmd_str, ' ');
// 	if (!cmd_array)
// 		exit(1);
// 	full_path = get_cmd_path(cmd_array[0], envp);
// 	if (!full_path)
// 	{
// 		ft_printf("%s: %s\n", cmd_array[0], strerror(errno));
// 		ft_free_array(cmd_array);
// 		exit(127);
// 	}
// 	execve(full_path, cmd_array, envp);
// 	perror("Execve failed\n");
// 	free(full_path);
// 	ft_free_array(cmd_array);
// 	exit(1);
// }

// void	ft_free_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	if (!array)
// 		return ;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// char	*get_cmd_path(char *cmd, char *envp[])
// {
// 	char	**paths_array;
// 	char	*path_result;
// 	char	*paths_str;
// 	int		i;

// 	paths_str = ft_getenv(envp);
// 	if (!paths_str)
// 		return (NULL);
// 	paths_array = ft_split(paths_str, ':');
// 	if (!paths_array)
// 		return (NULL);
// 	i = 0;
// 	while (paths_array[i])
// 	{
// 		path_result = join_path_cmd(paths_array[i], cmd);
// 		if (access(path_result, X_OK) == 0)
// 		{
// 			ft_free_array(paths_array);
// 			return (path_result);
// 		}
// 		free(path_result);
// 		i++;
// 	}
// 	ft_free_array(paths_array);
// 	return (NULL);
// }

// char	*join_path_cmd(char *path, char *cmd)
// {
// 	char	*aux;
// 	char	*path_cmd;

// 	aux = ft_strjoin(path, "/");
// 	if (!aux)
// 		return (NULL);
// 	path_cmd = ft_strjoin(aux, cmd);
// 	free(aux);
// 	return (path_cmd);
// }
