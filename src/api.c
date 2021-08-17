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
	int	i;
	int	j;

	i = 0;
	while (i < ROUTES)
	{
		j = 0;
		while (j < METHODS)
			api->routes[i][j++] = NULL;
		i++;
	}
}

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
		handle_request(c, (struct mg_http_message *)ev_data);
	(void)c;
	(void)fn_data;
}

void	api_do(struct s_api *ft_stats)
{
	mg_log_set("3");
	mg_mgr_init(&ft_stats->mgr);
	mg_http_listen(&ft_stats->mgr, "http://0.0.0.0:8000", cb, ft_stats);
	while (1)
		mg_mgr_poll(&ft_stats->mgr, 1000);
	mg_mgr_free(&ft_stats->mgr);
}
