/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junheeki <junheeki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:58:17 by junheeki          #+#    #+#             */
/*   Updated: 2022/12/01 11:20:58 by junheeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_line(int fd, char *buf, char *backup)
{
	int		count;
	char	*temp_pointer;

	count = 1;
	while (count)
	{
		count = read(fd, buf, BUFFER_SIZE); // read fd number of Buffer size,	if it works return Number of Bytes, failed return -1,	reached EOF return 0
		if (count == -1) //읽어온 바이트 수 실패시 -1
			return (0);
		else if (count == 0) // 더이상 읽을 바이트가 없다.
			break ;
		buf[count] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp_pointer = backup;
		backup = ft_strjoin(temp_pointer, buf);
		if (!backup)
			return (NULL);
		free(temp_pointer);
		temp_pointer = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_extract(char *line)	//1.Check \n position. 2. If you find EOF, then return 0, 3. After \n, saving at backup, 4.If first letter of backup is at EOF, memory free then return NULL. 5. We have to print data that line that we read before '\n', so save \0 at '\n'+ 1
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
	line[i + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buf;

	static char	*backup; // value will be stackup so after	/n still we can use the value
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)calloc((BUFFER_SIZE + 1), (sizeof(char)));
	if (!buf)
		return (NULL);
	line = ft_read_line(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	backup = ft_extract(line);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = 0;
	fd = open("./bible.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%p\n", line);
	printf("%s", line);
	return (0);
}
*/
