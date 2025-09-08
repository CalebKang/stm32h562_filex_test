/*
 * csv_file_operation.c
 *
 *  Created on: Sep 8, 2025
 *      Author: 
 */
#include "main.h"

static csv_conf_t *s_csv_conf;

int csv_file_create(char *filename, csv_conf_t *csv_conf)
{
  s_csv_conf = csv_conf;

  return 0;
}


int csv_file_update(char *filename, uint8_t *buff, int size)
{
  return 0;
}


int csv_file_close(char *filename)
{
  return 0;
}


int csv_file_is_full(void)
{
  return 0;
}


int csv_file_init(void)
{
  return 0;
}















