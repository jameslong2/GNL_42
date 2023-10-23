#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <errno.h>
size_t countn(char *s)
{
	size_t	l;
	size_t	count;

	count = 0;
	l = 0;
	if (!s)
		return (l);
	while (s[l])
	{
		if (s[l] == '\n')
			count++;
		l++;
	}
	return (count);
}

size_t countparts(char *s)
{
	size_t l;
	size_t count;
	int		button;

	button = 0;
	count = 0;
	l = 0;
	if (s[0] == 0)
		return (0);
	if (s[0] == '\n')
	{
		count++;
		l++;
	}
	while (s[l])
	{
			if(button == 0)
			{
				button = 1;
				count++;
			}
			else if (button == 1 && s[l] == '\n')
				button = 0;
		l++;
	}
	return (count);
}
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s)
		((unsigned char *)s)[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(size * count);
	if (tmp == NULL)
		return (NULL);
	while (i < count * size)
		((unsigned char *)tmp)[i++] = (unsigned char)0;
	return (tmp);
}

size_t countnext(char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i++] == '\n')
			break;
	}
	return (i);
}

char	*ft_union(char *s1, char *s2, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	act;

	i = 0;
	act = ft_strlen(s1);
	tmp = (char *)ft_calloc(act+len+1, sizeof(char));
	if (!tmp)
	{
		if (s1)
		{
			free(s1);
			s1 = 0;
		}
		return (0);
	}
	if (s1)
	{
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
	{
		i = 0;
		while (i < len)
		{
			tmp[act+i] = s2[i];
			i++;
		}
	}
	//tmp[act+i] = '\0';
	/*if (s1)
	{
		free(s1);
		s1 = 0;
	}*/
	return (tmp);
}

void	ft_reset(char *dst, char *src, size_t len)
{
	size_t	i;


	i = -1;
	if (ft_strlen(dst) == 0)
	{
		if (dst)
		{
			free(dst);
			dst = 0;
		}
		return ;
	}
	while (++i < len && (src != 0 && dst != 0) && len != 0)
		dst[i] = src[i];
	dst[i]=0;
}

char	*returnwithbuffer(char *swp, char *buf, size_t len)
{
		swp = ft_union(swp,buf,countnext(buf));
		if (!swp)
			return (0);
		ft_reset(buf, buf+countnext(buf),len);
		return (swp);
}
char	*get_next_line(int fd)
{
	static char	*buffer = 0;

	char		*swp;
	char		*tmp;
	int		res;


	res = 1;
	swp = 0;
	if (fd < 0 || read(fd,0,0) < 0 || BUFFER_SIZE <= 0 || errno == 1)
	{
		if (buffer)
		{
			free(buffer);
			buffer = 0;
		}
		return (0);
	}
	errno = 0;
	if (buffer)
	{
		if (ft_strlen(buffer) == countnext(buffer))
		{
			swp = ft_union(swp, buffer, ft_strlen(buffer));
			free(buffer);
			buffer = 0;
		}
		else if (ft_strlen(buffer) != countnext(buffer))
		{
			tmp = returnwithbuffer(swp, buffer, ft_strlen(buffer+countnext(buffer)));
			if (!tmp)
			{
				if (buffer)
				{
					free(buffer);
					buffer = 0;
				}
				return (0);
			}
			return (tmp);
		}
	}
	buffer = (char *)ft_calloc(BUFFER_SIZE+1,sizeof(char));
	if (!buffer)
	{
		if (swp)
		{
			free(swp);
			swp = 0;
		}
		return (0);
	}
	while (res > 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (ft_strchr(buffer,'\n'))
		{
			tmp = returnwithbuffer(swp, buffer, ft_strlen(buffer+countnext(buffer)));
			if (!tmp)
			{
				if (buffer)
				{
					free(buffer);
					buffer = 0;
				}
				return (0);
			}
			return (tmp);
		}
		swp = ft_union(swp,buffer,ft_strlen(buffer));
		if (!swp)
		{
			if (buffer)
			{
				free(buffer);
				buffer = 0;
			}
			return (NULL);
		}
		ft_bzero(buffer, BUFFER_SIZE+1);
	}
	if (buffer)
	{
		free(buffer);
		buffer = 0;
	}
	if (ft_strlen(swp) == 0)
	{
		free(swp);
		swp = 0;
	}
	return (swp);
}
