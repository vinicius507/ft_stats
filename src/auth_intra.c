/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth_intra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:38:22 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 17:38:22 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

static const char	*g_oauth_url = "https://api.intra.42.fr/oauth/token";

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message	*hm;
	struct s_api			*api;

	api = (struct s_api *)c->fn_data;
	if (ev == MG_EV_CONNECT)
		request_token_intra(c, api);
	else if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *)ev_data;
		mjson_get_string(hm->body.ptr, hm->body.len,
			 "$.access_token", api->req.access_token, 65);
		c->is_closing = 1;
		api->req.done = 1;
	}
	else if (ev == MG_EV_ERROR)
		api->req.done = 1;
	(void)c;
	(void)fn_data;
}

void	auth_intra(struct s_api *api)
{
	request("GET", g_oauth_url, cb, api);
}
