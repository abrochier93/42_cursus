#include "so_long.h"

void	ft_end_game(t_map *map)
{
	ft_put_str("So long, child...\n");
	mlx_destroy_window(map->mlx, map->win);
	free(map->map);
	exit(0);
}

void	ft_moved_into_collect(t_map *map, int x, int y)
{
	int	p_y;
	int	p_x;

	p_x = map->p_x;
	p_y = map->p_y;
	ft_remove_collect(&map->map[p_y][p_x], &map->map[p_y + y][p_x + x]);
	ft_put_str("You collected an object!\n");
	map->n_collect -= 1;
	map->found_collect = 1;
}

void	ft_moved_into_exit(t_map *map, int x, int y)
{
	int	p_y;
	int	p_x;

	p_y = map->p_y;
	p_x = map->p_x;
	if (map->n_collect == 0)
	{
		ft_found_exit(&map->map[p_y][p_x], &map->map[p_y + y][p_x + x]);
		map->end_game = 1;
		ft_put_str("You found an exit!\n");
		ft_put_str("Press any key to exit.\n");
	}
	else
		ft_put_str("Collect all objects first.\n");
}

void	ft_move_player(t_map *map, int x, int y)
{
	int	p_y;
	int	p_x;

	p_y = map->p_y;
	p_x = map->p_x;
	map->found_collect = 0;
	ft_check_if_end(map);
	if (map->map[p_y + y][p_x + x] != '1')
	{
		map->moves += 1;
		if (map->map[p_y + y][p_x + x] == '0')
			ft_swap_tiles(&map->map[p_y][p_x], &map->map[p_y + y][p_x + x]);
		else if (map->map[p_y + y][p_x + x] == 'C')
			ft_moved_into_collect(map, x, y);
		else if (map->map[p_y + y][p_x + x] == 'E')
			ft_moved_into_exit(map, x, y);
	}
	ft_populate_map(map, 40, 0);
	ft_put_str("Moves: ");
	ft_putnbr_fd(map->moves, 1);
	ft_put_str("\n");
}
