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

/* Callback for `mg_mgr_poll`. The base of the API.
 * @param c struct mg_connection *: connection
 * @param ev int: event type
 * @param ev_data void *: event data
 * @param fn_data void*: arbitrary pointer */
void	callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

#endif
