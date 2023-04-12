/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 18:01:21 by lsinke        #+#    #+#                 */
/*   Updated: 2021/12/18 18:01:21 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>

// Character boolean functions
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
bool			ft_isspace(int c);

// Character manipulation functions
int				ft_toupper(int c);
int				ft_tolower(int c);

// String<->Anything
int				ft_atoi(const char *str);
unsigned int	ft_hextoui(const char *str);
char			*ft_itoa(int n);
float			ft_strtof(const char *str, char **end);

// String manipulation functions
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstlen);
size_t			ft_strlcat(char *dst, const char *src, size_t dstlen);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *str, const char *find, size_t n);
char			*ft_strdup(const char *str);
char			*ft_substr(const char *s, size_t start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *str, const char *set);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			**ft_split(const char *str, char c);
void			**ft_split_map(const char *s, char c,
					void *(*map)(char *), void (*del)(void *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_strtoupper(char *s);
void			ft_strtolower(char *s);
bool			strcontains(const char *str, char c);

// Memory functions
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *dst, size_t len);
void			ft_free_mult(void **a);
void			*ft_memset(void *dst, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_realloc(void *oldptr, size_t oldsize, size_t newsize);

// File write functions
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

// Simple math
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_abs(int n);
int				ft_interpolate_i(int a, int b, double p);
double			ft_interpolate_d(double a, double b, double p);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst,
					void *(*map)(void *), void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *nw);
void			ft_lstadd_back(t_list **lst, t_list *nw);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstdelelem(t_list **list, t_list *elem, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
int				ft_lstsize(t_list *lst);

uint32_t		binary_search(int32_t *arr, int32_t val, uint32_t size);

#endif /* LIBFT_H */
