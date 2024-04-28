/*
 * Raspberry Pi Audio output using C asound library
 *
 * Compile:
 *   gcc -Wall -pthread -o aslibex aslibex.c -lasound
 *
 * Usage:
 *   ./aslibex
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <alsa/asoundlib.h>

int main(int argc, char *argv[]) {
  int i;
  snd_pcm_t *pcm;

  /* Open the ALSA sound device */
  snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);

  /* Set the ALSA sounc device parameters */
  snd_pcm_set_params(pcm, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 0);

  /* Create sound buffer */
  char data[8] = {1, 2, 4, 8, 16, 32, 64, 128};

  /* Play sound */
  snd_pcm_writei(pcm, data, 8);

  for (i = 0; i < 255; i++) {
    memset(data, i, 8);
    snd_pcm_writei(pcm, data, 8);
  }

  /* Close the ALSA sound device */
  snd_pcm_close(pcm);

  return EXIT_SUCCESS;
}

