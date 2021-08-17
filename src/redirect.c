/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:21:57 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/17 15:21:57 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

void	redirect(struct mg_connection *c, struct mg_http_message *req)
{
	mg_http_reply(c, 308, "location: /api/v1\r\n", "");
	(void)req;
}
