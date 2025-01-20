typedef struct s_redirect
{
	int		type_redirect;//0,1,2,3 << < > >>
	char	*limiter;
	struct s_redirect *next;
}	t_redirect;

typedef struct s_exec
{
	char	*path;
	char	**cmd;
	char	**command;
	char	**env;
	struct s_redirect	*redirect;
	int		pipe[2];
	pid_t pid;
	struct s_exec *next;
}	t_exec;

t_redirect* handler_redirect(char *token) {
	//GEnerar una memoria e i
#if 0
	t_redirect *tmp;
	int i = 0;
	int j = 0;
	while (token[i])
	{
		if (token[i] == '<')
			j++;
		if (token[i] == '>')
			j++;
		if (token[i] == '>>')
			j++;
		if (token[i] == '<<')
			j++;
		i++;
	}
	tmp = malloc(sizeof(t_redirect) * j);
	//LUego llenar la memoria

	tmp = malloc (sizeof(t_redirect) * j);
	j = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '<' && token[i] == '<<' && token[i] == '>' && token[i] == '>>'){
			tmp->type_redirect = ft_type_redirect(token[i]);
			j = i + 1;
			while(token[j] == ' ') //SEguir moviendose hasta encontrar el siguiente espacio ">archivo" | "> archivo"
				j++;
			tmp->limiter = ft_substr(token, i,  j);
		}
		i++;
	}
	return tmp;
# else 1

	t_redirect *first_node;
	t_redirect *last_node;
	t_redirect *new_node;
	int i = 0;
	int j = 0;
	while (token[i])
	{
		if (token[i] == '<' && token[i] == '<<' && token[i] == '>' && token[i] == '>>'){
			new_node = malloc(sizeof(t_redirect));
			j = i + 1;
			while(token[j] == ' ') //Seguir moviendose hasta encontrar el siguiente espacio ">archivo" | "> archivo"
				j++;
			new_node->limiter = ft_substr(token, i,  j);
			new_node->type_redirect = ft_type_redirect(token[i]);
			new_node->next = NULL;
		}
		if (last_node)
			last_node->next = new_node;
		else if (!last_node)
			first_node = new_node;
		last_node = new_node;
		i++;
	}
	return first_node;
#endif

}
void execute_redirects(t_exec *data) {
	t_redirect *tmp = data->redirect;
	dup2(data->pipe[0], 0);
	if (data->pipe[0] != 0)
		close(data->pipe[0]);
	dup2(data->pipe[1], 1);
	if (data->pipe[1] != 0)
		close(data->pipe[1]);
	while (tmp)
	{
		if (tmp->type_redirect == 0) // <
		{
			data->pipe[0] = open(tmp->limiter, O_RDONLY);
			if (data->pipe[0] < 0)
				ft_error("Error opening file\n", 125, &data);
			dup2(data->pipe[0], 0);
			close(data->pipe[0]);
		}
		if (tmp->type_redirect == 1) // >
		{
			data->pipe[1] = open(tmp->limiter, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->pipe[1] < 0)
				ft_error("Error opening file\n", 125, &data);
			dup2(data->pipe[1], 1);
			close(data->pipe[1]);
		}
		if (tmp->type_redirect == 2) // >>
		{
			data->pipe[1] = open(tmp->limiter, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data->pipe[1] < 0)
				ft_error("Error opening file\n", 125, &data);
			dup2(data->pipe[1], 1);
			close(data->pipe[1]);
		}
		if (tmp->type_redirect == 3) // <<
		{
			//heredoc
		}
		tmp = tmp->next;
	}
}
t_exec* ft_init_execute(char **tokens)
{
	int i = 0;
	int type[2];
	type[0] = 0;
	type[1] = 0;
	t_exec *new_node = malloc(sizeof(t_exec)* (ft_size(tokens) + 1)); // "cat -l -a << EOF > out >> hout" | "ls << END" 

	while (tokens[i]) {
		new_node[i].redirect = handler_redirect(tokens[i]); // "cat -l -a << EOF > out >> hout" -> "cat -l -a" ¡¡¡¡¡¡ " << EOF > out >> hout cat -l -a"
		new_node[i].cmd = split(tokens[i], ' '); //"cat -l -a" 
		new_node[i].pipe[0] = 0;
		new_node[i].pipe[0] = 1;
		i++;
	}
	new_node[i].cmd = NULL;
	return new_node;
}

void create_pid (t_exec *data) {
		data->pid = fork();
		if (data->pid < 0)
			ft_error("Error creating process\n", 125, &data);
		if (data->pid == 0){
			execute_redirects(data);
			execve(data->path, data->cmd, data->env);
			exit(1);
		}

}


int	pipex(char**tokens, int cmd_len)
{
	t_exec	*data = ft_init_execute(tokens);
	t_exec	*head = data;
	int i = 0;
	int status = 0;	
	int tmp = 0;

	while (data[i].cmd)
	{
		if (i == 0 && data[i + 1].cmd != NULL) // (data[i].pipe[0]->0)"cat -e" data[i].pipe[1]-> 4 | data[i + 1].pipe[0] -> 3 (data[i+1])"grep -e" | "grep"
		{
			pipe(data[i].pipe);
			data[i + 1].pipe[0] = data->pipe[0];
			data[i].pipe[0] = 0;
		} else if (data[i + 1].cmd != NULL){
			close(data[i].pipe[1]);
			tmp = data[i].pipe[0];
			pipe(data[i].pipe);
			data[i + 1].pipe[0] = data->pipe[0];
			data[i].pipe[0] = tmp;
			data[i].pipe[1] = data[i].pipe[1];
		} else if (data[i + 1].cmd == NULL){
			if (data[i].pipe[0] != 0)
				close(data[i].pipe[0]);
			data[i].pipe[1] = 1;
		}
		create_pid(data);
		if (data->pipe[1] != 1)
			close(data->pipe[1]);

		data = data->next;
	}
	data = head;
	while (data)
	{
		waitpid(data->pid, &status, 0);
		data = data->next;
	}
	
	exit(WEIXTATUS(status));
}