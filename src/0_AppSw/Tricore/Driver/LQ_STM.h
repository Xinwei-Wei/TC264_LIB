/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________

����iLLD_1_0_1_11_0�ײ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_STM_H_
#define _LQ_STM_H_

#include "include.h"

#define PWM_L1 IfxGtm_ATOM0_6_TOUT42_P23_1_OUT
#define PWM_L2 IfxGtm_ATOM0_5_TOUT40_P32_4_OUT
#define PWM_R1 IfxGtm_ATOM0_0_TOUT53_P21_2_OUT
#define PWM_R2 IfxGtm_ATOM0_4_TOUT50_P22_3_OUT

/**
 * 	STMģ��ö��
 */
typedef enum
{
	STM0 = 0,
	STM1
}STM_t;

/**
 * 	STMͨ��ö��
 */
typedef enum
{
	STM_Channel_0 = 0,
	STM_Channel_1
}STM_Channel_t;

/** STM��ʱ���ж� STM0  channel0 �жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  STM0_CH0_PRIORITY    110

/** STM��ʱ���ж� STM0  channel0 �жϹ��ĸ��ں˹��� ��Χ��0��CPU0   1��CPU1   3��DMA*/
#define  STM0_CH0_VECTABNUM    0

/** STM��ʱ���ж� STM0  channel1 �жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  STM0_CH1_PRIORITY    111

/** STM��ʱ���ж� STM0  channel1 �жϹ��ĸ��ں˹��� ��Χ��0��CPU0   1��CPU1   3��DMA*/
#define  STM0_CH1_VECTABNUM    0

/** STM��ʱ���ж� STM1  channel0 �жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  STM1_CH0_PRIORITY    112

/** STM��ʱ���ж� STM1  channel0 �жϹ��ĸ��ں˹��� ��Χ��0��CPU0   1��CPU1   3��DMA*/
#define  STM1_CH0_VECTABNUM    1

/** STM��ʱ���ж� STM1  channel1 �жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  STM1_CH1_PRIORITY    113

/** STM��ʱ���ж� STM1  channel1 �жϹ��ĸ��ں˹��� ��Χ��0��CPU0   1��CPU1   3��DMA*/
#define  STM1_CH1_VECTABNUM    1


extern IfxStm_CompareConfig g_StmCompareConfig[4];
void STM_InitConfig(STM_t STM, STM_Channel_t channel, uint32 us);
void STM_DelayUs(STM_t stm, uint32 us);
uint32 STM_GetNowUs(STM_t stm);
void delayms(unsigned short stmms);

/**
  * @brief    ��������ת��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      getSpeed_L();
  *
  * @date     2021/3/3 ������
  */
double getSpeed_L(void);

/**
  * @brief    ��������ת��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      getSpeed_R();
  *
  * @date     2021/3/3 ������
  */
double getSpeed_R(void);

/**
  * @brief    ��������PWM
  *
  * @param    percent: PWMռ�ձ�
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      setPWM_L(50.00);
  *
  * @date     2021/3/3 ������
  */
void setPWM_L(double percent);

/**
  * @brief    ��������PWM
  *
  * @param    percent: PWMռ�ձ�
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      setPWM_R(50.00);
  *
  * @date     2021/3/3 ������
  */
void setPWM_R(double percent);

#endif /* 0_APPSW_TRICORE_APP_LQ_STM_H_ */
