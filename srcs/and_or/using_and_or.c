#include "../../includes/minishell.h"
void	show_cmds(t_commande *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->path)
			ft_printf("PATH: %s\n", cmd->path);
		if (cmd->cmd)
		{
			i = -1;
			while (i++, cmd->cmd[i])
				ft_printf("CMD: %s\n", cmd->cmd[i]);
		}
		ft_printf("CMD_TYPE: %d\nINFILE: %d\n",cmd->cmd_type, cmd->infile);
		ft_printf("OUTFILE: %s, OUTFILE_TYPE: %d\n", cmd->outfile,
				cmd->outfile_type);
		ft_printf("EXIT_CODE: %d\n", cmd->exit_code);
		cmd = cmd->next;
		printf("------------------------------------------\n");
	}
}
void exec_and_or(t_env **lst_env, t_tkn_lst *node, char **env)
{
	t_and_or	*and_or;
    t_and_or    *before;
    int         exit_code;

    exit_code = 0;
	and_or = init_and_or();
	if (!and_or)
		return ;
    //echo je mange une pomme | wc >outfile && <infile grep je >outfile
    while (node)
    {
        and_or->cmd = creator(&node, *lst_env);
        exit_code = and_or->cmd->exit_code;
        if (and_or->cmd)
        {
            show_cmds(and_or->cmd);
            exit_code = exec_manage(and_or->cmd, lst_env, env);
            free_cmd(&and_or->cmd);
        }
        ft_printf("exit_code: %d\n", exit_code);
        printf("------------------NEXT--------------------\n");
        if (node && !ft_strcmp(node->value, "&&") && exit_code != 0)
            break;
        if (node && !ft_strcmp(node->value, "||") && exit_code == 0)
            break;
        if (node && (!ft_strcmp(node->value, "&&") || !ft_strcmp(node->value, "||")))
        {
            before = and_or;
            and_or->next = init_and_or();
            and_or = and_or->next;
            free_node_and_or(before);
            node = node->next;
        }
    }
    free_node_and_or(and_or);
}
