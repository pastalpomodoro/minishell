#include "../../includes/minishell.h"

t_commande	*cmd_init(void)
{
	t_commande	*cmd;

	cmd = malloc(sizeof(t_commande));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->outfile = NULL;
	cmd->fd_out = 1;
	cmd->outfile_type = 0;
	cmd->infile = 0;
	cmd->exit_code = 0;
	return (cmd);
}

void	free_cmd_node(t_commande **cmd)
{
	if ((*cmd)->infile > 2)
		close((*cmd)->infile);
	if ((*cmd)->outfile)
		free((*cmd)->outfile);
	if ((*cmd)->path)
		free((*cmd)->path);
	if ((*cmd)->cmd)
		free_double_tab((*cmd)->cmd);
	free((*cmd));
}

void	free_cmd(t_commande **cmd)
{
	t_commande	*tmp;

	while ((*cmd))
	{
		tmp = (*cmd)->next;
		free_cmd_node(cmd);
		(*cmd) = tmp;
	}
}
int is_pipe(t_commande **cmd, t_tkn_lst *next, t_tkn_lst *node, int *i)
{
	if (node->token == T_PIPE)
	{
		if (next)
		{
			if (next->token != T_LITERAL && next->token != T_REDIRECT)
				return (ft_printf("bash: syntax error near unexpected token `%s'\n", next->value), 0);
		}
		(*cmd)->next = cmd_init();
		if (!(*cmd)->next)
			return (0);
		(*cmd) = (*cmd)->next;
		*i = 0;
	}
	return (1);
}
t_commande	*creator(t_tkn_lst *node, t_env *env)
{
	t_commande	*cmd;
	t_commande	*init;
	t_tkn_lst	*next;
	int			i;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	i = 0;
	init = cmd;
	while (node)
	{
		next = node->next;
		if (node->token == T_REDIRECT && cmd->exit_code == 0)
		{
			if (redirect(node, &cmd) == -2)
				return (free_cmd(&init), NULL);
			node = node->next;
		}
		else if (node->token == T_LITERAL && i == 0 && cmd->exit_code == 0)
		{
			if (cmd_creator(node, &cmd, env) == -2)
				return (free_cmd(&init), NULL);
			i = 1;
		}
		else if (is_pipe(&cmd, next, node, &i) == 0)
			return (free_cmd(&init), NULL);
		else if (node->token == T_AND_OR)
			ft_printf("Faire le bonus");
		node = node->next;
	}
	return (init);
}
