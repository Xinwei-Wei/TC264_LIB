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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "..\Driver\include.h"//����ģ���ͷ�ļ�

#define PI		3.14159265358979323846

//�������˲�����
float K1_Kal = 0.02;
float angle_Kal, angle_dot_Kal;
float Q_angle_Kal = 0.001;		//����������Э����
float Q_gyro_Kal = 0.003;		//0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���
float R_angle_Kal = 0.5;		// ����������Э���� �Ȳ���ƫ��
float dt_Kal = 0.005;
char  C_0_Kal = 1;
float Q_bias_Kal, Angle_err_Kal;
float PCt_0_Kal, PCt_1_Kal, E_Kal;
float K_0_Kal, K_1_Kal, t_0_Kal, t_1_Kal;
float Pdot_Kal[4] ={0,0,0,0};
float PP_Kal[2][2] = { { 1, 0 },{ 0, 1 } };

/**
  * @brief    ��ȡMPU6050����ICM20602ԭʼ���� ����
  *
  * @param
  *
  * @return
  *
  * @note
  *
  * @see      Test_MPU6050();
  *
  * @date     2019/6/12 ������
  */
void Test_MPU6050(void)
{
	signed short  aacx=1,aacy=1,aacz=1;			//���ٶȴ�����ԭʼ����
	signed short  gyrox=2,gyroy=2,gyroz=2;		//������ԭʼ����

    OLED_Init();                          	//OLED��ʼ��
	IIC_Init();								//IIC��ʼ��
	MPU6050_Init();							//MPU6050��ʼ��
	OLED_EN(0,0,"MPU6050 Data: ",1);
	while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������
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
  * @brief    ����ȷ��ʱ
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      delayms_mpu(100);
  *
  * @date     2019/4/22 ����һ
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
  * @brief    ��ʼ��MPU6050 ���� ICM20602
  *
  * @param    ��
  *
  * @return   0����ʼ���ɹ�   1��ʧ��
  *
  * @note     ʹ��ǰ�ȳ�ʼ��IIC�ӿ�
  *
  * @see      MPU6050_Init();
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU6050_Init(void)
{
    int  res;
    res = 0;
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU6050
    delayms_mpu(100);  //��ʱ100ms
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU6050
    res += MPU_Set_Gyro_Fsr(2);					        	   //�����Ǵ�����,��2000dps
    res += MPU_Set_Accel_Fsr(0);					       	   //���ٶȴ�����,��4g
    res += MPU_Set_Rate(1000);						       	   //���ò�����1000Hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����

    if(res == 0)  //����Ĵ�����д��ɹ�
    {
        //printf("MPU set is OK!\r\n");
    }
    else return 1;

    return 0;
}

/**
  * @brief    ���������ǲ�����Χ
  *
  * @param    fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
  *
  * @return   0 �����óɹ�
  *
  * @note     ��
  *
  * @see      MPU_Set_Gyro_Fsr(3);		  //�����Ǵ�����,��2000dps
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Set_Gyro_Fsr(unsigned char fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}

/**
  * @brief    ���ü��ٶȼƲ�����Χ
  *
  * @param    fsr:0,��2g;1,��4g;2,��8g;3,��16g
  *
  * @return   0�����óɹ�
  *
  * @note     ��
  *
  * @see      MPU_Set_Accel_Fsr(1);		  //���ٶȴ�����,��4g
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Set_Accel_Fsr(unsigned char fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}

/**
  * @brief    �������ֵ�ͨ�˲�
  *
  * @param    lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
  *
  * @return   0�����óɹ�
  *
  * @note     ��
  *
  * @see      MPU_Set_LPF(100);
  *
  * @date     2019/6/12 ������
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
	return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,dat);//�������ֵ�ͨ�˲���
}

/**
  * @brief    ���ò�����
  *
  * @param    rate:4~1000(Hz)
  *
  * @return   0�����óɹ�
  *
  * @note     ��
  *
  * @see      MPU_Set_Rate(1000);       	   //���ò�����1000Hz
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Set_Rate(uint16 rate)
{
	unsigned char  dat;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	dat=1000/rate-1;
	MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,dat);	    //�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	                                //�Զ�����LPFΪ�����ʵ�һ��
}

/**
  * @brief    ��ȡ�¶�ֵ
  *
  * @param    ��
  *
  * @return   �¶�ֵ(������100��)
  *
  * @note     ��
  *
  * @see      signed short temp = MPU_Get_Temperature();
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ������ֵ
  *
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
  *
  * @see      signed short data[3];
  * @see      MPU_Get_Gyroscope(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ���ٶ�ֵ
  *
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
  *
  * @see      signed short data[3];
  * @see      MPU_Get_Accelerometer(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ ���ٶ�ֵ ���ٶ�ֵ
  *
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
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
  * @brief    IIC ������
  *
  * @param    addr:������ַ
  * @param    reg :Ҫ��ȡ�ļĴ�����ַ
  * @param    len :Ҫ��ȡ�ĳ���
  * @param    buf :��ȡ�������ݴ洢��
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      unsigned char buf[14];
  * @see      MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
    return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);
}

/**
  * @brief    IIC дһ���Ĵ���
  *
  * @param    addr  :������ַ
  * @param    reg   :�Ĵ�����ַ
  * @param    value :Ҫд���ֵ
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,1);
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
{
    return IIC_WriteByteToSlave(addr<<1, reg, value);
}

/**
  * @brief    IIC ��һ���Ĵ���
  *
  * @param    addr  :������ַ
  * @param    reg   :�Ĵ�����ַ
  *
  * @return   ��ȡ��ֵ
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);
  *
  * @date     2019/6/12 ������
  */
unsigned char MPU_Read_Byte(unsigned char addr,unsigned char reg)
{
    unsigned char value[1];
    MPU_Read_Len(addr, reg, 1, value);
    return value[0];
}

/**
  * @brief    ����Ƕ���Ǽ��ٶ�
  *
  * @param    Angle_Balance	:ƽ����ǵ�ַ
  * @param    Gyro_Balance	:ƽ����ٶȵ�ַ
  * @param    a_front	    :ǰ�����ٶȵ�ַ
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      Get_Angle(&Angle, &Gyro, &Afront);
  *
  * @date     2021/2/23 ���ڶ�
  */
void MPU_Get_Angle(float *Angle_Balance, float *Gyro_Balance, float *a_front)
{
	signed short aacx=0, aacy=0, aacz=0, gyrox=0, gyroy=0, gyroz=0;		//���ٶȡ�������ԭʼ����
	float Accel_Y, Accel_Angle, Accel_Z, Gyro_X, Gyro_Z, temp;			//�����������

    MPU_Get_Raw_data(&aacx, &aacy, &aacz, &gyrox, &gyroy, &gyroz);		//��ȡMPU6050����
    Accel_Y = -aacz; Accel_Z = aacy; Gyro_X = gyrox; Gyro_Z = gyroy;	//������ת��

	*Gyro_Balance = Gyro_X;									//����ƽ����ٶ�
	Accel_Angle = atan2(Accel_Y, Accel_Z)*180/3.1415926536;	//�������
	Gyro_X = Gyro_X/16.4;									//����������ת��

//	Kalman_Filter(Accel_Angle, Gyro_X);											//�������˲�
	angle_Kal = 0.02 * Accel_Angle + (1 - 0.02) * (angle_Kal + Gyro_X * 0.005);	//һ���˲�

	*Angle_Balance = angle_Kal;								//����ƽ�����

	/******************************ǰ�����ٶȼ���******************************/
	//MPU6050����
	if(angle_Kal <= 0)
		temp = pow(aacx/1638.4,2) + pow(Accel_Y/1638.4,2) + pow(Accel_Z/1638.4,2) - sqrt(9880 + 1500*sin(angle_Kal/180.0*PI));
	else
		temp = pow(aacx/1638.4,2) + pow(Accel_Y/1638.4,2) + pow(Accel_Z/1638.4,2) - sqrt(10030 + 400*sin(angle_Kal/180.0*PI) + 30*angle_Kal);
	temp = sqrt(fabs(temp));

	//��е��������
	if(temp > 8)//2.5
		temp -= 5;
	else
		temp = 0;

	//���ٶȷ����ж�
	if(Accel_Y*cos(angle_Kal/180.0*PI)-fabs(Accel_Z)*fabs(sin(angle_Kal/180.0*PI)) > 0)
		temp = -temp;
	*a_front = temp;

//	Gyro_Turn=Gyro_Z;										//����ת����ٶ�
}

/**
  * @brief    �������˲�
  *
  * @param    Accel	:ƽ�����
  * @param    Gyro	:ƽ����ٶ�
  *
  * @return   ��
  *
  * @note     by WeiXw
  *
  * @see      Kalman_Filter(Accel_Angle, Gyro_X);
  *
  * @date     2021/2/23 ���ڶ�
  */
void Kalman_Filter(float Accel,float Gyro)
{
	angle_Kal += (Gyro - Q_bias_Kal) * dt_Kal;					//�������
	Pdot_Kal[0] = Q_angle_Kal - PP_Kal[0][1] - PP_Kal[1][0];	//Pk-����������Э�����΢��

	Pdot_Kal[1] = -PP_Kal[1][1];
	Pdot_Kal[2] = -PP_Kal[1][1];
	Pdot_Kal[3] = Q_gyro_Kal;
	PP_Kal[0][0] += Pdot_Kal[0] * dt_Kal;	//Pk-����������Э����΢�ֵĻ���
	PP_Kal[0][1] += Pdot_Kal[1] * dt_Kal;	//����������Э����
	PP_Kal[1][0] += Pdot_Kal[2] * dt_Kal;
	PP_Kal[1][1] += Pdot_Kal[3] * dt_Kal;

	Angle_err_Kal = Accel - angle_Kal;		//zk-�������

	PCt_0_Kal = C_0_Kal * PP_Kal[0][0];
	PCt_1_Kal = C_0_Kal * PP_Kal[1][0];

	E_Kal = R_angle_Kal + C_0_Kal * PCt_0_Kal;

	K_0_Kal = PCt_0_Kal / E_Kal;
	K_1_Kal = PCt_1_Kal / E_Kal;

	t_0_Kal = PCt_0_Kal;
	t_1_Kal = C_0_Kal * PP_Kal[0][1];

	PP_Kal[0][0] -= K_0_Kal * t_0_Kal;		//����������Э����
	PP_Kal[0][1] -= K_0_Kal * t_1_Kal;
	PP_Kal[1][0] -= K_1_Kal * t_0_Kal;
	PP_Kal[1][1] -= K_1_Kal * t_1_Kal;

	angle_Kal += K_0_Kal * Angle_err_Kal;	//�������
	Q_bias_Kal += K_1_Kal * Angle_err_Kal;	//�������
	angle_dot_Kal = Gyro - Q_bias_Kal;		//���ֵ(�������)��΢��=���ٶ�
}
