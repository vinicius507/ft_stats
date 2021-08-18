/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_intra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 00:11:05 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/18 00:11:05 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	get_token_intra(struct mg_connection *c, struct s_api *api)
{
	struct mg_tls_opts	opts;
	extern const char	*g_oauth_url;

	if (mg_url_is_ssl(g_oauth_url))
	{
		bzero(&opts, sizeof(opts));
		opts.srvname = api->req.host;
		mg_tls_init(c, &opts);
	}
	mg_printf(c,
		"POST %s HTTP/1.0\r\n"
		"Host: %.*s\r\n"
		"Accept: */*\r\n",
		mg_url_uri(g_oauth_url),
		(int)api->req.host.len,
		api->req.host.ptr
		);
	mg_http_bauth(c,
		"cb8657e14837d297cc833ef943b48d1d988b6aa77eeac25db196c56c6048ee83",
		"21c57e8b841b42c2f01f55cfe6d3d1a4fc52ee692043e78b4d155b2b191e32d8"
		);
	mg_printf(c, "Content-Length: 29\r\n");
	mg_printf(c, "\r\n");
	mg_printf(c, "grant_type=client_credentials\r\n");
}
