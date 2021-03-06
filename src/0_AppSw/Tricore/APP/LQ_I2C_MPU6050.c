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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "..\Driver\include.h"//各个模块的头文件

#define PI		3.14159265358979323846

//卡尔曼滤波参数
float K1_Kal = 0.02;
float angle_Kal, angle_dot_Kal;
float Q_angle_Kal = 0.001;		//过程噪声的协方差
float Q_gyro_Kal = 0.003;		//0.003 过程噪声的协方差 过程噪声的协方差为一个一行两列矩阵
float R_angle_Kal = 0.5;		// 测量噪声的协方差 既测量偏差
float dt_Kal = 0.005;
char  C_0_Kal = 1;
float Q_bias_Kal, Angle_err_Kal;
float PCt_0_Kal, PCt_1_Kal, E_Kal;
float K_0_Kal, K_1_Kal, t_0_Kal, t_1_Kal;
float Pdot_Kal[4] ={0,0,0,0};
float PP_Kal[2][2] = { { 1, 0 },{ 0, 1 } };

/**
  * @brief    读取MPU6050或者ICM20602原始数据 测试
  *
  * @param
  *
  * @return
  *
  * @note
  *
  * @see      Test_MPU6050();
  *
  * @date     2019/6/12 星期三
  */
void Test_MPU6050(void)
{
	signed short  aacx=1,aacy=1,aacz=1;			//加速度传感器原始数据
	signed short  gyrox=2,gyroy=2,gyroz=2;		//陀螺仪原始数据

    OLED_Init();                          	//OLED初始化
	IIC_Init();								//IIC初始化
	MPU6050_Init();							//MPU6050初始化
	OLED_EN(0,0,"MPU6050 Data: ",1);
	while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据
        OLED_EN(OLED_NUM(OLED_EN(0,1,"ax: ",1), 1, aacx, 5, 2, 1)-6, 1, "      ", 1);
        OLED_EN(OLED_NUM(OLED_EN(0,2,"ay: ",1), 2, aacy, 5, 2, 1)-6, 2, "      ", 1);
        OLED_EN(OLED_NUM(OLED_EN(0,3,"az: ",1), 3, aacz, 5, 2, 1)-6, 3, "      ", 1);
        OLED_EN(OLED_NUM(OLED_EN(0,4,"gx: ",1), 4, gyrox, 5, 2, 1)-6, 4, "      ", 1);
        OLED_EN(OLED_NUM(OLED_EN(0,5,"gy: ",1), 5, gyroy, 5, 2, 1)-6, 5, "      ", 1);
        OLED_EN(OLED_NUM(OLED_EN(0,6,"gz: ",1), 6, gyroz, 5, 2, 1)-6, 6, "      ", 1);
//        for(int i=1; i<=6; i++)
//        	OLED_EN(78, i, "        ", 1);
        delayms(100);
    }
}

/**
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      delayms_mpu(100);
  *
  * @date     2019/4/22 星期一
*/
void delayms_mpu(uint16 ms)
{
	while(ms--)
	{
		uint16  i = 300;
		while(i--)
		{
			NOP(50);
		}
	}
}


/**
  * @brief    初始化MPU6050 或者 ICM20602
  *
  * @param    无
  *
  * @return   0：初始化成功   1：失败
  *
  * @note     使用前先初始化IIC接口
  *
  * @see      MPU6050_Init();
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU6050_Init(void)
{
    int  res;
    res = 0;
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU6050
    delayms_mpu(100);  //延时100ms
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU6050
    res += MPU_Set_Gyro_Fsr(2);					        	   //陀螺仪传感器,±2000dps
    res += MPU_Set_Accel_Fsr(0);					       	   //加速度传感器,±4g
    res += MPU_Set_Rate(1000);						       	   //设置采样率1000Hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //设置数字低通滤波器   98hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作

    if(res == 0)  //上面寄存器都写入成功
    {
        //printf("MPU set is OK!\r\n");
    }
    else return 1;

    return 0;
}

/**
  * @brief    设置陀螺仪测量范围
  *
  * @param    fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
  *
  * @return   0 ：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_Gyro_Fsr(3);		  //陀螺仪传感器,±2000dps
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Set_Gyro_Fsr(unsigned char fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}

/**
  * @brief    设置加速度计测量范围
  *
  * @param    fsr:0,±2g;1,±4g;2,±8g;3,±16g
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_Accel_Fsr(1);		  //加速度传感器,±4g
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Set_Accel_Fsr(unsigned char fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}

/**
  * @brief    设置数字低通滤波
  *
  * @param    lpf:数字低通滤波频率(Hz)
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_LPF(100);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Set_LPF(uint16 lpf)
{
	unsigned char  dat=0;
	if(lpf>=188)dat=1;
	else if(lpf>=98)dat=2;
	else if(lpf>=42)dat=3;
	else if(lpf>=20)dat=4;
	else if(lpf>=10)dat=5;
	else dat=6;
	return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,dat);//设置数字低通滤波器
}

/**
  * @brief    设置采样率
  *
  * @param    rate:4~1000(Hz)
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_Rate(1000);       	   //设置采样率1000Hz
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Set_Rate(uint16 rate)
{
	unsigned char  dat;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	dat=1000/rate-1;
	MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,dat);	    //设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	                                //自动设置LPF为采样率的一半
}

/**
  * @brief    获取温度值
  *
  * @param    无
  *
  * @return   温度值(扩大了100倍)
  *
  * @note     无
  *
  * @see      signed short temp = MPU_Get_Temperature();
  *
  * @date     2019/6/12 星期三
  */
