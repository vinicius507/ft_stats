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

static const char	*g_base_url = "https://api.intra.42.fr/v2/users";

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct s_api			*api;

	api = (struct s_api *)fn_data;
	if (ev == MG_EV_CONNECT)
		send_request(c, api);
	else if (ev == MG_EV_HTTP_MSG)
		handle_response(c, (struct mg_http_message *)ev_data);
	else if (ev == MG_EV_ERROR)
		api->req.done = 1;
}

void	get_user_data_intra(struct s_api *api, const char *user)
{
	char	*path;

	path = calloc(strlen(g_base_url) + strlen(user) + 1, sizeof(char));
	sprintf(path, "%s/%s", g_base_url, user);
	request("GET", path, cb, api);
	free(path);
	api->req.path = NULL;
}
