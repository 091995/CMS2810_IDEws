//����: cood.c
//�������: C:\SolarIDEws\SolarControl\cood_INVERTER.xml
//���� ��������: 19.10.2023 10:27:12
//������������: default
#include "DSP.h"
#include "main.h"
#include "cood2.h"
#include "co_ODvars.h"

// ����� 136 �������� � �������
// ����� 1019 ��������� � �������
Uint16 const co2_numOfInd = 136;
//����� ������������ ��� �����
Uint16 const co2_groupEnum = 15;
//���-�����:
Uint32 const co2_odHash[4] = {0xEC6610D0, 0x7C9DB4C5, 0xD1691444, 0x5CE16BC4};
//������� � �������� ����������

long const CO2_OD_TBL3[] = { (long)(&co2_vars.co_deviceType), //[1000h.00h], ��������=��� ����������, �������=Device Type, EngText=Device Type, ������=CAN
(long)(&co2_vars.co_errorRegister), //[1001h.00h], ��������=������� ������, �������=ErrReg, EngText=Error Register, ������=CAN
(long)(&co2_vars.co_deviceState), //[1002h.00h], ��������=Manufacturer Status Register, �������=DevSta, EngText=Manufacturer Status Register, ������=CAN
(long)(&co2_vars.co_emcyCOBID), //[1014h.00h], ��������=COB-ID Emergency Object, �������=eCOBID, EngText=COB-ID Emergency Object, ������=CAN
(long)(&co2_vars.co_CHBT), //[1016h.01h], ��������=����� �������� ��������� Heartbeat, �������=CHBT, EngText=Consumer Heartbeat Time, ������=CAN
(long)(&co2_vars.co_PHBT), //[1017h.00h], ��������=������ ��������� ��������� Heartbeat, �������=PHBT, EngText=Producer Heartbeat Time, ������=CAN
(long)(&co2_vars.co_vendorID), //[1018h.01h], ��������=��� �������������, �������=VendID, EngText=Vendor ID, ������=CAN
(long)(&co2_vars.co_productCode), //[1018h.02h], ��������=��� ��������, �������=PrCode, EngText=Product Code, ������=CAN
(long)(&co2_vars.co_revisionNumber), //[1018h.03h], ��������=����� �������, �������=RevNum, EngText=Revision Number, ������=CAN
(long)(&co2_vars.co_serialNumber), //[1018h.04h], ��������=�������� �����, �������=SerNum, EngText=Serial Number, ������=CAN
(long)(&co2_vars.co_csrxCOBID), //[1200h.01h], ��������=COB-ID Client->Server(rx), �������=CSRXID, EngText=COB-ID Client->Server(rx), ������=CAN
(long)(&co2_vars.co_sctxCOBID), //[1200h.02h], ��������=COB-ID Server->Client(tx), �������=SCTXID, EngText=COB-ID Server->Client(tx), ������=CAN
(long)(&co2_vars.co_cstxCOBID), //[1280h.01h], ��������=COB-ID Client->Server(tx), �������=CSTXID, EngText=COB-ID Client->Server(tx), ������=CAN
(long)(&co2_vars.co_scrxCOBID), //[1280h.02h], ��������=COB-ID Server->Client(rx), �������=SCRXID, EngText=COB-ID Server->Client(rx), ������=CAN
(long)(&co2_vars.co_ssNODEID), //[1280h.03h], ��������=NODE-ID on SDO server, �������=SDOSID, EngText=NODE-ID on SDO server, ������=CAN
(long)(&co2_vars.co_RPDO1COBID), //[1400h.01h], ��������=COB-ID for RPDO1, �������=IRPDO1, EngText=COB-ID for RPDO1, ������=CAN
(long)(&co2_vars.co_transType), //[1400h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO2COBID), //[1401h.01h], ��������=COB-ID for RPDO2, �������=IRPDO2, EngText=COB-ID for RPDO2, ������=CAN
(long)(&co2_vars.co_transType), //[1401h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO3COBID), //[1402h.01h], ��������=COB-ID for RPDO3, �������=IRPDO3, EngText=COB-ID for RPDO3, ������=CAN
(long)(&co2_vars.co_transType), //[1402h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO4COBID), //[1403h.01h], ��������=COB-ID for RPDO4, �������=IRPDO4, EngText=COB-ID for RPDO4, ������=CAN
(long)(&co2_vars.co_transType), //[1403h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO5COBID), //[1404h.01h], ��������=COB-ID for RPDO5, �������=IRPDO5, EngText=COB-ID for RPDO5, ������=CAN
(long)(&co2_vars.co_transType), //[1404h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO6COBID), //[1405h.01h], ��������=COB-ID for RPDO6, �������=IRPDO6, EngText=COB-ID for RPDO6, ������=CAN
(long)(&co2_vars.co_transType), //[1405h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO7COBID), //[1406h.01h], ��������=COB-ID for RPDO7, �������=IRPDO7, EngText=COB-ID for RPDO7, ������=CAN
(long)(&co2_vars.co_transType), //[1406h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO8COBID), //[1407h.01h], ��������=COB-ID for RPDO8, �������=IRPDO8, EngText=COB-ID for RPDO8, ������=CAN
(long)(&co2_vars.co_transType), //[1407h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_RPDO1_1Mapping), //[1600h.01h], ��������=RPDO1-1 Mapping, �������=RPM11, EngText=RPDO1-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO1_2Mapping), //[1600h.02h], ��������=RPDO1-2 Mapping, �������=RPM12, EngText=RPDO1-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO1_3Mapping), //[1600h.03h], ��������=RPDO1-3 Mapping, �������=RPM13, EngText=RPDO1-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO1_4Mapping), //[1600h.04h], ��������=RPDO1-4 Mapping, �������=RPM14, EngText=RPDO1-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO2_1Mapping), //[1601h.01h], ��������=RPDO2-1 Mapping, �������=RPM21, EngText=RPDO2-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO2_2Mapping), //[1601h.02h], ��������=RPDO2-2 Mapping, �������=RPM22, EngText=RPDO2-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO2_3Mapping), //[1601h.03h], ��������=RPDO2-3 Mapping, �������=RPM23, EngText=RPDO2-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO2_4Mapping), //[1601h.04h], ��������=RPDO2-4 Mapping, �������=RPM24, EngText=RPDO2-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO3_1Mapping), //[1602h.01h], ��������=RPDO3-1 Mapping, �������=RPM31, EngText=RPDO3-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO3_2Mapping), //[1602h.02h], ��������=RPDO3-2 Mapping, �������=RPM32, EngText=RPDO3-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO3_3Mapping), //[1602h.03h], ��������=RPDO3-3 Mapping, �������=RPM33, EngText=RPDO3-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO3_4Mapping), //[1602h.04h], ��������=RPDO3-4 Mapping, �������=RPM34, EngText=RPDO3-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO4_1Mapping), //[1603h.01h], ��������=RPDO4-1 Mapping, �������=RPM41, EngText=RPDO4-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO4_2Mapping), //[1603h.02h], ��������=RPDO4-2 Mapping, �������=RPM42, EngText=RPDO4-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO4_3Mapping), //[1603h.03h], ��������=RPDO4-3 Mapping, �������=RPM43, EngText=RPDO4-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO4_4Mapping), //[1603h.04h], ��������=RPDO4-4 Mapping, �������=RPM44, EngText=RPDO4-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO5_1Mapping), //[1604h.01h], ��������=RPDO5-1 Mapping, �������=RPM51, EngText=RPDO5-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO5_2Mapping), //[1604h.02h], ��������=RPDO5-2 Mapping, �������=RPM52, EngText=RPDO5-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO5_3Mapping), //[1604h.03h], ��������=RPDO5-3 Mapping, �������=RPM53, EngText=RPDO5-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO5_4Mapping), //[1604h.04h], ��������=RPDO5-4 Mapping, �������=RPM54, EngText=RPDO5-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO6_1Mapping), //[1605h.01h], ��������=RPDO6-1 Mapping, �������=RPM61, EngText=RPDO6-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO6_2Mapping), //[1605h.02h], ��������=RPDO6-2 Mapping, �������=RPM62, EngText=RPDO6-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO6_3Mapping), //[1605h.03h], ��������=RPDO6-3 Mapping, �������=RPM63, EngText=RPDO6-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO6_4Mapping), //[1605h.04h], ��������=RPDO6-4 Mapping, �������=RPM64, EngText=RPDO6-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO7_1Mapping), //[1606h.01h], ��������=RPDO7-1 Mapping, �������=RPM71, EngText=RPDO7-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO7_2Mapping), //[1606h.02h], ��������=RPDO7-2 Mapping, �������=RPM72, EngText=RPDO7-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO7_3Mapping), //[1606h.03h], ��������=RPDO7-3 Mapping, �������=RPM73, EngText=RPDO7-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO7_4Mapping), //[1606h.04h], ��������=RPDO7-4 Mapping, �������=RPM74, EngText=RPDO7-4 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO8_1Mapping), //[1607h.01h], ��������=RPDO8-1 Mapping, �������=RPM81, EngText=RPDO8-1 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO8_2Mapping), //[1607h.02h], ��������=RPDO8-2 Mapping, �������=RPM82, EngText=RPDO8-2 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO8_3Mapping), //[1607h.03h], ��������=RPDO8-3 Mapping, �������=RPM83, EngText=RPDO8-3 Mapping, ������=CAN
(long)(&co2_vars.co_RPDO8_4Mapping), //[1607h.04h], ��������=RPDO8-4 Mapping, �������=RPM84, EngText=RPDO8-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO1COBID), //[1800h.01h], ��������=COB-ID for TPDO1, �������=ITPDO1, EngText=COB-ID for TPDO1, ������=CAN
(long)(&co2_vars.co_transType), //[1800h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO1ITime), //[1800h.03h], ��������=Inhibit Time 1, �������=ITime1, EngText=Inhibit Time 1, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1800h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO1EventTimer), //[1800h.05h], ��������=Event Timer 1, �������=EvTmr1, EngText=Event Timer 1, ������=CAN
(long)(&co2_vars.co_TPDO2COBID), //[1801h.01h], ��������=COB-ID for TPDO2, �������=ITPDO2, EngText=COB-ID for TPDO2, ������=CAN
(long)(&co2_vars.co_transType), //[1801h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO2ITime), //[1801h.03h], ��������=Inhibit Time 2, �������=ITime2, EngText=Inhibit Time 2, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1801h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO2EventTimer), //[1801h.05h], ��������=Event Timer 2, �������=EvTmr2, EngText=Event Timer 2, ������=CAN
(long)(&co2_vars.co_TPDO3COBID), //[1802h.01h], ��������=COB-ID for TPDO3, �������=ITPDO3, EngText=COB-ID for TPDO3, ������=CAN
(long)(&co2_vars.co_transType), //[1802h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO3ITime), //[1802h.03h], ��������=Inhibit Time 3, �������=ITime3, EngText=Inhibit Time 3, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1802h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO3EventTimer), //[1802h.05h], ��������=Event Timer 3, �������=EvTmr3, EngText=Event Timer 3, ������=CAN
(long)(&co2_vars.co_TPDO4COBID), //[1803h.01h], ��������=COB-ID for TPDO4, �������=ITPDO4, EngText=COB-ID for TPDO4, ������=CAN
(long)(&co2_vars.co_transType), //[1803h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO4ITime), //[1803h.03h], ��������=Inhibit Time 4, �������=ITime4, EngText=Inhibit Time 4, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1803h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO4EventTimer), //[1803h.05h], ��������=Event Timer 4, �������=EvTmr4, EngText=Event Timer 4, ������=CAN
(long)(&co2_vars.co_TPDO5COBID), //[1804h.01h], ��������=COB-ID for TPDO5, �������=ITPDO5, EngText=COB-ID for TPDO5, ������=CAN
(long)(&co2_vars.co_transType), //[1804h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO5ITime), //[1804h.03h], ��������=Inhibit Time 5, �������=ITime5, EngText=Inhibit Time 5, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1804h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO5EventTimer), //[1804h.05h], ��������=Event Timer 5, �������=EvTmr5, EngText=Event Timer 5, ������=CAN
(long)(&co2_vars.co_TPDO6COBID), //[1805h.01h], ��������=COB-ID for TPDO6, �������=ITPDO6, EngText=COB-ID for TPDO6, ������=CAN
(long)(&co2_vars.co_transType), //[1805h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO6ITime), //[1805h.03h], ��������=Inhibit Time 6, �������=ITime6, EngText=Inhibit Time 6, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1805h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO6EventTimer), //[1805h.05h], ��������=Event Timer 6, �������=EvTmr6, EngText=Event Timer 6, ������=CAN
(long)(&co2_vars.co_TPDO7COBID), //[1806h.01h], ��������=COB-ID for TPDO7, �������=ITPDO7, EngText=COB-ID for TPDO7, ������=CAN
(long)(&co2_vars.co_transType), //[1806h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO7ITime), //[1806h.03h], ��������=Inhibit Time 7, �������=ITime7, EngText=Inhibit Time 7, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1806h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO7EventTimer), //[1806h.05h], ��������=Event Timer 7, �������=EvTmr7, EngText=Event Timer 7, ������=CAN
(long)(&co2_vars.co_TPDO8COBID), //[1807h.01h], ��������=COB-ID for TPDO8, �������=ITPDO8, EngText=COB-ID for TPDO8, ������=CAN
(long)(&co2_vars.co_transType), //[1807h.02h], ��������=��� ��������, �������=TransT, EngText=Transmission Type, ������=CAN
(long)(&co2_vars.co_TPDO8ITime), //[1807h.03h], ��������=Inhibit Time 8, �������=ITime8, EngText=Inhibit Time 8, ������=CAN
(long)(&co2_vars.co_compatEntry), //[1807h.04h], ��������=Compatibility Entry, �������=CompEn, EngText=Compatibility Entry, ������=CAN
(long)(&co2_vars.co_TPDO8EventTimer), //[1807h.05h], ��������=Event Timer 8, �������=EvTmr8, EngText=Event Timer 8, ������=CAN
(long)(&co2_vars.co_TPDO1_1Mapping), //[1A00h.01h], ��������=TPDO1-1 Mapping, �������=TPM11, EngText=TPDO1-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO1_2Mapping), //[1A00h.02h], ��������=TPDO1-2 Mapping, �������=TPM12, EngText=TPDO1-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO1_3Mapping), //[1A00h.03h], ��������=TPDO1-3 Mapping, �������=TPM13, EngText=TPDO1-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO1_4Mapping), //[1A00h.04h], ��������=TPDO1-4 Mapping, �������=TPM14, EngText=TPDO1-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO2_1Mapping), //[1A01h.01h], ��������=TPDO2-1 Mapping, �������=TPM21, EngText=TPDO2-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO2_2Mapping), //[1A01h.02h], ��������=TPDO2-2 Mapping, �������=TPM22, EngText=TPDO2-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO2_3Mapping), //[1A01h.03h], ��������=TPDO2-3 Mapping, �������=TPM23, EngText=TPDO2-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO2_4Mapping), //[1A01h.04h], ��������=TPDO2-4 Mapping, �������=TPM24, EngText=TPDO2-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO3_1Mapping), //[1A02h.01h], ��������=TPDO3-1 Mapping, �������=TPM31, EngText=TPDO3-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO3_2Mapping), //[1A02h.02h], ��������=TPDO3-2 Mapping, �������=TPM32, EngText=TPDO3-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO3_3Mapping), //[1A02h.03h], ��������=TPDO3-3 Mapping, �������=TPM33, EngText=TPDO3-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO3_4Mapping), //[1A02h.04h], ��������=TPDO3-4 Mapping, �������=TPM34, EngText=TPDO3-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO4_1Mapping), //[1A03h.01h], ��������=TPDO4-1 Mapping, �������=TPM41, EngText=TPDO4-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO4_2Mapping), //[1A03h.02h], ��������=TPDO4-2 Mapping, �������=TPM42, EngText=TPDO4-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO4_3Mapping), //[1A03h.03h], ��������=TPDO4-3 Mapping, �������=TPM43, EngText=TPDO4-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO4_4Mapping), //[1A03h.04h], ��������=TPDO4-4 Mapping, �������=TPM44, EngText=TPDO4-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO5_1Mapping), //[1A04h.01h], ��������=TPDO5-1 Mapping, �������=TPM51, EngText=TPDO5-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO5_2Mapping), //[1A04h.02h], ��������=TPDO5-2 Mapping, �������=TPM52, EngText=TPDO5-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO5_3Mapping), //[1A04h.03h], ��������=TPDO5-3 Mapping, �������=TPM53, EngText=TPDO5-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO5_4Mapping), //[1A04h.04h], ��������=TPDO5-4 Mapping, �������=TPM54, EngText=TPDO5-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO6_1Mapping), //[1A05h.01h], ��������=TPDO6-1 Mapping, �������=TPM61, EngText=TPDO6-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO6_2Mapping), //[1A05h.02h], ��������=TPDO6-2 Mapping, �������=TPM62, EngText=TPDO6-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO6_3Mapping), //[1A05h.03h], ��������=TPDO6-3 Mapping, �������=TPM63, EngText=TPDO6-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO6_4Mapping), //[1A05h.04h], ��������=TPDO6-4 Mapping, �������=TPM64, EngText=TPDO6-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO7_1Mapping), //[1A06h.01h], ��������=TPDO7-1 Mapping, �������=TPM71, EngText=TPDO7-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO7_2Mapping), //[1A06h.02h], ��������=TPDO7-2 Mapping, �������=TPM72, EngText=TPDO7-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO7_3Mapping), //[1A06h.03h], ��������=TPDO7-3 Mapping, �������=TPM73, EngText=TPDO7-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO7_4Mapping), //[1A06h.04h], ��������=TPDO7-4 Mapping, �������=TPM74, EngText=TPDO7-4 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO8_1Mapping), //[1A07h.01h], ��������=TPDO8-1 Mapping, �������=TPM81, EngText=TPDO8-1 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO8_2Mapping), //[1A07h.02h], ��������=TPDO8-2 Mapping, �������=TPM82, EngText=TPDO8-2 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO8_3Mapping), //[1A07h.03h], ��������=TPDO8-3 Mapping, �������=TPM83, EngText=TPDO8-3 Mapping, ������=CAN
(long)(&co2_vars.co_TPDO8_4Mapping), //[1A07h.04h], ��������=TPDO8-4 Mapping, �������=TPM84, EngText=TPDO8-4 Mapping, ������=CAN
(long)(&co2_vars.co_nodeID), //[2000h.00h], ��������=CAN NODE-ID, �������=NodeID, EngText=CAN NODE-ID, ������=CAN
(long)(&co2_vars.co_bitRate), //[2001h.00h], ��������=CAN Bit Rate, �������=CANBR, EngText=CAN Bit Rate, ������=CAN
(long)(&co2_vars.co_vendorID), //[2002h.01h], ��������=��� �������������, �������=VendID, EngText=Vendor ID, ������=CAN
(long)(&co2_vars.co_productCode), //[2002h.02h], ��������=��� ��������, �������=PrCode, EngText=Product Code, ������=CAN
(long)(&co2_vars.co_revisionNumber), //[2002h.03h], ��������=����� �������, �������=RevNum, EngText=Revision Number, ������=CAN
(long)(&co2_vars.co_serialNumber), //[2002h.04h], ��������=�������� �����, �������=SerNum, EngText=Serial Number, ������=CAN
(long)(&co2_vars.co_specialData1), //[2003h.01h], ��������=Special Data 1, �������=SpDat1, EngText=Special Data 1, ������=CAN
(long)(&co2_vars.co_specialData2), //[2003h.02h], ��������=Special Data 2, �������=SpDat2, EngText=Special Data 2, ������=CAN
(long)(&co2_vars.co_specialData3), //[2003h.03h], ��������=Special Data 3, �������=SpDat3, EngText=Special Data 3, ������=CAN
(long)(&co2_vars.co_specialData4), //[2003h.04h], ��������=Special Data 4, �������=SpDat4, EngText=Special Data 4, ������=CAN
(long)(&co2_vars.co_secretCode), //[2004h.00h], ��������=Secret Code, �������=Secret, EngText=Secret Code, ������=CAN
(long)(&co2_vars.co_protectBit), //[2005h.00h], ��������=Protect Bit, �������=ProtBt, EngText=Protect Bit, ������=CAN
(long)(&co2_odHash[0]), //[2007h.01h], ��������=md5_hash_0, �������=md5_hash_0, EngText=md5_hash_0, ������=CAN
(long)(&co2_odHash[1]), //[2007h.02h], ��������=md5_hash_1, �������=md5_hash_1, EngText=md5_hash_1, ������=CAN
(long)(&co2_odHash[2]), //[2007h.03h], ��������=md5_hash_2, �������=md5_hash_2, EngText=md5_hash_2, ������=CAN
(long)(&co2_odHash[3]), //[2007h.04h], ��������=md5_hash_3, �������=md5_hash_3, EngText=md5_hash_3, ������=CAN
(long)(&co2_vars.co_heartbeatFlag0), //[2010h.01h], ��������=Heartbeat Flag 0-31, �������=HFlag0, EngText=Heartbeat Flag 0-31, ������=CAN
(long)(&co2_vars.co_heartbeatFlag1), //[2010h.02h], ��������=Heartbeat Flag 32-63, �������=HFlag1, EngText=Heartbeat Flag 32-63, ������=CAN
(long)(&co2_vars.co_heartbeatFlag2), //[2010h.03h], ��������=Heartbeat Flag 64-95, �������=HFlag2, EngText=Heartbeat Flag 64-95, ������=CAN
(long)(&co2_vars.co_heartbeatFlag3), //[2010h.04h], ��������=Heartbeat Flag 96-127, �������=HFlag3, EngText=Heartbeat Flag 96-127, ������=CAN
(long)(&co2_vars.co_heartbeatMask0), //[2011h.01h], ��������=Heartbeat Mask 0-31, �������=HMask0, EngText=Heartbeat Mask 0-31, ������=CAN
(long)(&co2_vars.co_heartbeatMask1), //[2011h.02h], ��������=Heartbeat Mask 32-63, �������=HMask1, EngText=Heartbeat Mask 32-63, ������=CAN
(long)(&co2_vars.co_heartbeatMask2), //[2011h.03h], ��������=Heartbeat Mask 64-95, �������=HMask2, EngText=Heartbeat Mask 64-95, ������=CAN
(long)(&co2_vars.co_heartbeatMask3), //[2011h.04h], ��������=Heartbeat Mask 96-127, �������=HMask3, EngText=Heartbeat Mask 96-127, ������=CAN
(long)(&co2_vars.co_heartbeatAutoStart), //[2012h.00h], ��������=Heartbeat Autostart, �������=HBASta, EngText=Heartbeat Autostart, ������=CAN
(long)(&co2_vars.co_heartbeatAutoRecovery), //[2014h.00h], ��������=Heartbeat Autorecovery, �������=HBARec, EngText=Heartbeat Autorecovery, ������=CAN
(long)(&co2_vars.co_nodeState), //[2015h.00h], ��������=��������� �������� CAN-Open, �������=State, EngText=��������� �������� CAN-Open, ������=CAN
(long)(&co2_vars.co_emergencyErrorCode), //[2016h.00h], ��������=Emergency Error Code, �������=EmErCo, EngText=Emergency Error Code, ������=CAN
(long)(&co2_vars.co_deviceErrorState), //[2017h.00h], ��������=Device Error State, �������=DeErSt, EngText=Device Error State, ������=CAN
(long)(&co2_vars.co_ODCommand), //[2080h.01h], ��������=Object Dictionary Command, �������=ODComm, EngText=Object Dictionary Command, ������=CAN
(long)(&co2_vars.co_currentODIndex), //[2080h.02h], ��������=Current OD Index, �������=ODCInd, EngText=Current OD Index, ������=CAN
(long)(&co2_vars.co_currentODSubIndex), //[2080h.03h], ��������=Current OD Sub-Index, �������=ODCSub, EngText=Current OD Sub-Index, ������=CAN
(long)(&co2_vars.co_currentODEText), //[2080h.04h], ��������=Current OD Element Text, �������=ODCTxt, EngText=Current OD Element Text, ������=CAN
(long)(&co2_vars.co_currentODEFormat), //[2080h.05h], ��������=Current OD Element Format, �������=ODCFrm, EngText=Current OD Element Format, ������=CAN
(long)(&co2_vars.co_currentODEMin), //[2080h.06h], ��������=Current OD Element Min, �������=ODCMin, EngText=Current OD Element Min, ������=CAN
(long)(&co2_vars.co_currentODEMax), //[2080h.07h], ��������=Current OD Element Max, �������=ODCMax, EngText=Current OD Element Max, ������=CAN
(long)(&co2_vars.co_currentODEDefault), //[2080h.08h], ��������=Current OD Element Default, �������=ODCDef, EngText=Current OD Element Default, ������=CAN
(long)(&co2_vars.co_currentODEMinLow), //[2080h.09h], ��������=Current OD Element MinLow, �������=ODCMiL, EngText=Current OD Element MinLow, ������=CAN
(long)(&co2_vars.co_currentODEMaxLow), //[2080h.0Ah], ��������=Current OD Element MaxLow, �������=ODCMaL, EngText=Current OD Element MaxLow, ������=CAN
(long)(&co2_vars.co_currentODEDefaultLow), //[2080h.0Bh], ��������=Current OD Element Default Low, �������=ODCDeL, EngText=Current OD Element Default Low, ������=CAN
(long)(&co2_vars.co_currentODEAddrLow), //[2080h.0Ch], ��������=Current OD Element Address, �������=ODCAdr, EngText=Current OD Element Address, ������=CAN
(long)(&co2_vars.co_currentODEAddrLow), //[2080h.0Dh], ��������=Current OD Element Address, �������=ODCAdr, EngText=Current OD Element Address, ������=CAN
(long)(&co2_vars.co_currentODEType), //[2080h.0Eh], ��������=������ ����������, �������=������, EngText=Parameter Group, ������=CAN
(long)(&co2_vars.co_odIndexSize), //[2081h.00h], ��������=���������� ��������, �������=������, EngText=Number of Indexes, ������=CAN
(long)(&co2_vars.co_defaultIndex1), //[2082h.01h], ��������=Default Index 1, �������=DfInd1, EngText=Default Index 1, ������=CAN
(long)(&co2_vars.co_defaultIndex2), //[2082h.02h], ��������=Default Index 2, �������=DfInd2, EngText=Default Index 2, ������=CAN
(long)(&co2_vars.co_maskElement01), //[2083h.01h], ��������=Mask Element, �������=MskEl0, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement01), //[2083h.02h], ��������=Mask Element, �������=MskEl1, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement23), //[2083h.03h], ��������=Mask Element, �������=MskEl2, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement23), //[2083h.04h], ��������=Mask Element, �������=MskEl3, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement45), //[2083h.05h], ��������=Mask Element, �������=MskEl4, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement45), //[2083h.06h], ��������=Mask Element, �������=MskEl5, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement67), //[2083h.07h], ��������=Mask Element, �������=MskEl6, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement67), //[2083h.08h], ��������=Mask Element, �������=MskEl7, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement89), //[2083h.09h], ��������=Mask Element, �������=MskEl8, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElement89), //[2083h.0Ah], ��������=Mask Element, �������=MskEl9, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementAB), //[2083h.0Bh], ��������=Mask Element, �������=MskElA, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementAB), //[2083h.0Ch], ��������=Mask Element, �������=MskElB, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementCD), //[2083h.0Dh], ��������=Mask Element, �������=MskElC, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementCD), //[2083h.0Eh], ��������=Mask Element, �������=MskElD, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementEF), //[2083h.0Fh], ��������=Mask Element, �������=MskElE, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_maskElementEF), //[2083h.10h], ��������=Mask Element, �������=MskElF, EngText=Mask Element, ������=CAN
(long)(&co2_vars.co_scaleNum0), //[2100h.01h], ��������=Scale Number 0, �������=SN0, EngText=Scale Number 0, ������=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.02h], ��������=Scale Number 0 Format, �������=S0Fmt, EngText=Scale Number 0 Format, ������=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum1), //[2101h.01h], ��������=Scale Number 1, �������=SN1, EngText=Scale Number 1, ������=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.02h], ��������=Scale Number 1 Format, �������=S1Fmt, EngText=Scale Number 1 Format, ������=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum2), //[2102h.01h], ��������=Scale Number 2, �������=SN2, EngText=Scale Number 2, ������=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.02h], ��������=Scale Number 2 Format, �������=S2Fmt, EngText=Scale Number 2 Format, ������=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum3), //[2103h.01h], ��������=Scale Number 3, �������=SN3, EngText=Scale Number 3, ������=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.02h], ��������=Scale Number 3 Format, �������=S3Fmt, EngText=Scale Number 3 Format, ������=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum4), //[2104h.01h], ��������=Scale Number 4, �������=SN4, EngText=Scale Number 4, ������=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.02h], ��������=Scale Number 4 Format, �������=S4Fmt, EngText=Scale Number 4 Format, ������=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum5), //[2105h.01h], ��������=Scale Number 5, �������=SN5, EngText=Scale Number 5, ������=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.02h], ��������=Scale Number 5 Format, �������=S5Fmt, EngText=Scale Number 5 Format, ������=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum6), //[2106h.01h], ��������=Scale Number 6, �������=SN6, EngText=Scale Number 6, ������=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.02h], ��������=Scale Number 6 Format, �������=S6Fmt, EngText=Scale Number 6 Format, ������=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum7), //[2107h.01h], ��������=Scale Number 7, �������=SN7, EngText=Scale Number 7, ������=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.02h], ��������=Scale Number 7 Format, �������=S7Fmt, EngText=Scale Number 7 Format, ������=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum8), //[2108h.01h], ��������=Scale Number 8, �������=SN8, EngText=Scale Number 8, ������=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.02h], ��������=Scale Number 8 Format, �������=S8Fmt, EngText=Scale Number 8 Format, ������=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum9), //[2109h.01h], ��������=Scale Number 9, �������=SN9, EngText=Scale Number 9, ������=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.02h], ��������=Scale Number 9 Format, �������=S9Fmt, EngText=Scale Number 9 Format, ������=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumA), //[210Ah.01h], ��������=Scale Number A, �������=SNA, EngText=Scale Number A, ������=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.02h], ��������=Scale Number A Format, �������=SAFmt, EngText=Scale Number A Format, ������=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumB), //[210Bh.01h], ��������=Scale Number B, �������=SNB, EngText=Scale Number B, ������=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.02h], ��������=Scale Number B Format, �������=SBFmt, EngText=Scale Number B Format, ������=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumC), //[210Ch.01h], ��������=Scale Number C, �������=SNC, EngText=Scale Number C, ������=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.02h], ��������=Scale Number C Format, �������=SCFmt, EngText=Scale Number C Format, ������=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumD), //[210Dh.01h], ��������=Scale Number D, �������=SND, EngText=Scale Number D, ������=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.02h], ��������=Scale Number D Format, �������=SDFmt, EngText=Scale Number D Format, ������=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumE), //[210Eh.01h], ��������=Scale Number E, �������=SNE, EngText=Scale Number E, ������=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.02h], ��������=Scale Number E Format, �������=SEFmt, EngText=Scale Number E Format, ������=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNumF), //[210Fh.01h], ��������=Scale Number F, �������=SNF, EngText=Scale Number F, ������=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.02h], ��������=Scale Number F Format, �������=SFFmt, EngText=Scale Number F Format, ������=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum10), //[2110h.01h], ��������=Scale Number 10, �������=SN10, EngText=Scale Number 10, ������=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.02h], ��������=Scale Number 10 Format, �������=S10Fmt, EngText=Scale Number 10 Format, ������=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum11), //[2111h.01h], ��������=Scale Number 11, �������=SN11, EngText=Scale Number 11, ������=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.02h], ��������=Scale Number 11 Format, �������=S11Fmt, EngText=Scale Number 11 Format, ������=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum12), //[2112h.01h], ��������=Scale Number 12, �������=SN12, EngText=Scale Number 12, ������=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.02h], ��������=Scale Number 12 Format, �������=S12Fmt, EngText=Scale Number 12 Format, ������=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum13), //[2113h.01h], ��������=Scale Number 13, �������=SN13, EngText=Scale Number 13, ������=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.02h], ��������=Scale Number 13 Format, �������=S13Fmt, EngText=Scale Number 13 Format, ������=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum14), //[2114h.01h], ��������=Scale Number 14, �������=SN14, EngText=Scale Number 14, ������=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.02h], ��������=Scale Number 14 Format, �������=S14Fmt, EngText=Scale Number 14 Format, ������=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum15), //[2115h.01h], ��������=Scale Number 15, �������=SN15, EngText=Scale Number 15, ������=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.02h], ��������=Scale Number 15Format, �������=S15Fmt, EngText=Scale Number 15Format, ������=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum16), //[2116h.01h], ��������=Scale Number 16, �������=SN16, EngText=Scale Number 16, ������=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.02h], ��������=Scale Number 16Format, �������=S16Fmt, EngText=Scale Number 16Format, ������=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum17), //[2117h.01h], ��������=Scale Number 17, �������=SN17, EngText=Scale Number 17, ������=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.02h], ��������=Scale Number 17Format, �������=S17Fmt, EngText=Scale Number 17Format, ������=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum18), //[2118h.01h], ��������=Scale Number 18, �������=SN18, EngText=Scale Number 18, ������=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.02h], ��������=Scale Number 18Format, �������=S18Fmt, EngText=Scale Number 18Format, ������=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum19), //[2119h.01h], ��������=Scale Number 19, �������=SN19, EngText=Scale Number 19, ������=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.02h], ��������=Scale Number 19Format, �������=S19Fmt, EngText=Scale Number 19Format, ������=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum1A), //[211Ah.01h], ��������=Scale Number 1A, �������=SN1A, EngText=Scale Number 1A, ������=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.02h], ��������=Scale Number 1AFormat, �������=S1AFmt, EngText=Scale Number 1AFormat, ������=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum1B), //[211Bh.01h], ��������=Scale Number 1B, �������=SN1B, EngText=Scale Number 1B, ������=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.02h], ��������=Scale Number 1BFormat, �������=S1BFmt, EngText=Scale Number 1BFormat, ������=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum1C), //[211Ch.01h], ��������=Scale Number 1C, �������=SN1C, EngText=Scale Number 1C, ������=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.02h], ��������=Scale Number 1C Format, �������=S1CFmt, EngText=Scale Number 1C Format, ������=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&co2_vars.co_scaleNum1D), //[211Dh.01h], ��������=Scale Number 1D, �������=SN1D, EngText=Scale Number 1D, ������=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.02h], ��������=Scale Number 1D Format, �������=S1DFmt, EngText=Scale Number 1D Format, ������=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.03h], ��������=Scale Number Format Q, �������=Q-type, EngText=Scale Number Format Q, ������=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.04h], ��������=Scale Number Format NumOfFloat, �������=NFloat, EngText=Scale Number Format NumOfFloat, ������=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.05h], ��������=Scale Number Format Prefix, �������=Prefix, EngText=Scale Number Format Prefix, ������=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.06h], ��������=Scale Number Format Units, �������=33, EngText=Scale Number Format Units, ������=CAN
(long)(&cmd_logic.local_cmd.all), //[2502h.01h], ��������=cmd_pow_on, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.02h], ��������=cmd_pow_off, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.03h], ��������=cmd_trip_reset, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.04h], ��������=cmd_pulses_on, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.05h], ��������=cmd_pulses_off, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.06h], ��������=cmd_more, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.07h], ��������=cmd_less, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.08h], ��������=cmd_set_cmd_source_LOCAL, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.09h], ��������=cmd_set_cmd_source_REMOTE, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Ah], ��������=cmd_set_refs_source_LOCAL, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Bh], ��������=cmd_set_refs_source_REMOTE, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Ch], ��������=cmd_set_dio_logic_mode_manual, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Dh], ��������=cmd_set_dio_logic_mode_auto, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Eh], ��������=cmd_set_dio_logic_mode_test, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.0Fh], ��������=cmd_set_ctrl_profile1, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.10h], ��������=cmd_set_ctrl_profile2, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_cmd.all), //[2502h.11h], ��������=cmd_set_ctrl_profile3, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.status.cmd_source), //[2502h.12h], ��������=cmd_logic_all, �������=cmd_logic_all, EngText=cmd_logic_all, ������=������� � �������
(long)(&cmd_logic.status.refs_source), //[2502h.13h], ��������=refs_source, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.status.profile), //[2502h.14h], ��������=cmd_logic.status.profile, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.status.dio_logic_mode), //[2502h.15h], ��������=dio_logic_mode, �������=, EngText=, ������=������� � �������
(long)(&drv_interface.req_data), //[2506h.01h], ��������=������� ������ �����, �������=OfflineCounterMax, EngText=OfflineCounterMax, ������=��� �����
(long)(&drv_interface.ans_data), //[2506h.02h], ��������=������� ������ �����, �������=OfflineCounter, EngText=OfflineCounter, ������=��� �����
(long)(&drv_interface.data_Low), //[2506h.03h], ��������=data_Low, �������=data_Low, EngText=data_Low, ������=��� �����
(long)(&drv_interface.data_High), //[2506h.04h], ��������=data_High, �������=data_High, EngText=data_High, ������=��� �����
(long)(&RTCclock.packed_time), //[250Fh.00h], ��������=���� ��������� �������, �������=RTC, EngText=Real time clock, ������=�����������
(long)(&apl.protect_Code), //[2532h.01h], ��������=��� ������ ARM, �������=��� ������ ARM, EngText=, ������=�����������
(long)(&apl.alarm_Code), //[2532h.02h], ��������=���������� ���� ������, �������=���+, EngText=Extension of fault ID, ������=�����������
(long)(&disp_group_number), //[2534h.01h], ��������=����� ���� ��� ������ ����������, �������=� �� ��, EngText=, ������=CAN
(long)(&VendorToken), //[2600h.01h], ��������=VendorToken, �������=VendorToken, EngText=VendorToken, ������=��� �����
(long)(&co2_vars.co_blockTransferCommand), //[2700h.00h], ��������=Block Transfer Interpreter, �������=BT Interpreter, EngText=BT Interpreter, ������=����� ����������
(long)(&swu_vars), //[2701h.01h], ��������=cmd, �������=cmd, EngText=cmd, ������=����� ����������
(long)(&swu_vars), //[2701h.02h], ��������=status, �������=status, EngText=status, ������=����� ����������
(long)(&swu_vars), //[2701h.03h], ��������=quest1, �������=quest1, EngText=quest1, ������=����� ����������
(long)(&swu_vars), //[2701h.04h], ��������=quest2, �������=quest2, EngText=quest2, ������=����� ����������
(long)(&swu_vars), //[2701h.05h], ��������=quest3, �������=quest3, EngText=quest3, ������=����� ����������
(long)(&swu_vars), //[2701h.06h], ��������=quest4, �������=quest4, EngText=quest4, ������=����� ����������
(long)(&swu_vars), //[2701h.07h], ��������=ans1, �������=ans1, EngText=ans1, ������=����� ����������
(long)(&swu_vars), //[2701h.08h], ��������=ans2, �������=ans2, EngText=ans2, ������=����� ����������
(long)(&swu_vars), //[2701h.09h], ��������=ans3, �������=ans3, EngText=ans3, ������=����� ����������
(long)(&swu_vars), //[2701h.0Ah], ��������=ans4, �������=ans4, EngText=ans4, ������=����� ����������
(long)(&swu_vars), //[2701h.0Bh], ��������=addr, �������=addr, EngText=addr, ������=����� ����������
(long)(&swu_vars), //[2701h.0Ch], ��������=CPU_ID, �������=CPU_ID, EngText=CPU_ID, ������=����� ����������
(long)(&swu_vars), //[2701h.0Dh], ��������=sector_mask, �������=sector_mask, EngText=sector_mask, ������=����� ����������
(long)(&swu_vars), //[2701h.0Eh], ��������=version, �������=version, EngText=version, ������=����� ����������
(long)(&swu_vars), //[2701h.0Fh], ��������=CRC, �������=CRC, EngText=CRC, ������=����� ����������
(long)(&inv.status), //[3000h.00h], ��������=inv_status, �������=, EngText=, ������=��� �����
(long)(&msCounter), //[3100h.01h], ��������=������� ���������� 1 ���, �������=��.������.1 ���, EngText=, ������=��� �������
(long)(&FastCounter), //[3100h.02h], ��������=������� ���������� 10 ���, �������=��.������.10 ���, EngText=, ������=��� �������
(long)(&LoopCounter), //[3100h.03h], ��������=BackgroundCounter, �������=BackgroundCounter, EngText=, ������=��� �������
(long)(&TIsr10), //[3100h.04h], ��������=T_10���, �������=T_10���, EngText=T_10���, ������=��� �������
(long)(&TIsr1), //[3100h.05h], ��������=T_1���, �������=T_1���, EngText=T_1���, ������=��� �������
(long)(&rmp.T), //[5000h.01h], ��������=T �� ��������, �������=rmpT, EngText=T ������� �� ��������, ������=��
(long)(&rmp.input), //[5000h.02h], ��������=���� ��, �������=������, EngText=Ramp input, ������=��
(long)(&rmp.output), //[5000h.03h], ��������=����� ��, �������=�������, EngText=Ramp output, ������=��
(long)(&mppt.Dinit), //[5101h.01h], ��������=Dinit, �������=Dinit, EngText=Dinit, ������=MPPT
(long)(&mppt.Dmax), //[5101h.02h], ��������=Dmax, �������=Dmax, EngText=Dmax, ������=MPPT
(long)(&mppt.Dmin), //[5101h.03h], ��������=Dmin, �������=Dmin, EngText=Dmin, ������=MPPT
(long)(&mppt.deltaD), //[5101h.04h], ��������=deltaD, �������=deltaD, EngText=deltaD, ������=MPPT
(long)(&mppt.ena), //[5101h.05h], ��������=ena, �������=ena, EngText=ena, ������=MPPT
(long)(&mppt.V), //[5101h.06h], ��������=V, �������=V, EngText=V, ������=MPPT
(long)(&mppt.I), //[5101h.07h], ��������=I, �������=I, EngText=I, ������=MPPT
(long)(&mppt.D), //[5101h.08h], ��������=D, �������=D, EngText=D, ������=MPPT
(long)(&mppt.P), //[5101h.09h], ��������=P, �������=P, EngText=P, ������=MPPT
(long)(&mppt.delayvar), //[5101h.0Ah], ��������=delay, �������=, EngText=, ������=MPPT
(long)(&mppt.deltaV), //[5101h.0Bh], ��������=deltaV, �������=, EngText=, ������=MPPT
(long)(&mppt.Vmax), //[5101h.0Ch], ��������=Vmax, �������=, EngText=, ������=MPPT
(long)(&mppt.Vmin), //[5101h.0Dh], ��������=Vmin, �������=, EngText=, ������=MPPT
(long)(&pid_iq.pid_ref_reg3), //[5102h.01h], ��������=�������, �������=���-��, EngText=�������, ������=���. ���� Iq
(long)(&pid_iq.pid_fdb_reg3), //[5102h.02h], ��������=�������� �����, �������=���.��, EngText=�������� �����, ������=���. ���� Iq
(long)(&pid_iq.Kp_reg3), //[5102h.03h], ��������=�������. �����. Kp, �������=Kp, EngText=���������������� ����������� Kp, ������=���. ���� Iq
(long)(&pid_iq.pid_out_max), //[5102h.04h], ��������=�������� ������, �������=Max, EngText=�������� ������, ������=���. ���� Iq
(long)(&pid_iq.pid_out_min), //[5102h.05h], ��������=������� ������, �������=Min, EngText=������� ������, ������=���. ���� Iq
(long)(&pid_iq.Ki_reg3), //[5102h.06h], ��������=������������ �����. Ki, �������=Ki, EngText=������������ ����������� Ki, ������=���. ���� Iq
(long)(&pid_iq.Kd_reg3), //[5102h.07h], ��������=����. �����. Kd, �������=Kd, EngText=���������������� ����������� Kd, ������=���. ���� Iq
(long)(&pid_iq.Kc_reg3), //[5102h.08h], ��������=������.���������.�����������, �������=Kc, EngText=Integral correction gain, ������=���. ���� Iq
(long)(&pid_iq.e_reg3), //[5102h.09h], ��������=������ ��������������� ��������, �������=������, EngText=, ������=���. ���� Iq
(long)(&pid_iq.pid_out_reg3), //[5102h.0Ah], ��������=����� ����������, �������=�����, EngText=Controller Output, ������=���. ���� Iq
(long)(&pid_iq.up_reg3), //[5102h.0Bh], ��������=���.�������., �������=���.�������., EngText=Ud, ������=���. ���� Iq
(long)(&pid_iq.ui_reg3), //[5102h.0Ch], ��������=���.������., �������=���.������., EngText=Integral Output, ������=���. ���� Iq
(long)(&pid_iq.ud_reg3), //[5102h.0Dh], ��������=���.������., �������=���.������., EngText=Ud, ������=���. ���� Iq
(long)(&pid_id.pid_ref_reg3), //[5103h.01h], ��������=�������, �������=���-�, EngText=Reference, ������=���. ���� Id
(long)(&pid_id.pid_fdb_reg3), //[5103h.02h], ��������=�������� �����, �������=���.��, EngText=Feedback, ������=���. ���� Id
(long)(&pid_id.Kp_reg3), //[5103h.03h], ��������=�������. �����. Kp, �������=Kp, EngText=Kp, ������=���. ���� Id
(long)(&pid_id.pid_out_max), //[5103h.04h], ��������=�������� ������, �������=Max, EngText=Maximum Output Limits, ������=���. ���� Id
(long)(&pid_id.pid_out_min), //[5103h.05h], ��������=������� ������, �������=Min, EngText=Minimum Output Limits, ������=���. ���� Id
(long)(&pid_id.Ki_reg3), //[5103h.06h], ��������=������������ �����. Ki, �������=Ki, EngText=Ki, ������=���. ���� Id
(long)(&pid_id.Kd_reg3), //[5103h.07h], ��������=����. �����. Kd, �������=Kd, EngText=Kd, ������=���. ���� Id
(long)(&pid_id.Kc_reg3), //[5103h.08h], ��������=������.���������.�����������, �������=Kc, EngText=Integral correction gain, ������=���. ���� Id
(long)(&pid_id.e_reg3), //[5103h.09h], ��������=������ ��������������� ��������, �������=������, EngText=, ������=���. ���� Id
(long)(&pid_id.pid_out_reg3), //[5103h.0Ah], ��������=����� ����������, �������=�����, EngText=Controller output, ������=���. ���� Id
(long)(&pid_id.up_reg3), //[5103h.0Bh], ��������=���.�������., �������=���.�������., EngText=Ud, ������=���. ���� Id
(long)(&pid_id.ui_reg3), //[5103h.0Ch], ��������=���.������., �������=���.������., EngText=Integral Output, ������=���. ���� Id
(long)(&pid_id.ud_reg3), //[5103h.0Dh], ��������=���.������., �������=���.������., EngText=Ud, ������=���. ���� Id
(long)(&pid_Udc.pid_ref_reg3), //[5104h.01h], ��������=�������, �������=���-�, EngText=Reference, ������=��������� Udc1
(long)(&pid_Udc.pid_fdb_reg3), //[5104h.02h], ��������=�������� �����, �������=���.��, EngText=Feedback, ������=��������� Udc1
(long)(&pid_Udc.Kp_reg3), //[5104h.03h], ��������=�������. �����. Kp, �������=Kp, EngText=Kp, ������=��������� Udc1
(long)(&pid_Udc.Ki_reg3), //[5104h.04h], ��������=������������ �����. Ki, �������=Ki, EngText=Ki, ������=��������� Udc1
(long)(&pid_Udc.pid_out_max), //[5104h.05h], ��������=�������� ������, �������=Max, EngText=Maximum Output Limits, ������=��������� Udc1
(long)(&pid_Udc.pid_out_min), //[5104h.06h], ��������=������� ������, �������=Min, EngText=Minimum Output Limits, ������=��������� Udc1
(long)(&pid_Udc.pid_out_reg3), //[5104h.07h], ��������=����� ����������, �������=�����, EngText=Controller output, ������=��������� Udc1
(long)(&pid_Udc.up_reg3), //[5104h.08h], ��������=���.�������., �������=���.�������., EngText=Ud, ������=��������� Udc1
(long)(&pid_Udc.ui_reg3), //[5104h.09h], ��������=���.������., �������=���.������., EngText=Integral Output, ������=��������� Udc1
(long)(&pid_Udc.Kd_reg3), //[5104h.0Ah], ��������=����. �����. Kd, �������=Kd, EngText=Kd, ������=��������� Udc1
(long)(&pwm.UalphaRef), //[5105h.01h], ��������=Ua���, �������=Ua���, EngText=Ua���, ������=���
(long)(&pwm.UbetaRef), //[5105h.02h], ��������=Ub���, �������=Ub���, EngText=Ub���, ������=���
(long)(&pwm.U_lim), //[5105h.03h], ��������=U_���, �������=U_���, EngText=U_���, ������=���
(long)(&pwm.gammaA), //[5105h.04h], ��������=GammaA, �������=GmA, EngText=GammaA, ������=���
(long)(&pwm.gammaB), //[5105h.05h], ��������=GammaB, �������=GmB, EngText=GammaB, ������=���
(long)(&pwm.gammaC), //[5105h.06h], ��������=GammaC, �������=GmC, EngText=GammaC, ������=���
(long)(&pwm.k_pwm), //[5105h.07h], ��������=TPWM, �������=TPWM, EngText=TPWM, ������=���
(long)(&pwm.DeadBand), //[5105h.08h], ��������=������� ����� (���), �������=����. �����, EngText=DeadBand, ������=���
(long)(&pwm.MinGammaLimit), //[5105h.09h], ��������=����������� ���. ������., �������=GamLim, EngText=GamLim, ������=���
(long)(&pwm.U_ref_fan_pwm), //[5105h.0Ah], ��������=U_ref_fan_pwm, �������=, EngText=, ������=���
(long)(&pwm.I_ref_pwm), //[5105h.0Bh], ��������=I_ref_pwm, �������=, EngText=, ������=���
(long)(&pwm.PWM_type), //[5105h.0Ch], ��������=��� ���, �������=������, EngText=PWMType, ������=���
(long)(&pwm.UdCompEnable), //[5105h.0Dh], ��������=ULimitation, �������=ULimitation, EngText=ULimitation, ������=���
(long)(&pwm.Frequency), //[5105h.0Eh], ��������=������� ���, �������=F���, EngText=PWM frequency, ������=���
(long)(&pwm.sector), //[5105h.0Fh], ��������=������, �������=������, EngText=Sector, ������=���
(long)(&pwm.U_mag), //[5105h.10h], ��������=U_����, �������=U_����, EngText=U_����, ������=���
(long)(&pwm.PDP_Fault), //[5105h.11h], ��������=����� ������, �������=F_bits, EngText=F_bits, ������=���
(long)(&pwm.PDP_Fault), //[5105h.12h], ��������=����� ������, �������=F_bits, EngText=F_bits, ������=���
(long)(&pwm.PDP_Fault), //[5105h.13h], ��������=����� ������, �������=F_bits, EngText=F_bits, ������=���
(long)(&dcs_ctrl.state), //[510Bh.01h], ��������=sm_state, �������=smstat, EngText=sm_state, ������=�������
(long)(&inv.status), //[510Bh.02h], ��������=inv_status, �������=, EngText=, ������=�������
(long)(&dcs_ctrl.test_param1), //[510Bh.03h], ��������=test_param1, �������=, EngText=, ������=�������
(long)(&dcs_ctrl.test_param2), //[510Bh.04h], ��������=test_param2, �������=, EngText=, ������=�������
(long)(&inv.attempts_counter), //[510Bh.05h], ��������=attemps_counter, �������=, EngText=, ������=�������
(long)(&inv.sub_state), //[510Bh.06h], ��������=sub_state, �������=, EngText=, ������=�������
(long)(&inv.counter), //[510Bh.07h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&inv.sub_counter), //[510Bh.08h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&inv.params.go_day_mode_timeout_s), //[510Bh.09h], ��������=go_day_mode_timeout_s, �������=, EngText=, ������=�������
(long)(&inv.params.go_night_mode_timeout_s), //[510Bh.0Ah], ��������=go_night_mode_timeout_s, �������=, EngText=, ������=�������
(long)(&inv.params.P_low_time_s), //[510Bh.0Bh], ��������=P_low_time_s, �������=, EngText=, ������=�������
(long)(&inv.params.P_low_timeshift_s), //[510Bh.0Ch], ��������=P_low_timeshift, �������=, EngText=, ������=�������
(long)(&inv.params.P_low_attempts_max), //[510Bh.0Dh], ��������=P_low_attemps_max, �������=, EngText=, ������=�������
(long)(&inv.params.P_night), //[510Bh.0Eh], ��������=P_night, �������=, EngText=, ������=�������
(long)(&inv.params.Udc_day), //[510Bh.0Fh], ��������=Udc_day, �������=, EngText=, ������=�������
(long)(&inv.params.Udc_night), //[510Bh.10h], ��������=Udc_night, �������=, EngText=, ������=�������
(long)(&dcs_refs.Id_ref), //[510Bh.11h], ��������=dcs_refs.Id_ref, �������=dcs_refs.Id_ref, EngText=dcs_refs.Id_ref, ������=�������
(long)(&dcs_refs.Iq_ref), //[510Bh.12h], ��������=dcs_refs.Iq_ref, �������=dcs_refs.Iq_ref, EngText=dcs_refs.Iq_ref, ������=�������
(long)(&HAL.DIO.DI_1), //[510Bh.13h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&HAL.DIO.DI_4), //[510Bh.14h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[0].o_word), //[510Bh.15h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[1].o_word), //[510Bh.16h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[2].o_word), //[510Bh.17h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[0].i_word), //[510Bh.18h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[1].i_word), //[510Bh.19h], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[2].i_word), //[510Bh.1Ah], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&can_mini.can_io[0].a_inp), //[510Bh.1Bh], ��������=internal_use_only, �������=, EngText=, ������=�������
(long)(&inv.params.Udc_level_go_on), //[510Bh.1Ch], ��������=Udc_level_go_on, �������=, EngText=, ������=�������
(long)(&inv.params.Udc_min_lim_power), //[510Bh.1Dh], ��������=Udc_min_lim_power, �������=, EngText=, ������=�������
(long)(&inv.params.Udc_max_lim_power), //[510Bh.1Eh], ��������=Udc_max_lim_power, �������=, EngText=, ������=�������
(long)(&dcs_prot.Imax), //[510Eh.01h], ��������=Imax, �������=, EngText=, ������=������
(long)(&dcs_prot.Udc_max), //[510Eh.02h], ��������=Udc1_max, �������=, EngText=, ������=������
(long)(&dcs_prot.Udc_min), //[510Eh.03h], ��������=Udc1_min, �������=, EngText=, ������=������
(long)(&dcs_prot.U1_max), //[510Eh.04h], ��������=U1max, �������=, EngText=, ������=������
(long)(&dcs_prot.U1_min), //[510Eh.05h], ��������=U1min, �������=, EngText=, ������=������
(long)(&dcs_prot.Idc_max), //[510Eh.06h], ��������=Idc1_max, �������=, EngText=, ������=������
(long)(&dio_protect.bit_fault1), //[510Eh.07h], ��������=dio_prot_bit_fault1, �������=, EngText=, ������=������
(long)(&dcs_prot.bit_alarm1), //[510Eh.08h], ��������=bit_alarm, �������=, EngText=, ������=������
(long)(&dio_protect.bit_alarm1), //[510Eh.09h], ��������=bit_alarm, �������=, EngText=, ������=������
(long)(&dcs_prot.bit_fault1), //[510Eh.0Ah], ��������=dcs_prot_bit_fault1, �������=, EngText=, ������=������
(long)(&dcs_prot.bit_fault1), //[510Eh.0Bh], ��������=dcs_prot_bit_fault1, �������=, EngText=, ������=������
(long)(&dcs_prot.masked_bit_fault1), //[510Eh.0Ch], ��������=dcs_prot_masked_bit_fault1, �������=, EngText=, ������=������
(long)(&dcs_prot.masked_bit_fault1), //[510Eh.0Dh], ��������=dcs_prot_masked_bit_fault1, �������=, EngText=, ������=������
(long)(&dcs_prot.mask_fault_pwm1), //[510Eh.0Eh], ��������=dcs_prot_mask_fault_pwm, �������=, EngText=, ������=������
(long)(&dcs_prot.mask_fault_pwm1), //[510Eh.0Fh], ��������=dcs_prot_mask_fault_pwm, �������=, EngText=, ������=������
(long)(&dcs_prot.mask_fault_off), //[510Eh.10h], ��������=dcs_prot_mask_fault_off, �������=, EngText=, ������=������
(long)(&dcs_prot.mask_fault_off), //[510Eh.11h], ��������=dcs_prot_mask_fault_off, �������=, EngText=, ������=������
(long)(&dio_protect.bit_fault1), //[510Eh.12h], ��������=dio_prot_bit_fault1, �������=, EngText=, ������=������
(long)(&dio_protect.bit_fault1), //[510Eh.13h], ��������=dio_prot_bit_fault1, �������=, EngText=, ������=������
(long)(&dio_protect.masked_bit_fault1), //[510Eh.14h], ��������=dio_prot_masked_bit_fault1, �������=, EngText=, ������=������
(long)(&dio_protect.masked_bit_fault1), //[510Eh.15h], ��������=dio_prot_masked_bit_fault1, �������=, EngText=, ������=������
(long)(&dio_protect.mask_fault_pwm1), //[510Eh.16h], ��������=dio_prot_mask_fault_pwm, �������=, EngText=, ������=������
(long)(&dio_protect.mask_fault_pwm1), //[510Eh.17h], ��������=dio_prot_mask_fault_pwm, �������=, EngText=, ������=������
(long)(&dio_protect.mask_fault_off), //[510Eh.18h], ��������=dio_prot_mask_fault_off, �������=, EngText=, ������=������
(long)(&dio_protect.mask_fault_off), //[510Eh.19h], ��������=dio_prot_mask_fault_off, �������=, EngText=, ������=������
(long)(&dcs_prot.T_max), //[510Eh.1Ah], ��������=������� �max, �������=Tmax, EngText=Tmax, ������=������
(long)(&apl_protect.AR1.ena), //[510Fh.01h], ��������=apl_protect.AR1.ena, �������=, EngText=, ������=������
(long)(&apl_protect.masked_word[0]), //[510Fh.02h], ��������=apl_protect.masked_word0, �������=, EngText=, ������=������
(long)(&apl_protect.masked_word[1]), //[510Fh.03h], ��������=apl_protect.masked_word1, �������=, EngText=, ������=������
(long)(&apl_protect.masked_off_word[0]), //[510Fh.04h], ��������=apl_protect.masked_off_word0, �������=, EngText=, ������=������
(long)(&apl_protect.masked_off_word[1]), //[510Fh.05h], ��������=apl_protect.masked_off_word1, �������=, EngText=, ������=������
(long)(&apl_protect.mask_apv_word[0]), //[510Fh.06h], ��������=apl_protect.mask_apv_word0, �������=, EngText=, ������=������
(long)(&apl_protect.mask_apv_word[0]), //[510Fh.07h], ��������=apl_protect.mask_apv_word0, �������=, EngText=, ������=������
(long)(&apl_protect.mask_apv_word[1]), //[510Fh.08h], ��������=apl_protect.mask_apv_word1, �������=, EngText=, ������=������
(long)(&apl_protect.mask_apv_word[1]), //[510Fh.09h], ��������=apl_protect.mask_apv_word1, �������=, EngText=, ������=������
(long)(&pll.Ua), //[5111h.01h], ��������=pll_Ua, �������=, EngText=, ������=������������� � �����
(long)(&pll.Ub), //[5111h.02h], ��������=pll_Ub, �������=, EngText=, ������=������������� � �����
(long)(&pll.Uc), //[5111h.03h], ��������=pll_Uc, �������=, EngText=, ������=������������� � �����
(long)(&pll.Um1), //[5111h.04h], ��������=pll_Um1, �������=, EngText=, ������=������������� � �����
(long)(&pll.Um2), //[5111h.05h], ��������=pll_Um2, �������=, EngText=, ������=������������� � �����
(long)(&pll.wt_e), //[5111h.06h], ��������=pll_wt_e, �������=, EngText=, ������=������������� � �����
(long)(&pll.fs), //[5111h.07h], ��������=pll.fs, �������=, EngText=, ������=������������� � �����
(long)(&pll.alpha), //[5111h.08h], ��������=pll.alpha, �������=, EngText=, ������=������������� � �����
(long)(&cmd_logic.remote_refs.P_ref), //[5112h.01h], ��������=remote.P_ref, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_refs.P_ref), //[5112h.02h], ��������=local.P_ref, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.refs.P_ref), //[5112h.03h], ��������=refs.P_ref, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.remote_refs.P_dcdc_ref), //[5112h.04h], ��������=remote.P_dcdc_ref, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.local_refs.P_dcdc_ref), //[5112h.05h], ��������=local.P_dcdc_ref, �������=, EngText=, ������=������� � �������
(long)(&cmd_logic.refs.P_dcdc_ref), //[5112h.06h], ��������=refs.P_dcdc_ref, �������=, EngText=, ������=������� � �������
(long)(&dcs_ctrl.cmd_set_mode), //[5112h.07h], ��������=������� ������, �������=ErrReg, EngText=Error Register, ������=������� � �������
(long)(&inv_params.I_nom), //[5113h.01h], ��������=����������� ���, �������=, EngText=����������� ���, ������=�����. �����
(long)(&inv_params.U_nom), //[5113h.02h], ��������=����������� ���������� ����., �������=U�_���, EngText=����������� ���������� ����., ������=�����. �����
(long)(&inv_params.Udc_nom), //[5113h.03h], ��������=����������� ���������� ���, �������=Udc���, EngText=����������� ���������� ���, ������=�����. �����
(long)(&inv_params.Rs), //[5113h.04h], ��������=Rs, �������=Rs, EngText=Rs, ������=�����. �����
(long)(&inv_params.Ls), //[5113h.05h], ��������=Ls, �������=Ls, EngText=Ls, ������=�����. �����
(long)(&inv_params.freq_nom), //[5113h.06h], ��������=����������� �������, �������=���.����., EngText=Rated frequency, ������=�����. �����
(long)(&sw.HardwareType), //[5114h.01h], ��������=��� ���������� �����, �������=HardwareType, EngText=HardwareType, ������=��������� ��
(long)(&sw.AutoOffset), //[5114h.02h], ��������=��� ���� ����., �������=�������, EngText=AutoOffset, ������=��������� ��
(long)(&sw.Reboot), //[5114h.03h], ��������=������������, �������=������������, EngText=Reboot, ������=��������� ��
(long)(&sim.dcs_sim_ena), //[5115h.01h], ��������=dcs_sim_ena, �������=, EngText=, ������=���������
(long)(&sim.dio_sim_ena), //[5115h.02h], ��������=dio_sim_ena, �������=, EngText=, ������=���������
(long)(&sim.freq), //[5115h.03h], ��������=freq, �������=, EngText=, ������=���������
(long)(&sim.angle), //[5115h.04h], ��������=angle, �������=, EngText=, ������=���������
(long)(&sim.Um1_tr), //[5115h.05h], ��������=Um1_tr, �������=, EngText=, ������=���������
(long)(&sim.Udc_ref), //[5115h.06h], ��������=sim.Udc_ref, �������=, EngText=, ������=���������
(long)(&sim.I_diesel), //[5115h.07h], ��������=I_diesel, �������=, EngText=, ������=���������
(long)(&sim.Idc_ref), //[5115h.08h], ��������=sim.Idc_ref, �������=, EngText=, ������=���������
(long)(&sim.Ua_tr), //[5115h.09h], ��������=Ua_tr, �������=, EngText=, ������=���������
(long)(&sim.Ub_tr), //[5115h.0Ah], ��������=Ub_tr, �������=, EngText=, ������=���������
(long)(&sim.Uc_tr), //[5115h.0Bh], ��������=Uc_tr, �������=, EngText=, ������=���������
(long)(&sim.Um1_f), //[5115h.0Ch], ��������=Um1_f, �������=, EngText=, ������=���������
(long)(&sim.Ua_f), //[5115h.0Dh], ��������=Ua_f, �������=, EngText=, ������=���������
(long)(&sim.Ub_f), //[5115h.0Eh], ��������=Ub_f, �������=, EngText=, ������=���������
(long)(&sim.Uc_f), //[5115h.0Fh], ��������=Uc_f, �������=, EngText=, ������=���������
(long)(&sim.Ia_tr), //[5115h.10h], ��������=Ia_tr, �������=, EngText=, ������=���������
(long)(&sim.Ib_tr), //[5115h.11h], ��������=Ib_tr, �������=, EngText=, ������=���������
(long)(&sim.Ic_tr), //[5115h.12h], ��������=Ic_tr, �������=, EngText=, ������=���������
(long)(&sim.Ia_inv), //[5115h.13h], ��������=Ia_inv, �������=, EngText=, ������=���������
(long)(&sim.Ib_inv), //[5115h.14h], ��������=Ib_inv, �������=, EngText=, ������=���������
(long)(&sim.Ic_inv), //[5115h.15h], ��������=Ic_inv, �������=, EngText=, ������=���������
(long)(&sim.event), //[5115h.16h], ��������=sim.event, �������=, EngText=, ������=���������
(long)(&sim.event_timeout), //[5115h.17h], ��������=sim.event_timeout, �������=, EngText=, ������=���������
(long)(&adc.sUbc_inv.value), //[5116h.01h], ��������=Ubc_inv, �������=, EngText=, ������=���
(long)(&adc.sUac_inv.value), //[5116h.02h], ��������=Uac_inv, �������=, EngText=, ������=���
(long)(&adc.sUnc_inv.value), //[5116h.03h], ��������=Unc_inv, �������=, EngText=, ������=���
(long)(&adc.sUbc_inv._100to1V_gain), //[5116h.04h], ��������=Ubc_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sUac_inv._100to1V_gain), //[5116h.05h], ��������=Uac_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sUnc_inv._100to1V_gain), //[5116h.06h], ��������=Unc_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sUbc_inv.offset), //[5116h.07h], ��������=Ubc_inv_offset, �������=, EngText=, ������=���
(long)(&adc.sUac_inv.offset), //[5116h.08h], ��������=Uac_inv_offset, �������=, EngText=, ������=���
(long)(&adc.sUnc_inv.offset), //[5116h.09h], ��������=Unc_inv_offset, �������=, EngText=, ������=���
(long)(&delimeter_sign), //[5116h.0Ah], ��������=__________________________, �������=, EngText=, ������=���
(long)(&adc.sUbc_tr.value), //[5116h.0Bh], ��������=Ubc_tr, �������=, EngText=, ������=���
(long)(&adc.sUac_tr.value), //[5116h.0Ch], ��������=Uac_tr, �������=, EngText=, ������=���
(long)(&adc.sUnc_tr.value), //[5116h.0Dh], ��������=Unc_tr, �������=, EngText=, ������=���
(long)(&adc.sUbc_tr._100to1V_gain), //[5116h.0Eh], ��������=Ubc_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sUac_tr._100to1V_gain), //[5116h.0Fh], ��������=Uac_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sUnc_tr._100to1V_gain), //[5116h.10h], ��������=Unc_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sUbc_tr.offset), //[5116h.11h], ��������=Ubc_tr_offset, �������=, EngText=, ������=���
(long)(&adc.sUac_tr.offset), //[5116h.12h], ��������=Uac_tr_offset, �������=, EngText=, ������=���
(long)(&adc.sUnc_tr.offset), //[5116h.13h], ��������=Unc_tr_offset, �������=, EngText=, ������=���
(long)(&delimeter_sign), //[5116h.14h], ��������=__________________________, �������=, EngText=, ������=���
(long)(&adc.Ia_inv), //[5116h.15h], ��������=Ia_inv, �������=, EngText=, ������=���
(long)(&adc.Ib_inv), //[5116h.16h], ��������=Ib_inv, �������=, EngText=, ������=���
(long)(&adc.Ic_inv), //[5116h.17h], ��������=Ic_inv, �������=, EngText=, ������=���
(long)(&adc.sIa_inv._100to1V_gain), //[5116h.18h], ��������=Ia_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sIb_inv._100to1V_gain), //[5116h.19h], ��������=Ib_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sIc_inv._100to1V_gain), //[5116h.1Ah], ��������=Ic_inv_gain, �������=, EngText=, ������=���
(long)(&adc.sIa_inv.offset), //[5116h.1Bh], ��������=Ia_inv_offset, �������=, EngText=, ������=���
(long)(&adc.sIb_inv.offset), //[5116h.1Ch], ��������=Ib_inv_offset, �������=, EngText=, ������=���
(long)(&adc.sIc_inv.offset), //[5116h.1Dh], ��������=Ic_inv_offset, �������=, EngText=, ������=���
(long)(&delimeter_sign), //[5116h.1Eh], ��������=__________________________, �������=, EngText=, ������=���
(long)(&adc.Ia_tr), //[5116h.1Fh], ��������=Ia_tr, �������=, EngText=, ������=���
(long)(&adc.Ib_tr), //[5116h.20h], ��������=Ib_tr, �������=, EngText=, ������=���
(long)(&adc.Ic_tr), //[5116h.21h], ��������=Ic_tr, �������=, EngText=, ������=���
(long)(&adc.sIa_tr._100to1V_gain), //[5116h.22h], ��������=Ia_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sIb_tr._100to1V_gain), //[5116h.23h], ��������=Ib_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sIc_tr._100to1V_gain), //[5116h.24h], ��������=Ic_tr_gain, �������=, EngText=, ������=���
(long)(&adc.sIa_tr.offset), //[5116h.25h], ��������=Ia_tr_offset, �������=, EngText=, ������=���
(long)(&adc.sIb_tr.offset), //[5116h.26h], ��������=Ib_tr_offset, �������=, EngText=, ������=���
(long)(&adc.sIc_tr.offset), //[5116h.27h], ��������=Ic_tr_offset, �������=, EngText=, ������=���
(long)(&delimeter_sign), //[5116h.28h], ��������=__________________________, �������=, EngText=, ������=���
(long)(&adc.sIdc._100to1V_gain), //[5116h.29h], ��������=Idc_meas_gain, �������=, EngText=, ������=���
(long)(&adc.sIdc.offset), //[5116h.2Ah], ��������=Idc_meas_offset, �������=, EngText=, ������=���
(long)(&adc.Idc), //[5116h.2Bh], ��������=Idc_meas, �������=, EngText=, ������=���
(long)(&adc.sUdc._100to1V_gain), //[5116h.2Ch], ��������=Udc_meas_gain, �������=, EngText=, ������=���
(long)(&adc.sUdc.offset), //[5116h.2Dh], ��������=Udc_meas_offset, �������=, EngText=, ������=���
(long)(&adc.Udc), //[5116h.2Eh], ��������=Udc_meas, �������=, EngText=, ������=���
(long)(&adc.I_REF_PWM_adc), //[5116h.2Fh], ��������=I_REF_PWM_adc, �������=, EngText=, ������=���
(long)(&adc._0p75V_REF_adc), //[5116h.30h], ��������=_0p75V_REF_adc, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.Udc_adc_reg), //[5116h.31h], ��������=Udc_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U1_BC_adc_reg), //[5116h.32h], ��������=U1_BC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U1_AC_adc_reg), //[5116h.33h], ��������=U1_AC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U1_NC_adc_reg), //[5116h.34h], ��������=U1_NC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U2_BC_adc_reg), //[5116h.35h], ��������=U2_BC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U2_AC_adc_reg), //[5116h.36h], ��������=U2_AC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.U2_NC_adc_reg), //[5116h.37h], ��������=U2_NC_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I2_C_adc_reg), //[5116h.38h], ��������=I2_C_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I2_B_adc_reg), //[5116h.39h], ��������=I2_B_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I2_A_adc_reg), //[5116h.3Ah], ��������=I2_A_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I1_C_adc_reg), //[5116h.3Bh], ��������=I1_C_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I1_B_adc_reg), //[5116h.3Ch], ��������=I1_B_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.I1_A_adc_reg), //[5116h.3Dh], ��������=I1_A_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.Idc_adc_reg), //[5116h.3Eh], ��������=Idc_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs._0p75V_adc_reg), //[5116h.3Fh], ��������=_0p75V_adc_reg, �������=, EngText=, ������=���
(long)(&HAL.ADC.regs.IREF_PWM_adc_reg), //[5116h.40h], ��������=I_REF_PWM_adc_reg, �������=, EngText=, ������=���
(long)(&adc.auto_offset_ena), //[5116h.41h], ��������=��� ���� ����., �������=�������, EngText=AutoOffset, ������=���
(long)(&cur_par.Pdc), //[5138h.01h], ��������=Pdc, �������=, EngText=, ������=�����������
(long)(&cur_par.Pac), //[5138h.02h], ��������=Pac, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ia_inv), //[5138h.03h], ��������=Ia_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ib_inv), //[5138h.04h], ��������=Ib_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ic_inv), //[5138h.05h], ��������=Ic_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ia_tr), //[5138h.06h], ��������=Ia_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ib_tr), //[5138h.07h], ��������=Ib_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ic_tr), //[5138h.08h], ��������=Ic_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Uab_inv), //[5138h.09h], ��������=Uab_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ubc_inv), //[5138h.0Ah], ��������=Ubc_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Uca_inv), //[5138h.0Bh], ��������=Uca_inv_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Uab_tr), //[5138h.0Ch], ��������=Uab_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Ubc_tr), //[5138h.0Dh], ��������=Ubc_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.rms.Uca_tr), //[5138h.0Eh], ��������=Uca_tr_rms, �������=, EngText=, ������=�����������
(long)(&adc.Uab_inv), //[5138h.0Fh], ��������=Uab_inv, �������=, EngText=, ������=�����������
(long)(&adc.Ubc_inv), //[5138h.10h], ��������=Ubc_inv, �������=, EngText=, ������=�����������
(long)(&adc.Uca_inv), //[5138h.11h], ��������=Uca_inv, �������=, EngText=, ������=�����������
(long)(&adc.Uab_tr), //[5138h.12h], ��������=Uab_tr, �������=, EngText=, ������=�����������
(long)(&adc.Ubc_tr), //[5138h.13h], ��������=Ubc_tr, �������=, EngText=, ������=�����������
(long)(&adc.Uca_tr), //[5138h.14h], ��������=Uca_tr, �������=, EngText=, ������=�����������
(long)(&pll.Um1), //[5138h.15h], ��������=Um1_tr, �������=, EngText=, ������=�����������
(long)(&pll.Um2), //[5138h.16h], ��������=Um2_tr, �������=, EngText=, ������=�����������
(long)(&global_time.PowerOn_time_min), //[5138h.17h], ��������=����� ����������� ���������, ���, �������=Power On Time, EngText=Power On Time, ������=�����������
(long)(&global_time.operational_time_min), //[5138h.18h], ��������=����� ������ �������, ���, �������=Work Time, EngText=Work Time, ������=�����������
(long)(&cur_par.Qac), //[5138h.19h], ��������=Qac, �������=, EngText=, ������=�����������
(long)(&cur_par.S), //[5138h.1Ah], ��������=Sac, �������=, EngText=, ������=�����������
(long)(&cur_par.cos_fi), //[5138h.1Bh], ��������=cos(fi), �������=, EngText=, ������=�����������
(long)(&adc.Edc_day), //[5138h.1Ch], ��������=Edc_day, �������=, EngText=, ������=�����������
(long)(&adc.Edc_total), //[5138h.1Dh], ��������=Edc_total, �������=, EngText=, ������=�����������
(long)(&adc.sUbc_tr.calibration.gain), //[5139h.01h], ��������=sUbc_tr.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sUbc_inv.calibration.gain), //[5139h.02h], ��������=sUbc_inv.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIa_tr.calibration.gain), //[5139h.03h], ��������=sIa_tr.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIb_tr.calibration.gain), //[5139h.04h], ��������=sIb_tr.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIc_tr.calibration.gain), //[5139h.05h], ��������=sIc_tr.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIa_inv.calibration.gain), //[5139h.06h], ��������=sIa_inv.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIb_inv.calibration.gain), //[5139h.07h], ��������=sIb_inv.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIc_inv.calibration.gain), //[5139h.08h], ��������=sIc_inv.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sUdc.calibration.gain), //[5139h.09h], ��������=sUdc.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sIdc.calibration.gain), //[5139h.0Ah], ��������=sIdc.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&adc.sI_diesel.calibration.gain), //[5139h.0Bh], ��������=sI_diesel.calibration.gain, �������=, EngText=, ������=���������� ���������
(long)(&dlog.mode_reset), //[5150h.01h], ��������=dlog.mode_reset, �������=mode, EngText=dlog.mode_reset, ������=dlog
(long)(&dlog.control), //[5150h.02h], ��������=dlog.control, �������=dlcont, EngText=dlog.control, ������=dlog
(long)(&dlog.ind_subind1), //[5150h.03h], ��������=dlog.ind_subind1, �������=dlisi1, EngText=dlog.ind_subind1, ������=dlog
(long)(&dlog.ind_subind2), //[5150h.04h], ��������=dlog.ind_subind2, �������=dlisi2, EngText=dlog.ind_subind2, ������=dlog
(long)(&dlog.ind_subind3), //[5150h.05h], ��������=dlog.ind_subind3, �������=dlisi3, EngText=dlog.ind_subind3, ������=dlog
(long)(&dlog.ind_subind4), //[5150h.06h], ��������=dlog.ind_subind4, �������=dlisi4, EngText=dlog.ind_subind4, ������=dlog
(long)(&dlog.StartBits), //[5150h.07h], ��������=StartBitL, �������=StrtBL, EngText=StartBitL, ������=dlog
(long)(&dlog.StartBits), //[5150h.08h], ��������=StartBitH, �������=StrtBH, EngText=StartBitH, ������=dlog
(long)(&dlog.OneShotOperation), //[5150h.09h], ��������=OneShotOperation, �������=OneShotOp, EngText=OneShotOperation, ������=dlog
(long)(&dlog.trig_shift), //[5150h.0Ah], ��������=���������� ����� �����������, �������=N �������., EngText=Prehistory Points Number, ������=dlog
(long)(&dlog.next_value_var), //[5151h.00h], ��������=dlog.next_value_var, �������=dlnval, EngText=dlog.next_value_var, ������=��� �����
(long)(&Debug1), //[5174h.01h], ��������=DebugL1, �������=DebugL1, EngText=DebugL1, ������=��� �������
(long)(&Debug1), //[5174h.02h], ��������=DebugL1, �������=DebugL1, EngText=DebugL1, ������=��� �������
(long)(&Debug2), //[5174h.03h], ��������=DebugL2, �������=DebugL2, EngText=DebugL2, ������=��� �������
(long)(&Debug2), //[5174h.04h], ��������=DebugL2, �������=DebugL2, EngText=DebugL2, ������=��� �������
(long)(&Debug3), //[5174h.05h], ��������=DebugI3, �������=DebugI3, EngText=DebugI3, ������=��� �������
(long)(&Debug3), //[5174h.06h], ��������=DebugI3, �������=DebugI3, EngText=DebugI3, ������=��� �������
(long)(&Debug4), //[5174h.07h], ��������=DebugI4, �������=DebugI4, EngText=DebugI4, ������=��� �������
(long)(&Debug4), //[5174h.08h], ��������=DebugI4, �������=DebugI4, EngText=DebugI4, ������=��� �������
(long)(&DebugW1), //[5174h.09h], ��������=DebugW1, �������=DebugW1, EngText=DebugW1, ������=��� �������
(long)(&DebugW1), //[5174h.0Ah], ��������=DebugW1, �������=DebugW1, EngText=DebugW1, ������=��� �������
(long)(&DebugW2), //[5174h.0Bh], ��������=DebugW2, �������=DebugW2, EngText=DebugW2, ������=��� �������
(long)(&DebugW2), //[5174h.0Ch], ��������=DebugW2, �������=DebugW2, EngText=DebugW2, ������=��� �������
(long)(&DebugW3), //[5174h.0Dh], ��������=DebugW3, �������=DebugW3, EngText=DebugW3, ������=��� �������
(long)(&DebugW3), //[5174h.0Eh], ��������=DebugW3, �������=DebugW3, EngText=DebugW3, ������=��� �������
(long)(&DebugW4), //[5174h.0Fh], ��������=DebugW4, �������=DebugW4, EngText=, ������=��� �������
(long)(&DebugW4), //[5174h.10h], ��������=DebugW4, �������=DebugW4, EngText=, ������=��� �������
(long)(&DebugF1), //[5174h.11h], ��������=DebugF1, �������=DebugF1, EngText=, ������=��� �������
(long)(&DebugF2), //[5174h.12h], ��������=DebugF2, �������=DebugF2, EngText=, ������=��� �������
(long)(&DebugF3), //[5174h.13h], ��������=DebugF3, �������=DebugF3, EngText=, ������=��� �������
(long)(&DebugF4), //[5174h.14h], ��������=DebugF4, �������=DebugF4, EngText=, ������=��� �������
(long)(&fan_actrl.Temp_max_fan), //[5175h.01h], ��������=������� �max, �������=Tmax, EngText=Tmax, ������=������� ����������
(long)(&fan_actrl.Temp_min_fan), //[5175h.02h], ��������=������� �min, �������=Tmin, EngText=Tmin, ������=������� ����������
(long)(&fan_actrl.V_out), //[5175h.03h], ��������=�����, �������=U_out, EngText=U_out, ������=������� ����������
(long)(&fan_actrl.V_fdb), //[5175h.04h], ��������=�������� ������, �������=U_fdb, EngText=U_fdb, ������=������� ����������
(long)(&fan_actrl.state), //[5175h.05h], ��������=state, �������=state, EngText=state, ������=������� ����������
(long)(&fan_actrl.T), //[5175h.06h], ��������=�����������, �������=t, EngText=temperature, ������=������� ����������
(long)(&fan_dctrl.T_max), //[5176h.01h], ��������=������� �max, �������=Tmax, EngText=Tmax, ������=������� ����������
(long)(&fan_dctrl.Temp_lo), //[5176h.02h], ��������=Temp_lo, �������=Temp_lo, EngText=Temp_lo, ������=������� ����������
(long)(&fan_dctrl.Temp_lo2hi), //[5176h.03h], ��������=Temp_lo2hi, �������=Temp_lo2hi, EngText=Temp_lo2hi, ������=������� ����������
(long)(&fan_dctrl.Temp_hi2lo), //[5176h.04h], ��������=Temp_hi2lo, �������=Temp_hi2lo, EngText=Temp_hi2lo, ������=������� ����������
(long)(&fan_dctrl.Temp_hi), //[5176h.05h], ��������=Temp_hi, �������=Temp_hi, EngText=Temp_hi, ������=������� ����������
(long)(&fan_dctrl.time_hi2lo_ms), //[5176h.06h], ��������=time_hi2lo_ms, �������=time_hi2lo_ms, EngText=time_hi2lo_ms, ������=������� ����������
(long)(&fan_dctrl.state), //[5176h.07h], ��������=state, �������=state, EngText=state, ������=������� ����������
(long)(&fan_spec.d_fdb), //[5176h.08h], ��������=state, �������=state, EngText=state, ������=������� ����������
(long)(&fan_dctrl.T), //[5176h.09h], ��������=�����������, �������=t, EngText=temperature, ������=������� ����������
(long)(&adc.T1), //[5177h.01h], ��������=������ ����������� �1, �������=T1, EngText=T1, ������=������� ����������
(long)(&adc.T2), //[5177h.02h], ��������=������ ����������� �2, �������=T2, EngText=T2, ������=������� ����������
(long)(&adc.T3), //[5177h.03h], ��������=������ ����������� �3, �������=T3, EngText=T3, ������=������� ����������
(long)(&adc.T4), //[5177h.04h], ��������=������ ����������� �4, �������=T4, EngText=T4, ������=������� ����������
(long)(&adc.T1_inv1), //[5177h.05h], ��������=����������� IGBT#1, �������=, EngText=, ������=������� ����������
(long)(&adc.T2_inv1), //[5177h.06h], ��������=����������� IGBT#2, �������=, EngText=, ������=������� ����������
(long)(&adc.T3_inv1), //[5177h.07h], ��������=����������� IGBT#3, �������=, EngText=, ������=������� ����������
(long)(&adc.T1_inv2), //[5177h.08h], ��������=����������� IGBT#1, �������=, EngText=, ������=������� ����������
(long)(&adc.T2_inv2), //[5177h.09h], ��������=����������� IGBT#2, �������=, EngText=, ������=������� ����������
(long)(&adc.T3_inv2), //[5177h.0Ah], ��������=����������� IGBT#3, �������=, EngText=, ������=������� ����������
(long)(&ModBus.Enabled), //[5A20h.01h], ��������=�������, �������=���, EngText=Enabled, ������=MODBUS
(long)(&ModBus.RSNodeID), //[5A20h.02h], ��������=����� � ���� ModBus, �������=, EngText=, ������=MODBUS
(long)(&ModBus.BaudRate), //[5A20h.03h], ��������=, �������=, EngText=, ������=MODBUS
(long)(&ModBus.OfflineCounterMax), //[5A20h.04h], ��������=������� ������ �����, �������=OfflineCounterMax, EngText=OfflineCounterMax, ������=MODBUS
(long)(&ModBus.AutoRestart), //[5A20h.05h], ��������=���������� ��� ����� �� �����, �������=auto_res, EngText=auto_res, ������=MODBUS
(long)(&ModBus.OfflineCounter), //[5A20h.06h], ��������=������� ������ �����, �������=OfflineCounter, EngText=OfflineCounter, ������=MODBUS
(long)(&ModBus.isOnline), //[5A20h.07h], ��������=Udc_meas_offset, �������=, EngText=, ������=MODBUS
(long)(&ModBus.received_data), //[5A20h.08h], ��������=Udc_meas, �������=, EngText=, ������=MODBUS
(long)(&ModBus.MBInternals.TxState), //[5A20h.09h], ��������=��������� �������� �������, �������=TXState, EngText=TXState, ������=MODBUS
(long)(&ModBus.GPIOsValue), //[5A20h.0Ah], ��������=dio_prot_mask_fault_off, �������=, EngText=, ������=MODBUS
(long)(&ModBus.ReceivePacketCounter), //[5A20h.0Bh], ��������=������� �������, �������=ReceivePacketCounte, EngText=ReceivePacketCounter, ������=MODBUS
(long)(&ModBus.ReceiveByteCounter), //[5A20h.0Ch], ��������=���� �������, �������=ReceiveByteCounter, EngText=ReceiveByteCounter, ������=MODBUS
(long)(&aux_Q4.state), //[5A78h.01h], ��������=state, �������=, EngText=, ������=Q4
(long)(&aux_Q4.aux_on), //[5A78h.02h], ��������=aux_on, �������=, EngText=, ������=Q4
(long)(&aux_Q4.aux_off), //[5A78h.03h], ��������=aux_off, �������=, EngText=, ������=Q4
(long)(&aux_Q4.hold_on), //[5A78h.04h], ��������=hold_on, �������=, EngText=, ������=Q4
(long)(&aux_Q4.hold_off), //[5A78h.05h], ��������=hold_off, �������=, EngText=, ������=Q4
(long)(&aux_Q26.state), //[5A79h.01h], ��������=state, �������=, EngText=, ������=Q26
(long)(&aux_Q26.aux_on), //[5A79h.02h], ��������=aux_on, �������=, EngText=, ������=Q26
(long)(&aux_Q26.aux_off), //[5A79h.03h], ��������=aux_off, �������=, EngText=, ������=Q26
(long)(&aux_Q26.hold_on), //[5A79h.04h], ��������=hold_on, �������=, EngText=, ������=Q26
(long)(&aux_Q26.hold_off), //[5A79h.05h], ��������=hold_off, �������=, EngText=, ������=Q26
(long)(&aux_K7.state), //[5A7Ah.01h], ��������=state, �������=, EngText=, ������=K7
(long)(&aux_K7.aux_on), //[5A7Ah.02h], ��������=aux_on, �������=, EngText=, ������=K7
(long)(&aux_K7.aux_off), //[5A7Ah.03h], ��������=aux_off, �������=, EngText=, ������=K7
(long)(&aux_K7.hold_on), //[5A7Ah.04h], ��������=hold_on, �������=, EngText=, ������=K7
(long)(&aux_K7.hold_off), //[5A7Ah.05h], ��������=hold_off, �������=, EngText=, ������=K7
(long)(&dcdc.ena), //[5A7Bh.01h], ��������=ena, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.status), //[5A7Bh.02h], ��������=status, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.status_prev), //[5A7Bh.03h], ��������=status_pre, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.Udc1), //[5A7Bh.04h], ��������=Udc_meas, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.P_ref_kW_IQ8), //[5A7Bh.05h], ��������=P_BMS_ref, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.Idc2_ref), //[5A7Bh.06h], ��������=I_BMS_ref, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.regs.ctrl_word), //[5A7Bh.07h], ��������=ctrl_word, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.E_charge_persent), //[5A7Bh.08h], ��������=E_charge, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.U2_meas_V_I12Q4), //[5A7Bh.09h], ��������=U2_meas, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.I2_meas_A_I12Q4), //[5A7Bh.0Ah], ��������=I2_meas, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.P_meas_kW_IQ8), //[5A7Bh.0Bh], ��������=P_meas, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.regs.status_word), //[5A7Bh.0Ch], ��������=status_word, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.regs.link), //[5A7Bh.0Dh], ��������=link, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.operating), //[5A7Bh.0Eh], ��������=operating, �������=, EngText=, ������=DCDC_MASTER
(long)(&aux_Q6.state), //[5A7Ch.01h], ��������=state, �������=, EngText=, ������=Q6
(long)(&aux_Q6.aux_on), //[5A7Ch.02h], ��������=aux_on, �������=, EngText=, ������=Q6
(long)(&aux_Q6.aux_off), //[5A7Ch.03h], ��������=aux_off, �������=, EngText=, ������=Q6
(long)(&aux_Q6.hold_on), //[5A7Ch.04h], ��������=hold_on, �������=, EngText=, ������=Q6
(long)(&aux_Q6.hold_off), //[5A7Ch.05h], ��������=hold_off, �������=, EngText=, ������=Q6
(long)(&aux_Q6.cmd_in), //[5A7Ch.06h], ��������=cmd, �������=cmd, EngText=cmd, ������=Q6
(long)(&dcdc.abc.time_H_charge), //[5A7Dh.01h], ��������=time_H_charge, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.time_H_discharge), //[5A7Dh.02h], ��������=time_H_discharge, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.charge_P), //[5A7Dh.03h], ��������=charge_P, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.discharge_P), //[5A7Dh.04h], ��������=discharge_P, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.P_ref), //[5A7Dh.05h], ��������=internal_use_only, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.charge_counter), //[5A7Dh.06h], ��������=charge_counter, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.discharge_counter), //[5A7Dh.07h], ��������=discharge_counter, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.abc.ena), //[5A7Dh.08h], ��������=ena, �������=ena, EngText=ena, ������=DCDC_MASTER
(long)(&dcdc.charge_state), //[5A7Dh.09h], ��������=state, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.U2_min), //[5A7Dh.0Ah], ��������=U_min, �������=, EngText=, ������=DCDC_MASTER
(long)(&dcdc.discharge_type), //[5A7Dh.0Bh], ��������=discharge_type, �������=, EngText=, ������=DCDC_MASTER
(long)(&adc.I_diesel), //[5A7Eh.01h], ��������=I_diesel, �������=, EngText=, ������=������
(long)(&adc.P_diesel), //[5A7Eh.02h], ��������=P_diesel, �������=, EngText=, ������=������
(long)(&diesel.fuel_level), //[5A7Eh.03h], ��������=diesel_fuel, �������=, EngText=, ������=������
(long)(&diesel.ready), //[5A7Eh.04h], ��������=diesel_ready, �������=, EngText=, ������=������
(long)(&diesel.operating), //[5A7Eh.05h], ��������=diesel_operating, �������=, EngText=, ������=������
(long)(&diesel.cmd_in_on), //[5A7Eh.06h], ��������=diesel_start, �������=, EngText=, ������=������
(long)(&diesel.cmd_in_off), //[5A7Eh.07h], ��������=diesel_stop, �������=, EngText=, ������=������
(long)(&diesel.P_ref), //[5A7Eh.08h], ��������=diesel_P_ref, �������=, EngText=, ������=������
(long)(&diesel.ON), //[5A7Eh.09h], ��������=diesel_ON, �������=, EngText=, ������=������
(long)(&diesel.ena), //[5A7Eh.0Ah], ��������=ena, �������=ena, EngText=ena, ������=������
(long)(&diesel.state), //[5A7Eh.0Bh], ��������=diesel_state, �������=, EngText=, ������=������
(long)(&sc_profile.profile), //[5A7Fh.01h], ��������=sc_profile, �������=, EngText=, ������=�������
(long)(&sc_profile.status), //[5A7Fh.02h], ��������=status, �������=status, EngText=status, ������=�������
(long)(&sc_profile.profile1_state), //[5A7Fh.03h], ��������=profile1_state, �������=, EngText=, ������=�������
(long)(&sc_profile.profile2_state), //[5A7Fh.04h], ��������=profile2_state, �������=, EngText=, ������=�������
(long)(&sc_profile.profile3_state), //[5A7Fh.05h], ��������=profile3_state, �������=, EngText=, ������=�������
(long)(&sc_profile.profile4_state), //[5A7Fh.06h], ��������=profile4_state, �������=, EngText=, ������=�������
(long)(&sc_profile.in.cmd_local_set_profile), //[5A7Fh.07h], ��������=cmd_local_set_profile, �������=, EngText=, ������=�������
(long)(&sc_profile.in.cmd_remote_set_profile), //[5A7Fh.08h], ��������=cmd_remote_set_profile, �������=, EngText=, ������=�������
(long)(&dcs_ctrl.ctrl_mode_synced_P_gen), //[5A7Fh.09h], ��������=dcs_ctrl.ctrl_mode_synced_P_gen, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Ah], ��������=week, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Bh], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Ch], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Dh], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Eh], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.0Fh], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.10h], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_daily_cicle.week), //[5A7Fh.11h], ��������=��, �������=, EngText=, ������=�������
(long)(&sm_grid_day_solar_mppt_charge_batt.set.dcdc_P_charge), //[5A80h.01h], ��������=dcdc_P_charge, �������=, EngText=, ������=�������
(long)(&sm_grid_day_solar_mppt_charge_batt.set.dcdc_I_charge), //[5A80h.02h], ��������=dcdc_I_charge, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.set.dcdc_P_discharge), //[5A81h.01h], ��������=dcdc_P_discharge, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.set.dcdc_I_discharge), //[5A81h.02h], ��������=dcdc_I_discharge, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.counter_diesel), //[5A81h.03h], ��������=counter_diesel, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.set.diesel_P_ref), //[5A81h.04h], ��������=diesel_P_ref, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.warming_time), //[5A81h.05h], ��������=warming_time, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.counter_batt), //[5A81h.06h], ��������=counter_batt, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.start_hour), //[5A81h.07h], ��������=start_hour, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.start_minute), //[5A81h.08h], ��������=start_minute, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.autostart), //[5A81h.09h], ��������=autostart, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.fade_hour), //[5A81h.0Ah], ��������=fade_hour, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.fade_minute), //[5A81h.0Bh], ��������=fade_minute, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.without_batt), //[5A81h.0Ch], ��������=without_batt, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.without_diesel), //[5A81h.0Dh], ��������=without_diesel, �������=, EngText=, ������=�������
(long)(&sm_grid_evng_batt_diesel.batt_idle_time_min), //[5A81h.0Eh], ��������=batt_idle_time_min, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.set.dcdc_P_charge), //[5A82h.01h], ��������=dcdc_P_charge, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.set.dcdc_I_charge), //[5A82h.02h], ��������=dcdc_I_charge, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.start_hour), //[5A82h.03h], ��������=start_hour, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.start_minute), //[5A82h.04h], ��������=start_minute, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.autostart), //[5A82h.05h], ��������=autostart, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.night_to_day_hour), //[5A82h.06h], ��������=night_to_day_hour, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.night_to_day_minute), //[5A82h.07h], ��������=night_to_day_minute, �������=, EngText=, ������=�������
(long)(&sm_grid_night_batt_charge.jump_time_min), //[5A82h.08h], ��������=jump_time_min, �������=, EngText=, ������=�������
(long)(&vacuum.cmd_in_on), //[5A83h.01h], ��������=cmd_in_on, �������=, EngText=, ������=vacuum
(long)(&vacuum.cmd_in_off), //[5A83h.02h], ��������=cmd_in_off, �������=, EngText=, ������=vacuum
(long)(&vacuum.cmd_in_block), //[5A83h.03h], ��������=cmd_in_block, �������=, EngText=, ������=vacuum
(long)(&vacuum.cmd_out_on), //[5A83h.04h], ��������=cmd_out_on, �������=, EngText=, ������=vacuum
(long)(&vacuum.cmd_out_off), //[5A83h.05h], ��������=cmd_out_off, �������=, EngText=, ������=vacuum
(long)(&vacuum.cmd_out_block), //[5A83h.06h], ��������=cmd_out_block, �������=, EngText=, ������=vacuum
(long)(&vacuum.on), //[5A83h.07h], ��������=on, �������=, EngText=, ������=vacuum
(long)(&vacuum.off), //[5A83h.08h], ��������=off, �������=, EngText=, ������=vacuum
(long)(&vacuum.blocked), //[5A83h.09h], ��������=blocked, �������=, EngText=, ������=vacuum
(long)(&vacuum.state), //[5A83h.0Ah], ��������=state, �������=state, EngText=state, ������=vacuum
(long)(&sm_isla_batt_diesel.Udc2_high), //[5A84h.01h], ��������=Udc2_high, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.Udc2_low), //[5A84h.02h], ��������=Udc2_low, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.fade_hour), //[5A84h.03h], ��������=fade_hour, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.fade_minute), //[5A84h.04h], ��������=fade_minute, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.ena), //[5A84h.05h], ��������=ena, �������=ena, EngText=ena, ������=�������
(long)(&sm_isla_batt_diesel.invs_off), //[5A84h.06h], ��������=invs_off, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.autostart), //[5A84h.07h], ��������=autostart, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.start_hour), //[5A84h.08h], ��������=start_hour, �������=, EngText=, ������=�������
(long)(&sm_isla_batt_diesel.start_minute), //[5A84h.09h], ��������=start_minute, �������=, EngText=, ������=�������
};
Uint16 const CO2_OD_TBL2[] = {
32045, 1, 0,

31021, 2, 1,

32041, 3, 2,

32013, 4, 3,

28814, 5, 3,

64769, 5, 4,
(Uint16)(2000), (((Uint32)2000)>>16),

64257, 6, 5,
(Uint16)(1000),

28801, 7, 1,

32013, 8, 6,

32013, 9, 7,

32013, 10, 8,

32013, 11, 9,

19631, 12, 1,

31021, 13, 10,

31021, 14, 11,

19632, 15, 1,

30765, 16, 12,

30765, 17, 13,

29741, 18, 14,

18607, 19, 3,

64813, 20, 15,
(Uint16)(0x180), (((Uint32)0x180)>>16),

28973, 21, 16,
0,
0,

18607, 22, 3,

64813, 23, 17,
(Uint16)(0x280), (((Uint32)0x280)>>16),

28973, 21, 18,
0,
0,

18607, 24, 3,

64809, 25, 19,
(Uint16)(0x0401), (((Uint32)0x0401)>>16),

28969, 21, 20,
0,
0,

18607, 26, 3,

64809, 27, 21,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),

