/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42stats.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:01:58 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/16 21:01:58 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STATS_H
# define FT_STATS_H

# include "mongoose.h"

/* API Routes for better performance.
 * `ROUTES` serves for declaring the routes array. */
enum e_routes
{
	API_V1,
	API_V1_,
	ROUTES,
};

/* HTTP Request Methods.
 * `METHODS` serves for declaring the callbacks array. */
enum e_methods
{
	DELETE,
	GET,
	PATCH,
	POST,
	PUT,
	METHODS,
};

struct s_api
{
	 void			(*routes[ROUTES][METHODS])();
	 struct mg_mgr	mgr;
};

/* Initializes the API data structure. */
void	api_init(struct s_api *api);

/* Register a route in the API. */
void	register_route(int method, int id, void (*cb)(), struct s_api *api);

/* Gets `e_route route_id`. */
int		get_route_id(struct mg_http_message *hm);

/* Handles Requests. */
void	handle_request(struct mg_connection *c, struct mg_http_message *req);

/* Starts `mg_mgr` and starts listening to requests. */
void	api_do(struct s_api *ft_stats);

#endif
