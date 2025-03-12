/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:30:23 by cwolf             #+#    #+#             */
/*   Updated: 2025/03/11 15:36:52 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GB_COLLEC_H
# define GB_COLLEC_H

typedef struct s_gc_node
{
	void *ptr;
	struct s_gc_node *next;
}				t_gc_node;

typedef struct s_gc_manager
{
    t_gc_node *head;
} 			t_gc_manager;

void *gc_alloc(int size);
void gc_free_all(void);
void gc_free_one(void *ptr);
t_gc_manager* get_gc_instance();
void gc_print_list(void);

//Functions

char	*ft_substr_gc(char const *s, unsigned int start, size_t len);
char	*ft_strdup_gc(const char *s1);
char	*ft_strjoin_gc(char const *s1, char const *s2);
t_token	*token_init_gc(int type, char *value);
t_list	*ft_lstnew_gc(void *content);
t_token	*token_init_gc(int type, char *value);
char	**ft_split_gc(char const *s, char c);
char	*ft_itoa_gc(int n);



#endif