/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:18 by bessabri          #+#    #+#             */
/*   Updated: 2024/12/29 11:39:54 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_function(int fd, char *res)
{
	ssize_t	n;
	char	*buffer;
	char	*tmp;

	buffer = malloc((size_t)(BUFFER_SIZE)+1);
	if (!buffer)
		return (0);
	n = 1;
	while (!ft_strchr(res, '\n') && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			return (free(buffer), free(res), NULL);
		}
		buffer[n] = '\0';
		tmp = ft_strjoin(res, buffer);
		if (!tmp)
			return (free(buffer), free(res), NULL);
		free(res);
		res = tmp;
	}
	free(buffer);
	return (res);
}

static char	*handle_newline(char *res)
{
	char	*newline;
	int		i;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	newline = malloc(i + 2);
	if (!newline)
		return (free(res), NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		newline[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
	{
		newline[i] = res[i];
		i++;
	}
	newline[i] = '\0';
	return (newline);
}

static char	*achb9a(char *res)
{
	int		i;
	int		j;
	char	*lib9a;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\0' || res[i + 1] == '\0')
	{
		free(res);
		return (NULL);
	}
	lib9a = malloc(ft_strlen(res) - i + 1);
	if (!lib9a)
		return (free(res), NULL);
	j = 0;
	i++;
	while (res[i])
	{
		lib9a[j++] = res[i++];
	}
	lib9a[j] = '\0';
	free(res);
	return (lib9a);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
	{
		return (NULL);
	}
	s[fd] = read_function(fd, s[fd]);
	if (!s[fd] || s[fd][0] == '\0')
	{
		free(s[fd]);
		s[fd] = NULL;
		return (NULL);
	}
	line = handle_newline(s[fd]);
	if (!line)
		return (free(s[fd]), s[fd] = NULL, NULL);
	s[fd] = achb9a(s[fd]);
	return (line);
}

