#include "get_next_line.h"

void ft_bzero(void *p,int bytes)
{
	while (bytes--)
		*((char *)p++) = 0;
}

int ft_strlen(char *s)
{
	int i;

	if (!s)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return i;
}

void	*my_calloc(int bytes)
{
	void *p;

	p = malloc(bytes);
	if(!p)
		exit(EXIT_FAILURE);
	ft_bzero(p,bytes);
	return p;
}

void append_string(char **buffer, char *holder, int holder_size)
{
	int		buffer_size;
	char	*appended_string;
	int		i;
	int		j;

	if (!holder_size)
		return ;
	buffer_size = ft_strlen(*buffer);
	appended_string = my_calloc(buffer_size + holder_size + 1);
	i = 0;
	while(i < buffer_size)
	{
		appended_string[i] = (*buffer)[i];
		i++;
	}
	j = 0;
	while (j < holder_size)
	{
		appended_string[i] = holder[j];
		i++;
		j++;
	}
	free(*buffer);
	*buffer = appended_string;
}

int read_line(char **buffer, int fd)
{
	int bytes_read;
	char *holder;

	holder = my_calloc(BUFFER_SIZE * sizeof(char));
	bytes_read = read(fd, holder, BUFFER_SIZE);
	if (bytes_read == -1)
		exit(EXIT_FAILURE);
	append_string(buffer, holder, bytes_read);
	free(holder);
	return bytes_read;
}

char *return_line(char **buffer,int nl_index)
{
	char *line;
	char *tmp;

	line = NULL;
	tmp = NULL;
	append_string(&line, *buffer, nl_index + 1);
	append_string(&tmp, *buffer + (nl_index + 1), ft_strlen(*buffer + (nl_index + 1)));
	free(*buffer);
	*buffer = tmp;
	return line;
}

int contains_nl(char *s)
{
	int i;
	
	if (s)
	{
		i = 0;
		while(s[i])
		{
			if(s[i] == '\n')
				return i;
			i++;
		}
	}
	return -1;
}

char *get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*tmp;
	int			bytes_read;
	int			nl_index;

	if (fd < 0 || fd > OPEN_MAX)
		exit(0);
	while (1)
	{
		if ((nl_index  = contains_nl(buffer[fd])) != -1)
			return return_line(&buffer[fd],nl_index);
		bytes_read = read_line(&buffer[fd],fd);
		if (bytes_read == 0)
		{
			tmp = buffer[fd];
			buffer[fd] = NULL;
			return tmp;
		}	
	}
	return NULL;
}