28969, 21, 22,
0,
0,

18607, 28, 3,

64813, 29, 23,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),

28973, 21, 24,
0,
0,

18607, 30, 3,

64813, 31, 25,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),

28973, 21, 26,
0,
0,

18607, 32, 3,

64801, 33, 27,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),

28961, 21, 28,
0,
0,

18607, 34, 3,

64801, 35, 29,
(Uint16)(0x0501), (((Uint32)0x0501)>>16),

28961, 21, 30,
0,
0,

19633, 36, 3,

61741, 37, 31,
(Uint16)(0x511E0500), (((Uint32)0x511E0500)>>16),

61741, 38, 32,
(Uint16)(0x511E0600), (((Uint32)0x511E0600)>>16),

61741, 39, 33,
(Uint16)(0), (((Uint32)0)>>16),

61741, 40, 34,
(Uint16)(0), (((Uint32)0)>>16),

19633, 41, 3,

61741, 42, 35,
(Uint16)(0x511E0700), (((Uint32)0x511E0700)>>16),

61741, 43, 36,
(Uint16)(0x511E0800), (((Uint32)0x511E0800)>>16),

61741, 44, 37,
(Uint16)(0), (((Uint32)0)>>16),

61741, 45, 38,
(Uint16)(0), (((Uint32)0)>>16),

