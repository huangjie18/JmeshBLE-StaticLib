#ifndef APP_QSPI_WRAPPER_H_
#define APP_QSPI_WRAPPER_H_
#include <stdint.h>
#include <stdbool.h>
#include "dw_apb_ssi_typedef.h"
void app_qspi_init_wrapper(uint8_t mode);

void app_qspi_uninit_wrapper(void);

void app_qspi_std_write_wrapper(uint8_t *data,uint32_t length);

void app_qspi_flash_program_wrapper(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length);

void app_qspi_std_read_wrapper(uint8_t *cmd_buf,uint8_t cmd_len,uint8_t *data_buf,uint16_t data_len);

void app_qspi_multi_read_wrapper(uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length,bool quad);

void app_qspi_config_for_cache_wrapper(uint16_t cache_line_size,uint8_t spi_mode);

uint32_t app_qspi_dr_reg_addr_for_cache_wrapper(void);

void app_qspi_disable_for_cache_wrapper(void);


#endif
