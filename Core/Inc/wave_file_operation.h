/*
 * wave_file_operation.h
 *
 *  Created on: Sep 8, 2025
 *      Author: 
 */

#ifndef INC_WAVE_FILE_OPERATION_H_
#define INC_WAVE_FILE_OPERATION_H_

typedef struct
{
#define WAV_RECORD_BUFF_SIZE  (1024)
  uint32_t recod_buff[WAV_RECORD_BUFF_SIZE];
  int update_pointer;
  record_e status;
  uint32_t file_number;
  char filename[64];
  uint32_t sample_rate;
  uint32_t bit_per_sample;
  uint32_t channel_number;
  uint32_t max_file_size;
  uint32_t saved_file_size;
  filetype_e file_type;
}wave_conf_t;

int wave_file_create(char *filename, wave_conf_t *wave_conf);
int wave_file_update(char *filename, uint8_t *buff, int size);
int wave_file_close(char *filename);
int wave_file_is_full(void);
int wave_file_init(void);

#endif /* INC_WAVE_FILE_OPERATION_H_ */
