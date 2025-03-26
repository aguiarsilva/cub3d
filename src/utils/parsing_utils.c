#include "cub3d.h"


int	ft_empty_char(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (STATUS_FAIL);
	else
		return (STATUS_OK);
}

size_t	ft_max_width(t_map_data *map_data, int i)
{
	size_t	max_len;

	max_len = ft_strlen(map_data->file[i]);
	while (map_data->file[i])
	{
		if (ft_strlen(map_data->file[i]) > max_len)
			max_len = ft_strlen(map_data->file[i]);
		i++;
	}
	return (max_len);
}

bool	ft_comfirm_digit_absence(char *str)
{
	int		i;
	bool	found_no_digit;

	i = 0;
	found_no_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = false;
		i++;
	}
	return (found_no_digit);
}

int	ft_skip_whitespace(char *line, int *index)
{
	while (line[*index] == ' ' || line[*index] == '\t' || line[*index] == '\n')
		(*index)++;
	return (1);
}
