
#include "../include/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	is_map_start(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (0);
		line++;
	}
	return (1);
}
