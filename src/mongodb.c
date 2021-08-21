/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mongodb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:19:54 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/19 18:19:54 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stats.h"

static mongoc_client_t		*g_client;
static mongoc_collection_t	*g_collection;
static bson_oid_t			g_id;
static bson_oid_t			*g_temp;

static void	mongo_create(const char *s)
{
	bson_error_t		error;
	bson_t				*bson;

	bson = bson_new_from_json((const uint8_t *)s, -1, &error);
	if (!mongoc_collection_insert_one(g_collection, bson, NULL, NULL, &error))
		fprintf(stderr, "%s\n", error.message);
	bson_destroy(bson);
}

int	mongo_read(const char *login)
{
	const bson_t		*doc;
	bson_t				*query;
	mongoc_cursor_t		*cursor;
	bson_iter_t			iter;
	bson_iter_t			id;

	query = bson_new();
	BSON_APPEND_UTF8(query, "login", login);
	cursor = mongoc_collection_find_with_opts(g_collection, query, NULL, NULL);
	if (mongoc_cursor_next(cursor, &doc))
	{
		if (bson_iter_init(&iter, doc)
			&& bson_iter_find_descendant(&iter, "_id", &id)
			&& BSON_ITER_HOLDS_OID(&id))
		{
			g_temp = (bson_oid_t *)bson_iter_oid(&id);
			bson_oid_copy(g_temp, &g_id);
			bson_destroy(query);
			mongoc_cursor_destroy(cursor);
			return (0);
		}
	}
	bson_destroy(query);
	mongoc_cursor_destroy(cursor);
	return (1);
}

static void	mongo_update(const char *s)
{
	bson_t			*query;
	bson_t			update;
	bson_t			*user_data;
	bson_error_t	error;

	query = NULL;
	query = BCON_NEW("_id", BCON_OID(&g_id));
	bson_init(&update);
	user_data = bson_new_from_json((const uint8_t *)s, -1, &error);
	bson_append_document(&update, "$set", 4, user_data);
	if (!mongoc_collection_update_one(g_collection, query,
			 &update, NULL, NULL, &error))
		fprintf(stderr, "%s\n", error.message);
	bson_destroy(query);
	bson_destroy(&update);
	bson_destroy(user_data);
}

void	db_add(const char *s, struct mg_str login)
{
	char	*str;

	g_client = mongoc_client_new(getenv("DB_ADDRESS"));
	g_collection = mongoc_client_get_collection(g_client, "users", "data");
	bson_oid_init(&g_id, NULL);
	str = strndup(login.ptr + 1, login.len - 2);
	if (mongo_read(str))
		mongo_create(s);
	else
		mongo_update(s);
	mongoc_collection_destroy(g_collection);
	mongoc_client_destroy(g_client);
	free(str);
}
