/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��zyf/chiusir
��E-mail  ��chiusir@163.com
�������汾��V1.0
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
����iLLD_1_0_1_11_0�ײ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_INCLUDE_H_
#define _LQ_INCLUDE_H_

/////////////c��׼���ļ�//////////////////////////////////////////////////
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

/////////////illD�ײ���ļ�//////////////////////////////////////////////////
#include <Asclin\Asc\IfxAsclin_Asc.h>
#include "Asclin\Spi\IfxAsclin_Spi.h"
#include "Ccu6\TPwm\IfxCcu6_TPwm.h"
#include "Ccu6\Timer\IfxCcu6_Timer.h"
#include "Ccu6\Icu\IfxCcu6_Icu.h"
#include "Ccu6\PwmBc\IfxCcu6_PwmBc.h"
#include "Compilers.h"
#include "ConfigurationIsr.h"
#include <Configuration.h>
#include <Cif\Cam\IfxCif_Cam.h>
#include "Cif\Std\IfxCif.h"
#include "Cpu\Std\Ifx_Types.h"
#include "Cpu\Irq\IfxCpu_Irq.h"
#include <Cpu\Std\IfxCpu.h>
#include "Cpu\Std\Platform_Types.h"
#include "Cpu\Std\IfxCpu_Intrinsics.h"
#include <Dma\Dma\IfxDma_Dma.h>
#include "Flash\Std\IfxFlash.h"
#include <Fft\Fft\IfxFft_Fft.h>
#include "Gtm\Std\IfxGtm.h"
#include "Gtm\Std\IfxGtm_Tom.h"
#include "Gtm\Std\IfxGtm_Tim.h"
#include "Gtm\Atom\Pwm\IfxGtm_Atom_Pwm.h"
#include "Gtm\Tim\In\IfxGtm_Tim_In.h"
#include "Gtm\Tom\Pwm\IfxGtm_Tom_Pwm.h"
#include "Gtm\Tom\Timer\IfxGtm_Tom_Timer.h"
#include "Gtm\Tom\PwmHl\IfxGtm_Tom_PwmHl.h"
#include "Gtm\Trig\IfxGtm_Trig.h"
#include <Gpt12\IncrEnc\IfxGpt12_IncrEnc.h>
#include "Gpt12\Std\IfxGpt12.h"
//#include "Ifx_Assert.h"
#include <I2c\I2c\IfxI2c_I2c.h>
#include "IfxCpu_reg.h"
#include <Ifx_Cfg.h>
#include "IfxScu_reg.h"
#include "IfxPort_reg.h"
#include "Port\Std\IfxPort.h"
#include "Port\Io\IfxPort_Io.h"
#include "Qspi\SpiMaster\IfxQspi_SpiMaster.h"
#include "Qspi\SpiSlave\IfxQspi_SpiSlave.h"
#include "SysSe\Bsp\Bsp.h"
#include "Stm\Std\IfxStm.h"
#include "Scu\Std\IfxScuWdt.h"
#include "Src\Std\IfxSrc.h"
#include "Scu\Std\IfxScuEru.h"
#include "Tricore\Compilers\Compilers.h"
#include "Vadc\Adc\IfxVadc_Adc.h"
#include "_PinMap\IfxGtm_PinMap.h"
#include "_Reg\IfxVadc_reg.h"
#include "_Reg\IfxStm_reg.h"
#include "_Utilities\Ifx_Assert.h"

/////////////���������ļ�//////////////////////////////////////////////////
#include "LQ_ADC.h"
#include "LQ_DMA.h"
#include "LQ_EEPROM.h"
#include "LQ_FFT.h"
#include "LQ_GPIO.h"
#include "LQ_GPT12_ENC.h"
#include "LQ_GTM.h"
#include "LQ_SOFTI2C.h"
#include "LQ_SPI.h"
#include "LQ_STM.h"
#include "LQ_UART.h"

/////////////�û�Ӧ��ʵ��//////////////////////////////////////////////////
//#include "..\APP\LQ_CAM.h"
#include "..\APP\LQ_ADC_7Mic.h"
#include "..\APP\LQ_CAMERA.h"
#include "..\APP\LQ_I2C_9AX.h"
#include "..\APP\LQ_GPIO_ExInt.h"
#include "..\APP\LQ_ICM20602.h"
#include "..\APP\LQ_GPIO_KEY.h"
#include "..\APP\LQ_GPIO_LED.h"
#include "..\APP\LQ_GPT_mini512.h"
#include "..\APP\LQ_Atom_Motor.h"
#include "..\APP\LQ_I2C_MPU6050.h"
#include "..\APP\LQ_MT9V034.h"
//#include "..\APP\LQ_OLED096.h"
#include "..\APP\LQ_Tom_Servo.h"
#include "..\APP\LQ_I2C_VL53.h"
#include "..\APP\LQ_TFT18.h"
#include "..\APP\OLED_IIC.h"
////////////////////////////////////////////////////////////////////////////
typedef struct
{
    float32 sysFreq;  //Actual SPB frequency
    float32 cpuFreq;  //Actual CPU frequency
    float32 pllFreq;  //Actual PLL frequency
    float32 stmFreq;  //Actual STM frequency
} AppInfo;

// Application information
typedef struct
{
    AppInfo info;     //Info object
} App_Cpu0;

#endif
////////////////////////////////////////////////////////////////////////////