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

static void	redirect(struct mg_connection *c, struct mg_http_message *req)
{
	mg_http_reply(c, 308, "location: /api/v1\r\n", "");
	(void)req;
}

int	main(void)
{
	struct s_api	api;

	api_init(&api);
	register_route(GET, API_V1_, redirect, &api);
	api_do(&api);
	return (0);
}
