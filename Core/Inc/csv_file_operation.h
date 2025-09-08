/*
 * csv_file_operation.h
 *
 *  Created on: Sep 8, 2025
 *      Author: 
 */

#ifndef INC_CSV_FILE_OPERATION_H_
#define INC_CSV_FILE_OPERATION_H_

typedef struct
{
#define CSV_RECORD_BUFF_SIZE  (64)
  uint32_t recod_buff[CSV_RECORD_BUFF_SIZE];
  uint32_t update_100hz;
  record_e status;
  uint32_t file_number;
  char filename[64];
  uint32_t max_file_size;
  uint32_t saved_file_size;
  filetype_e file_type;
}csv_conf_t;

int csv_file_create(char *filename, csv_conf_t *csv_conf);
int csv_file_update(char *filename, uint8_t *buff, int size);
int csv_file_close(char *filename);
int csv_file_is_full(void);
int csv_file_init(void);

#endif /* INC_CSV_FILE_OPERATION_H_ */
