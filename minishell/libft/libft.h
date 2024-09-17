/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gluisier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:27:38 by gluisier          #+#    #+#             */
/*   Updated: 2022/09/06 13:13:06 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include "printf/includes/ft_printf.h"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

char	*get_next_line(int fd);

int		ft_printf(const char *format, ...);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_lcs(char *s1, char *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);

t_list	*ft_lst_contains(t_list *lst, void *cont, int (*cmp)(void *, void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *));

typedef struct s_doublelist
{
	void				*content;
	struct s_doublelist	*prev;
	struct s_doublelist	*next;
}	t_dblst;

t_dblst	*ft_dblst_new(void *content);
int		ft_dblst_size(t_dblst *lst);
t_dblst	*ft_dblst_last(t_dblst *lst);
void	ft_dblst_addfront(t_dblst **alst, t_dblst *new);
void	ft_dblst_addback(t_dblst **alst, t_dblst *new);
char	**ltoa(t_dblst *lst);
t_dblst	*ft_atol(char **ar);

t_dblst	*ft_dblst_contains(t_dblst *lst, void *cont, int (*cmp)(void*, void*));
void	ft_dblst_delone(t_dblst *lst, void (*del)(void *));
void	ft_dblst_clear(t_dblst **lst, void (*del)(void *));
void	ft_dblst_append(t_dblst **lst, t_dblst *ap);

typedef struct s_stack
{
	t_dblst	*first;
	t_dblst	*last;
}	t_stack;

t_stack	*ft_stack_new(t_dblst *content);
void	ft_stack_destroy(t_stack **stack, void (*del)(void *));
size_t	ft_stack_size(t_stack *stack);
void	ft_stack_push(t_stack *stack, t_dblst *new);
t_dblst	*ft_stack_pop(t_stack *stack);

void	ft_stack_swap(t_stack *stack);
void	ft_stack_rotate(t_stack *stack);
void	ft_stack_rrotate(t_stack *stack);

void	ft_mergesort(int *ar, size_t size);

#endif