19629, 46, 3,

61737, 47, 39,
(Uint16)(0), (((Uint32)0)>>16),

61737, 48, 40,
(Uint16)(0), (((Uint32)0)>>16),

61737, 49, 41,
(Uint16)(0), (((Uint32)0)>>16),

61737, 50, 42,
(Uint16)(0), (((Uint32)0)>>16),

19629, 51, 3,

61737, 52, 43,
(Uint16)(0), (((Uint32)0)>>16),

61737, 53, 44,
(Uint16)(0), (((Uint32)0)>>16),

61737, 54, 45,
(Uint16)(0), (((Uint32)0)>>16),

61737, 55, 46,
(Uint16)(0), (((Uint32)0)>>16),

19625, 56, 3,

61741, 57, 47,
(Uint16)(0), (((Uint32)0)>>16),

61741, 58, 48,
(Uint16)(0), (((Uint32)0)>>16),

61741, 59, 49,
(Uint16)(0), (((Uint32)0)>>16),

61741, 60, 50,
(Uint16)(0), (((Uint32)0)>>16),

19625, 61, 3,

61741, 62, 51,
(Uint16)(0), (((Uint32)0)>>16),

61741, 63, 52,
(Uint16)(0), (((Uint32)0)>>16),

61741, 64, 53,
(Uint16)(0), (((Uint32)0)>>16),

