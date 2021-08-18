/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:37:23 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 22:37:23 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	get_user_data(struct mg_connection *c, struct mg_http_message *req)
{
	struct s_api	*api;
	char			*user;

	api = (struct s_api *)c->fn_data;
	auth_intra(api);
	if (api->req.access_token[0] == '\0')
	{
		mg_http_reply(c, 500, "", "");
		return ;
	}
	user = strndup(req->uri.ptr + 8, req->uri.len - 8);
	get_user_data_intra(api, user);
	free(user);
	mg_http_reply(c, 200, "", "");
}
