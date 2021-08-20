/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:07:19 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/19 13:07:19 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

static const char	*g_queries[] = {
	"$.id", "$.login", "$.displayname", "$.staff?",
	"$.projects_users[%d].marked", "$.projects_users[%d].final_mark", "$.wallet"
};

static inline void	get_mg_str(struct mg_str *mg_s, struct s_user *user,
	size_t len, const char *query)
{
	bzero(mg_s, sizeof(struct mg_str));
	mjson_find(user->_str, len, query, &mg_s->ptr, (int *)&mg_s->len);
}

static inline int	get_number(struct s_user *user,
	size_t len, const char *query)
{
	int			n;
	const char	*s;
	int			res;
	int			ret;

	res = 0;
	ret = mjson_find(user->_str, len, query, &s, &n);
	if (ret == MJSON_TOK_NUMBER)
		res = atoi(s);
	else if (ret == MJSON_TOK_TRUE)
		res = 1;
	return (res);
}

static inline void	get_projects_data(struct s_user *user, size_t len)
{
	int			i;
	const char	*s;
	int			n;
	int			ret;
	char		query[36];

	i = 0;
	snprintf(query, 36, g_queries[4], i);
	ret = mjson_find(user->_str, len, query, &s, &n);
	while (ret > 0)
	{
		if (ret == MJSON_TOK_TRUE)
		{
			snprintf(query, 36, g_queries[5], i);
			mjson_find(user->_str, len, query, &s, &n);
			user->finished_projects++;
			user->gpa += atoi(s);
		}
		i++;
		snprintf(query, 36, g_queries[4], i);
		ret = mjson_find(user->_str, len, query, &s, &n);
	}
	if (user->finished_projects)
		user->gpa /= user->finished_projects;
}

void	parse_user_data(struct s_api *api, struct s_user *user)
{
	const char	*s;
	int			n;
	size_t		json_len;

	s = NULL;
	n = 0;
	bzero(user, sizeof(struct s_user));
	user->_str = strdup(api->res.body);
	json_len = strlen(user->_str);
	user->intra_id = get_number(user, json_len, g_queries[0]);
	get_mg_str(&user->login, user, json_len, g_queries[1]);
	get_mg_str(&user->displayname, user, json_len, g_queries[2]);
	user->staff = get_number(user, json_len, g_queries[3]);
	get_projects_data(user, json_len);
	user->stardew_coefficient = (double)get_number(user, json_len, g_queries[6])
		/ 350;
}
