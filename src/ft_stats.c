/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:27:19 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/16 21:27:19 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"
#include "mongoose.h"

static const char	*g_web_root_dir = ".";
static const char	*g_listening_address = "http://localhost:8000";

static void	cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_serve_opts	opts;

	(void)fn_data;
	opts.root_dir = g_web_root_dir;
	opts.extra_headers = NULL;
	opts.fs = NULL;
	opts.mime_types = NULL;
	opts.ssi_pattern = NULL;
	if (ev == MG_EV_HTTP_MSG)
		mg_http_serve_dir(c, ev_data, &opts);
}

int	main(void)
{
	struct mg_mgr	mgr;

	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, g_listening_address, cb, &mgr);
	while (1)
		mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	return (0);
}
