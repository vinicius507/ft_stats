/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:52:36 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/16 22:52:36 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message		*hm;

	(void)fn_data;
	hm = (struct mg_http_message *)ev_data;
	if (ev == MG_EV_HTTP_MSG)
	{
		if (mg_http_match_uri(hm, "/api/v1"))
			mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
		else if (mg_http_match_uri(hm, "/api/v1/*"))
			mg_http_reply(c, 200, "", "{\"result\": \"%s\"}\n", "Test");
	}
}
