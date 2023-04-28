/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrochie <abrochie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:06:40 by abrochie          #+#    #+#             */
/*   Updated: 2023/04/24 14:43:57 by abrochie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_no_exit(void)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Exit number is NOT valid.\n", 1);
}
