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

static const char	*g_bool[2] = {"false", "true"};

static void	handle_ok(struct mg_connection *c, struct s_user *user)
{
	struct s_api	*api;
	const char		*json_str;

	api = (struct s_api *)c->fn_data;
	parse_user_data(api, user);
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{"
		"\"intra_id\": %d,"
		"\"login\": %.*s,"
		"\"name\": %.*s,"
		"\"staff\": %s,"
		"\"finished_projects\": %d,"
		"\"gpa\": %.2f,"
		"\"stardew_coefficient\": %.2f"
		"}",
		user->intra_id,
		(int)user->login.len, user->login.ptr,
		(int)user->displayname.len, user->displayname.ptr,
		g_bool[user->staff], user->finished_projects, user->gpa
		);
	json_str = strchr((const char *)c->send.buf, '{');
	json_str = strndup(json_str,
			c->send.len - ((size_t)json_str - (size_t)c->send.buf));
	db_add(json_str, user->login);
	free((char *)json_str);
	free((void *)user->_str);
}

void	get_user_data(struct mg_connection *c, struct mg_http_message *req)
{
	struct s_api	*api;
	char			*query;
	struct s_user	user;

	api = (struct s_api *)c->fn_data;
	auth_intra(api);
	if (api->req.access_token[0] == '\0')
	{
		mg_http_reply(c, 500, "", "");
		return ;
	}
	query = strndup(req->uri.ptr + 8, req->uri.len - 8);
	get_user_data_intra(api, query);
	if (api->res.status == 200)
		handle_ok(c, &user);
	else if (api->res.status == 404)
		mg_http_reply(c, 404, "", "");
	else if (api->res.status == 500)
		mg_http_reply(c, 500, "", "");
	else
		mg_http_reply(c, 400, "", "");
	free(query);
	free((void *)api->res.body);
	api->res.body = NULL;
}
