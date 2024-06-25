/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:17:14 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 23:18:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# include <stdint.h>
# include <stdbool.h>
# include "../mem.h"

# include <pulse/def.h>
# include <pulse/sample.h>
# include <pulse/simple.h>

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
}	t_sound;

typedef struct s_sound_system
{
	pthread_t			thread;
	pthread_mutex_t		mutex;

	pa_sample_format_t	format;
	uint32_t 			frequency;
	uint8_t				channel_count;

	pa_simple			*simple;

	t_sound				sound;
	bool				valid;

	bool				shutdown;
}	t_sound_system;

void	sound_read_from_wav(t_sound *sound, char *filename, t_alloc_table *at);

void	sound_system_init(
	t_sound_system *sys,
	pa_sample_format_t format,
	uint32_t frequency,
	uint8_t channel_count);
void	sound_system_send(t_sound_system *sys, t_sound sound);
void	sound_system_shutdown(t_sound_system *sys);

#endif
