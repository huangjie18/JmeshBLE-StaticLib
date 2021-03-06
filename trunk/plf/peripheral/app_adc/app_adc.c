/*
 * app_adc.c
 *
 *  Created on: 2018��6��26��
 *      Author: jiachuang
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "reg_adc.h"
#include "field_manipulate.h"
#include "app_adc.h"
#include "bx_dbg.h"
#include "ll.h"
#include "rwip.h"
#include "log.h"
#include "co_utils.h"
#include "app_dmac_wrapper.h"
#include "string.h"
#include "plf.h"
#include "rf_reg_typedef.h"
#include "reg_sysc_cpu.h"

extern periph_universal_func_set_t adc_universal_func;



/**
 * @brief  ADC RF_REG setting
 */
void adc_rf_setting_differential_mode(void)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP =0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current =3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 =0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM =0 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT=1;
    hwp_rf_reg->rf_reg_7.ADC_REF_BYPASS =0 ;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode =0 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 0;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 0;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
}

/**
 * @brief  ADC RF_REG setting
 */
void adc_rf_setting_single_mode(void)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP =0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current =3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 =0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM =0 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT=1;
    hwp_rf_reg->rf_reg_7.ADC_REF_BYPASS =0 ;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode =1 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 0;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 0;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
}


void app_adc_set_ldo_delay_us(reg_adc_t *reg , uint16_t us)
{
    uint16_t adc_ldo_val = 0;
    adc_ldo_val = us * APB_CLK / MHZ;
    if(adc_ldo_val > 0x3FF) adc_ldo_val = 0x3FF;
    if(adc_ldo_val < 1)     adc_ldo_val = 1;

    FIELD_WR(reg,CTRL_DELAY,ADC_CH_DLY ,adc_ldo_val);
    FIELD_WR(reg,CTRL_DELAY,ADC_LDO_DLY,adc_ldo_val);
}



void app_adc_init(periph_inst_handle_t hdl)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    reg_adc_t *reg = inst->reg;

    //NO USE
    adc_universal_func.sw_rst_func(inst);
    adc_universal_func.pin_cfg_func(inst,0,0);
    adc_universal_func.intr_op_func(inst,INTR_CLR);
    adc_universal_func.clk_src_cfg_func(inst,0);
    adc_universal_func.clk_gate_func(inst,SET_CLK);
    
    //SET PARAM
    adc_rf_setting_single_mode();
    app_adc_set_ldo_delay_us(reg , inst->param.ldo_delay_us);
    if(inst->param.ldo_force_on)
    {
        FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 1);
    }
    else
    {
        FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 0);
    }
    
    //STAT
    adc_universal_func.sys_stat_func(inst,ADC_INIT);
}

void app_adc_uninit(periph_inst_handle_t hdl)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    reg_adc_t *reg = inst->reg;
    
    //NO USE
    adc_universal_func.clk_gate_func(inst,CLR_CLK);
    adc_universal_func.intr_op_func(inst,INTR_DISABLE);
    
    //Close LDO FORCE ON
    FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 0);

    //STAT
    adc_universal_func.sys_stat_func(inst,ADC_UNINIT);
}

void adc_transfer_sanity_check(uint8_t channel)
{
    // Sanity check
    if(channel > ADC_CHANNEL_SUM_CNT)
    {
        BX_ASSERT(0);
    }
}



uint16_t app_adc_read_without_dma(periph_inst_handle_t hdl , uint8_t channel)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    reg_adc_t *reg = inst->reg;

    //read
    adc_transfer_sanity_check(channel);
    adc_universal_func.sys_stat_func(inst,ADC_READ_START);
    FIELD_WR(reg, CTRL_SNGL, ADC_SNGL_CH   , channel);
    FIELD_WR(reg, CTRL_SNGL, ADC_SNGL_START, 1);
    // wait adc data ready.
    while(FIELD_RD(reg, CTRL_SNGL, ADC_SNGL_START));
    adc_universal_func.sys_stat_func(inst,ADC_READ_DONE);
    
    //return
    return FIELD_RD(reg, CTRL_SNGL, ADC_ADC_DATA_SNGL);

}


static void adc_read_complete(app_adc_inst_t *inst)
{
    void (*callback) (void*,uint8_t) = NULL;
    void * dummy = NULL;
    // Retrieve callback pointer
    callback = inst->env.callback;
    dummy = inst->env.dummy;
    BX_ASSERT(callback);
    // Clear callback pointer
    inst->env.callback = NULL;
    inst->env.dummy = NULL;
    //set iic idle status
    adc_universal_func.sys_stat_func(inst,ADC_READ_DONE);
    // Call handler
    callback(dummy, RWIP_EIF_STATUS_OK);
}

void app_adc_disable_dma(reg_adc_t *reg)
{
    sysc_cpu_adc_has_dma_setf(0);
    FIELD_WR(reg, CTRL0    , ADC_DMA_EN     , 0);
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_START , 0);
}

static void adc_read_dma_callback(app_adc_inst_t *inst)
{
    app_adc_disable_dma(inst->reg);
    adc_read_complete(inst);
}

void app_adc_read_with_dma(periph_inst_handle_t hdl , uint8_t channel , void (*callback) (void*,uint8_t),void* dummy)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    reg_adc_t *reg = inst->reg;
    //set adc param
    sysc_cpu_adc_has_dma_setf(1);
    FIELD_WR(reg, CTRL0    , ADC_DMA_EN     , 1);
    FIELD_WR(reg, CTRL_DMA , ADC_MULT_DLY   , inst->param.dma_delay);
    FIELD_WR(reg, CTRL_DMA , ADC_MULT_NUM   , inst->param.dma_size - 1);
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_CH    , channel);
    while(FIELD_RD(reg, CTRL_MULT, ADC_MULT_START));//wait last ADC convert complete
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_START , 1);
    //set adc idle status
    inst->env.callback = callback;
    inst->env.dummy    = dummy;
    adc_universal_func.sys_stat_func(inst,ADC_READ_START);

    //set dma para
    app_dmac_transfer_param_t param = 
    {
        .callback = (void (*)(void*))adc_read_dma_callback,
        .callback_param = inst,
        .src = (uint8_t *)&reg->FIFO,
        .dst = (uint8_t *)inst->param.dma_bufptr,
        .length = inst->param.dma_size,
        .src_tr_width = Transfer_Width_16_bits,
        .dst_tr_width = Transfer_Width_16_bits,
        .src_msize = Burst_Transaction_Length_1,
        .dst_msize = Burst_Transaction_Length_1,
        .tt_fc = Peripheral_to_Memory_DMAC_Flow_Controller,
        .src_per = Dmac_Iic1_Rx,
        .dst_per = 0,
        .int_en = 1,
    };
    app_dmac_start_wrapper(&param);
}



