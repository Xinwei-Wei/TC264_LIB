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
STM��Ϊϵͳ����ȫ�ֶ�ʱ��������Ϊϵͳ�ṩ����ʱ�ӣ����������ȽϼĴ�����
�ɲ��������������жϣ�����������
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

//PID��غ궨��
#define PERIOD_DISTANCE		10.5		//һ���������ڣ�0-65535���ľ���
//#define ANGLE_MID			7.45		//ƽ���е��ֵ

//PID��ز�������
double Kp_Speed_L=0.500, Ki_Speed_L=0.0000, Kd_Speed_L=3.40;	//�����ٶ�P��I��D
double Kp_Speed_R=0.500, Ki_Speed_R=0.0000, Kd_Speed_R=3.40;	//�����ٶ�P��I��D
//double Kp_Angle=25.00, Ki_Angle=0.000, Kd_Angle=0.000;			//ƽ��P��I��D
//double Kp_Accel=0.050, Ki_Accel=0.000, Kd_Accel=0.000;			//����P��I��D
//double Kp_Veloc=0.100, Ki_Veloc=0.000, Kd_Veloc=0.000;			//�ٶ�P��I��D

//PID��ر�������
double error_L=0, errSum_L=0, errLast_L=0;	//����ת��������ܺ͡��ϴ����
double error_R=0, errSum_R=0, errLast_R=0;	//����ת��������ܺ͡��ϴ����
double pwm_L=0, Pwm_L, pwm_R=0, Pwm_R;		//������PWM����

int CNT_SPEED_L=0, Period_Counter_L=0, now_L=0, before_L=0;							//����ת�١�Ȧ�����������ϴζ���
int CNT_SPEED_R=0, Period_Counter_R=0, now_R=0, before_R=0;							//����ת�١�Ȧ�����������ϴζ���
int	target_Speed, speed_L, postion_L, target_L=0, speed_R, postion_R, target_R=0;	//Ŀ��ת�١�˲ʱת�١�λ�á�Ŀ��ת��

//float err_Angle, errLast_Angle, target_Angle, ang, gyr, afr;	//�Ƕ����ϴ���Ŀ��Ƕȣ�MPU6050����ֵ���Ƕȡ����ٶȡ�ǰ�����ٶ�
//float err_Accel, errLast_Accel, target_Accel;					//�������ϴ���Ŀ�����
//float err_Veloc, errLast_Veloc, target_Veloc;					//�ٶ����ϴ���Ŀ���ٶ�

//�����������ر�������
int flag=0;
double monitor_STM=0;

#define IFX_INTPRIO_STM0_SR0  	  5   //�жϷ����
/*************************************************************************
*  �������ƣ�
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��STM�ж�
*************************************************************************/
IFX_INTERRUPT(STM0_CH0_IRQHandler, STM0_CH0_VECTABNUM, STM0_CH0_PRIORITY);
IFX_INTERRUPT(STM0_CH1_IRQHandler, STM0_CH1_VECTABNUM, STM0_CH1_PRIORITY);
IFX_INTERRUPT(STM1_CH0_IRQHandler, STM1_CH0_VECTABNUM, STM1_CH0_PRIORITY);
IFX_INTERRUPT(STM1_CH1_IRQHandler, STM1_CH1_VECTABNUM, STM1_CH1_PRIORITY);

/** �ⲿ�ж�CPU��� */
const uint8 StmIrqVectabNum[4]  = {STM0_CH0_VECTABNUM, STM0_CH1_VECTABNUM, STM1_CH0_VECTABNUM, STM1_CH1_VECTABNUM};

/** �ⲿ�ж����ȼ� */
const uint8 StmIrqPriority[4]   = {STM0_CH0_PRIORITY, STM0_CH1_PRIORITY, STM1_CH0_PRIORITY, STM1_CH1_PRIORITY};

/** �ⲿ�жϷ�������ַ */
const void *StmIrqFuncPointer[4] = {&STM0_CH0_IRQHandler, &STM0_CH1_IRQHandler, &STM1_CH0_IRQHandler, &STM1_CH1_IRQHandler};


//	STM��ʼ�����ýṹ��
IfxStm_CompareConfig g_StmCompareConfig[4];

/*****************************************STM�жϷ�����******************************************/

