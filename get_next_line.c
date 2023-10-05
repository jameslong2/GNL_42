#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

size_t lennul(char *s)
{
	size_t	l;

	l = 0;
	if (!s)
		return (l);
	while (s[l++])
		;
	l--;
	return (l);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(size * count);
	if (tmp == 0)
		return (0);
	while (i < count * size)
		((unsigned char *)tmp)[i++] = (unsigned char)0;
	return (tmp);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	char		*swp;
	char		*prev;
	size_t		i;
	int		res;
	//int		last;


	if (fd < 0 || read(fd,0,0) < 0)
	{
		return (0);
	}
	res = 1;
	tmp = 0;
	swp = 0;
	//last = res;
	/*if (buffer != 0)
	{
		if (ft_strchr(buffer , '\n'))
		{
			if (ft_strchr(buffer, '\n') + 1 > 0)
			{
				swp = (char *)ft_calloc( ft_strlen(ft_strchr(buffer, '\n') +1)+ 1, sizeof(char));
				ft_strlcpy(swp, ft_strchr(buffer, '\n') +1, ft_strlen(ft_strchr(buffer, '\n') + 1)+1);
				ft_bzero(buffer, BUFFER_SIZE + 1);
			}
		}
	}*/

	prev = 0;
	if (ft_strlen(buffer) > 0)
	{
		prev = (char *)ft_calloc(ft_strlen(buffer) + 1, sizeof(char));
		ft_strlcpy(prev, buffer, ft_strlen(buffer));
	}
	if (buffer)
		free(buffer);
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1),sizeof(char));
	if (!buffer)
		return (0);
	res = read(fd, buffer, BUFFER_SIZE);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (i == 0 && res == 0)
	{
		if (prev)
			free(prev);
		free(buffer);
		return (0);
	}
	if (prev != 0)
	{
		if (ft_strchr(prev, '\n')!= 0)
		{
			if (ft_strlen(ft_strchr(prev, '\n')+1) > 0)
			{
				swp = (char *)ft_calloc( ft_strlen(ft_strchr(prev, '\n')+1)+1, sizeof(char));
				ft_strlcpy(swp, ft_strchr(prev, '\n')+1, ft_strlen(ft_strchr(prev, '\n'))+1);
			}
		}
		free(prev);
	}
	while (res > 0)
	{
		//res = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
		{
			i++;
		}
		if (buffer[i] == '\n')
			i++;
		if (tmp)
			free(tmp);
		tmp = (char *)ft_calloc(ft_strlen(swp)+ i +1,sizeof(char));
		ft_strlcpy(tmp,swp, ft_strlen(swp) + 1);
		ft_strlcpy(tmp + ft_strlen(swp), buffer, i+1);
		if (swp)
			free(swp);
		swp = (char *)ft_calloc(ft_strlen(tmp)+1, sizeof(char));
		ft_strlcpy(swp, tmp,ft_strlen(tmp) + 1);
		if (ft_strchr(buffer, '\n'))
			break;
		ft_bzero(buffer, BUFFER_SIZE +1);
		//last = res;
		res = read(fd, buffer, BUFFER_SIZE);
	}
	if (tmp)
		free(tmp);
	//if (buffer)
	//	free(buffer);
	return (swp);
}
