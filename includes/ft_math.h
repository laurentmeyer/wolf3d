/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:44:42 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/15 12:44:44 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define DEG_TO_RAD (M_PI / 180.0)

double	lerp_double(double a, double b, double p);
float	normalize_degrees(float degrees);
float	abs_float(float f);

#endif
