/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:16:49 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/25 23:42:21 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"
#include "../cub3d.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <pulse/simple.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

void	sound_read_from_wav(t_sound *sound, char *filename, t_alloc_table *at)
{
	const char	*data;
	size_t		len;

	data = read_to_string(filename, &len, at);
	if (!data)
		return ;
	sound->buffer = (void *) data + sizeof(t_wav_hdr);
	ft_memcpy(&sound->wav, data, sizeof(t_wav_hdr));
}

static bool	must_shutdown(t_sound_system *sys)
{
	bool	b;

	pthread_mutex_lock(&sys->mutex);
	b = sys->shutdown;
	pthread_mutex_unlock(&sys->mutex);
	return (b);
}

static bool	is_valid(t_sound_system *sys)
{
	bool	b;

	pthread_mutex_lock(&sys->mutex);
	b = sys->valid;
	pthread_mutex_unlock(&sys->mutex);
	return (b);
}

// PA_SAMPLE_S16LE / 48000 Hz / 2 channels - used by high quality audio
// PA_SAMPLE_U8    / 11025 Hz / 1 channel  - used by FreeDom sfx
static void sound_routine(t_sound_system *sys)
{
	pa_sample_spec	ss;

	ss.rate = sys->frequency;
	ss.channels = sys->channel_count;
	// if (sound->wav.bits_per_sample == 16)
	// 	ss.format = PA_SAMPLE_S16LE;
	// else if (sound->wav.bits_per_sample == 8)
	// 	ss.format = PA_SAMPLE_U8;
	ss.format = sys->format;
	pthread_mutex_lock(&sys->mutex);
	sys->simple = pa_simple_new(NULL, "MUSIC", PA_STREAM_PLAYBACK, NULL, "MUSIC", &ss, NULL, NULL, NULL);
	pthread_mutex_unlock(&sys->mutex);
	while (!must_shutdown(sys))
	{
		while (!is_valid(sys))
			;
		pthread_mutex_lock(&sys->mutex);
		sys->valid = false;
		pa_simple_write(sys->simple, sys->sound.buffer, sys->sound.wav.file_size - sizeof(t_wav_hdr), NULL);
		pthread_mutex_unlock(&sys->mutex);
		pa_simple_drain(sys->simple, NULL);
	}
	pa_simple_free(sys->simple);
}

void	sound_system_init(
	t_sound_system *sys,
	pa_sample_format_t format,
	uint32_t frequency,
	uint8_t channel_count)
{
	sys->valid = false;
	sys->frequency = frequency;
	sys->channel_count = channel_count;
	sys->format = format;
	pthread_mutex_init(&sys->mutex, NULL);
	pthread_create(&sys->thread, NULL, (void *) sound_routine, sys);
}

void	sound_system_send(t_sound_system *sys, t_sound sound)
{
	pthread_mutex_lock(&sys->mutex);
	pa_simple_flush(sys->simple, NULL);
	sys->sound = sound;
	sys->valid = true;
	pthread_mutex_unlock(&sys->mutex);
}

void	sound_system_shutdown(t_sound_system *sys)
{
	pthread_mutex_lock(&sys->mutex);
	sys->shutdown = true;
	pthread_mutex_unlock(&sys->mutex);
}
