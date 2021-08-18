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

int	main(void)
{
	struct s_api	api;

	api_init(&api);
	register_route(GET, API_V1_, redirect, &api);
	register_route(GET, API_V1_USER, get_user_data, &api);
	api_do(&api);
	return (0);
}
