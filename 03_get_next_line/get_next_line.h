
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 5

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_nl
{
	int		rd;
	char	*buf;
	char	*next_line;
	int		nl_pos;
}			t_nl;

char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_str_free(void *str);
char		*get_new_line(char *str, int *pos);
void		ft_bzero(void *b, size_t len);

#endif