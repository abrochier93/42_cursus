
#include "so_long.h"

int	ft_count_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_open_for_validation(char	*file, int *size)
{
	int	fp;

	fp = open(file, O_RDONLY);
	if (fp == -1)
	{
		ft_file_error();
		exit(0);
	}
	else
	{
		ft_validate_map(fp, size);
		if (close(fp) != 0)
		{
			perror("Error\n");
			exit(0);
		}
	}
}

void	ft_var_counter(char line_c, int *e_num, int *c_num, int *p_num)
{
	if (line_c == 'E')
		*e_num += 1;
	else if (line_c == 'C')
		*c_num += 1;
	else if (line_c == 'P')
		*p_num += 1;
}

void	ft_check_min_chars(char *line)
{
	static int	e_num;
	static int	c_num;
	static int	p_num;
	int			i;

	if (!e_num)
		e_num = 0;
	if (!c_num)
		c_num = 0;
	if (!p_num)
		p_num = 0;
	if (line[0] == '\0' && (e_num == 0 || c_num == 0 || p_num == 0))
	{
		if (e_num == 0)
			ft_exit_error();
		if (p_num == 0)
			ft_player_error();
		if (c_num == 0)
			ft_collectible_error();
		exit(0);
	}
	i = 0;
	while (line[i++] != '\0')
		ft_var_counter(line[i], &e_num, &c_num, &p_num);
}

void	ft_validate_map(int file, int *size)
{
	char	*line;
	char	*previous_line;
	previous_line = NULL;
	while (1)
	{
		line = get_next_line(file);
		if (line == NULL)
		{
			ft_check_min_chars("");
			break ;
		}
		*size += ft_count_chars(line + 1);
		if (!previous_line)
			ft_check_horizontal_border(line);
		else
			ft_check_middle_line(line);
		ft_check_map_length(line);
		ft_check_min_chars(line);
		ft_check_foreign_chars(line);
		previous_line = line;
	}
	ft_check_horizontal_border(previous_line);
	free(line);
}
