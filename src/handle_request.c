/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_request.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 10:56:57 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 10:56:57 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

static int	get_method(struct mg_http_message *req)
{
	if (!mg_ncasecmp("DELETE", req->method.ptr, req->method.len))
		return (DELETE);
	else if (!mg_ncasecmp("GET", req->method.ptr, req->method.len))
		return (GET);
	else if (!mg_ncasecmp("PATCH", req->method.ptr, req->method.len))
		return (PATCH);
	else if (!mg_ncasecmp("POST", req->method.ptr, req->method.len))
		return (POST);
	else if (!mg_ncasecmp("PUT", req->method.ptr, req->method.len))
		return (PUT);
	return (-1);
}

void	handle_request(struct mg_connection *c, struct mg_http_message *req)
{
	int				method;
	int				route_id;
	struct s_api	*api;

	method = get_method(req);
	route_id = get_route_id(req);
	api = (struct s_api *)c->fn_data;
	if (method < 0)
		mg_http_reply(c, 400, "", "");
	else if (route_id < 0)
		mg_http_reply(c, 404, "", "");
	else if (api->routes[route_id][method] == NULL)
		mg_http_reply(c, 405, "", "");
	else
		api->routes[route_id][method](c, req);
}
