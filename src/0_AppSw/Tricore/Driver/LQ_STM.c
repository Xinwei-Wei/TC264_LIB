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
STM作为系统级的全局定时器，可以为系统提供基础时钟，内有两个比较寄存器，
可产生两个独立的中断，以满足需求。
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

//PID相关宏定义
#define PERIOD_DISTANCE		10.5		//一个计数周期（0-65535）的距离
//#define ANGLE_MID			7.45		//平衡机械中值

//PID相关参数定义
double Kp_Speed_L=0.500, Ki_Speed_L=0.0000, Kd_Speed_L=3.40;	//左轮速度P、I、D
double Kp_Speed_R=0.500, Ki_Speed_R=0.0000, Kd_Speed_R=3.40;	//右轮速度P、I、D
//double Kp_Angle=25.00, Ki_Angle=0.000, Kd_Angle=0.000;			//平衡P、I、D
//double Kp_Accel=0.050, Ki_Accel=0.000, Kd_Accel=0.000;			//加速P、I、D
//double Kp_Veloc=0.100, Ki_Veloc=0.000, Kd_Veloc=0.000;			//速度P、I、D

//PID相关变量定义
double error_L=0, errSum_L=0, errLast_L=0;	//左轮转速误差、误差总和、上次误差
double error_R=0, errSum_R=0, errLast_R=0;	//右轮转速误差、误差总和、上次误差
double pwm_L=0, Pwm_L, pwm_R=0, Pwm_R;		//左右轮PWM控制

int CNT_SPEED_L=0, Period_Counter_L=0, now_L=0, before_L=0;							//左轮转速、圈数、读数、上次读数
int CNT_SPEED_R=0, Period_Counter_R=0, now_R=0, before_R=0;							//右轮转速、圈数、读数、上次读数
int	target_Speed, speed_L, postion_L, target_L=0, speed_R, postion_R, target_R=0;	//目标转速、瞬时转速、位置、目标转速

//float err_Angle, errLast_Angle, target_Angle, ang, gyr, afr;	//角度误差、上次误差、目标角度，MPU6050返回值：角度、角速度、前进加速度
//float err_Accel, errLast_Accel, target_Accel;					//加速误差、上次误差、目标加速
//float err_Veloc, errLast_Veloc, target_Veloc;					//速度误差、上次误差、目标速度

//监视与控制相关变量定义
int flag=0;
double monitor_STM=0;

#define IFX_INTPRIO_STM0_SR0  	  5   //中断服务号
/*************************************************************************
*  函数名称：
*  功能说明：
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：STM中断
*************************************************************************/
IFX_INTERRUPT(STM0_CH0_IRQHandler, STM0_CH0_VECTABNUM, STM0_CH0_PRIORITY);
IFX_INTERRUPT(STM0_CH1_IRQHandler, STM0_CH1_VECTABNUM, STM0_CH1_PRIORITY);
IFX_INTERRUPT(STM1_CH0_IRQHandler, STM1_CH0_VECTABNUM, STM1_CH0_PRIORITY);
IFX_INTERRUPT(STM1_CH1_IRQHandler, STM1_CH1_VECTABNUM, STM1_CH1_PRIORITY);

/** 外部中断CPU标号 */
const uint8 StmIrqVectabNum[4]  = {STM0_CH0_VECTABNUM, STM0_CH1_VECTABNUM, STM1_CH0_VECTABNUM, STM1_CH1_VECTABNUM};

/** 外部中断优先级 */
const uint8 StmIrqPriority[4]   = {STM0_CH0_PRIORITY, STM0_CH1_PRIORITY, STM1_CH0_PRIORITY, STM1_CH1_PRIORITY};

/** 外部中断服务函数地址 */
const void *StmIrqFuncPointer[4] = {&STM0_CH0_IRQHandler, &STM0_CH1_IRQHandler, &STM1_CH0_IRQHandler, &STM1_CH1_IRQHandler};


//	STM初始化配置结构体
IfxStm_CompareConfig g_StmCompareConfig[4];

/*****************************************STM中断服务函数******************************************/

