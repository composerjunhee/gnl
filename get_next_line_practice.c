/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_practice.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junheeki <junheeki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:24:14 by junheeki          #+#    #+#             */
/*   Updated: 2022/11/30 12:03:22 by junheeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char ft_read(int fd, char *buf, char *backup)
{
	int	count;
	char *temp_pointer;

	count = 1;
	while(count)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
			return (NULL);
		else if (count == 0)
			break ;
		buf[count] = '\0';
		if(!backup)
			backup = ft_strdup("");
		temp_pointer = backup;
		backup = ft_strjoin(temp_pointer, buf);
		if (!backup)
			return(NULL);
		free(temp_pointer);
		temp_pointer = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_extract(char *line)
{
	int		i;
	char	*result;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (0);
	result = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free(result);
		result = NULL;
		return (NULL);
	}
	line [i + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	char *line;
	char *buf;
	static char *backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)calloc((BUFFER_SIZE + 1), (sizeof(char)));
	if (!buf)
		return (NULL);
	line = ft_read(fd, buf, backup);
	free(buf);
	buf = NULL;
	if(!line)
		return (NULL);
	backup = ft_extract(line);
	return (line);
}
