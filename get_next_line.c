/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:18 by bessabri          #+#    #+#             */
/*   Updated: 2024/12/28 10:58:26 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_function(int fd, char *res)
{
	ssize_t	n;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	n = 1;
	while (!ft_strchr(res, '\n') && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(buffer);
			return (NULL);
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

char	*handle_newline(char *res)
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

char	*achb9a(char *res)
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
		return (0);
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
	static char	*s;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = read_function(fd, s);
	if (!s || s[0] == '\0')
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	line = handle_newline(s);
	if (!line)
		return (free(s), s = NULL, NULL);
	s = achb9a(s);
	return (line);
}

// int main()
// {
//     int fd;
//     char *res2;
//     fd = open("file.txt",O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return 1;
//     }
//     while ((res2 = get_next_line(fd)) != NULL)
//     {
//     	printf("%s",res2);
//         free(res2);
//     }

//     close (fd);    
// }
