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

void	mongo_add(const char *s)
{
	mongoc_client_t		*client;
	mongoc_database_t	*database;
	mongoc_collection_t	*collection;
	bson_error_t		error;
	bson_t				*bson;

	client = mongoc_client_new(
			"mongodb+srv://ftstats:ftstats@cluster0.fppou.mongodb.net/"
			"users?retryWrites=true&w=majority"
			);
	database = mongoc_client_get_database(client, "users");
	collection = mongoc_client_get_collection(client, "users", "data");
	bson = bson_new_from_json((const uint8_t *)s, -1, &error);
	if (!mongoc_collection_insert_one(collection, bson, NULL, NULL, &error))
		fprintf(stderr, "%s\n", error.message);
	bson_destroy(bson);
	mongoc_collection_destroy(collection);
	mongoc_database_destroy(database);
	mongoc_client_destroy(client);
}
