#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	t_list
{
	char	*key;
	char	*value;
}		s_list;

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

int	ft_strcmp(char *s1, char *s2)
{
	int	count;

	count = 0;
	while (s1[count] != '\0' && s2[count] != '\0')
	{
		if (s1[count] == s2[count])
		{
			count++;
		}
		else
		{
			return (s1[count] - s2[count]);
		}
	}
	return (s1[count] - s2[count]);
}

int	dict_entries(char *dict, int bytes)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (i++ < bytes)
	{
		if (dict[i] == '\n')
			count++;
	}
	return (count);
}

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

void ft_trim(char *str)
{
    int len;

	len = ft_strlen(str);
    while (len > 0 && ft_isspace(str[len - 1]))
		str[--len] = '\0';
}

char	*ft_strdup(char *src)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	j = -1;
	while (src[i])
		i++;
	t = malloc(i + 1);
	if (t == NULL)
		return (NULL);
	while (src[++j])
	{
		t[j] = src[j];
	}
	t[j] = '\0';
	return (t);
}

s_list	*do_struct(char *str, int bytes)
{
	s_list 	*ref_list;
	int		i;
	int		m;
	int		struct_i;

	i = 0;
	struct_i = 0;
	ref_list = (s_list *) malloc ((dict_entries(str, bytes) + 1) * sizeof(s_list));
	while (i < bytes && struct_i < dict_entries(str, bytes))
	{
		m = 0;
		ref_list[struct_i].key = (char *) malloc (1024 * sizeof(char));
		ref_list[struct_i].value = (char *) malloc (1024 * sizeof(char));
		while (str[i] != ':' && ft_isspace(str[i]) == 0)
		{
			ref_list[struct_i].key[m] = str[i];
			i++;
			m++;
		}
		ref_list[struct_i].key[m] = '\0';
		while (str[i] == ':' || ft_isspace(str[i]) == 1)
			i++;
		m = 0;
		while (str[i] != '\n')
		{
			ref_list[struct_i].value[m] = str[i];
			i++;
			m++;
		}
		ref_list[struct_i].value[m] = '\0';
		ft_trim(ref_list[struct_i].value);
		while (ft_isspace(str[i]))
			i++;
		struct_i++;
	}
	ref_list[struct_i].key = NULL;
	ref_list[struct_i].value = NULL;
	return(ref_list);
}

