/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:17:14 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/10 13:23:41 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# include <stdint.h>

typedef struct s_sound
{
	uint16_t	*buffer;
}	t_sound;

void	sound_read_from_wav(t_sound *sound, char *filename);

#endif
