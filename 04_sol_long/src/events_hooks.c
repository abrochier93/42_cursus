#include "so_long.h"

int	ft_close_window(t_map *map)
{
	ft_end_game(map);
	return (1);
}

int	ft_key_event(t_map *map, int py, int px, int direction)
{
	ft_move_player(map, py, px);
	map->p_direction = direction;
	ft_populate_map(map, 40, 0);
	return (1);
}

int	ft_keyboard_events(int key, t_map *map)
{
	if (key == 65307 || key == 53)
		ft_close_window(map);
	if (map->p_death != 1 && map->end_game != 1)
	{
		if (key == 119 || key == 65362 || key == 13 || key == 126)
			ft_key_event(map, 0, -1, 0);
		else if (key == 100 || key == 65363 || key == 2 || key == 124)
			ft_key_event(map, 1, 0, 1);
		else if (key == 115 || key == 65364 || key == 1 || key == 125)
			ft_key_event(map, 0, 1, 2);
		else if (key == 97 || key == 65361 || key == 0 || key == 123)
			ft_key_event(map, -1, 0, 3);
	}
	else
		ft_close_window(map);
	return (1);
}

void	ft_listen_events(t_map *map)
{
	mlx_hook(map->win, 02, (1L << 0), ft_keyboard_events, map);
	mlx_hook(map->win, 17, (1L << 8), ft_close_window, map);
}