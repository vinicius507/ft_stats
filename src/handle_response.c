/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_response.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:38:21 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/19 10:38:21 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	handle_response(struct mg_connection *c, struct mg_http_message *res)
{
	struct s_api	*api;

	api = (struct s_api *)c->fn_data;
	api->res.status = atoi(res->uri.ptr);
	if (res->body.len > 0 && res->body.ptr != NULL)
		api->res.body = strndup(res->body.ptr, res->body.len);
	c->is_closing = 1;
	api->req.done = 1;
}
