#include "string.h"
#include "stdio.h"
#include "unistd.h"

int	check_empty_lines_in_map(char **lines, int start, char *content)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (content[j] && i < start)
	{
		while (content[j] == '\n')
			j++;
		while (content[j] && content[j] != '\n')
			j++;
		if (content[j] == '\n')
			j++;
		i++;
	}
	while (lines[i])
	{
		if (content[j] == '\n')
			return (0);
		k = 0;
		while (content[j + k] && content[j + k] != '\n')
			k++;
		if (strncmp(lines[i], content + j, k - 1) != 0 || lines[i][k] != '\0')
			return (0);
		j += k;
		if (content[j] == '\n')
			j++;
		i++;
	}
	return (1);
}

int	main(void)
{
	char *content;
	char **split_content = (char *[]){"NO ./textures-fullrobin/east.xpm", "SO ./textures-stylemineraft/south.xpm", "WE ./textures-stylemineraft/west.xpm", "EA ./textures-stylemineraft/east.xpm", "F 220,100,0", "C 225,30,100", "        000000000000000000", "        111111111111111111111111", "        222222222222222222222", "        33333333333333333333333333333", NULL};

	content = "NO ./textures-fullrobin/east.xpm\nSO ./textures-stylemineraft/south.xpm\nWE ./textures-stylemineraft/west.xpm\nEA ./textures-stylemineraft/east.xpm\n\nF 220,100,0\nC 225,30,100\n        000000000000000000\n        111111111111111111111111\n        222222222222222222222\n\n        33333333333333333333333333333\n";

	if (!check_empty_lines_in_map(split_content, 6, content))
		printf("space in line found\n");	
	else
		printf("no space in line found\n");	
	return (0);
}