/*************************************************************************
*  �������ƣ�void STM0_CH0_IRQHandler(void)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��STM0_CH0ʹ�õ��жϷ�����
*************************************************************************/
void STM0_CH0_IRQHandler(void)
{
	//����жϱ�־
	IfxStm_clearCompareFlag(&MODULE_STM0, g_StmCompareConfig[0].comparator);

	//�����µ��ж����ã���ʼ�´��ж�
	IfxStm_increaseCompare(&MODULE_STM0, g_StmCompareConfig[0].comparator, g_StmCompareConfig[0].ticks);

	/* �û����� */

	//�������ش�ת��
	CNT_SPEED_L =  ENC_GetCounter(ENC4_InPut_P02_8);
	CNT_SPEED_R = -ENC_GetCounter(ENC2_InPut_P33_7);


	//MPU6050�ش��Ƕȡ����ٶȡ�ǰ�����ٶ�
//	MPU_Get_Angle(&ang, &gyr, &afr);

//	//���ٶȿ��ƣ������ٶȵ�Ŀ����ٶȿ��ƣ�
//	err_Veloc = target_Veloc - (CNT_SPEED_L + CNT_SPEED_R) / 2;
//	target_Accel = Kp_Veloc * err_Veloc;
//
//	//ƽ��Ƕȿ��ƣ����ڼ��ٶȵ�Ŀ��Ƕȿ��ƣ�
//	err_Accel = target_Accel - afr;
//	target_Angle = Kp_Accel * err_Accel + ANGLE_MID;
//
//	//ƽ����ƣ����ڽǶȵ�Ŀ��ת�ٿ��ƣ�
//	errLast_Angle = err_Angle;
//	err_Angle = ang - target_Angle;
//	target_Speed = Kp_Angle * err_Angle + Kd_Angle * (err_Angle - errLast_Angle);

	//��ͣ���ƣ�������������Ŀ��ת�ٿ��ƣ�
	switch(flag)
	{
		case 1: target_L = 100; target_R = 0; break;
		case 0: target_L = 0; target_R = 0; break;
	}

	/******************** ת�ٿ��ƣ�����Ŀ��ת�ٵ�ת�ٿ��ƣ�********************/
	//����ת�ټ���
	speed_L = getSpeed_L();
//	postion_L = getDistance_L();
	errLast_L = error_L;
	error_L = target_L-speed_L;
	errSum_L += error_L;

	//���ֻ����޷�
	if(errSum_L > 50)
		errSum_L = 50;
	if(errSum_L < -50)
		errSum_L = -50;

	//����PID����
	pwm_L += Kp_Speed_L * error_L + Ki_Speed_L * errSum_L + Kd_Speed_L * (error_L - errLast_L);

	//������������
//	if(pwm_L > 0)
//		pwm_L += 50;
//	if(pwm_L < 0)
//		pwm_L -= 50;

	//����PWM�޷�
	if(pwm_L > 1600)
		pwm_L = 1600;
	if(pwm_L < -1600)
		pwm_L = -1600;

	//����ת�ټ���
	speed_R = getSpeed_R();
//	postion_R = getDistance_R();
	errLast_R = error_R;
	error_R = target_R - speed_R;
	errSum_R += error_R;

	//���ֻ����޷�
	if(errSum_R > 50)
		errSum_R = 50;
	if(errSum_R < -50)
		errSum_R = -50;

	//����PID����
	pwm_R += Kp_Speed_R * error_R + Ki_Speed_R * errSum_R + Kd_Speed_R * (error_R - errLast_R);

	//������������
	if(pwm_R > 0)
		Pwm_R += 50;
	if(pwm_R < 0)
		Pwm_R -= 50;

	//����PWM�޷�
	if(Pwm_R > 2000)
		Pwm_R = 2000;
	if(Pwm_R < -2000)
		Pwm_R = -2000;

	/*******************************�������*******************************/
//	ATOM_PWM_SetDuty(ATOMPWM0, Pwm_L*5/2, 12500);	//���ֿ���
//	ATOM_PWM_SetDuty(ATOMPWM0, 3000, 12500);		//���ֲ���
//	ATOM_PWM_SetDuty(ATOMPWM4, Pwm_R*5/2, 12500);	//���ֿ���
//	ATOM_PWM_SetDuty(ATOMPWM4, 8000, 12500);		//���ֲ���
//	setPWM_L(pwm_L / 20.0);	//���ֿ��ƣ��ٷֱȣ�
	setPWM_L(20);	//���ֿ��ƣ��ٷֱȣ�
//	setPWM_R(Pwm_R / 20.0);	//���ֿ��ƣ��ٷֱȣ�
	setPWM_R(40);	//���ֿ��ƣ��ٷֱȣ�

	/*************************������������λ��**************************/
//	Test_Send_User(speed_L,postion_L,pwm_L,speed_R,postion_R,pwm_R,0,0,0,0,0,0,0,0,0);
//	Test_Send_User(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
//	UART_PutBuff(UART0, "Hello", 5);
//	UART_PutStr(UART0, "Hello");
}

