/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:17:14 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/11 10:48:07 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# include <stdint.h>
# include <pulse/simple.h>
# include <stdbool.h>

typedef struct s_wav_hdr
{
	char		magic[4];
	uint32_t	file_size;
	char		format[4];

	char		format_id[4];
	uint32_t	block_size;
	uint16_t	audio_format;
	uint16_t	channel_count;
	uint32_t	frequency;

	uint32_t	byte_per_sec;
	uint16_t	byte_per_block;
	uint16_t	bits_per_sample;

	char		data[4];
	uint32_t	data_size;
}	t_wav_hdr;

typedef struct s_sound
{
	uint16_t	*buffer;
	t_wav_hdr	wav;
	bool		valid;
	pthread_t	thread;
}	t_sound;

void	sound_read_from_wav(t_sound *sound, char *filename);
void	sound_play(t_sound *sound);

#endif
