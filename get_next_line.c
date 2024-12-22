/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bessabri <bessabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:18 by bessabri          #+#    #+#             */
/*   Updated: 2024/12/22 23:49:47 by bessabri         ###   ########.fr       */
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
    ssize_t n;
    char    *buffer;
    
    buffer = malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return (0);

    while (!ft_strchr(res,'\n') && n > 0)
    {

        n = read(fd, buffer,BUFFER_SIZE);
        buffer[n]='\0';
        res = ft_strjoin(res,buffer);
    }
    free(buffer);
    return (res);
} 

char    *handle_newline(char *res)
{
    char    *newline;
    int i;

    i = 0;
    while (res[i] && res[i]!= '\n')
        i++;
    //if (res[i] == '\n')
    //    i++;
    newline = malloc(i + 1);
    if (!newline)
    return (0);
    i = 0;
    while (res[i] && res[i]!= '\n')
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
    free(res);
    return (newline);    
}
char    *achb9a(char *res)
{
    int total_size;
    int i;
    int j;
    char    *lib9a;

    i = 0;
    j = 0;
    while (res[i] && res[i]!= '\n')
        i++;
    if (res[i] == '\0' || res[i + 1] == '\0')
        return NULL;

    total_size = ft_strlen(res);
    lib9a = malloc(total_size - i + 1);
    if (!lib9a)
        return (0);
    i++;
    while (res[i])
    {
        lib9a[j] = res[i];
        i++;
        j++;
    }
    free(res);
    lib9a[j] = '\0';
    return (lib9a);
}
char *get_next_line(int fd)
{
    static char *s;
    char    *line;
    s = read_function(fd,s);
    if (!s)
        return (NULL);
    line = handle_newline(s);
    s =achb9a(s);
    return (line);

}
int main()
{
    int fd;
    char *res2;
    fd = open("file.txt",O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
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