/*************************************************************************
*  �������ƣ�void STM0_CH1_IRQHandler(void)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��STM0_CH1ʹ�õ��жϷ�����
*************************************************************************/
void STM0_CH1_IRQHandler(void)
{
	//����жϱ�־
	IfxStm_clearCompareFlag(&MODULE_STM0, g_StmCompareConfig[1].comparator);

	//�����µ��ж����ã���ʼ�´��ж�
	IfxStm_increaseCompare(&MODULE_STM0, g_StmCompareConfig[1].comparator, g_StmCompareConfig[1].ticks);

	/* �û����� */
	LED_Ctrl(LED1,RVS);        //��ƽ��ת,LED��˸

}

/*************************************************************************
*  �������ƣ�void STM1_CH0_IRQHandler(void)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��STM1_CH0ʹ�õ��жϷ�����
*************************************************************************/
void STM1_CH0_IRQHandler(void)
{
	//����жϱ�־
	IfxStm_clearCompareFlag(&MODULE_STM1, g_StmCompareConfig[2].comparator);

	//�����µ��ж����ã���ʼ�´��ж�
	IfxStm_increaseCompare(&MODULE_STM1, g_StmCompareConfig[2].comparator, g_StmCompareConfig[2].ticks);

	/* �û����� */
	LED_Ctrl(LED0,RVS);        //��ƽ��ת,LED��˸
}

/*************************************************************************
*  �������ƣ�void STM1_CH1_IRQHandler(void)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��30��
*  ��    ע��STM1_CH1ʹ�õ��жϷ�����
*************************************************************************/
void STM1_CH1_IRQHandler(void)
{
	//����жϱ�־
	IfxStm_clearCompareFlag(&MODULE_STM1, g_StmCompareConfig[3].comparator);

	//�����µ��ж����ã���ʼ�´��ж�
	IfxStm_increaseCompare(&MODULE_STM1, g_StmCompareConfig[3].comparator, g_StmCompareConfig[3].ticks);

	/* �û����� */
	LED_Ctrl(LED1,RVS);        //��ƽ��ת,LED��˸
}

 /*************************************************************************
 *  �������ƣ�void STM_Init(STM_t stm, STM_Channel_t channel, uint32 us)
 *  ����˵����STM��ʼ��
 *  ����˵����
 * @param    stm      �� STM���     STM0 �� STM1
 * @param    channel  �� STMͨ��     STM_Channel_0  STM_Channel_1
 * @param    us       �� STM��ʱ�ж� ʱ��
 *  �������أ���
 *  �޸�ʱ�䣺2020��3��10��
 *  ��    ����STM_InitConfig(STM0, STM_Channel_0, 50000);  //STM0 ͨ��0��ʼ�� 50000us ����һ���ж�
 *  ��    ע���ⲿ�жϷ�������LQ_STM.c��  �ж����ȼ�������LQ_STM.h�� ���������޸�
 *************************************************************************/
 void STM_InitConfig(STM_t stm, STM_Channel_t channel, uint32 us)
 {
 	char      interruptState;
 	interruptState = disableInterrupts();

 	Ifx_STM * STM = IfxStm_getAddress((IfxStm_Index)stm);
 	uint8_t Index = (uint8_t)IfxStm_getIndex(STM) * 2 + (uint8_t)channel;

 	IfxStm_CompareConfig *stmCompareConfig = &g_StmCompareConfig[Index];

 	//���ýṹ��ʵ������
 	IfxStm_initCompareConfig(stmCompareConfig);

     //����
 	IfxStm_enableOcdsSuspend(STM);

 	//��ȡSTMģ���΢���ʱ tick ��ֵ
 	sint32 ticks = IfxStm_getTicksFromMicroseconds((Ifx_STM *)STM, us);

 	//�޸�ticks��ֵ��ʹ�ܴ������
 	stmCompareConfig->ticks = ticks;
 	stmCompareConfig->comparator           = (IfxStm_Comparator)channel;
 	stmCompareConfig->comparatorInterrupt  = (IfxStm_ComparatorInterrupt)channel; //�ж�ѡ��
 	stmCompareConfig->triggerPriority      = StmIrqPriority[Index];               //�ж����ȼ�����
 	stmCompareConfig->typeOfService        = StmIrqVectabNum[Index];              //�����ں�

 	//�ȽϹ��ܳ�ʼ��
 	IfxStm_initCompare(STM, stmCompareConfig);
 	IfxCpu_Irq_installInterruptHandler((void*)StmIrqFuncPointer[Index], StmIrqPriority[Index]);//�����жϺ������жϺ�

 	restoreInterrupts(interruptState);
 }


 /*************************************************************************
 *  �������ƣ�void STM_DelayUs(STM_t stm, uint32 us)
 *  ����˵����STM��ʱ
 *  ����˵����
 * @param    stm      �� STM���     STM0 �� STM1
 * @param    us       �� STM��ʱ     ʱ�� us
 *  �������أ���
 *  �޸�ʱ�䣺2020��3��10��
 *  ��    ����STM_DelayUs(STM0, 5000);  //��ʱ5000us
 *  ��    ע��ʹ����ʱ����ʱ����ȷ����ӦSTMģ����ù�STM_Init����
 *************************************************************************/
 void STM_DelayUs(STM_t stm, uint32 us)
 {
 	Ifx_STM * STM = IfxStm_getAddress((IfxStm_Index)stm);
 	uint32 tick = IfxStm_getTicksFromMicroseconds(STM, us);
 	IfxStm_waitTicks(STM, tick);
 }

 /*************************************************************************
 *  �������ƣ�void delayms(unsigned short stmms)
 *  ����˵������ʱ����
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��3��10��
 *  ��    ע��IfxStm_waitTicks(&MODULE_STM0, 1);��Լ10΢��
 *************************************************************************/
 void delayms(unsigned short stmms)	//
 {
   while(stmms--)
   {
 	  IfxStm_waitTicks(&MODULE_STM0, 100000);
   }
 }
 /*************************************************************************
 *  �������ƣ�uint32  STM_GetNowUs(STM_t stm)
 *  ����˵����STM��ȡ��ǰʱ��
 *  ����˵����
 * @param    stm      �� STM���     STM0 �� STM1
 * @param    us       �� STM��ʱ     ʱ�� us
 *  �������أ���
 *  �޸�ʱ�䣺2020��3��10��
 *  ��    ����int32_t NowTime =  STM_GetNowUs(STM0);  //��ȡSTM0 ��ǰʱ��
 *  ��    ע��ʹ����ʱ����ʱ����ȷ����ӦSTMģ����ù�STM_Init����
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
double getSpeed_L(void)	//��λcm/s
{
	return CNT_SPEED_L * 100.0 * PERIOD_DISTANCE / 1024.0;
}

/**
  * @brief    ��������λ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      getDistance_L();
  *
  * @date     2021/3/3 ������
  */
