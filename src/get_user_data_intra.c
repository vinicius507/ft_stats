/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_data_intra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:17:42 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/18 14:17:42 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

static const char	*g_base_url = "https://api.intra.42.fr/v2/users/";

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message	*hm;
	struct s_api			*api;

	api = (struct s_api *)c->fn_data;
	if (ev == MG_EV_CONNECT)
		send_request(c, api);
	else if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *)ev_data;
		printf("%.*s\n", (int)hm->message.len, hm->message.ptr);
		c->is_closing = 1;
		api->req.done = 1;
	}
	else if (ev == MG_EV_ERROR)
		api->req.done = 1;
	(void)c;
	(void)fn_data;
}

void	get_user_data_intra(struct s_api *api, const char *user)
{
	struct mg_connection	*c;

	api->req.type = "GET";
	api->req.path = calloc(strlen(g_base_url) + strlen(user) + 1, sizeof(char));
	sprintf((char *)api->req.path, "%s%s", g_base_url, user);
	api->req.host = mg_url_host(g_base_url);
	api->req.done = 0;
	c = mg_http_connect(&api->mgr, api->req.path, cb, api);
	while (c && api->req.done == 0)
		mg_mgr_poll(&api->mgr, 1000);
	free((char *)api->req.path);
	api->req.path = NULL;
}
