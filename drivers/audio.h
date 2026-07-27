/*
 * Audio Driver - Sound Card and Audio Output
 */

#ifndef AUDIO_DRIVER_H
#define AUDIO_DRIVER_H

#include <stdint.h>

void init_audio(void);
void play_sound(uint32_t frequency, uint32_t duration);
void stop_sound(void);
void play_wav(const char* filename);
void set_volume(uint8_t volume);

#endif