char	*search(char *av, char *buffer, s_list *ref_list, ssize_t bytes_read)
{
	int	i;
	int	count;

	i = -1;
	count = dict_entries(buffer, bytes_read);
	while (++i < count)
	{
		if (ft_strcmp(ref_list[i].key, av) == 0)
			return(ref_list[i].value);
	}
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	count_dest;
	int	count_src;

	count_dest = 0;
	count_src = 0;
	while (dest[count_dest] != '\0')
	{
		count_dest++;
	}
	while (src[count_src] != '\0')
	{
		dest[count_dest] = src[count_src];
		count_dest++;
		count_src++;
	}
	dest[count_dest] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	count;

	count = 0;
	while (src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	*charToString(char c) 
{
    char *str;

	str = (char *) malloc(4 * sizeof(char));
    str[0] = c;
    str[1] = '\0';
    return (str);
}

void	convert(char *av, char *buffer, s_list *ref_list, ssize_t bytes_read)
{
	int		count;
	
	count = ft_strlen(av);
	if (count == 1)
		printf("%s", search(av, buffer, ref_list, bytes_read));
	else if (count == 2)
	{
		if (av[0] == '0')
		{
			if (av[1] != '0')
				printf("%s", search(&av[count - 1], buffer, ref_list, bytes_read));
		}
		else
		{
			if (av[0] == '1')
				printf("%s", search(av, buffer, ref_list, bytes_read));
			else
			{
				printf("%s ", search(ft_strcat(charToString(av[0]), "0"), buffer, ref_list, bytes_read));
				if (av[count - 1] != '0')
					printf("%s", search(&av[count - 1], buffer, ref_list, bytes_read));
			}
		}
	}
	else if (count == 3)
	{
		if (av[0] == '0')
		{
			if (av[1] == '0')
			{
				if(av[count - 1] != '0')
					printf("%s", search(&av[count - 1], buffer, ref_list, bytes_read));
			}
			else
			{
				if (av[1] == '1')
					printf("%s", search(&av[1], buffer, ref_list, bytes_read));
				else
				{
					printf("%s ", search(ft_strcat(charToString(av[0]), "0"), buffer, ref_list, bytes_read));
					if (av[count - 1] != '0')
						printf("%s", search(&av[count - 1], buffer, ref_list, bytes_read));
				}
			}
		}	
		else
		{
			printf("%s ", search(charToString(av[0]), buffer, ref_list, bytes_read));
			printf("%s ", search("100", buffer, ref_list, bytes_read));
			if (av[1] == '1')
				printf("%s ", search(&av[1], buffer, ref_list, bytes_read));
			else
			{
				if (av[1] != '0')
					printf("%s ", search(ft_strcat(charToString(av[1]), "0"), buffer, ref_list, bytes_read));
				if(av[count - 1] != '0')
					printf("%s", search(&av[count - 1], buffer, ref_list, bytes_read));
			}
		}
	}
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (count < n && src[count])
	{
		dest[count] = src[count];
		count++;
	}
	while (count < n)
	{
		dest[count] = '\0';
		count++;
	}
	return (dest);
}

char	*ft_truncate(char *str, int start, int end) 
{
	int		length;
	char	*result;

    if (start < 0 || end < 0 || start > end || start >= ft_strlen(str))
        return NULL; 
    length = end - start;
    result = (char *)malloc((length + 1) * sizeof(char));
    if (!result)
		return (NULL);
    ft_strncpy(result, str + start, length);
	result[length] = '\0';
    return result;
}

/*
char *append_zero(int i)
{
    int		len;
	char 	*str;
	int		j;
		
	len = 2 + (i * 3);
	j = -1;
    str = (char *)malloc(len * sizeof(char));
    if (!str) 
        return (NULL);
    str[0] = '1';
	str[1] = '\0';
	while (++j < i)
        ft_strncpy(str, "000", 3);
	str[len - 1] = '\0';
	printf("%s", str);
    return (str);
}
*/

char *append_zero(int i)
{
    int 	len;
    char 	*str;
    int		j;
	int		index;

    len = 2 + (i * 3);
    j = -1;
	index = 1;
    str = (char *)malloc(len * sizeof(char));
    if (!str)
        return (NULL);
    str[0] = '1';
    str[1] = '\0';
    while (++j < i) 
	{
        ft_strcat(&str[index], "000");
        index += 3;
    }
    return (str);
}

void	print_number(char *av, char *buffer, s_list *ref_list, ssize_t bytes_read)
{
	int		mod;
	int		div;
	int		start;
	int		end;
	char	*str;

	mod = ft_strlen(av) % 3;
	div = ft_strlen(av) / 3;
	start = 0;
	end = 0;
	if (mod != 0)
	{
		end = mod;
		convert(ft_truncate(av, start, end), buffer, ref_list, bytes_read);
		str = append_zero(div);
		printf("%s ", search(str, buffer, ref_list, bytes_read));
		free(str);
	}
	while (--div >= 0)
	{
		start = end;
		end += 3;
		convert(ft_truncate(av, start, end), buffer, ref_list, bytes_read);
		if (div != 0 && ft_strcmp(ft_truncate(av, start, end), "000") != 0)
		{
			str = append_zero(div);
			printf("%s ", search(append_zero(div), buffer, ref_list, bytes_read));
			free(str);
		}
	}
}

#include<stdio.h>
int	main(int ac, char **av)
{
	int		fd;
	char	*buffer;
	ssize_t	bytes_read;
	s_list	*ref_list;

	buffer = (char *) malloc(1024 * sizeof(char));
	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
		write(1, "Error!\n", 7);
	bytes_read = read(fd, buffer, 1024);
	buffer[bytes_read] = '\0';
	ref_list = do_struct(buffer, bytes_read);
	//printf("%s\n", ref_list[0].value);
	/*
	while (++i < dict_entries(buffer, bytes_read))
		printf("%s: %s\n", ref_list[i].key, ref_list[i].value);
	while (str[++i])
		printf("%s", str[i]);
	*/
	close(fd);
	if (ac == 2)
	{
		printf("%s\n", ft_truncate(av[1], 0, 2));
		print_number(av[1], buffer, ref_list, bytes_read);
	}
	return (0);
}
