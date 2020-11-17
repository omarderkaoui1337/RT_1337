/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scaling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oderkaou <oderkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:17:49 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/11/12 16:46:08 by oderkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_vector	vec_kscale(float k, t_vector v)
{
	return ((t_vector){k * v.x, k * v.y, k * v.z});
}

float			get_dist(t_vector eye, t_vector look_at)
{
	float result;
	float a;
	float b;
	float c;

	a = pow((look_at.x - eye.x), 2);
	b = pow((look_at.y - eye.y), 2);
	c = pow((look_at.z - eye.z), 2);
	result = sqrt(a + b + c);
	return (result);
}