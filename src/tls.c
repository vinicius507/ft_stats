/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 09:56:33 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/18 09:56:33 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	tls_init(struct mg_connection *c)
{
	struct s_api		*api;
	struct mg_tls_opts	opts;

	api = (struct s_api *)c->fn_data;
	if (mg_url_is_ssl(api->req.path))
	{
		bzero(&opts, sizeof(opts));
		opts.srvname = api->req.host;
		mg_tls_init(c, &opts);
	}
}
