/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:06:02 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:21:28 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	score_line(t_stacks *stacks, int nb, int **line)
{
	int	i;
	int	score;

	*line = malloc((nb + 1) * sizeof(**line));
	if (!*line)
		return (-2);
	i = 0;
	while (i < nb + 1)
	{
		(*line)[i] = -1;
		i++;
	}
	score = score_recur(stacks, nb, nb, line);
	if (score == -2)
	{
		free(*line);
		*line = (void *) 0;
	}
	return (score);
}

int	score_recur(t_stacks *stacks, int step, int nb, int **line)
{
	int	*new;
	int	i;
	int	score;
	int	score_tab[2];

	if (step == 0)
		return (stop_recur(stacks, line, nb));
	i = 0;
	while ((*line)[i] != -1)
		i++;
	new = tab_int_copy(*line, nb + 1);
	if (!new)
		return (-2);
	new[i] = int_content(stacks->a);
	move(stacks, RA, 0);
	score_tab[0] = -3;
	if ((*line)[0] == -1 || new[i - 1] < new[i])
		score_tab[0] = score_recur(stacks, step - 1, nb, &new);
	score_tab[1] = score_recur(stacks, step - 1, nb, line);
	move(stacks, RRA, 0);
	score = choose_best_score(score_tab, line, &new);
	return (score);
}

int	stop_recur(t_stacks *stacks, int **line, int nb)
{
	int	i;
	int	sep;

	i = 0;
	while (i++ < nb)
		move(stacks, RRA, 0);
	sep = 0;
	while ((*line)[sep] != -1)
		sep++;
	(*line)[nb] = sep;
	i = 0;
	while (i++ < nb)
	{
		if (!is_in_tab(*line, int_content(stacks->a), nb))
			(*line)[sep++] = int_content(stacks->a);
		move(stacks, RA, 0);
	}
	return (score_tab(*line, nb));
}

int	score_tab(int *line, int nb)
{
	int	i;
	int	pivot;

	pivot = 1;
	i = line[nb];
	if (i < nb - 1 && line[i] < line[i + 1])
			pivot = -1;
	i++;
	while (i < nb - 1)
	{
		if (line[i] * pivot < line[i + 1] * pivot)
			return (-1);
		i++;
	}
	return (line[nb]);
}

int	choose_best_score(int *score, int **line, int **new)
{
	if (score[0] > score[1])
	{
		free(*line);
		*line = *new;
	}
	else
		free(*new);
	*new = (void *) 0;
	if (score[1] == -2 || score[0] == -2)
		return (-2);
	if (score[0] > score[1])
		return (score[0]);
	return (score[1]);
}