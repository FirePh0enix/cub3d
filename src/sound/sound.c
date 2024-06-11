/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:16:49 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/11 10:37:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"
#include "../cub3d.h"
#include <pthread.h>
#include <pulse/def.h>
#include <pulse/sample.h>
#include <pulse/simple.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

void	sound_read_from_wav(t_sound *sound, char *filename)
{
	const char	*data;
	size_t		len;

	data = read_to_string(filename, &len);
	if (!data)
		return ;
	sound->valid = true;
	sound->thread = 0;
	sound->buffer = (void *) data + sizeof(t_wav_hdr);
	ft_memcpy(&sound->wav, data, sizeof(t_wav_hdr));
}

static void sound_routine(t_sound *sound)
{
	pa_simple		*simple;
	pa_sample_spec	ss;

	ss.rate = sound->wav.frequency;
	ss.channels = sound->wav.channel_count;
	if (sound->wav.bits_per_sample == 16)
		ss.format = PA_SAMPLE_S16LE;
	else if (sound->wav.bits_per_sample == 8)
		ss.format = PA_SAMPLE_U8;
	simple = pa_simple_new(NULL, "MUSIC", PA_STREAM_PLAYBACK, NULL, "MUSIC", &ss, NULL, NULL, NULL);
	pa_simple_write(simple, sound->buffer, sound->wav.file_size - sizeof(t_wav_hdr), NULL);
	pa_simple_drain(simple, NULL);
	pa_simple_free(simple);
}

void	sound_play(t_sound *sound)
{
	// FIXME:
	// Don't create one thread every time the sound is played, it causes freezes !
	if (sound->thread)
		pthread_join(sound->thread, NULL);
	if (sound->valid)
		pthread_create(&sound->thread, NULL, (void *) sound_routine, sound);
}
