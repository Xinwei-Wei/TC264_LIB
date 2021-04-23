/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年4月10日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】Hightec4.9.3/Tasking6.3及以上版本
【Target 】 TC264DA
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________

基于iLLD_1_0_1_11_0底层程序
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_STM_H_
#define _LQ_STM_H_

#include "include.h"

#define PWM_L1 IfxGtm_ATOM0_6_TOUT42_P23_1_OUT
#define PWM_L2 IfxGtm_ATOM0_5_TOUT40_P32_4_OUT
#define PWM_R1 IfxGtm_ATOM0_0_TOUT53_P21_2_OUT
#define PWM_R2 IfxGtm_ATOM0_4_TOUT50_P22_3_OUT

/**
 * 	STM模块枚举
 */
typedef enum
{
	STM0 = 0,
	STM1
}STM_t;

/**
 * 	STM通道枚举
 */
typedef enum
{
	STM_Channel_0 = 0,
	STM_Channel_1
}STM_Channel_t;

/** STM定时器中断 STM0  channel0 中断服务函数优先级   范围：1-255   数字越大 优先级越高  注意优先级不要重复 */
#define  STM0_CH0_PRIORITY    110

/** STM定时器中断 STM0  channel0 中断归哪个内核管理？ 范围：0：CPU0   1：CPU1   3：DMA*/
#define  STM0_CH0_VECTABNUM    0

/** STM定时器中断 STM0  channel1 中断服务函数优先级   范围：1-255   数字越大 优先级越高  注意优先级不要重复 */
#define  STM0_CH1_PRIORITY    111

/** STM定时器中断 STM0  channel1 中断归哪个内核管理？ 范围：0：CPU0   1：CPU1   3：DMA*/
#define  STM0_CH1_VECTABNUM    0

/** STM定时器中断 STM1  channel0 中断服务函数优先级   范围：1-255   数字越大 优先级越高  注意优先级不要重复 */
#define  STM1_CH0_PRIORITY    112

/** STM定时器中断 STM1  channel0 中断归哪个内核管理？ 范围：0：CPU0   1：CPU1   3：DMA*/
#define  STM1_CH0_VECTABNUM    1

/** STM定时器中断 STM1  channel1 中断服务函数优先级   范围：1-255   数字越大 优先级越高  注意优先级不要重复 */
#define  STM1_CH1_PRIORITY    113

/** STM定时器中断 STM1  channel1 中断归哪个内核管理？ 范围：0：CPU0   1：CPU1   3：DMA*/
#define  STM1_CH1_VECTABNUM    1


extern IfxStm_CompareConfig g_StmCompareConfig[4];
void STM_InitConfig(STM_t STM, STM_Channel_t channel, uint32 us);
void STM_DelayUs(STM_t stm, uint32 us);
uint32 STM_GetNowUs(STM_t stm);
void delayms(unsigned short stmms);

/**
  * @brief    计算左轮转速
  *
  * @param    无
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      getSpeed_L();
  *
  * @date     2021/3/3 星期三
  */
double getSpeed_L(void);

/**
  * @brief    计算右轮转速
  *
  * @param    无
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      getSpeed_R();
  *
  * @date     2021/3/3 星期三
  */
double getSpeed_R(void);

/**
  * @brief    设置左轮PWM
  *
  * @param    percent: PWM占空比
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      setPWM_L(50.00);
  *
  * @date     2021/3/3 星期三
  */
void setPWM_L(double percent);

/**
  * @brief    设置右轮PWM
  *
  * @param    percent: PWM占空比
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      setPWM_R(50.00);
  *
  * @date     2021/3/3 星期三
  */
void setPWM_R(double percent);

#endif /* 0_APPSW_TRICORE_APP_LQ_STM_H_ */