//double getDistance_L(void)   //��λcm
//{
//	double Period_distance_L = PERIOD_DISTANCE;     //һ����������ת�ľ���
//	return Period_Counter_L * Period_distance_L + ENC_GetCounter(ENC2_InPut_P33_7) * Period_distance_L / 65535.0;
//}

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
double getSpeed_R(void)   //��λcm/s
{
	return CNT_SPEED_R * 100.0 * PERIOD_DISTANCE / 1024.0;
}

/**
  * @brief    ��������λ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      getDistance_R();
  *
  * @date     2021/3/3 ������
  */
//double getDistance_R(void)   //��λcm
//{
//	double Period_distance_R = PERIOD_DISTANCE;     //һ����������ת�ľ���
//	return Period_Counter_R * Period_distance_R + ENC_GetCounter(ENC4_InPut_P02_8) * Period_distance_R / 65535.0;
//}

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
void setPWM_L(double percent)
{
	ATOM_PWM_SetDuty(PWM_L1, 100*(50+percent/2.0), 12500);
	ATOM_PWM_SetDuty(PWM_L2, 100*(50-percent/2.0), 12500);
}

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
void setPWM_R(double percent)
{
	ATOM_PWM_SetDuty(PWM_R1, 100*(50-percent/2.0), 12500);
	ATOM_PWM_SetDuty(PWM_R2, 100*(50+percent/2.0), 12500);
}

/**
  * @brief    ����ƽ��PWM
  *
  * @param    Angle	:���
  * @param    Gyro	:���ٶ�
  *
  * @return   PWM����ֵ
  *
  * @note     by WeiXw
  *
  * @see      Balance_PWM(Angle, Gyro);
  *
  * @date     2021/2/23 ���ڶ�
  */
//int Balance_PWM(float Angle, float Gyro)
//{
//	float Bias;
//	int balance;
//	Bias = Angle - ANGLE_MID;							//===���ƽ��ĽǶ���ֵ �ͻ�е���
//	balance = Kp_Balance * Bias + Gyro * Kd_Balance;	//===����ƽ����Ƶĵ��PWM
//	return balance;
//}
