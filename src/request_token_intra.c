/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_token_intra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 00:11:05 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/18 00:11:05 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	request_token_intra(struct mg_connection *c, struct s_api *api)
{
	tls_init(c);
	mg_printf(c,
		"POST %s HTTP/1.0\r\n"
		"Host: %.*s\r\n"
		"Accept: */*\r\n",
		mg_url_uri(api->req.path),
		(int)api->req.host.len,
		api->req.host.ptr
		);
	mg_http_bauth(c,
		"21c57e8b841b42c2f01f55cfe6d3d1a4fc52ee692043e78b4d155b2b191e32d8",
		getenv("CLIENT_SECRET")
		);
	mg_printf(c, "Content-Length: 29\r\n");
	mg_printf(c, "\r\n");
	mg_printf(c, "grant_type=client_credentials\r\n");
}
