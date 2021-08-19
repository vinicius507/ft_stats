/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:13:04 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 22:13:04 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	send_request(struct mg_connection *c, struct s_api *api)
{
	tls_init(c);
	mg_printf(c,
		"%s %s HTTP/1.0\r\n"
		"Host: %.*s\r\n"
		"Authorization: Bearer %s\r\n"
		"Accept: */*\r\n",
		api->req.type, mg_url_uri(api->req.path),
		(int)api->req.host.len, api->req.host.ptr,
		api->req.access_token
		);
	if (api->req.body == NULL)
	{
		mg_printf(c, "\r\n");
		return ;
	}
	mg_printf(c,
		"Content-Length: %d\r\n"
		"\r\n"
		"%s\r\n",
		strlen(api->req.body), api->req.body);
}
