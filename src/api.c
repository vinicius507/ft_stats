/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:45:21 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 09:45:21 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	api_init(struct s_api *api)
{
	bzero(&api->req, sizeof(api->req));
	bzero(&api->res, sizeof(api->res));
	bzero(api->routes, sizeof(api->routes));
}

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
		handle_request(c, (struct mg_http_message *)ev_data);
	(void)fn_data;
}

void	api_do(struct s_api *api)
{
	mg_log_set("3");
	mg_mgr_init(&api->mgr);
	mg_http_listen(&api->mgr, "http://0.0.0.0:4242", cb, api);
	while (1)
		mg_mgr_poll(&api->mgr, 1000);
}
