/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntothmur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:01:33 by ntothmur          #+#    #+#             */
/*   Updated: 2019/01/19 15:10:05 by ntothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_writeline(char **tmp, char **line, char *str)
{
	if ((*tmp = ft_strchr(str, '\n')))
	{
		if (!(*line = ft_strsub(str, 0, (*tmp - str))) ||
							!(*tmp = ft_strdup(*tmp + 1)))
		{
			ft_strdel(&str);
			return (-1);
		}
		ft_strdel(&str);
		return (1);
	}
	else if (*str)
	{
		if (!(*line = ft_strdup(str)))
			return (-1);
		ft_strdel(&str);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char		*str;
	char		buf[BUFF_SIZE + 1];
	static char	*tmp[OPEN_MAX];
	int			i;

	if ((read(fd, buf, 0) < 0) || fd > OPEN_MAX || BUFF_SIZE == 0)
		return (-1);
	if (tmp[fd] == NULL)
	{
		if (!(tmp[fd] = ft_strnew(0)))
			return (-1);
	}
	str = tmp[fd];
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!(str = ft_strjoin(tmp[fd], buf)))
			return (-1);
		ft_strdel(&tmp[fd]);
		if (ft_strchr(str, '\n') != NULL)
			break ;
		tmp[fd] = str;
	}
	return (ft_writeline(&tmp[fd], line, str));
}
