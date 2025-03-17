#include "../../include/minishell.h"

int get_env(char *env_name, char **env, int last_exit)
{
	int i;

	i = -1;
	if (env_name[1] == '?')
		return (ft_itoa(last_exit));
	else if (contains_only(env_name, '$'))
		return (ft_strdup(env_name));
	else if (env_name[1] == '$')
		return (ft_itoa())
}