/*************************************************************************
*  函数名称：void STM0_CH0_IRQHandler(void)
*  功能说明：
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：STM0_CH0使用的中断服务函数
*************************************************************************/
void STM0_CH0_IRQHandler(void)
{
	//清除中断标志
	IfxStm_clearCompareFlag(&MODULE_STM0, g_StmCompareConfig[0].comparator);

	//开启新的中断配置，开始下次中断
	IfxStm_increaseCompare(&MODULE_STM0, g_StmCompareConfig[0].comparator, g_StmCompareConfig[0].ticks);

	/* 用户代码 */

	//编码器回传转速
	CNT_SPEED_L =  ENC_GetCounter(ENC4_InPut_P02_8);
	CNT_SPEED_R = -ENC_GetCounter(ENC2_InPut_P33_7);


	//MPU6050回传角度、角速度、前进加速度
//	MPU_Get_Angle(&ang, &gyr, &afr);

//	//加速度控制（基于速度的目标加速度控制）
//	err_Veloc = target_Veloc - (CNT_SPEED_L + CNT_SPEED_R) / 2;
//	target_Accel = Kp_Veloc * err_Veloc;
//
//	//平衡角度控制（基于加速度的目标角度控制）
//	err_Accel = target_Accel - afr;
//	target_Angle = Kp_Accel * err_Accel + ANGLE_MID;
//
//	//平衡控制（基于角度的目标转速控制）
//	errLast_Angle = err_Angle;
//	err_Angle = ang - target_Angle;
//	target_Speed = Kp_Angle * err_Angle + Kd_Angle * (err_Angle - errLast_Angle);

	//启停控制（基于主函数的目标转速控制）
	switch(flag)
	{
		case 1: target_L = 100; target_R = 0; break;
		case 0: target_L = 0; target_R = 0; break;
	}

	/******************** 转速控制（基于目标转速的转速控制）********************/
	//左轮转速计算
	speed_L = getSpeed_L();
//	postion_L = getDistance_L();
	errLast_L = error_L;
	error_L = target_L-speed_L;
	errSum_L += error_L;

	//左轮积分限幅
	if(errSum_L > 50)
		errSum_L = 50;
	if(errSum_L < -50)
		errSum_L = -50;

	//左轮PID控制
	pwm_L += Kp_Speed_L * error_L + Ki_Speed_L * errSum_L + Kd_Speed_L * (error_L - errLast_L);

	//左轮死区消除
//	if(pwm_L > 0)
//		pwm_L += 50;
//	if(pwm_L < 0)
//		pwm_L -= 50;

	//左轮PWM限幅
	if(pwm_L > 1600)
		pwm_L = 1600;
	if(pwm_L < -1600)
		pwm_L = -1600;

	//右轮转速计算
	speed_R = getSpeed_R();
//	postion_R = getDistance_R();
	errLast_R = error_R;
	error_R = target_R - speed_R;
	errSum_R += error_R;

	//右轮积分限幅
	if(errSum_R > 50)
		errSum_R = 50;
	if(errSum_R < -50)
		errSum_R = -50;

	//右轮PID控制
	pwm_R += Kp_Speed_R * error_R + Ki_Speed_R * errSum_R + Kd_Speed_R * (error_R - errLast_R);

	//右轮死区消除
	if(pwm_R > 0)
		Pwm_R += 50;
	if(pwm_R < 0)
		Pwm_R -= 50;

	//右轮PWM限幅
	if(Pwm_R > 2000)
		Pwm_R = 2000;
	if(Pwm_R < -2000)
		Pwm_R = -2000;

	/*******************************电机控制*******************************/
//	ATOM_PWM_SetDuty(ATOMPWM0, Pwm_L*5/2, 12500);	//左轮控制
//	ATOM_PWM_SetDuty(ATOMPWM0, 3000, 12500);		//左轮测试
//	ATOM_PWM_SetDuty(ATOMPWM4, Pwm_R*5/2, 12500);	//右轮控制
//	ATOM_PWM_SetDuty(ATOMPWM4, 8000, 12500);		//右轮测试
//	setPWM_L(pwm_L / 20.0);	//左轮控制（百分比）
	setPWM_L(20);	//左轮控制（百分比）
//	setPWM_R(Pwm_R / 20.0);	//右轮控制（百分比）
	setPWM_R(40);	//右轮控制（百分比）

	/*************************发送数据至上位机**************************/
//	Test_Send_User(speed_L,postion_L,pwm_L,speed_R,postion_R,pwm_R,0,0,0,0,0,0,0,0,0);
//	Test_Send_User(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
//	UART_PutBuff(UART0, "Hello", 5);
//	UART_PutStr(UART0, "Hello");
}

