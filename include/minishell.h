/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:06:36 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 14:58:55 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "token.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "gc_collec.h"

int		*get_exit_status(void);

int		*get_exit_status(void);

//builtins
int		is_builtin(char *cmd);
void	run_builtins(t_exec_cmd *cmd, char ***envp);
void	exec_cd(t_exec_cmd *cmd);
void	exec_export(t_exec_cmd *cmd, char ***envp);
void	exec_unset(t_exec_cmd *cmd, char ***envp);
void	exec_echo(t_exec_cmd *cmd);
void	exec_pwd(void);
void	exec_exit(t_exec_cmd *cmd);
void	add_env_var(char ***envp, char *value);

// utils
char	*get_env_var(char *key, char **envp);
char	**ft_split2(char const *s, char *delimiters);
void	panic(char *error_msg);
int		fork_plus(void);
void	reset_standard_fds(int in, int out, int err);
char	*ft_char_to_str(char c);
void	print_string_array(char **prompt);
void	print_export(char **arr);
void	print_list(t_list *list);
void	print_tokens(t_list *tokens);
void	free_str_arr(char **arr);
void	free_token(void *ptr);
char	**copy_env(char *envp[]);
void	update_exit_status(int *exit_status);
void	ft_list_remove(t_list **begin_list);

//execute
char	*read_prompt(void);
void	run(t_cmd *cmd, char ***envp);
void	run_exec(t_exec_cmd *exec, char *envp[]);
void	run_pipe(t_pipe_cmd *pipe_cmd, char *envp[]);
void	run_back(t_back_cmd *back, char *envp[]);
void	run_seq(t_seq_cmd *seq, char *envp[]);
void	run_redir(t_redir_cmd *redir, char *envp[]);
void	run_heredoc(t_heredoc_cmd *heredoc, char *envp[]);
void	run_cmds(t_cmd *cmd, char ***envp);

// pipex_utils
char	*get_envp(char *key, char *envp[]);
char	*get_cmd_path(char *cmd, char *envp[]);
char	**get_paths(char *envp[]);
void	handle_error(char *msg, int exit_code);

// parse
void	print_ast(t_cmd *cmd, int depth);
t_cmd	*parse_cmd(t_list **list);
t_cmd	*parse_line(t_list **list);
t_cmd	*parse_block(t_list **list);
t_cmd	*parse_pipe(t_list **liste);
t_cmd	*parse_exec(t_list **liste);
t_cmd	*parse_redir(t_list **list, t_cmd *cmd);
t_cmd	*exec_cmd_init(char **cmd_args);
t_cmd	*redir_cmd_init(t_cmd *cmd, char *file, int fd, int mode);
t_cmd	*heredoc_cmd_init(t_cmd *cmd, char *value);
t_cmd	*pipe_cmd_init(t_cmd *left, t_cmd *right);
t_cmd	*seq_cmd_init(t_cmd *left, t_cmd *right);
t_cmd	*back_cmd_init(t_cmd *left);

// tokens
char	*expand_str(char *str, char **envp);
t_token	*token_init(int type, char *value);
t_list	*tokenizer(char *prompt, char **envp);
int		get_token_type(char c);
char	*open_quote_prompt(char *input, char qoute_type);
char	*open_heredoc_prompt(char *delimeter);
char	*parse_qoutes(char **prompt, char quote_type, char **envp);
t_list	*parse_text(char **prompt, char **envp);
t_list	*parse_operator(char **prompt);
t_list	*parse_heredoc(char **prompt);
char	is_symbol(char *str, int in_quotes);
void	skip_whitespace(char **prompt);

// signals
void	setup_signals(int in_child);

#endif