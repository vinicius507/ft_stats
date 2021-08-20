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

static struct s_api	*g_api = NULL;

static void	_sig_term_handler(int signum)
{
	mongoc_cleanup();
	mg_mgr_free(&g_api->mgr);
	exit(EXIT_SUCCESS);
	(void)signum;
}

void	catch_sigterm(void)
{
	static struct sigaction	_sigact;

	memset(&_sigact, 0, sizeof(_sigact));
	_sigact.sa_handler = _sig_term_handler;
	sigaction(SIGTERM, &_sigact, NULL);
}

int	main(void)
{
	struct s_api	api;

	g_api = &api;
	catch_sigterm();
	api_init(&api);
	register_route(GET, API_V1_, redirect, &api);
	register_route(GET, API_V1_USER, get_user_data, &api);
	api_do(&api);
	return (EXIT_SUCCESS);
}