/*************************************************************************
*  函数名称：void STM0_CH1_IRQHandler(void)
*  功能说明：
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：STM0_CH1使用的中断服务函数
*************************************************************************/
void STM0_CH1_IRQHandler(void)
{
	//清除中断标志
	IfxStm_clearCompareFlag(&MODULE_STM0, g_StmCompareConfig[1].comparator);

	//开启新的中断配置，开始下次中断
	IfxStm_increaseCompare(&MODULE_STM0, g_StmCompareConfig[1].comparator, g_StmCompareConfig[1].ticks);

	/* 用户代码 */
	LED_Ctrl(LED1,RVS);        //电平翻转,LED闪烁

}

/*************************************************************************
*  函数名称：void STM1_CH0_IRQHandler(void)
*  功能说明：
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：STM1_CH0使用的中断服务函数
*************************************************************************/
void STM1_CH0_IRQHandler(void)
{
	//清除中断标志
	IfxStm_clearCompareFlag(&MODULE_STM1, g_StmCompareConfig[2].comparator);

	//开启新的中断配置，开始下次中断
	IfxStm_increaseCompare(&MODULE_STM1, g_StmCompareConfig[2].comparator, g_StmCompareConfig[2].ticks);

	/* 用户代码 */
	LED_Ctrl(LED0,RVS);        //电平翻转,LED闪烁
}

/*************************************************************************
*  函数名称：void STM1_CH1_IRQHandler(void)
*  功能说明：
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月30日
*  备    注：STM1_CH1使用的中断服务函数
*************************************************************************/
void STM1_CH1_IRQHandler(void)
{
	//清除中断标志
	IfxStm_clearCompareFlag(&MODULE_STM1, g_StmCompareConfig[3].comparator);

	//开启新的中断配置，开始下次中断
	IfxStm_increaseCompare(&MODULE_STM1, g_StmCompareConfig[3].comparator, g_StmCompareConfig[3].ticks);

	/* 用户代码 */
	LED_Ctrl(LED1,RVS);        //电平翻转,LED闪烁
}

 /*************************************************************************
 *  函数名称：void STM_Init(STM_t stm, STM_Channel_t channel, uint32 us)
 *  功能说明：STM初始化
 *  参数说明：
 * @param    stm      ： STM标号     STM0 、 STM1
 * @param    channel  ： STM通道     STM_Channel_0  STM_Channel_1
 * @param    us       ： STM定时中断 时间
 *  函数返回：无
 *  修改时间：2020年3月10日
 *  举    例：STM_InitConfig(STM0, STM_Channel_0, 50000);  //STM0 通道0初始化 50000us 进入一次中断
 *  备    注：外部中断服务函数在LQ_STM.c中  中断优先级配置在LQ_STM.h中 可以自行修改
 *************************************************************************/
 void STM_InitConfig(STM_t stm, STM_Channel_t channel, uint32 us)
 {
 	char      interruptState;
 	interruptState = disableInterrupts();

 	Ifx_STM * STM = IfxStm_getAddress((IfxStm_Index)stm);
 	uint8_t Index = (uint8_t)IfxStm_getIndex(STM) * 2 + (uint8_t)channel;

 	IfxStm_CompareConfig *stmCompareConfig = &g_StmCompareConfig[Index];

 	//调用结构体实现配置
 	IfxStm_initCompareConfig(stmCompareConfig);

     //挂起
 	IfxStm_enableOcdsSuspend(STM);

 	//获取STM模块的微秒计时 tick 数值
 	sint32 ticks = IfxStm_getTicksFromMicroseconds((Ifx_STM *)STM, us);

 	//修改ticks数值，使能触发输出
 	stmCompareConfig->ticks = ticks;
 	stmCompareConfig->comparator           = (IfxStm_Comparator)channel;
 	stmCompareConfig->comparatorInterrupt  = (IfxStm_ComparatorInterrupt)channel; //中断选择
 	stmCompareConfig->triggerPriority      = StmIrqPriority[Index];               //中断优先级设置
 	stmCompareConfig->typeOfService        = StmIrqVectabNum[Index];              //服务内核

 	//比较功能初始化
 	IfxStm_initCompare(STM, stmCompareConfig);
 	IfxCpu_Irq_installInterruptHandler((void*)StmIrqFuncPointer[Index], StmIrqPriority[Index]);//配置中断函数和中断号

 	restoreInterrupts(interruptState);
 }


 /*************************************************************************
 *  函数名称：void STM_DelayUs(STM_t stm, uint32 us)
 *  功能说明：STM延时
 *  参数说明：
 * @param    stm      ： STM标号     STM0 、 STM1
 * @param    us       ： STM延时     时间 us
 *  函数返回：无
 *  修改时间：2020年3月10日
 *  举    例：STM_DelayUs(STM0, 5000);  //延时5000us
 *  备    注：使用延时函数时，请确保对应STM模块调用过STM_Init函数
 *************************************************************************/
 void STM_DelayUs(STM_t stm, uint32 us)
 {
 	Ifx_STM * STM = IfxStm_getAddress((IfxStm_Index)stm);
 	uint32 tick = IfxStm_getTicksFromMicroseconds(STM, us);
 	IfxStm_waitTicks(STM, tick);
 }

 /*************************************************************************
 *  函数名称：void delayms(unsigned short stmms)
 *  功能说明：延时函数
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2020年3月10日
 *  备    注：IfxStm_waitTicks(&MODULE_STM0, 1);大约10微秒
 *************************************************************************/
 void delayms(unsigned short stmms)	//
 {
   while(stmms--)
   {
 	  IfxStm_waitTicks(&MODULE_STM0, 100000);
   }
 }
 /*************************************************************************
 *  函数名称：uint32  STM_GetNowUs(STM_t stm)
 *  功能说明：STM获取当前时间
 *  参数说明：
 * @param    stm      ： STM标号     STM0 、 STM1
 * @param    us       ： STM延时     时间 us
 *  函数返回：无
 *  修改时间：2020年3月10日
 *  举    例：int32_t NowTime =  STM_GetNowUs(STM0);  //获取STM0 当前时间
 *  备    注：使用延时函数时，请确保对应STM模块调用过STM_Init函数
 *************************************************************************/
 uint32  STM_GetNowUs(STM_t stm)
 {
 	Ifx_STM * STM = IfxStm_getAddress((IfxStm_Index)stm);
 	sint32 freq = (sint32)IfxStm_getFrequency(STM)/1000000;
 	Ifx_TickTime stmNow;
 	char      interruptState;

 	interruptState = disableInterrupts();
 	stmNow         = (Ifx_TickTime)IfxStm_get(STM) & TIME_INFINITE;
 	restoreInterrupts(interruptState);

 	return (uint32_t)(stmNow/freq);
 }

