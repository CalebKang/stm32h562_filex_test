/*
 * wave_file_operation.c
 *
 *  Created on: Sep 8, 2025
 *      Author: 
 */
#include "main.h"
#include "app_filex.h"

static wave_conf_t *s_wave_conf;
static uint8_t s_wave_header[44];

static void wave_file_create_header(void)
{
  uint32_t   FileSize;      /* 4 */
  uint16_t   NbrChannels;   /* 22 */
  uint32_t   SampleRate;    /* 24 */

  uint32_t   ByteRate;      /* 28 */
  uint16_t   BlockAlign;    /* 32 */
  uint16_t   BitPerSample;  /* 34 */

  SampleRate = s_wave_conf->sample_rate;      /* Audio sampling frequency */
  NbrChannels = s_wave_conf->channel_number;  /* Number of channels: 1:Mono or 2:Stereo */
  BitPerSample = s_wave_conf->bit_per_sample; /* Number of bits per sample (16, 24 or 32) */
  FileSize = s_wave_conf->saved_file_size;    /* Total length of useful audio data (payload) */
  ByteRate = (SampleRate*(BitPerSample/8)*NbrChannels); /* Number of bytes per second  (sample rate * block align)  */
  BlockAlign = NbrChannels *(BitPerSample/8);           /* channels * bits/sample / 8 */

  /* Write chunkID, must be 'RIFF'  ------------------------------------------*/
  s_wave_header[0] = 'R';
  s_wave_header[1] = 'I';
  s_wave_header[2] = 'F';
  s_wave_header[3] = 'F';

  /* Write the file length ----------------------------------------------------*/
  /* The sampling time: this value will be be written back at the end of the
     recording opearation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  s_wave_header[4] = (uint8_t)(FileSize);
  s_wave_header[5] = (uint8_t)(FileSize >> 8);
  s_wave_header[6] = (uint8_t)(FileSize >> 16);
  s_wave_header[7] = (uint8_t)(FileSize >> 24);

  /* Write the file format, must be 'WAVE' -----------------------------------*/
  s_wave_header[8]  = 'W';
  s_wave_header[9]  = 'A';
  s_wave_header[10] = 'V';
  s_wave_header[11] = 'E';

  /* Write the format chunk, must be'fmt ' -----------------------------------*/
  s_wave_header[12]  = 'f';
  s_wave_header[13]  = 'm';
  s_wave_header[14]  = 't';
  s_wave_header[15]  = ' ';

  /* Write the length of the 'fmt' data, must be 0x10 ------------------------*/
  s_wave_header[16]  = 0x10;
  s_wave_header[17]  = 0x00;
  s_wave_header[18]  = 0x00;
  s_wave_header[19]  = 0x00;

  /* Write the audio format, must be 0x01 (PCM) ------------------------------*/
  s_wave_header[20]  = 0x01;
  s_wave_header[21]  = 0x00;

  /* Write the number of channels, ie. 0x01 (Mono) ---------------------------*/
  s_wave_header[22]  = NbrChannels;
  s_wave_header[23]  = 0x00;

  /* Write the Sample Rate in Hz ---------------------------------------------*/
  /* Write Little Endian ie. 8000 = 0x00001F40 => byte[24]=0x40, byte[27]=0x00*/
  s_wave_header[24]  = (uint8_t)((SampleRate & 0xFF));
  s_wave_header[25]  = (uint8_t)((SampleRate >> 8) & 0xFF);
  s_wave_header[26]  = (uint8_t)((SampleRate >> 16) & 0xFF);
  s_wave_header[27]  = (uint8_t)((SampleRate >> 24) & 0xFF);

  /* Write the Byte Rate -----------------------------------------------------*/
  s_wave_header[28]  = (uint8_t)((ByteRate & 0xFF));
  s_wave_header[29]  = (uint8_t)((ByteRate >> 8) & 0xFF);
  s_wave_header[30]  = (uint8_t)((ByteRate >> 16) & 0xFF);
  s_wave_header[31]  = (uint8_t)((ByteRate >> 24) & 0xFF);

  /* Write the block alignment -----------------------------------------------*/
  s_wave_header[32]  = BlockAlign;
  s_wave_header[33]  = 0x00;

  /* Write the number of bits per sample -------------------------------------*/
  s_wave_header[34]  = BitPerSample;
  s_wave_header[35]  = 0x00;

  /* Write the Data chunk, must be 'data' ------------------------------------*/
  s_wave_header[36]  = 'd';
  s_wave_header[37]  = 'a';
  s_wave_header[38]  = 't';
  s_wave_header[39]  = 'a';

  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  s_wave_header[40] = (uint8_t)(FileSize);
  s_wave_header[41] = (uint8_t)(FileSize >> 8);
  s_wave_header[42] = (uint8_t)(FileSize >> 16);
  s_wave_header[43] = (uint8_t)(FileSize >> 24);
}

static void wave_file_update_header(void)
{
  uint32_t   FileSize;      /* 4 */

  FileSize = s_wave_conf->saved_file_size;

  /* Write the file length ----------------------------------------------------*/
  /* The sampling time: this value will be be written back at the end of the
     recording opearation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  s_wave_header[4] = (uint8_t)(FileSize);
  s_wave_header[5] = (uint8_t)(FileSize >> 8);
  s_wave_header[6] = (uint8_t)(FileSize >> 16);
  s_wave_header[7] = (uint8_t)(FileSize >> 24);
  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  FileSize -=44;
  s_wave_header[40] = (uint8_t)(FileSize);
  s_wave_header[41] = (uint8_t)(FileSize >> 8);
  s_wave_header[42] = (uint8_t)(FileSize >> 16);
  s_wave_header[43] = (uint8_t)(FileSize >> 24);
  /* Return 0 if all operations are OK */
}

int wave_file_create(char *filename, wave_conf_t *wave_conf)
{
  s_wave_conf = wave_conf;
  wave_file_create_header();

  //file_make
  return 0;
}


int wave_file_update(char *filename, uint8_t *buff, int size)
{
  s_wave_conf->saved_file_size += size;

  //file_write

  if(s_wave_conf->saved_file_size >= s_wave_conf->max_file_size)
  {
    return 1;
  }

  return 0;
}


int wave_file_close(char *filename)
{
  wave_file_update_header();

  //file_write

  //file_close
  return 0;
}


int wave_file_is_full(void)
{
  return 0;
}






















