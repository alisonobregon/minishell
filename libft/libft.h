/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:40:01 by gongarci          #+#    #+#             */
/*   Updated: 2024/09/04 20:27:52 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <math.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*<ctype.h>*/
int		ft_isalpha(int i);
int		ft_isdigit(int i);
int		ft_isalnum(int i);
int		ft_isascii(int i);
int		ft_toupper(int i);
int		ft_tolower(int i);
int		ft_isprint(int i);
int		ft_blank(int c);
/*<string.h>*/
int		ft_strlen(const char *str);
int		ft_empty(char *argv);
int		ft_len(char	**array);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_int_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t bytes_copied);
int		ft_memcmp(const void *dest, const void *src, size_t n_bytes);
void	*ft_memchr(const void *s, int c, size_t n_bytes);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		int_max(int a, int b);
// GNL
char	*get_next_line(int fd);
int		ft_gnlstrlen(const char *str);
char	*ft_gnlstrdup(const char *str);
void	*ft_gnlmemcpy(void *dest, const void *src, size_t bytes);
void	*ft_gnlmemset(void *b, int c, size_t len);
int		allocate_memory(char **buffer, char **line);
int		join_and_check(char *buffer, char **line);
int		reader(char **buffer, char **line, int fd);
char	*free_memory(char **p);
char	*ft_gnlstrjoin(char *s1, char *s2, int len2);
// printf
int		ft_printf(char const *str, ...);
void	ft_putchar(char c, int *len);
void	ft_string(char *args, int *len);
void	ft_putnbr(int number, int *len);
void	ft_unsigned_int(unsigned int number, int *len);
void	ft_puthexa(unsigned int number, char c, int *len);
void	ft_putmem(unsigned long long n, int *len);
int		ft_unprintf(int aux, int *len);

#endif