/////////////////////////////////////////////////////////////////////////////////////

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
double getSpeed_L(void)	//单位cm/s
{
	return CNT_SPEED_L * 100.0 * PERIOD_DISTANCE / 1024.0;
}

/**
  * @brief    计算左轮位移
  *
  * @param    无
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      getDistance_L();
  *
  * @date     2021/3/3 星期三
  */
//double getDistance_L(void)   //单位cm
//{
//	double Period_distance_L = PERIOD_DISTANCE;     //一个计数周期转的距离
//	return Period_Counter_L * Period_distance_L + ENC_GetCounter(ENC2_InPut_P33_7) * Period_distance_L / 65535.0;
//}

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
double getSpeed_R(void)   //单位cm/s
{
	return CNT_SPEED_R * 100.0 * PERIOD_DISTANCE / 1024.0;
}

/**
  * @brief    计算右轮位移
  *
  * @param    无
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      getDistance_R();
  *
  * @date     2021/3/3 星期三
  */
//double getDistance_R(void)   //单位cm
//{
//	double Period_distance_R = PERIOD_DISTANCE;     //一个计数周期转的距离
//	return Period_Counter_R * Period_distance_R + ENC_GetCounter(ENC4_InPut_P02_8) * Period_distance_R / 65535.0;
//}

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
void setPWM_L(double percent)
{
	ATOM_PWM_SetDuty(PWM_L1, 100*(50+percent/2.0), 12500);
	ATOM_PWM_SetDuty(PWM_L2, 100*(50-percent/2.0), 12500);
}

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
void setPWM_R(double percent)
{
	ATOM_PWM_SetDuty(PWM_R1, 100*(50-percent/2.0), 12500);
	ATOM_PWM_SetDuty(PWM_R2, 100*(50+percent/2.0), 12500);
}

/**
  * @brief    计算平衡PWM
  *
  * @param    Angle	:倾角
  * @param    Gyro	:角速度
  *
  * @return   PWM计算值
  *
  * @note     by WeiXw
  *
  * @see      Balance_PWM(Angle, Gyro);
  *
  * @date     2021/2/23 星期二
  */
//int Balance_PWM(float Angle, float Gyro)
//{
//	float Bias;
//	int balance;
//	Bias = Angle - ANGLE_MID;							//===求出平衡的角度中值 和机械相关
//	balance = Kp_Balance * Bias + Gyro * Kd_Balance;	//===计算平衡控制的电机PWM
//	return balance;
//}
