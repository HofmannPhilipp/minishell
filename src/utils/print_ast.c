/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:16:13 by phhofman          #+#    #+#             */
/*   Updated: 2025/03/16 17:27:35 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// const char* cmd_type_to_str(int type)
// {
// 	switch (type) {
// 		case TEXT: return "TEXT";
// 		case EXEC: return "EXEC";
// 		case REDIR: return "REDIR";
// 		case PIPE: return "PIPE";
// 		case SEQ: return "SEQ";
// 		case BACK: return "BACK";
// 		case PARENS: return "PARENS";
// 		case BUILTIN: return "BUILTIN";
// 		case HERE_DOC: return "HERE_DOC";
// 		default: return "UNKNOWN";
// 	}
// }

// void print_ast(t_cmd *cmd, int depth)
// {
// 	if (!cmd) return;

// 	// Einrückung basierend auf der Tiefe im Baum
// 	for (int i = 0; i < depth; i++) {
// 		printf("  ");
// 	}

// 	// Ausgabe des aktuellen Knotens
// 	printf("%s", cmd_type_to_str(cmd->type));

// 	switch (cmd->type) {
// 		case EXEC: {
// 			t_exec_cmd *exec_cmd = (t_exec_cmd *)cmd;
// 			printf(": ");
// 			for (int i = 0; exec_cmd->cmd_args[i]; i++) {
// 				printf("%s ", exec_cmd->cmd_args[i]);
// 			}
// 			printf("\n");
// 			break;
// 		}
// 		case BUILTIN: {
// 			t_builtin_cmd *builtin_cmd = (t_builtin_cmd *)cmd;
// 			printf(": ");
// 			for (int i = 0; builtin_cmd->cmd_args[i]; i++) {
// 				printf("%s ", builtin_cmd->cmd_args[i]);
// 			}
// 			printf("\n");
// 			break;
// 		}
// 		case REDIR: {
// 			t_redir_cmd *redir_cmd = (t_redir_cmd *)cmd;
// 			printf(": %s, fd: %d, mode: %d\n", redir_cmd->file, 
// 	redir_cmd->fd, redir_cmd->mode);
// 			print_ast(redir_cmd->cmd, depth + 1);
// 			break;
// 		}
// 		case PIPE: {
// 			t_pipe_cmd *pipe_cmd = (t_pipe_cmd *)cmd;
// 			printf("\n");
// 			print_ast(pipe_cmd->left, depth + 1);
// 			print_ast(pipe_cmd->right, depth + 1);
// 			break;
// 		}
// 		case SEQ: {
// 			t_seq_cmd *seq_cmd = (t_seq_cmd *)cmd;
// 			printf("\n");
// 			print_ast(seq_cmd->left, depth + 1);
// 			print_ast(seq_cmd->right, depth + 1);
// 			break;
// 		}
// 		case BACK: {
// 			t_back_cmd *back_cmd = (t_back_cmd *)cmd;
// 			printf("\n");
// 			print_ast(back_cmd->left, depth + 1);
// 			break;
// 		}
// 		case HERE_DOC: {
// 			t_heredoc_cmd *heredoc_cmd = (t_heredoc_cmd *)cmd;
// 			printf(": Content: %s\n", heredoc_cmd->value);
// 			print_ast(heredoc_cmd->cmd, depth + 1);
// 			break;
// 		}
// 		default:
// 			printf("\n");
// 			break;
// 	}
// }
