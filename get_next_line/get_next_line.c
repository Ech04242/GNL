/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassara <tlassara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:14:18 by tlassara          #+#    #+#             */
/*   Updated: 2022/05/19 15:07:55 by tlassara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*end_buff(char *buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (0);
	}
	i++;
	j = 0;
	while (buff[i])
	{
		buff[j] = buff[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	return (buff);
}

static char	*end_line(char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	return (ft_substr(buff, 0, i));
}

static char	*check_buff(int fd, char *buff)
{
	int	end_file;


	if (!BUFFER_SIZE || fd <= 0)
		return (0);
	if (!buff)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char *));
		buff[0] = '\0';
	}
	if (!buff)
		return (0);
	if (!*buff)
		end_file = read(fd, buff, BUFFER_SIZE);
	if (!end_file)
	{
		free(buff);
		return (0);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			end_file;

	buff = check_buff(fd, buff);
	if (buff)
		end_file = 1;
	else
		return (0);
	line = ft_calloc(ft_strlen(buff), sizeof(char *));
	if (!line)
		return (0);
	while (!(ft_strchr(buff, '\n')) && *buff && end_file)
	{
		line = ft_strjoinfree(line, buff, 1);
		if (!line)
			return (0);
		end_file = read(fd, buff, BUFFER_SIZE);
		buff[end_file] = '\0';
	}
	if (end_file)
		line = ft_strjoinfree(line, end_line(buff), 3);
	buff = end_buff(buff);
	return (line);
}

int	main()
{
	size_t	fd;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	//printf("%s", str);
	 while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	//str2 = get_next_line(fd);
	close(fd);
	free(str);
	return (0);
}