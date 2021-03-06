/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdikilu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:07:28 by fdikilu           #+#    #+#             */
/*   Updated: 2017/02/23 18:49:48 by fdikilu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	print_tetri(t_list *point, char *soluce, char lettre, int *tab_arg)
{
	int		str_index;

	if (!point)
		return (1);
	else
	{
		str_index = ((int *)point->content)[1] *
			(tab_arg[0] + 1) + ((int *)point->content)[0] + tab_arg[1];
		if (str_index >= ft_strlen(soluce))
			return (-1);
		if (soluce[str_index] == '.')
		{
			if (print_tetri(point->next, soluce, lettre, tab_arg) == 1)
			{
				soluce[str_index] = lettre;
				return (1);
			}
			else
				return (0);
		}
		else
			return (0);
	}
}

static int	place_tetri(t_tetri *tetriminos, char *soluce, int s_width, int i)
{
	int		print;
	int		tab_arg[2];

	tab_arg[0] = s_width;
	tab_arg[1] = i;
	print = print_tetri(tetriminos->point, soluce, tetriminos->lettre, tab_arg);
	if (print == 1)
		return (1);
	else if (print == -1)
		return (0);
	else
		return (place_tetri(tetriminos, soluce, s_width, i + 1));
}

static void	rm_bad_tetri(char *soluce, char lettre)
{
	int		i;

	i = 0;
	while (soluce[i])
	{
		if (soluce[i] >= lettre && soluce[i] <= 'Z')
			soluce[i] = '.';
		i++;
	}
}

int			solve(t_tetri **tab_tetri, \
	char *soluce, int index_tab, int *tab_arg)
{
	int		i;

	i = 0;
	if (index_tab == tab_arg[0])
		return (place_tetri(tab_tetri[index_tab], soluce, tab_arg[1], i));
	else
	{
		while (i < (tab_arg[1] * tab_arg[1]))
		{
			if (!(place_tetri(tab_tetri[index_tab], soluce, tab_arg[1], i)))
				return (0);
			if (solve(tab_tetri, soluce, index_tab + 1, tab_arg))
				return (1);
			i++;
			rm_bad_tetri(soluce, tab_tetri[index_tab]->lettre);
		}
		return (0);
	}
}
