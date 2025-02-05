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

t_commande	*creator(t_tkn_lst *node, t_env *env)
{
	t_commande	*cmd;
	t_commande	*init;
	int			i;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	i = 0;
	init = cmd;
	while (node)
	{
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
		else if (node->token == T_PIPE)
		{
			cmd->next = cmd_init();
			if (!cmd->next)
				return (NULL);
			cmd = cmd->next;
			i = 0;
		}
		node = node->next;
	}
	return (init);
}
