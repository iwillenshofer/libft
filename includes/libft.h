/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 06:31:07 by iwillens          #+#    #+#             */
/*   Updated: 2024/05/31 12:02:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_strtoupper(char *str);
int		ft_isprint(int c);
int		ft_lstsize(t_list *lst);
int		ft_atoi(const char *str);
t_list	*ft_lstlast(t_list *lst);
size_t	ft_strlen(const char *s);
t_list	*ft_lstnew(void *content);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
t_list	*ft_lstmap(t_list *lst,
			void *(*f)(void *), void (*del)(void *));
char	*ft_strnstr(const char *haystack,
			const char *needle, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_islower(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
int		ft_isblank(int c);
void	ft_putendl(char *s);
char	*ft_strndup(const char *s1, size_t n);
int		ft_isnumeric(char *str);
char	*ft_itoa_base(long long int n, size_t base, char optsigned);

/*
**	add-ons
*/
size_t	ft_numlen_base(long long n, char *base);
ssize_t	ft_putnbr_base(long long n, char *base, int fd);
size_t	ft_strfind_first(const char *str, const char *set);
ssize_t	ft_putchar_fd_count(char c, int fd);
ssize_t	ft_itoa_base_buf(long long n, char *base, char *buf);

int		ft_ishex(int c);
size_t	ft_arglen(char **arg);
int		ft_ishex(int c);;
double	ft_sqrt(double number);
char	*ft_notnumeric(char *s);
char	*ft_nothex(char *s);
void	ft_puthex(size_t nb);
char	*ft_strcpy(char *dst, char *src);
size_t	ft_atoul(const char *str);
void    ft_putbits(unsigned char byte);
void	ft_putbytes(void *bytes, size_t size);
void	ft_puthexbyte(unsigned char c);
void	ft_puthex_bytes(void *bytes, size_t size, size_t space, size_t carr);
int     ft_strcmp(const char *s1, const char *s2);

#endif