61741, 65, 54,
(Uint16)(0), (((Uint32)0)>>16),

19629, 66, 3,

61729, 67, 55,
(Uint16)(0), (((Uint32)0)>>16),

61729, 68, 56,
(Uint16)(0), (((Uint32)0)>>16),

61729, 69, 57,
(Uint16)(0), (((Uint32)0)>>16),

61729, 70, 58,
(Uint16)(0), (((Uint32)0)>>16),

19629, 71, 3,

61729, 72, 59,
(Uint16)(0), (((Uint32)0)>>16),

61729, 73, 60,
(Uint16)(0), (((Uint32)0)>>16),

61729, 74, 61,
(Uint16)(0), (((Uint32)0)>>16),

61729, 75, 62,
(Uint16)(0), (((Uint32)0)>>16),

16562, 76, 2,

32045, 77, 63,
0,

31021, 21, 64,
0,

64301, 78, 65,
(Uint16)(100),

47405, 79, 66,
(Uint16)(0),

64301, 80, 67,
(Uint16)(100),

16560, 81, 2,

32045, 82, 68,
0,

31021, 21, 69,
0,

64301, 83, 70,
(Uint16)(100),

47405, 79, 71,
(Uint16)(0),

64301, 84, 72,
(Uint16)(1000),

16562, 85, 2,

