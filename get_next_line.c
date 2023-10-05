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
	size_t		i;
	size_t		j;
	int		res;

	res = 1;
	if (fd < 0 || read(fd,0,0) < 0)
	{
		return (0);
	}
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1),sizeof(char));
	tmp = 0;
	swp = 0;
	if (!buffer)
		return (0);
	while (res > 0)
	{
		swp = ft_strjoin(swp,tmp,0);
		res = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
		{
			i++;
		}
		if (i== 0 && res == 0 && !tmp)
		{
			free(buffer);
			return (0);
		}
		//swp = ft_strjoin(swp,tmp,0);
		tmp = (char *)ft_calloc((i +1),sizeof(char));
		j = 0;
		while (j <= i)
		{
			tmp[j] = buffer[j];
			j++;
		}
		tmp = ft_strjoin(swp, tmp,0);
		if (swp)
			free(swp);
		ft_bzero(buffer, BUFFER_SIZE +1);
		if (ft_strchr(tmp, '\n'))
			break;
	}
	//tmp = ft_strjoin(tmp, buffer,1);
	if (buffer)
		free(buffer);
	return (tmp);
}
