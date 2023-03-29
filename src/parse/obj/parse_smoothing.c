/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_smoothing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lsinke <lsinke@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 19:33:36 by lsinke        #+#    #+#                 */
/*   Updated: 2023/03/24 19:33:36 by lsinke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <libft.h>

t_parse_err	parse_smoothing(char **linep, t_object *object, t_conf_data *conf)
{
	int32_t	val;

	(void) object;
	if (ft_strncmp(*linep, "off", 3) == 0)
	{
		conf->smoothing = false;
		*linep += 3;
	}
	else if (ft_strncmp(*linep, "on", 2) == 0)
	{
		conf->smoothing = true;
		*linep += 2;
	}
	else if (ft_isdigit(**linep))
	{
		val = ft_atoi(*linep);
		while (ft_isdigit(**linep))
			*linep += 1;
		conf->smoothing = (val != 0);
	}
	return (SUCCESS);
}