32041, 86, 73,
0,

31017, 21, 74,
0,

64297, 87, 75,
(Uint16)(100),

47401, 79, 76,
(Uint16)(0),

64297, 88, 77,
(Uint16)(1000),

16556, 89, 2,

32041, 90, 78,
0,

31017, 21, 79,
0,

64297, 91, 80,
(Uint16)(100),

47401, 79, 81,
(Uint16)(0),

64297, 92, 82,
(Uint16)(1000),

16554, 93, 2,

32045, 94, 83,
0,

31021, 21, 84,
0,

64301, 95, 85,
(Uint16)(100),

47405, 79, 86,
(Uint16)(0),

64301, 96, 87,
(Uint16)(1000),

16552, 97, 2,

32045, 98, 88,
0,

31021, 21, 89,
0,

64301, 99, 90,
(Uint16)(100),

47405, 79, 91,
(Uint16)(0),

64301, 100, 92,
(Uint16)(1000),

16554, 101, 2,

32033, 102, 93,
0,

31009, 21, 94,
0,

64289, 103, 95,
(Uint16)(100),

47393, 79, 96,
(Uint16)(0),

64289, 104, 97,
(Uint16)(1000),

16556, 105, 2,

32033, 106, 98,
0,

31009, 21, 99,
0,

64289, 107, 100,
(Uint16)(100),

