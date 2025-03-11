/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:41:43 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/11 11:13:04 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H

typedef enum e_token_type{
	TEXT,
	EXEC,
	REDIR,
	PIPE,
	SEQ,
	BACK,
	PARENS,
	BUILTIN,
	HERE_DOC,
}	t_token_type;

typedef struct	s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct	s_cmd
{
	int		type;
}			t_cmd;

typedef struct	s_exec_cmd
{
	int		type;
	char	**cmd_args;		// ["cat", "-e", "Makefile", NULL];
}			t_exec_cmd;

typedef struct	s_builtin_cmd
{
	int		type;
	char	**cmd_args;		// ["cat", "-e", "Makefile", NULL];
}			t_builtin_cmd;

typedef struct	s_redir_cmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		is_heredoc;
	char	*heredoc;
	int		fd;				// STDIN | STDOUT
	int		mode;			// O_WRONLY | O_CREATE | O_APPEND}	
}		t_redir_cmd;

typedef struct	s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe_cmd;

typedef struct	s_seq_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_seq_cmd;

typedef struct	s_back_cmd
{
	int		type;
	t_cmd	*left;
}			t_back_cmd;

typedef struct	s_heredoc_cmd
{
	int		type;
	t_cmd	*cmd;
	char	*value;
}			t_heredoc_cmd;

#endif