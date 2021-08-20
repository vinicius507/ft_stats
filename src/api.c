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

static int	g_done = 0;

static void	_sig_term_handler(int signum)
{
	g_done = 1;
	(void)signum;
}

static void	catch_sigterm(void)
{
	static struct sigaction	_sigact;

	memset(&_sigact, 0, sizeof(_sigact));
	_sigact.sa_handler = _sig_term_handler;
	sigaction(SIGTERM, &_sigact, NULL);
}

void	api_init(struct s_api *api)
{
	bzero(&api->req, sizeof(api->req));
	bzero(&api->res, sizeof(api->res));
	bzero(api->routes, sizeof(api->routes));
	mongoc_init();
}

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
		handle_request(c, (struct mg_http_message *)ev_data);
	(void)fn_data;
}

void	api_do(struct s_api *api)
{
	catch_sigterm();
	mg_log_set("3");
	mg_mgr_init(&api->mgr);
	mg_http_listen(&api->mgr, "http://0.0.0.0:4242", cb, api);
	while (g_done == 0)
		mg_mgr_poll(&api->mgr, 1000);
	mongoc_cleanup();
	mg_mgr_free(&api->mgr);
}