short MPU_Get_Temperature(void)
{
    unsigned char  buf[2];
    short raw;
	float temp;
	MPU_Read_Len(MPU6050_ADDR,MPU_TEMP_OUTH_REG,2,buf);
    raw=((uint16)buf[0]<<8)|buf[1];
    temp=21+((double)raw)/333.87;
    return (short)temp*100;
}

/**
  * @brief    获取陀螺仪值
  *
  * @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      signed short data[3];
  * @see      MPU_Get_Gyroscope(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Get_Gyroscope(signed short *gx,signed short *gy,signed short *gz)
{
    unsigned char  buf[6],res;
	res=MPU_Read_Len(MPU6050_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16)buf[0]<<8)|buf[1];
		*gy=((uint16)buf[2]<<8)|buf[3];
		*gz=((uint16)buf[4]<<8)|buf[5];
	}
    return res;
}

/**
  * @brief    获取加速度值
  *
  * @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      signed short data[3];
  * @see      MPU_Get_Accelerometer(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Get_Accelerometer(signed short *ax,signed short *ay,signed short *az)
{
    unsigned char  buf[6],res;
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16)buf[0]<<8)|buf[1];
		*ay=((uint16)buf[2]<<8)|buf[3];
		*az=((uint16)buf[4]<<8)|buf[5];
	}
    return res;
}

/**
  * @brief    获取 加速度值 角速度值
  *
  * @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
  * @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      signed short data[6];
  * @see      ICM_Get_Raw_data(&data[0], &data[1], &data[2],&data[3], &data[4], &data[5]);
  *
  */
unsigned char MPU_Get_Raw_data(signed short *ax,signed short *ay,signed short *az,signed short *gx,signed short *gy,signed short *gz)
{
    unsigned char  buf[14],res;
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
	if(res==0)
	{
		*ax=((uint16)buf[0]<<8)|buf[1];
		*ay=((uint16)buf[2]<<8)|buf[3];
		*az=((uint16)buf[4]<<8)|buf[5];
        *gx=((uint16)buf[8]<<8)|buf[9];
		*gy=((uint16)buf[10]<<8)|buf[11];
		*gz=((uint16)buf[12]<<8)|buf[13];
	}
    return res;
}

/**
  * @brief    IIC 连续读
  *
  * @param    addr:器件地址
  * @param    reg :要读取的寄存器地址
  * @param    len :要读取的长度
  * @param    buf :读取到的数据存储区
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      unsigned char buf[14];
  * @see      MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
    return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);
}

/**
  * @brief    IIC 写一个寄存器
  *
  * @param    addr  :器件地址
  * @param    reg   :寄存器地址
  * @param    value :要写入的值
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,1);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
{
    return IIC_WriteByteToSlave(addr<<1, reg, value);
}

/**
  * @brief    IIC 读一个寄存器
  *
  * @param    addr  :器件地址
  * @param    reg   :寄存器地址
  *
  * @return   读取的值
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);
  *
  * @date     2019/6/12 星期三
  */
unsigned char MPU_Read_Byte(unsigned char addr,unsigned char reg)
{
    unsigned char value[1];
    MPU_Read_Len(addr, reg, 1, value);
    return value[0];
}

/**
  * @brief    计算角度与角加速度
  *
  * @param    Angle_Balance	:平衡倾角地址
  * @param    Gyro_Balance	:平衡角速度地址
  * @param    a_front	    :前进加速度地址
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      Get_Angle(&Angle, &Gyro, &Afront);
  *
  * @date     2021/2/23 星期二
  */