47393, 79, 101,
(Uint16)(0),

64289, 108, 102,
(Uint16)(1000),

19633, 109, 3,

63789, 110, 103,
(Uint16)(0), (((Uint32)0)>>16),

63789, 111, 104,
(Uint16)(0), (((Uint32)0)>>16),

63789, 112, 105,
(Uint16)(0), (((Uint32)0)>>16),

63789, 113, 106,
(Uint16)(0), (((Uint32)0)>>16),

19633, 114, 3,

63789, 115, 107,
(Uint16)(0), (((Uint32)0)>>16),

63789, 116, 108,
(Uint16)(0), (((Uint32)0)>>16),

63789, 117, 109,
(Uint16)(0), (((Uint32)0)>>16),

63789, 118, 110,
(Uint16)(0), (((Uint32)0)>>16),

19629, 119, 3,

63785, 120, 111,
(Uint16)(0), (((Uint32)0)>>16),

63785, 121, 112,
(Uint16)(0), (((Uint32)0)>>16),

63785, 122, 113,
(Uint16)(0), (((Uint32)0)>>16),

63785, 123, 114,
(Uint16)(0), (((Uint32)0)>>16),

19629, 124, 3,

63785, 125, 115,
(Uint16)(0), (((Uint32)0)>>16),

63785, 126, 116,
(Uint16)(0), (((Uint32)0)>>16),

63785, 127, 117,
(Uint16)(0), (((Uint32)0)>>16),

63785, 128, 118,
(Uint16)(0), (((Uint32)0)>>16),

19625, 129, 3,

63789, 130, 119,
(Uint16)(0), (((Uint32)0)>>16),

63789, 131, 120,
(Uint16)(0), (((Uint32)0)>>16),

63789, 132, 121,
(Uint16)(0), (((Uint32)0)>>16),

63789, 133, 122,
(Uint16)(0), (((Uint32)0)>>16),

19625, 134, 3,

63789, 135, 123,
(Uint16)(0), (((Uint32)0)>>16),

63789, 136, 124,
(Uint16)(0), (((Uint32)0)>>16),

63789, 137, 125,
(Uint16)(0), (((Uint32)0)>>16),

63789, 138, 126,
(Uint16)(0), (((Uint32)0)>>16),

19629, 139, 3,

63777, 140, 127,
(Uint16)(0), (((Uint32)0)>>16),

63777, 141, 128,
(Uint16)(0), (((Uint32)0)>>16),

63777, 142, 129,
(Uint16)(0), (((Uint32)0)>>16),

63777, 143, 130,
(Uint16)(0), (((Uint32)0)>>16),

19629, 144, 3,

63777, 145, 131,
(Uint16)(0), (((Uint32)0)>>16),

63777, 146, 132,
(Uint16)(0), (((Uint32)0)>>16),

63777, 147, 133,
(Uint16)(0), (((Uint32)0)>>16),

63777, 148, 134,
(Uint16)(0), (((Uint32)0)>>16),

64173, 149, 135,
(Uint16)(1),
1, 127,

53469, 150, 136,
(Uint16)(3),

28845, 7, 1,

32041, 8, 137,

32041, 9, 138,

32041, 10, 139,

32041, 11, 140,

28845, 151, 1,

31529, 152, 141,

31529, 153, 142,

31529, 154, 143,

31529, 155, 144,

64813, 156, 145,
(Uint16)(0), (((Uint32)0)>>16),

20669, 157, 146,

28845, 158, 1,

32033, 159, 147,

32033, 160, 148,

32033, 161, 149,

32033, 162, 150,

28849, 163, 1,

32013, 164, 151,

32013, 165, 152,

32013, 166, 153,

32013, 167, 154,

28849, 168, 3,

64781, 169, 155,
(Uint16)(0), (((Uint32)0)>>16),

64781, 170, 156,
(Uint16)(0), (((Uint32)0)>>16),

64781, 171, 157,
(Uint16)(0), (((Uint32)0)>>16),

64781, 172, 158,
(Uint16)(0), (((Uint32)0)>>16),

53433, 173, 159,
(Uint16)(1),

53437, 174, 160,
(Uint16)(1),

30989, 175, 161,

31489, 176, 162,

32001, 177, 163,

28859, 178, 2,

47661, 179, 164,
(Uint16)(0),

47661, 180, 165,
(Uint16)(0x2000),

47661, 181, 166,
(Uint16)(0),

31277, 182, 167,
0,

31277, 183, 168,
0,

31277, 184, 169,
0,

31277, 185, 170,
0,

31277, 186, 171,
0,

31277, 187, 172,
0,

31277, 188, 173,
0,

31277, 189, 174,
0,

31277, 190, 175,
0,

31277, 190, 176,
0,

31277, 191, 177,
0,

31277, 192, 178,

28847, 193, 3,

48169, 194, 179,
(Uint16)(0x30000000), (((Uint32)0x30000000)>>16),

48169, 195, 180,
(Uint16)(0x30000000), (((Uint32)0x30000000)>>16),

28857, 196, 2,

36905, 197, 181,
(Uint16)(0),

36913, 198, 182,
(Uint16)(0),

36905, 199, 183,
(Uint16)(0),

36913, 200, 184,
(Uint16)(0),

36905, 201, 185,
(Uint16)(0),

36913, 202, 186,
(Uint16)(0),

36905, 203, 187,
(Uint16)(0),

36913, 204, 188,
(Uint16)(0),

36905, 205, 189,
(Uint16)(0),

36913, 206, 190,
(Uint16)(0),

36905, 207, 191,
(Uint16)(0),

36913, 208, 192,
(Uint16)(0),

36905, 209, 193,
(Uint16)(0),

36913, 210, 194,
(Uint16)(0),

36905, 211, 195,
(Uint16)(0),

36913, 212, 196,
(Uint16)(0),

28339, 213, 2,

31533, 214, 197,
0,

47917, 215, 198,
(Uint16)(64),

37117, 216, 199,
(Uint16)(0),

37074, 217, 200,
(Uint16)(2),

36580, 218, 201,
(Uint16)(0),

37143, 219, 202,
(Uint16)(0),

28339, 220, 2,

31533, 221, 203,
0,

47917, 222, 204,
(Uint16)(4160),

37117, 216, 205,
(Uint16)(0),

37072, 217, 206,
(Uint16)(2),

36578, 218, 207,
(Uint16)(0),

37143, 219, 208,
(Uint16)(4),

28339, 223, 2,

31529, 224, 209,
0,

47913, 225, 210,
(Uint16)(3136),

37113, 216, 211,
(Uint16)(0),

37074, 217, 212,
(Uint16)(2),

36576, 218, 213,
(Uint16)(0),

37143, 219, 214,
(Uint16)(3),

28339, 226, 2,

31529, 227, 215,
0,

47913, 228, 216,
(Uint16)(2112),

37113, 216, 217,
(Uint16)(0),

37068, 217, 218,
(Uint16)(2),

36578, 218, 219,
(Uint16)(0),

37143, 219, 220,
(Uint16)(2),

28331, 229, 2,

31533, 230, 221,
0,

47917, 231, 222,
(Uint16)(1088),

37117, 216, 223,
(Uint16)(0),

37066, 217, 224,
(Uint16)(2),

36580, 218, 225,
(Uint16)(0),

37143, 219, 226,
(Uint16)(1),

28331, 232, 2,

31533, 233, 227,
0,

47917, 234, 228,
(Uint16)(1088),

37117, 216, 229,
(Uint16)(0),

37064, 217, 230,
(Uint16)(2),

36570, 218, 231,
(Uint16)(0),

37143, 219, 232,
(Uint16)(1),

28331, 235, 2,

31521, 236, 233,
0,

47905, 237, 234,
(Uint16)(1088),

37105, 216, 235,
(Uint16)(0),

37066, 217, 236,
(Uint16)(2),

36568, 218, 237,
(Uint16)(0),

37143, 219, 238,
(Uint16)(1),

28331, 238, 2,

31521, 239, 239,
0,

47905, 240, 240,
(Uint16)(2112),

37105, 216, 241,
(Uint16)(0),

37068, 217, 242,
(Uint16)(2),

36570, 218, 243,
(Uint16)(0),

37143, 219, 244,
(Uint16)(2),

28323, 241, 2,

31533, 242, 245,
0,

47917, 243, 246,
(Uint16)(9414),

37117, 216, 247,
(Uint16)(6),

37058, 217, 248,
(Uint16)(2),

36564, 218, 249,
(Uint16)(1),

37127, 219, 250,
(Uint16)(9),

28323, 244, 2,

31533, 245, 251,
0,

47917, 246, 252,
(Uint16)(5184),

37117, 216, 253,
(Uint16)(0),

37056, 217, 254,
(Uint16)(2),

36562, 218, 255,
(Uint16)(0),

37127, 219, 256,
(Uint16)(5),

28323, 247, 2,

31529, 248, 257,
0,

47913, 249, 258,
(Uint16)(12352),

37113, 216, 259,
(Uint16)(0),

37058, 217, 260,
(Uint16)(2),

36560, 218, 261,
(Uint16)(0),

37127, 219, 262,
(Uint16)(12),

28323, 250, 2,

31529, 251, 263,
0,

47913, 252, 264,
(Uint16)(6208),

37113, 216, 265,
(Uint16)(0),

37068, 217, 266,
(Uint16)(2),

36562, 218, 267,
(Uint16)(0),

37127, 219, 268,
(Uint16)(6),

28331, 253, 2,

31533, 254, 269,
0,

47917, 255, 270,
(Uint16)(7232),

37117, 216, 271,
(Uint16)(0),

37066, 217, 272,
(Uint16)(2),

36564, 218, 273,
(Uint16)(0),

37127, 219, 274,
(Uint16)(7),

28331, 256, 2,

31533, 257, 275,
0,

47917, 258, 276,
(Uint16)(2112),

37117, 216, 277,
(Uint16)(0),

37064, 217, 278,
(Uint16)(2),

36570, 218, 279,
(Uint16)(0),

37127, 219, 280,
(Uint16)(2),

28331, 259, 2,

31505, 260, 281,
0,

47889, 261, 282,
(Uint16)(1088),

37089, 216, 283,
(Uint16)(0),

37066, 217, 284,
(Uint16)(2),

36568, 218, 285,
(Uint16)(0),

37127, 219, 286,
(Uint16)(1),

28331, 262, 2,

31505, 263, 287,
0,

47889, 264, 288,
(Uint16)(96),

37089, 216, 289,
(Uint16)(0),

37068, 217, 290,
(Uint16)(3),

36570, 218, 291,
(Uint16)(0),

37127, 219, 292,
(Uint16)(0),

28339, 265, 2,

31501, 266, 293,
0,

47885, 267, 294,
(Uint16)(3136),

37117, 216, 295,
(Uint16)(0),

37074, 217, 296,
(Uint16)(2),

36548, 218, 297,
(Uint16)(0),

37143, 219, 298,
(Uint16)(3),

28339, 268, 2,

31501, 269, 299,
0,

47885, 270, 300,
(Uint16)(9408),

37117, 216, 301,
(Uint16)(0),

37072, 217, 302,
(Uint16)(2),

36546, 218, 303,
(Uint16)(1),

37143, 219, 304,
(Uint16)(9),

28339, 271, 2,

31497, 272, 305,
0,

47881, 273, 306,
(Uint16)(9408),

37113, 216, 307,
(Uint16)(0),

37074, 217, 308,
(Uint16)(2),

36544, 218, 309,
(Uint16)(1),

37143, 219, 310,
(Uint16)(9),

28339, 274, 2,

31497, 275, 311,
0,

47881, 276, 312,
(Uint16)(12352),

37113, 216, 313,
(Uint16)(0),

37036, 217, 314,
(Uint16)(2),

36546, 218, 315,
(Uint16)(0),

37143, 219, 316,
(Uint16)(12),

28299, 277, 2,

31501, 278, 317,
0,

47885, 279, 318,
(Uint16)(13376),

37117, 216, 319,
(Uint16)(0),

37034, 217, 320,
(Uint16)(2),

36548, 218, 321,
(Uint16)(0),

37143, 219, 322,
(Uint16)(13),

28299, 280, 2,

31501, 281, 323,
0,

47885, 282, 324,
(Uint16)(10304),

37117, 216, 325,
(Uint16)(0),

37032, 217, 326,
(Uint16)(2),

36570, 218, 327,
(Uint16)(0),

37143, 219, 328,
(Uint16)(10),

28299, 283, 2,

31489, 284, 329,
0,

47873, 285, 330,
(Uint16)(14400),

37105, 216, 331,
(Uint16)(0),

37034, 217, 332,
(Uint16)(2),

36568, 218, 333,
(Uint16)(0),

37143, 219, 334,
(Uint16)(14),

28299, 286, 2,

31489, 287, 335,
0,

47873, 288, 336,
(Uint16)(15430),

37105, 216, 337,
(Uint16)(6),

37036, 217, 338,
(Uint16)(2),

