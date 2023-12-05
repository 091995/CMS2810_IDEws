/*
 * dcs_base.h
 *
 *  Created on: 15 ���. 2019 �.
 *      Author: admin
 */

#ifndef DCS_DCS_BASE_H_
#define DCS_DCS_BASE_H_

//#define _PI    (float)3.1415926535897932384626433832795
#define _PI_2  (float)(_PI*0.5)
#define _3_2PI (float)(_PI*1.5)
#define _2PI_3 (float)(_PI*2./3.)
#define _3PI_2 (float)(_PI*3./2.)
#define _2PI   (float)(_PI*2.0)
#define _PI_4  (float)(_PI*0.25)
#define _1_2PI (float)(0.5/_PI)


#define FREQ_PWM 4000
#define Td (1.0/8000.0)

// ������������ �������� � ������������� ��������
// ���������� ���� 38.5�� - KUs_38_5 = 1/(38.5e3*sqrt(2/3)). - ��������� ������� ���������� (31,44��)
// ���������� ���� 230��  - KUs_230  = 1/(230e3*sqrt(2/3)).  - ��������� ������� ���������� (187,8��)
// �������� 120����		  - Kpow	 = 1/(120e6).			 - ����������� ����� ��������
// ���������� �� ��		  - KUdc	 = 1/(38.5e3*sqrt(2/3)). - ��������� ������� ���������� (31,44��)

#define _1_Td			(1.0/Td)
#define _1_TdTd			(1.0/(Td*Td))
#define _2Td			(Td*2.)
#define _1_2Td			(1.0/(Td*2.))
#define _TdTd			(Td*Td)
#define _Td_2			(Td*0.5)
#define _3Td_2			(Td*1.5)

#define _sqrt_3			1.732050808
#define _1_sqrt_3		(1.0/1.732050808)
#define _sqrt_2			(1.414213562)
#define _1_sqrt_2		(1.0/1.414213562)
#define _sqrt3_2		0.866025404
#define _sqrt2_sqrt3	0.816496580927726
#define _sqrt3_sqrt2	(1.732050808/1.414213562)

#endif /* DCS_DCS_BASE_H_ */