void MPU_Get_Angle(float *Angle_Balance, float *Gyro_Balance, float *a_front)
{
	signed short aacx=0, aacy=0, aacz=0, gyrox=0, gyroy=0, gyroz=0;		//加速度、陀螺仪原始数据
	float Accel_Y, Accel_Angle, Accel_Z, Gyro_X, Gyro_Z, temp;			//参与计算数据

    MPU_Get_Raw_data(&aacx, &aacy, &aacz, &gyrox, &gyroy, &gyroz);		//读取MPU6050数据
    Accel_Y = -aacz; Accel_Z = aacy; Gyro_X = gyrox; Gyro_Z = gyroy;	//坐标轴转换

	*Gyro_Balance = Gyro_X;									//更新平衡角速度
	Accel_Angle = atan2(Accel_Y, Accel_Z)*180/3.1415926536;	//计算倾角
	Gyro_X = Gyro_X/16.4;									//陀螺仪量程转换

//	Kalman_Filter(Accel_Angle, Gyro_X);											//卡尔曼滤波
	angle_Kal = 0.02 * Accel_Angle + (1 - 0.02) * (angle_Kal + Gyro_X * 0.005);	//一阶滤波

	*Angle_Balance = angle_Kal;								//更新平衡倾角

	/******************************前进加速度计算******************************/
	//MPU6050补正
	if(angle_Kal <= 0)
		temp = pow(aacx/1638.4,2) + pow(Accel_Y/1638.4,2) + pow(Accel_Z/1638.4,2) - sqrt(9880 + 1500*sin(angle_Kal/180.0*PI));
	else
		temp = pow(aacx/1638.4,2) + pow(Accel_Y/1638.4,2) + pow(Accel_Z/1638.4,2) - sqrt(10030 + 400*sin(angle_Kal/180.0*PI) + 30*angle_Kal);
	temp = sqrt(fabs(temp));

	//机械抖动消除
	if(temp > 8)//2.5
		temp -= 5;
	else
		temp = 0;

	//加速度方向判断
	if(Accel_Y*cos(angle_Kal/180.0*PI)-fabs(Accel_Z)*fabs(sin(angle_Kal/180.0*PI)) > 0)
		temp = -temp;
	*a_front = temp;

//	Gyro_Turn=Gyro_Z;										//更新转向角速度
}

/**
  * @brief    卡尔曼滤波
  *
  * @param    Accel	:平衡倾角
  * @param    Gyro	:平衡角速度
  *
  * @return   无
  *
  * @note     by WeiXw
  *
  * @see      Kalman_Filter(Accel_Angle, Gyro_X);
  *
  * @date     2021/2/23 星期二
  */
void Kalman_Filter(float Accel,float Gyro)
{
	angle_Kal += (Gyro - Q_bias_Kal) * dt_Kal;					//先验估计
	Pdot_Kal[0] = Q_angle_Kal - PP_Kal[0][1] - PP_Kal[1][0];	//Pk-先验估计误差协方差的微分

	Pdot_Kal[1] = -PP_Kal[1][1];
	Pdot_Kal[2] = -PP_Kal[1][1];
	Pdot_Kal[3] = Q_gyro_Kal;
	PP_Kal[0][0] += Pdot_Kal[0] * dt_Kal;	//Pk-先验估计误差协方差微分的积分
	PP_Kal[0][1] += Pdot_Kal[1] * dt_Kal;	//先验估计误差协方差
	PP_Kal[1][0] += Pdot_Kal[2] * dt_Kal;
	PP_Kal[1][1] += Pdot_Kal[3] * dt_Kal;

	Angle_err_Kal = Accel - angle_Kal;		//zk-先验估计

	PCt_0_Kal = C_0_Kal * PP_Kal[0][0];
	PCt_1_Kal = C_0_Kal * PP_Kal[1][0];

	E_Kal = R_angle_Kal + C_0_Kal * PCt_0_Kal;

	K_0_Kal = PCt_0_Kal / E_Kal;
	K_1_Kal = PCt_1_Kal / E_Kal;

	t_0_Kal = PCt_0_Kal;
	t_1_Kal = C_0_Kal * PP_Kal[0][1];

	PP_Kal[0][0] -= K_0_Kal * t_0_Kal;		//后验估计误差协方差
	PP_Kal[0][1] -= K_0_Kal * t_1_Kal;
	PP_Kal[1][0] -= K_1_Kal * t_0_Kal;
	PP_Kal[1][1] -= K_1_Kal * t_1_Kal;

	angle_Kal += K_0_Kal * Angle_err_Kal;	//后验估计
	Q_bias_Kal += K_1_Kal * Angle_err_Kal;	//后验估计
	angle_dot_Kal = Gyro - Q_bias_Kal;		//输出值(后验估计)的微分=角速度
}
