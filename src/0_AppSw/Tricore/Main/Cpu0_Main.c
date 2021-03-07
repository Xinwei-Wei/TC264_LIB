#include "..\Driver\include.h"//各个模块的头文件

#define FeedSafetyDog() IfxScuWdt_serviceSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword())	//喂狗

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
	System_Init();	//系统初始化
	Periph_Init();	//外设初始化
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

//系统初始化函数组
void System_Init(void)
{
	//关闭CPU总中断
	IfxCpu_disableInterrupts();

	//关闭看门狗
	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	//读取总线频率
	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

	//开启看门狗，1100ms
//	Wdt_Init(1100);
	initTime();

	//开启CPU总中断
	IfxCpu_enableInterrupts();
}

//外设初始化函数组
void Periph_Init(void)
{
    OLED_Init();											//初始化4线OLED
	IIC_Init();												//初始化IIC
	MPU6050_Init();											//初始化MPU6050
    UART_InitConfig(UART0_RX_P14_1,UART0_TX_P14_0, 115200);	//初始化UART0，波特率115200
    ENC_InitConfig(ENC2_InPut_P33_7, ENC2_Dir_P33_6);		//初始化Encoder_L
    ENC_InitConfig(ENC4_InPut_P02_8, ENC4_Dir_P33_5);		//初始化Encoder_R
    ATOM_PWM_InitConfig(PWM_L, 5000, 12500);				//左轮PWM输出，基准占空比50%
    PIN_InitConfig(DIR_L, PIN_MODE_OUTPUT, 1);				//左轮方向输出，默认GND
    ATOM_PWM_SetDuty(PWM_L, 0, 12500);						//左轮停止
    ATOM_PWM_InitConfig(PWM_R, 5000, 12500);				//右轮PWM输出，基准占空比50%
    PIN_InitConfig(DIR_R, PIN_MODE_OUTPUT, 0);				//右轮方向输出，默认VCC
    ATOM_PWM_SetDuty(PWM_R, 0, 12500);						//右轮停止
    GPIO_LED_Init();										//初始化LED，P10.6、P10.5
    GPIO_KEY_Init();										//初始化按键
    STM_InitConfig(STM0, STM_Channel_0, 10000);				//初始化PID控制定时器，中断间隔10ms
}

//看门狗初始化函数
void Wdt_Init(uint16 ms)
{
	uint16 num = ms * 6;													//计算喂狗间隔
	Ifx_SCU_WDTS *SafetyWatchdog = &MODULE_SCU.WDTS;						//看门狗选择
	IfxScuWdt_Config Wdt_config;											//看门狗配置结构体
	IfxScuWdt_initConfig(&Wdt_config);										//初始化配置结构体
	Wdt_config.reload = 0xFFFF - num;										//配置时间
	IfxScuWdt_initSafetyWatchdog(SafetyWatchdog, &Wdt_config);				//初始化看门狗
	IfxScuWdt_enableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());	//使能看门狗
}
