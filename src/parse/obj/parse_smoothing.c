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
	else if (**linep == '0')
	{
		conf->smoothing = false;
		*linep += 1;
	}
	else if (**linep == '1')
	{
		conf->smoothing = true;
		*linep += 1;
	}
	return (SUCCESS);
}
