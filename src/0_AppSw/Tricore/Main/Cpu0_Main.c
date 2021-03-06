#include "..\Driver\include.h"//����ģ���ͷ�ļ�

#define FeedSafetyDog() IfxScuWdt_serviceSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword())	//ι��

App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */

extern double pwm_L, Pwm_L, pwm_R, Pwm_R;
extern int	target_Speed, speed_L, postion_L, target_L, speed_R, postion_R, target_R;
extern float err_Angle, errLast_Angle, target_Angle, ang, gyr, afr;
extern int flag;

void System_Init(void);
void Periph_Init(void);
void Wdt_Init(uint16);

int core0_main (void)
{
	System_Init();	//ϵͳ��ʼ��
	Periph_Init();	//�����ʼ��
    while(1)
	{
    	FeedSafetyDog();
    	OLED_NUM(0, 0, ang, 5, 3, 2);
    	OLED_NUM(0, 2, afr, 5, 3, 2);
    	OLED_NUM(0, 4, target_Angle, 5, 3, 2);
    	OLED_NUM(0, 6, target_Speed, 5, 3, 2);
    	if(!KEY_Read(KEY1))
    	{
    		delayms(10);
    		if(!KEY_Read(KEY1))
    		{
//    			target_L = 100;
//    			target_R = 0;
    			flag = 1;
    		}
    		while(!KEY_Read(KEY1));
    	}
    	if(!KEY_Read(KEY0))
    	{
    		delayms(10);
    		if(!KEY_Read(KEY0))
    		{
//    			target_L = 0;
//    			target_R = 0;
    			flag = 0;
    		}
    		while(!KEY_Read(KEY0));
    	}
    	Test_Send_User(speed_L,100,0,0,0,0,0,0,0,0,0,0,0,0,0);
    	delayms(100);
//    	LED_Ctrl(LED0,RVS);
//    	LED_Ctrl(LED2,RVS);
//    	LED_Ctrl(LED1,RVS);
//    	LED_Ctrl(LED3,RVS);
//    	delayms(50);
	}
	return 0;
}

//ϵͳ��ʼ��������
void System_Init(void)
{
	//�ر�CPU���ж�
	IfxCpu_disableInterrupts();

	//�رտ��Ź�
	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	//��ȡ����Ƶ��
	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

	//�������Ź���1100ms
//	Wdt_Init(1100);
	initTime();

	//����CPU���ж�
	IfxCpu_enableInterrupts();
}

//�����ʼ��������
void Periph_Init(void)
{
    OLED_Init();											//��ʼ��4��OLED
	IIC_Init();												//��ʼ��IIC
	MPU6050_Init();											//��ʼ��MPU6050
    UART_InitConfig(UART0_RX_P14_1,UART0_TX_P14_0, 115200);	//��ʼ��UART0��������115200
    ENC_InitConfig(ENC2_InPut_P33_7, ENC2_Dir_P33_6);		//��ʼ��Encoder_L
    ENC_InitConfig(ENC4_InPut_P02_8, ENC4_Dir_P33_5);		//��ʼ��Encoder_R
    ATOM_PWM_InitConfig(PWM_L, 5000, 12500);				//����PWM�������׼ռ�ձ�50%
    PIN_InitConfig(DIR_L, PIN_MODE_OUTPUT, 1);				//���ַ��������Ĭ��GND
    ATOM_PWM_SetDuty(PWM_L, 0, 12500);						//����ֹͣ
    ATOM_PWM_InitConfig(PWM_R, 5000, 12500);				//����PWM�������׼ռ�ձ�50%
    PIN_InitConfig(DIR_R, PIN_MODE_OUTPUT, 0);				//���ַ��������Ĭ��VCC
    ATOM_PWM_SetDuty(PWM_R, 0, 12500);						//����ֹͣ
    GPIO_LED_Init();										//��ʼ��LED��P10.6��P10.5
    GPIO_KEY_Init();										//��ʼ������
    STM_InitConfig(STM0, STM_Channel_0, 10000);				//��ʼ��PID���ƶ�ʱ�����жϼ��10ms
}

//���Ź���ʼ������
void Wdt_Init(uint16 ms)
{
	uint16 num = ms * 6;													//����ι�����
	Ifx_SCU_WDTS *SafetyWatchdog = &MODULE_SCU.WDTS;						//���Ź�ѡ��
	IfxScuWdt_Config Wdt_config;											//���Ź����ýṹ��
	IfxScuWdt_initConfig(&Wdt_config);										//��ʼ�����ýṹ��
	Wdt_config.reload = 0xFFFF - num;										//����ʱ��
	IfxScuWdt_initSafetyWatchdog(SafetyWatchdog, &Wdt_config);				//��ʼ�����Ź�
	IfxScuWdt_enableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());	//ʹ�ܿ��Ź�
}