36570, 218, 339,
(Uint16)(0),

37143, 219, 340,
(Uint16)(15),

28291, 289, 2,

31501, 290, 341,
0,

47885, 291, 342,
(Uint16)(16448),

37117, 216, 343,
(Uint16)(0),

37026, 217, 344,
(Uint16)(2),

36564, 218, 345,
(Uint16)(0),

36583, 219, 346,
(Uint16)(16),

28291, 292, 2,

31501, 293, 347,
0,

47885, 294, 348,
(Uint16)(13376),

37117, 216, 349,
(Uint16)(0),

37024, 217, 350,
(Uint16)(2),

36562, 218, 351,
(Uint16)(0),

36583, 219, 352,
(Uint16)(13),

28291, 295, 2,

31497, 296, 353,
0,

47881, 297, 354,
(Uint16)(14400),

37113, 216, 355,
(Uint16)(0),

37026, 217, 356,
(Uint16)(2),

36560, 218, 357,
(Uint16)(0),

36583, 219, 358,
(Uint16)(14),

28291, 298, 2,

31497, 299, 359,
0,

47881, 300, 360,
(Uint16)(64),

37113, 216, 361,
(Uint16)(0),

37036, 217, 362,
(Uint16)(2),

36562, 218, 363,
(Uint16)(0),

36583, 219, 364,
(Uint16)(0),

28299, 301, 2,

31501, 302, 365,
0,

47885, 303, 366,
(Uint16)(9408),

37117, 216, 367,
(Uint16)(0),

37034, 217, 368,
(Uint16)(2),

36564, 218, 369,
(Uint16)(1),

36583, 219, 370,
(Uint16)(9),

28299, 304, 2,

31501, 305, 371,
0,

47885, 306, 372,
(Uint16)(0),

37117, 216, 373,
(Uint16)(0),

37032, 217, 374,
(Uint16)(0),

36570, 218, 375,
(Uint16)(0),

36583, 219, 376,
(Uint16)(0),

28354, 394, 4,

36537, 668, 377,
(Uint16)(256),
0,
0,

36542, 669, 378,
(Uint16)(256),
0,
0,

36543, 670, 379,
(Uint16)(256),
0,
0,

36540, 671, 380,
(Uint16)(256),
0,
0,

36541, 672, 381,
(Uint16)(256),
0,
0,

36546, 673, 382,
(Uint16)(256),
0,
0,

36547, 674, 383,
(Uint16)(256),
0,
0,

36544, 675, 384,
(Uint16)(256),
0,
0,

36545, 676, 385,
(Uint16)(256),
0,
0,

36550, 677, 386,
(Uint16)(256),
0,
0,

36551, 678, 387,
(Uint16)(256),
0,
0,

36548, 679, 388,
(Uint16)(256),
0,
0,

36549, 680, 389,
(Uint16)(256),
0,
0,

36554, 681, 390,
(Uint16)(256),
0,
0,

36555, 682, 391,
(Uint16)(256),
0,
0,

36552, 683, 392,
(Uint16)(256),
0,
0,

36552, 684, 393,
(Uint16)(256),
0,
0,

45993, 667, 394,
(Uint16)(0),
0, 1,

45225, 687, 395,
(Uint16)(0),
0, 1,

45225, 688, 396,
(Uint16)(0),
0, 1,

45225, 689, 397,
(Uint16)(0),
0, 1,

28333, 615, 3,

48417, 581, 398,
(Uint16)(0), (((Uint32)0)>>16),

48417, 582, 399,
(Uint16)(0), (((Uint32)0)>>16),

48417, 617, 400,
(Uint16)(0), (((Uint32)0)>>16),

48417, 618, 401,
(Uint16)(0), (((Uint32)0)>>16),

48401, 311, 402,
(Uint16)(438392299), (((Uint32)438392299)>>16),

28239, 312, 1,

20169, 313, 403,

20169, 314, 404,

28238, 315, 2,

45261, 316, 405,
(Uint16)(15),

27822, 577, 3,

45357, 577, 406,
(Uint16)(0x75855007), (((Uint32)0x75855007)>>16),

45869, 596, 407,
(Uint16)(0),

28346, 597, 7,

45741, 598, 408,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 599, 409,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 600, 410,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 601, 411,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 602, 412,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 603, 413,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 604, 414,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 605, 415,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 606, 416,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 607, 417,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 608, 418,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 609, 419,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 610, 420,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45741, 611, 421,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

45357, 612, 422,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

31533, 382, 423,

3762, 312, 2,

47917, 318, 424,
(Uint16)(58002),

47917, 319, 425,
(Uint16)(14349),

47917, 320, 426,
(Uint16)(64364),

47917, 321, 427,
(Uint16)(3745),

47917, 322, 428,
(Uint16)(1832),

28848, 323, 7,

58853, 324, 429,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(_IQ(120.0)), (((Uint32)_IQ(120.0))>>16),

26437, 325, 430,
0,
0,
0,
0,
0,
0,

26437, 326, 431,
0,
0,
0,
0,
0,
0,

20152, 654, 7,

