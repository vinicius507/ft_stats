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
# include "mjson.h"

/* API Routes for better performance.
 * `ROUTES` serves for declaring the routes array. */
enum e_routes
{
	API_V1,
	API_V1_,
	API_V1_USER,
	ROUTES,
};

/* HTTP Request Methods.
 * `METHODS` serves for declaring the callbacks array. */
enum e_methods
{
	DELETE,
	GET,
	HEAD,
	OPTIONS,
	PATCH,
	POST,
	PUT,
	METHODS,
};

struct s_request
{
	int				done:1;
	struct mg_str	host;
	const char		*path;
	char			token[65];
};

struct s_api
{
	 void				(*routes[ROUTES][METHODS])();
	 struct mg_mgr		mgr;
	 struct s_request	req;
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
void	api_do(struct s_api *api);

/* Redirects to `/api/v1`. */
void	redirect(struct mg_connection *c, struct mg_http_message *req);

/* Checks if path being requested is SSL and initialize TLS. */
void	tls_init(struct mg_connection *c);

/* Gets OAuth token from École 42 api. */
void	request_token_intra(struct mg_connection *c, struct s_api *api);

/* Authenticate at École 42 intranet. */
void	auth_intra(struct s_api *api);

/* Get user data. */
void	get_user_data(struct mg_connection *c, struct mg_http_message *req);

#endif
