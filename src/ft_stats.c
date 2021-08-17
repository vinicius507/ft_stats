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

static const char	*g_listening_address = "http://localhost:8000";

int	main(void)
{
	struct mg_mgr		mgr;

	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, g_listening_address, callback, NULL);
	while (1)
		mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	return (0);
}