9637, 655, 432,
(Uint16)(0x01000000), (((Uint32)0x01000000)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9637, 656, 433,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9637, 657, 434,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9637, 658, 435,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15661, 659, 436,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

26021, 660, 437,
0,
0,
0,
0,
0,
0,

25925, 661, 438,
0,
0,
0,
0,
0,
0,

9637, 662, 439,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

26373, 663, 440,
0,
0,
0,
0,
0,
0,

15405, 927, 441,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

9637, 928, 442,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

26021, 929, 443,
0,
0,
0,
0,
0,
0,

26021, 930, 444,
0,
0,
0,
0,
0,
0,

20154, 347, 7,

25921, 348, 445,
0,
0,
0,
0,
0,
0,

25921, 349, 446,
0,
0,
0,
0,
0,
0,

9377, 350, 447,
(Uint16)(335544), (((Uint32)335544)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9505, 351, 448,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),

9505, 352, 449,
(Uint16)(-16777216), (((Uint32)-16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),

9377, 353, 450,
(Uint16)(2684354), (((Uint32)2684354)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9377, 354, 451,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9377, 335, 452,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

25921, 336, 453,
0,
0,
0,
0,
0,
0,

25889, 355, 454,
0,
0,
0,
0,
0,
0,

25889, 338, 455,
0,
0,
0,
0,
0,
0,

25889, 339, 456,
0,
0,
0,
0,
0,
0,

25889, 340, 457,
0,
0,
0,
0,
0,
0,

20148, 327, 7,

25921, 328, 458,
0,
0,
0,
0,
0,
0,

25921, 329, 459,
0,
0,
0,
0,
0,
0,

9377, 330, 460,
(Uint16)(335544), (((Uint32)335544)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9505, 331, 461,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),

9505, 332, 462,
(Uint16)(-16777216), (((Uint32)-16777216)>>16),
(Uint16)(_IQ(-1.0)), (((Uint32)_IQ(-1.0))>>16), (Uint16)(_IQ(1.0)), (((Uint32)_IQ(1.0))>>16),

9377, 333, 463,
(Uint16)(2684354), (((Uint32)2684354)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9377, 334, 464,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9377, 335, 465,
(Uint16)(8388608), (((Uint32)8388608)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

25921, 336, 466,
0,
0,
0,
0,
0,
0,

25889, 337, 467,
0,
0,
0,
0,
0,
0,

25889, 338, 468,
0,
0,
0,
0,
0,
0,

25889, 339, 469,
0,
0,
0,
0,
0,
0,

25889, 340, 470,
0,
0,
0,
0,
0,
0,

20151, 384, 7,

25285, 328, 471,
0,
0,
0,
0,
0,
0,

25285, 329, 472,
0,
0,
0,
0,
0,
0,

8901, 330, 473,
(Uint16)(167772), (((Uint32)167772)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8901, 333, 474,
(Uint16)(167772), (((Uint32)167772)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8901, 331, 475,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8901, 332, 476,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

25285, 337, 477,
0,
0,
0,
0,
0,
0,

25285, 338, 478,
0,
0,
0,
0,
0,
0,

25285, 339, 479,
0,
0,
0,
0,
0,
0,

8901, 334, 480,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20158, 362, 7,

25893, 363, 481,
0,
0,
0,
0,
0,
0,

25893, 364, 482,
0,
0,
0,
0,
0,
0,

8901, 365, 483,
(Uint16)(14529069), (((Uint32)14529069)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0x01000000), (((Uint32)0x01000000)>>16),

31533, 366, 484,
0,
0,
0,
0,
0,
0,

31533, 367, 485,
0,
0,
0,
0,
0,
0,

31533, 368, 486,
0,
0,
0,
0,
0,
0,

31533, 369, 487,
0,
0,
0,
0,
0,
0,

11429, 370, 488,
(Uint16)(3355443), (((Uint32)3355443)>>16),
(Uint16)(_IQ(2.0)), (((Uint32)_IQ(2.0))>>16), (Uint16)(_IQ(10.0)), (((Uint32)_IQ(10.0))>>16),

11429, 371, 489,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(_IQ(10)), (((Uint32)_IQ(10))>>16),

10949, 372, 490,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

10949, 373, 491,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15149, 374, 492,
(Uint16)(1),
0,
0,
0,
0,
0,

15277, 375, 493,
(Uint16)(1),
0, 0,
0,
0,
0,

9367, 376, 494,
(Uint16)(20480), (((Uint32)20480)>>16),
(Uint16)(2048), (((Uint32)2048)>>16), (Uint16)(10240), (((Uint32)10240)>>16),

31277, 377, 495,
0,
0,
0,
0,
0,
0,

25893, 378, 496,
0,
0,
0,
0,
0,
0,

31533, 379, 497,
0,
0,
0,
0,
0,
0,

31533, 379, 498,
0,
0,
0,
0,
0,
0,

31533, 379, 499,
0,
0,
0,
0,
0,
0,

20171, 497, 7,

31273, 381, 500,
0,
0,
0,
0,
0,
0,

4393, 382, 501,
0,
0,
0,
0,
0,
0,

14889, 690, 502,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 691, 503,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 790, 504,
(Uint16)(0),
0,
0,
0,
0,
0,

31273, 791, 505,
0,
0,
0,
0,
0,
0,

31785, 744, 506,
0,
0,
0,
0,
0,
0,

31785, 744, 507,
0,
0,
0,
0,
0,
0,

15401, 792, 508,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

15401, 793, 509,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

15401, 794, 510,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

15401, 795, 511,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

15401, 796, 512,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

9457, 797, 513,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9617, 798, 514,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9617, 799, 515,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9521, 388, 516,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9521, 389, 517,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14889, 744, 518,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 744, 519,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 744, 520,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 744, 521,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 744, 522,
(Uint16)(0),
0,
0,
0,
0,
0,

4137, 744, 523,
0,
0,
0,
0,
0,
0,

4137, 744, 524,
0,
0,
0,
0,
0,
0,

4137, 744, 525,
0,
0,
0,
0,
0,
0,

31273, 744, 526,
0,
0,
0,
0,
0,
0,

9617, 785, 527,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9617, 800, 528,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9617, 801, 529,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20151, 455, 7,

9529, 469, 530,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9625, 470, 531,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9625, 471, 532,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 457, 533,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 458, 534,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9529, 468, 535,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15121, 464, 536,
(Uint16)(0),
0,
0,
0,
0,
0,

15121, 456, 537,
(Uint16)(0),
0,
0,
0,
0,
0,

15121, 456, 538,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 460, 539,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 460, 540,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 461, 541,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 461, 542,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 462, 543,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 462, 544,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 463, 545,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 463, 546,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 464, 547,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 464, 548,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 465, 549,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 465, 550,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 466, 551,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 466, 552,
(Uint16)(0),
0,
0,
0,
0,
0,

53265, 467, 553,
(Uint16)(0),
0,
0,
0,
0,
0,

53289, 467, 554,
(Uint16)(0),
0,
0,
0,
0,
0,

16045, 636, 555,
(Uint16)(0),
0, 0,
0,
0,
0,

20136, 857, 2,

14865, 858, 556,
(Uint16)(0),

31505, 865, 557,
0,

31505, 866, 558,
0,

31505, 867, 559,
0,

31505, 868, 560,
0,

53265, 863, 561,
(Uint16)(0),

53289, 863, 562,
(Uint16)(0),

53265, 864, 563,
(Uint16)(0),

53289, 864, 564,
(Uint16)(0),

20149, 514, 1,

25861, 515, 565,

25861, 516, 566,

25861, 517, 567,

25861, 518, 568,

25861, 519, 569,

25253, 520, 570,

25317, 521, 571,

25253, 522, 572,

20144, 394, 7,

9633, 395, 573,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9633, 397, 574,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9633, 399, 575,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9425, 396, 576,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9425, 398, 577,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9425, 400, 578,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15113, 2, 579,
(Uint16)(0),
0,
0,
0,
0,
0,

20147, 652, 7,

9337, 401, 580,
(Uint16)(5), (((Uint32)5)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9305, 402, 581,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9305, 404, 582,
(Uint16)(36), (((Uint32)36)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(1000), (((Uint32)1000)>>16),

10113, 405, 583,
(Uint16)(1048576), (((Uint32)1048576)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

10145, 406, 584,
(Uint16)(16777), (((Uint32)16777)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

25785, 407, 585,
0,
0,
0,
0,
0,
0,

20104, 409, 4,

4365, 410, 586,
0,
0,
0,

15117, 413, 587,
(Uint16)(1),
0,
0,

14477, 414, 588,
(Uint16)(0),
0, 1,

20154, 700, 7,

15117, 701, 589,
(Uint16)(0),
0,
0,
0,
0,
0,

15117, 702, 590,
(Uint16)(0),
0,
0,
0,
0,
0,

8893, 703, 591,
(Uint16)(3276800), (((Uint32)3276800)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 704, 592,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 706, 593,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9605, 722, 594,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9541, 720, 595,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9509, 723, 596,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 707, 597,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 708, 598,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 709, 599,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 710, 600,
(Uint16)(16777216), (((Uint32)16777216)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 711, 601,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 712, 602,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 713, 603,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 714, 604,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 715, 605,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 716, 606,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 717, 607,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 718, 608,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8869, 719, 609,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15373, 724, 610,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

15373, 725, 611,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

20174, 527, 7,

9497, 530, 612,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 533, 613,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 536, 614,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 528, 615,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 531, 616,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 534, 617,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 529, 618,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 532, 619,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 535, 620,
(Uint16)(0),
0,
0,
0,
0,
0,

31489, 573, 621,
0,
0,
0,
0,
0,
0,

9497, 539, 622,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 542, 623,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9497, 545, 624,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 537, 625,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 540, 626,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 543, 627,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 538, 628,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 541, 629,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 544, 630,
(Uint16)(0),
0,
0,
0,
0,
0,

31489, 573, 631,
0,
0,
0,
0,
0,
0,

9529, 548, 632,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9529, 551, 633,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9529, 554, 634,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 546, 635,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 549, 636,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 552, 637,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 547, 638,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 550, 639,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 553, 640,
(Uint16)(0),
0,
0,
0,
0,
0,

31489, 573, 641,
0,
0,
0,
0,
0,
0,

9529, 557, 642,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9529, 560, 643,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

9529, 563, 644,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 555, 645,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 558, 646,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 561, 647,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 556, 648,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 559, 649,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 562, 650,
(Uint16)(0),
0,
0,
0,
0,
0,

31489, 573, 651,
0,
0,
0,
0,
0,
0,

8881, 564, 652,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 565, 653,
(Uint16)(0),
0,
0,
0,
0,
0,

9529, 566, 654,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

8881, 567, 655,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

14849, 568, 656,
(Uint16)(0),
0,
0,
0,
0,
0,

9625, 569, 657,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

16001, 570, 658,
(Uint16)(0),
0, 0,
0,
0,
0,

16001, 571, 659,
(Uint16)(0),
0, 0,
0,
0,
0,

15105, 417, 660,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 418, 661,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 419, 662,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 420, 663,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 421, 664,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 422, 665,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 423, 666,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 424, 667,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 425, 668,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 426, 669,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 427, 670,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 428, 671,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 429, 672,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 430, 673,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 431, 674,
(Uint16)(0),
0,
0,
0,
0,
0,

15105, 432, 675,
(Uint16)(0),
0,
0,
0,
0,
0,

14849, 413, 676,
(Uint16)(0),
0,
0,
0,
0,
0,

20138, 476, 1,

25845, 922, 677,

26037, 923, 678,

25909, 477, 679,

25909, 478, 680,

25909, 479, 681,

25909, 480, 682,

25909, 481, 683,

25909, 482, 684,

25301, 483, 685,

25301, 484, 686,

25301, 485, 687,

25301, 486, 688,

25301, 487, 689,

25301, 488, 690,

25301, 489, 691,

25301, 490, 692,

25301, 491, 693,

25301, 492, 694,

25301, 493, 695,

25301, 494, 696,

25301, 495, 697,

25301, 496, 698,

28141, 613, 699,

28141, 614, 700,

26037, 924, 701,

26037, 925, 702,

25269, 926, 703,

27893, 919, 704,

1854, 920, 705,

20038, 844, 2,

15309, 845, 706,
(Uint16)(100),

15309, 846, 707,
(Uint16)(100),

15309, 847, 708,
(Uint16)(100),

15309, 848, 709,
(Uint16)(100),

15309, 849, 710,
(Uint16)(100),

15309, 850, 711,
(Uint16)(100),

15309, 851, 712,
(Uint16)(100),

15309, 852, 713,
(Uint16)(100),

15309, 853, 714,
(Uint16)(100),

15309, 854, 715,
(Uint16)(100),

15309, 855, 716,
(Uint16)(100),

20023, 443, 7,

14477, 444, 717,
(Uint16)(0),
0,
0,
0,
0,
0,

14989, 445, 718,
(Uint16)(192), (((Uint32)192)>>16),
0,
0,
0,
0,

14989, 446, 719,
(Uint16)(1359151123), (((Uint32)1359151123)>>16),
0,
0,
0,
0,

14989, 447, 720,
(Uint16)(1359085569), (((Uint32)1359085569)>>16),
0,
0,
0,
0,

14989, 448, 721,
(Uint16)(1359151122), (((Uint32)1359151122)>>16),
0,
0,
0,
0,

14989, 449, 722,
(Uint16)(1359020033), (((Uint32)1359020033)>>16),
0,
0,
0,
0,

53645, 450, 723,
(Uint16)(0),
0,
0,
0,
0,
0,

53685, 451, 724,
(Uint16)(1),
0,
0,
0,
0,
0,

11837, 452, 725,
(Uint16)(0),
0,
0,
0,
0,
0,

10949, 453, 726,
(Uint16)(6710886), (((Uint32)6710886)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15757, 454, 727,
(Uint16)(50461787), (((Uint32)50461787)>>16),

20025, 497, 7,

25669, 498, 728,
0,
0,
0,
0,
0,
0,

32205, 498, 729,
0,
0,
0,
0,
0,
0,

25669, 499, 730,
0,
0,
0,
0,
0,
0,

32205, 499, 731,
0,
0,
0,
0,
0,
0,

30925, 500, 732,
0,
0,
0,
0,
0,
0,

31693, 500, 733,
0,
0,
0,
0,
0,
0,

30925, 501, 734,
0,
0,
0,
0,
0,
0,

31693, 501, 735,
0,
0,
0,
0,
0,
0,

9285, 502, 736,
(Uint16)(16777), (((Uint32)16777)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15821, 502, 737,
(Uint16)(16777), (((Uint32)16777)>>16),
0,
0,
0,
0,

9285, 503, 738,
(Uint16)(-190048), (((Uint32)-190048)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15821, 503, 739,
(Uint16)(-190048), (((Uint32)-190048)>>16),
0,
0,
0,
0,

9285, 504, 740,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15821, 504, 741,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

9285, 505, 742,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15821, 505, 743,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

50253, 506, 744,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

50253, 507, 745,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

50253, 508, 746,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

50253, 509, 747,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20043, 635, 7,

49214, 636, 748,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

49214, 637, 749,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

79, 638, 750,
0,
0,
0,
0,
0,
0,

79, 639, 751,
0,
0,
0,
0,
0,
0,

31693, 646, 752,
0,
0,
0,
0,
0,
0,

62, 634, 753,
0,
0,
0,
0,
0,
0,

20022, 640, 7,

49212, 636, 754,
(Uint16)(1119092736), (((Uint32)1119092736)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

49212, 641, 755,
(Uint16)(1108082688), (((Uint32)1108082688)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

49212, 642, 756,
(Uint16)(1114636288), (((Uint32)1114636288)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

49212, 643, 757,
(Uint16)(1113325568), (((Uint32)1113325568)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

49212, 644, 758,
(Uint16)(1109393408), (((Uint32)1109393408)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15041, 645, 759,
(Uint16)(30000), (((Uint32)30000)>>16),
0,
0,
0,
0,

31681, 646, 760,
0,
0,
0,
0,
0,
0,

31681, 646, 761,
0,
0,
0,
0,
0,
0,

49212, 634, 762,
(Uint16)(1103626240), (((Uint32)1103626240)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

20023, 634, 1,

32333, 647, 763,

32333, 648, 764,

32333, 649, 765,

32333, 650, 766,

32333, 730, 767,

32333, 731, 768,

32333, 732, 769,

32333, 730, 770,

32333, 731, 771,

32333, 732, 772,

19641, 510, 3,

15149, 589, 773,
(Uint16)(1),
0,

15149, 511, 774,
(Uint16)(1),
0,

14637, 437, 775,
(Uint16)(9600), (((Uint32)9600)>>16),

14637, 581, 776,
(Uint16)(20000), (((Uint32)20000)>>16),

15149, 583, 777,
(Uint16)(1),
0,

31021, 582, 778,
0,
0,

31533, 568, 779,
0,
0,

31533, 569, 780,
0,
0,

31533, 578, 781,
0,
0,

31533, 467, 782,
0,
0,

31533, 579, 783,
0,
0,

31533, 580, 784,
0,
0,

19522, 734, 1,

31437, 738, 785,

31437, 739, 786,

31437, 740, 787,

31437, 741, 788,

31437, 742, 789,

19520, 735, 1,

31437, 738, 790,

31437, 739, 791,

31437, 740, 792,

31437, 741, 793,

31437, 742, 794,

19522, 736, 1,

31433, 738, 795,

31433, 739, 796,

31433, 740, 797,

31433, 741, 798,

31433, 742, 799,

19515, 767, 7,

15049, 768, 800,
(Uint16)(0),
0,
0,
0,
0,
0,

15049, 769, 801,
(Uint16)(0),
0,
0,
0,
0,
0,

31433, 770, 802,
0,
0,
0,
0,
0,
0,

12625, 569, 803,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

12833, 774, 804,
(Uint16)(0),
0, 0,
0,
0,
0,

15757, 772, 805,
(Uint16)(0),
0, 0,
0,
0,
0,

11721, 775, 806,
(Uint16)(0),
0,
0,
0,
0,
0,

17609, 776, 807,
0,
0,
0,
0,
0,
0,

32173, 781, 808,
0,
0,
0,
0,
0,
0,

32141, 777, 809,
0,
0,
0,
0,
0,
0,

29217, 778, 810,
0,
0,
0,
0,
0,
0,

28105, 779, 811,
0,
0,
0,
0,
0,
0,

31433, 780, 812,
0,
0,
0,
0,
0,
0,

15049, 788, 813,
(Uint16)(0),
0,
0,
0,
0,
0,

19531, 733, 1,

31437, 738, 814,

31437, 739, 815,

31437, 740, 816,

31437, 741, 817,

31437, 742, 818,

31437, 598, 819,

19526, 813, 4,

14797, 814, 820,
(Uint16)(0), (((Uint32)0)>>16),
0,

14797, 815, 821,
(Uint16)(0), (((Uint32)0)>>16),
0,

12837, 816, 822,
(Uint16)(0),
0, 0,

12837, 817, 823,
(Uint16)(0),
0, 0,

12837, 744, 824,
(Uint16)(0),
0, 0,

14797, 818, 825,
(Uint16)(0), (((Uint32)0)>>16),
0,

14797, 819, 826,
(Uint16)(0), (((Uint32)0)>>16),
0,

14797, 659, 827,
(Uint16)(0), (((Uint32)0)>>16),
0,

14797, 738, 828,
(Uint16)(0), (((Uint32)0)>>16),
0,

32169, 942, 829,
0,
0,
0,

1229, 957, 830,
(Uint16)(0),
0,
0,

19524, 821, 7,

28857, 720, 831,
0,
0,
0,
0,
0,
0,

30457, 721, 832,
0,
0,
0,
0,
0,
0,

15057, 822, 833,
(Uint16)(0),
0,
0,
0,
0,
0,

15057, 823, 834,
(Uint16)(0),
0,
0,
0,
0,
0,

15057, 826, 835,
(Uint16)(0),
0,
0,
0,
0,
0,

15057, 824, 836,
(Uint16)(0),
0,
0,
0,
0,
0,

15057, 825, 837,
(Uint16)(0),
0,
0,
0,
0,
0,

12601, 827, 838,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15313, 829, 839,
(Uint16)(0),
0,
0,
0,
0,
0,

15313, 659, 840,
(Uint16)(0),
0,
0,
0,
0,
0,

31441, 836, 841,
0,
0,
0,
0,
0,
0,

19520, 830, 2,

27857, 831, 842,
0,

31441, 599, 843,
0,

31441, 832, 844,
0,

31441, 833, 845,
0,

31441, 834, 846,
0,

31441, 835, 847,
0,

15313, 839, 848,
(Uint16)(0),

15313, 840, 849,
(Uint16)(0),

15313, 888, 850,
(Uint16)(0),

11729, 771, 851,
(Uint16)(0),

11585, 912, 852,
(Uint16)(0),

11584, 913, 853,
(Uint16)(0),

11583, 914, 854,
(Uint16)(0),

11582, 915, 855,
(Uint16)(0),

11581, 916, 856,
(Uint16)(0),

11580, 917, 857,
(Uint16)(0),

11579, 918, 858,
(Uint16)(0),

19631, 880, 7,

14037, 885, 859,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15729, 873, 860,
(Uint16)(0),
0, 0,
0,
0,
0,

19643, 879, 7,

14037, 884, 861,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15729, 871, 862,
(Uint16)(0),
0, 0,
0,
0,
0,

14637, 889, 863,
(Uint16)(0), (((Uint32)0)>>16),
0,
0,
0,
0,

12741, 827, 864,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

1069, 872, 865,
(Uint16)(0),
0,
0,
0,
0,
0,

31021, 890, 866,
0,
0,
0,
0,
0,
0,

14893, 892, 867,
(Uint16)(0),
0,
0,
0,
0,
0,

14893, 893, 868,
(Uint16)(0),
0,
0,
0,
0,
0,

14893, 894, 869,
(Uint16)(0),
0,
0,
0,
0,
0,

14893, 895, 870,
(Uint16)(0),
0,
0,
0,
0,
0,

14893, 896, 871,
(Uint16)(0),
0,
0,
0,
0,
0,

1069, 954, 872,
(Uint16)(0),
0,
0,
0,
0,
0,

1069, 955, 873,
(Uint16)(0),
0,
0,
0,
0,
0,

14893, 961, 874,
(Uint16)(0),
0,
0,
0,
0,
0,

19633, 878, 7,

14033, 885, 875,
(Uint16)(0), (((Uint32)0)>>16),
(Uint16)(0), (((Uint32)0)>>16), (Uint16)(0), (((Uint32)0)>>16),

15725, 873, 876,
(Uint16)(0),
0, 0,
0,
0,
0,

14889, 892, 877,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 893, 878,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 894, 879,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 897, 880,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 898, 881,
(Uint16)(0),
0,
0,
0,
0,
0,

14889, 953, 882,
(Uint16)(0),
0,
0,
0,
0,
0,

19639, 900, 2,

15145, 901, 883,
(Uint16)(0),

15145, 902, 884,
(Uint16)(0),

15145, 903, 885,
(Uint16)(0),

15145, 904, 886,
(Uint16)(0),

15145, 905, 887,
(Uint16)(0),

15145, 906, 888,
(Uint16)(0),

15145, 907, 889,
(Uint16)(0),

15145, 908, 890,
(Uint16)(0),

15145, 909, 891,
(Uint16)(0),

31529, 646, 892,
0,

19638, 877, 4,

15689, 910, 893,
(Uint16)(0),
0, 0,

15689, 911, 894,
(Uint16)(0),
0, 0,

14893, 895, 895,
(Uint16)(0),
0,
0,

14893, 896, 896,
(Uint16)(0),
0,
0,

14893, 659, 897,
(Uint16)(0),
0,
0,

31277, 869, 898,
0,
0,
0,

14893, 894, 899,
(Uint16)(0),
0,
0,

14893, 892, 900,
(Uint16)(0),
0,
0,

14893, 893, 901,
(Uint16)(0),
0,
0,
};
int16 const CO2_OD_TBL1[] = { 4096, 0,
4097, 3,
4098, 6,
4116, 9,
4118, 12,
4119, 20,
4120, 24,
4608, 39,
4736, 48,
5120, 60,
5121, 73,
5122, 86,
5123, 99,
5124, 112,
5125, 125,
5126, 138,
5127, 151,
5632, 164,
5633, 187,
5634, 210,
5635, 233,
5636, 256,
5637, 279,
5638, 302,
5639, 325,
6144, 348,
6145, 371,
6146, 394,
6147, 417,
6148, 440,
6149, 463,
6150, 486,
6151, 509,
6656, 532,
6657, 555,
6658, 578,
6659, 601,
6660, 624,
6661, 647,
6662, 670,
6663, 693,
8192, 716,
8193, 722,
8194, 726,
8195, 741,
8196, 756,
8197, 761,
8199, 764,
8208, 779,
8209, 794,
8210, 817,
8212, 821,
8213, 825,
8214, 828,
8215, 831,
8320, 834,
8321, 893,
8322, 896,
8323, 909,
8448, 976,
8449, 1003,
8450, 1030,
8451, 1057,
8452, 1084,
8453, 1111,
8454, 1138,
8455, 1165,
8456, 1192,
8457, 1219,
8458, 1246,
8459, 1273,
8460, 1300,
8461, 1327,
8462, 1354,
8463, 1381,
8464, 1408,
8465, 1435,
8466, 1462,
8467, 1489,
8468, 1516,
8469, 1543,
8470, 1570,
8471, 1597,
8472, 1624,
8473, 1651,
8474, 1678,
8475, 1705,
8476, 1732,
8477, 1759,
9474, 1786,
9478, 1915,
9487, 1938,
9522, 1943,
9524, 1952,
9728, 1959,
9984, 1967,
9985, 1971,
12288, 2109,
12544, 2112,
20480, 2135,
20737, 2165,
20738, 2285,
20739, 2405,
20740, 2525,
20741, 2618,
20747, 2792,
20750, 3065,
20751, 3302,
20753, 3341,
20754, 3368,
20755, 3434,
20756, 3491,
20757, 3512,
20758, 3722,
20792, 4310,
20793, 4400,
20816, 4447,
20817, 4540,
20852, 4545,
20853, 4728,
20854, 4785,
20855, 4869,
23072, 4902,
23160, 4965,
23161, 4983,
23162, 5001,
23163, 5019,
23164, 5148,
23165, 5169,
23166, 5238,
23167, 5340,
23168, 5411,
23169, 5432,
23170, 5561,
23171, 5636,
23172, 5679,
};
Uint16 const co2_SPIrange1rw = CO2_SPI_START_ADDR+0;
Uint16 const co2_SPIrange1rwCRC = CO2_SPI_START_ADDR+8;
Uint16 const co2_SPIrange1rwp = CO2_SPI_START_ADDR+10;
Uint16 const co2_SPIrange1rwpCRC = CO2_SPI_START_ADDR+336;
Uint16 const co2_SPIrange1rwps = CO2_SPI_START_ADDR+338;
Uint16 const co2_SPIrange1rwpsCRC = CO2_SPI_START_ADDR+338;
Uint16 const co2_SPIrange2rw = CO2_SPI_START_ADDR+340;
Uint16 const co2_SPIrange2rwCRC = CO2_SPI_START_ADDR+663;
Uint16 const co2_SPIrange2rwp = CO2_SPI_START_ADDR+665;
Uint16 const co2_SPIrange2rwpCRC = CO2_SPI_START_ADDR+690;
Uint16 const co2_SPIrange2rwps = CO2_SPI_START_ADDR+692;
Uint16 const co2_SPIrange2rwpsCRC = CO2_SPI_START_ADDR+692;
Uint16 const co2_SPIrange3rw = CO1_SPI_START_ADDR+694;
Uint16 const co2_SPIrange3rwCRC = CO1_SPI_START_ADDR+704;
Uint16 const co2_SPIrange3rwp = CO1_SPI_START_ADDR+706;
Uint16 const co2_SPIrange3rwpCRC = CO1_SPI_START_ADDR+706;
Uint16 const co2_SPIrange3rwps = CO1_SPI_START_ADDR+708;
Uint16 const co2_SPIrange3rwpsCRC = CO1_SPI_START_ADDR+708;
Uint16 const co2_SPIrange4rw = CO1_SPI_START_ADDR+710;
Uint16 const co2_SPIrange4rwCRC = CO1_SPI_START_ADDR+710;
Uint16 const co2_SPIrange4rwp = CO1_SPI_START_ADDR+712;
Uint16 const co2_SPIrange4rwpCRC = CO1_SPI_START_ADDR+712;
Uint16 const co2_SPIrange4rwps = CO1_SPI_START_ADDR+714;
Uint16 const co2_SPIrange4rwpsCRC = CO1_SPI_START_ADDR+714;
Uint16 const co2_SPIrange5rw = CO1_SPI_START_ADDR+716;
Uint16 const co2_SPIrange5rwCRC = CO1_SPI_START_ADDR+1597;
Uint16 const co2_SPIrange5rwp = CO1_SPI_START_ADDR+1599;
Uint16 const co2_SPIrange5rwpCRC = CO1_SPI_START_ADDR+1603;
Uint16 const co2_SPIrange5rwps = CO1_SPI_START_ADDR+1605;
Uint16 const co2_SPIrange5rwpsCRC = CO1_SPI_START_ADDR+1605;
Uint16 const co2_first1000 = 0;
Uint16 const co2_first2000 = 82;
Uint16 const co2_first3000 = 194;
Uint16 const co2_first4000 = 198;
Uint16 const co2_first5000 = 198;
//������� �����

Uint16 const CO2_TYPE_DEF_TABLE[] = {    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)1,\
    (Uint16)0,\
    (Uint16)-1,\
    (Uint16)-1,\
    (Uint16)4,\
    (Uint16)0,\
    (Uint16)5,\
    (Uint16)5,\
    (Uint16)0,\
    (Uint16)27,\
    (Uint16)17,\
    (Uint16)8,\
    (Uint16)7,\
    (Uint16)6,\
    (Uint16)20,\
    (Uint16)15,\
    (Uint16)9,\
    (Uint16)16,\
    (Uint16)16,\
    (Uint16)11,\
    (Uint16)1,\
    (Uint16)13,\
    (Uint16)12,\
    (Uint16)18,\
    (Uint16)14,\
    (Uint16)-1,\
    (Uint16)2,\
    (Uint16)28,\
    (Uint16)0,\
    (Uint16)27,\
    (Uint16)24,\
    (Uint16)24,\
    (Uint16)24,\
    (Uint16)3,\
    (Uint16)26,\
    (Uint16)31,\
    (Uint16)32,\
    (Uint16)29,\
    (Uint16)25,\
    (Uint16)29,\
    (Uint16)33,\
    (Uint16)34,\
    (Uint16)34,\
    (Uint16)34,\
    (Uint16)34,\
    (Uint16)38,\
    (Uint16)34,\
};
//������� CALLBACK-�������

//**************************************************************
long const CO2_OD_CALLBACK_TBL[]={0,//1000h.00h
0,//1001h.00h
0,//1002h.00h
0,//1014h.00h
0,//1016h.00h
0,//1017h.00h
0,//1018h.00h
0,//1200h.00h
0,//1280h.00h
0,//1400h.00h
0,//1401h.00h
0,//1402h.00h
0,//1403h.00h
0,//1404h.00h
0,//1405h.00h
0,//1406h.00h
0,//1407h.00h
0,//1600h.00h
0,//1601h.00h
0,//1602h.00h
0,//1603h.00h
0,//1604h.00h
0,//1605h.00h
0,//1606h.00h
0,//1607h.00h
0,//1800h.00h
0,//1801h.00h
0,//1802h.00h
0,//1803h.00h
0,//1804h.00h
0,//1805h.00h
0,//1806h.00h
0,//1807h.00h
0,//1A00h.00h
0,//1A01h.00h
0,//1A02h.00h
0,//1A03h.00h
0,//1A04h.00h
0,//1A05h.00h
0,//1A06h.00h
0,//1A07h.00h
0,//2000h.00h
0,//2001h.00h
0,//2002h.00h
0,//2003h.00h
0,//2004h.00h
0,//2005h.00h
0,//2007h.00h
0,//2010h.00h
0,//2011h.00h
0,//2012h.00h
0,//2014h.00h
0,//2015h.00h
0,//2016h.00h
0,//2017h.00h
0,//2080h.00h
0,//2081h.00h
0,//2082h.00h
0,//2083h.00h
0,//2100h.00h
0,//2101h.00h
0,//2102h.00h
0,//2103h.00h
0,//2104h.00h
0,//2105h.00h
0,//2106h.00h
0,//2107h.00h
0,//2108h.00h
0,//2109h.00h
0,//210Ah.00h
0,//210Bh.00h
0,//210Ch.00h
0,//210Dh.00h
0,//210Eh.00h
0,//210Fh.00h
0,//2110h.00h
0,//2111h.00h
0,//2112h.00h
0,//2113h.00h
0,//2114h.00h
0,//2115h.00h
0,//2116h.00h
0,//2117h.00h
0,//2118h.00h
0,//2119h.00h
0,//211Ah.00h
0,//211Bh.00h
0,//211Ch.00h
0,//211Dh.00h
0,//2502h.00h
0,//2506h.00h
(long)((void(*)(long))callback_RTC),//250Fh.00h
0,//2532h.00h
0,//2534h.00h
0,//2600h.00h
(long)((void(*)(long))callback_BTcmd),//2700h.00h
0,//2701h.00h
0,//3000h.00h
0,//3100h.00h
0,//5000h.00h
0,//5101h.00h
0,//5102h.00h
0,//5103h.00h
0,//5104h.00h
0,//5105h.00h
0,//510Bh.00h
0,//510Eh.00h
0,//510Fh.00h
0,//5111h.00h
0,//5112h.00h
0,//5113h.00h
0,//5114h.00h
0,//5115h.00h
0,//5116h.00h
0,//5138h.00h
0,//5139h.00h
0,//5150h.00h
(long)((void(*)(long))callback_dlog),//5151h.00h
0,//5174h.00h
0,//5175h.00h
0,//5176h.00h
0,//5177h.00h
0,//5A20h.00h
0,//5A78h.00h
0,//5A79h.00h
0,//5A7Ah.00h
0,//5A7Bh.00h
0,//5A7Ch.00h
0,//5A7Dh.00h
0,//5A7Eh.00h
0,//5A7Fh.00h
0,//5A80h.00h
0,//5A81h.00h
0,//5A82h.00h
0,//5A83h.00h
0,//5A84h.00h
};

