/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:37:49 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 09:37:49 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

inline void	register_route(int method, int id, void (*cb)(), struct s_api *api)
{
	api->routes[id][method] = cb;
}

int	get_route_id(struct mg_http_message *req)
{
	if (mg_http_match_uri(req, "/api/v1/"))
		return (API_V1_);
	else if (mg_http_match_uri(req, "/api/v1/*"))
		return (API_V1_USER);
	return (-1);
}
