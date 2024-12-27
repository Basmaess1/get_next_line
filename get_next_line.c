/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:18 by bessabri          #+#    #+#             */
/*   Updated: 2024/12/28 00:18:24 by bessabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
char *read_function(int fd, char *res)
{
    ssize_t	n;
    char    *buffer;
    
    buffer = malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return (0);
    while (!ft_strchr(res,'\n'))
    {
        n = read(fd, buffer,BUFFER_SIZE);
        if (n == -1)
        {
            free(buffer);
            return (NULL);
        }
	if (n == 0)
		break;
        buffer[n]='\0';
        res = ft_strjoin(res,buffer);
    }
    free(buffer);
    return (res);
} 

char    *handle_newline(char *res)
{
    char	*newline;
    int		i;

    i = 0;
    while (res[i] && res[i]!= '\n')
        i++;
    newline = malloc(i + 2);
    if (!newline)
    return (0);
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
char    *achb9a(char *res)
{
    int total_size;
    int i;
    int j;
    char    *lib9a;

    i = 0;
    while (res[i] && res[i]!= '\n')
        i++;
    if (res[i] == '\0' || res[i + 1] == '\0')
    {
        free(res);
        return (0);
    }
    total_size = ft_strlen(res);
    lib9a = malloc(total_size - i + 1);
    if (!lib9a)
    {
        free(res);
        return (0);
    }
    i++;
    j = 0;
    while (res[i])
    {
        lib9a[j] = res[i];
        i++;
        j++;
    }
    lib9a[j] = '\0';
    free(res);
    return (lib9a);
}
char *get_next_line(int fd)
{
    static char *s;
    char    *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    s = read_function(fd,s);
    if (!s || s[0] == '\0')
    {
	    free(s);
	    return (NULL);
    }
    line = handle_newline(s);
    s = achb9a(s);
    return (line);
}
int main()
{
    int fd;
    char *res2;
    fd = open("file.txt",O_RDONLY);
    while ((res2 = get_next_line(fd)) != NULL)
    {
    	printf("%s",res2);
    }

    close (fd);    
}
    // if (!s)
    // {
    //     s = malloc(1);
    //     if (!s)
    //     return (NULL);
    //     s[0]='\0';
    // }
