/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:45:25 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/19 10:45:25 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	request(const char *method, const char *url, mg_event_handler_t cb,
	struct s_api *api)
{
	struct mg_connection	*c;

	api->req.type = method;
	api->req.path = url;
	api->req.host = mg_url_host(api->req.path);
	api->req.done = 0;
	c = mg_http_connect(&api->mgr, api->req.path, cb, api);
	while (c && api->req.done == 0)
		mg_mgr_poll(&api->mgr, 1000);
	api->req.path = NULL;
}
