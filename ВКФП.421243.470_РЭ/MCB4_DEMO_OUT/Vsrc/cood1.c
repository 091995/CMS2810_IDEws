// ����: cood1.c
// �������: C:\Users\Favarit\workspace_v8\project\MCB4_DEMO\Profiles\MCD4_DEMO_profile.xml
// ������������: ������� �������
// ���� ��������: 25.04.2023 12:51:39
// ������������: default
// COODEdit Basic v.7.5.3
#include "DSP.h"
#include "main.h"
#include "cood1.h"
#include "co_ODvars.h"

// ����� 120 �������� � �������
// ����� 726 ��������� � �������
Uint16 const co1_numOfInd = 120;
// ����� ������������ ��� �����
Uint16 const co1_groupEnum = 15;
// ���-�����:
Uint32 const co1_odHash[4] = {0x12DEEF44, 0xA33490A9, 0xF5B40F87, 0xF23B68F2};
// ������� � �������� ����������
long const CO1_OD_TBL3[] = {
(long)(&co1_vars.co_deviceType),	//[1000h.00h], ��������: ��� ����������, �������: Device Type, ������: CAN
(long)(&co1_vars.co_errorRegister),	//[1001h.00h], ��������: ������� ������, �������: ErrReg, ������: CAN
(long)(&co1_vars.co_deviceState),	//[1002h.00h], ��������: Manufacturer Status Register, �������: DevSta, ������: CAN
(long)(&co1_vars.co_emcyCOBID),	//[1014h.00h], ��������: COB-ID Emergency Object, �������: eCOBID, ������: CAN
(long)(&co1_vars.co_CHBT),	//[1016h.01h], ��������: ����� �������� ��������� Heartbeat, �������: CHBT, ������: CAN
(long)(&co1_vars.co_PHBT),	//[1017h.00h], ��������: ������ ��������� ��������� Heartbeat, �������: PHBT, ������: CAN
(long)(&co1_vars.co_vendorID),	//[1018h.01h], ��������: ��� �������������, �������: VendID, ������: CAN
(long)(&co1_vars.co_productCode),	//[1018h.02h], ��������: ��� ��������, �������: PrCode, ������: CAN
(long)(&co1_vars.co_revisionNumber),	//[1018h.03h], ��������: ����� �������, �������: RevNum, ������: CAN
(long)(&co1_vars.co_serialNumber),	//[1018h.04h], ��������: �������� �����, �������: SerNum, ������: CAN
(long)(&co1_vars.co_csrxCOBID),	//[1200h.01h], ��������: COB-ID Client->Server(rx), �������: CSRXID, ������: CAN
(long)(&co1_vars.co_sctxCOBID),	//[1200h.02h], ��������: COB-ID Server->Client(tx), �������: SCTXID, ������: CAN
(long)(&co1_vars.co_cstxCOBID),	//[1280h.01h], ��������: COB-ID Client->Server(tx), �������: CSTXID, ������: CAN
(long)(&co1_vars.co_scrxCOBID),	//[1280h.02h], ��������: COB-ID Server->Client(rx), �������: SCRXID, ������: CAN
(long)(&co1_vars.co_ssNODEID),	//[1280h.03h], ��������: NODE-ID on SDO server, �������: SDOSID, ������: CAN
(long)(&co1_vars.co_RPDO1COBID),	//[1400h.01h], ��������: COB-ID for RPDO1, �������: IRPDO1, ������: CAN
(long)(&co1_vars.co_transType),	//[1400h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO2COBID),	//[1401h.01h], ��������: COB-ID for RPDO2, �������: IRPDO2, ������: CAN
(long)(&co1_vars.co_transType),	//[1401h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO3COBID),	//[1402h.01h], ��������: COB-ID for RPDO3, �������: IRPDO3, ������: CAN
(long)(&co1_vars.co_transType),	//[1402h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO4COBID),	//[1403h.01h], ��������: COB-ID for RPDO4, �������: IRPDO4, ������: CAN
(long)(&co1_vars.co_transType),	//[1403h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO5COBID),	//[1404h.01h], ��������: COB-ID for RPDO5, �������: IRPDO5, ������: CAN
(long)(&co1_vars.co_transType),	//[1404h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO6COBID),	//[1405h.01h], ��������: COB-ID for RPDO6, �������: IRPDO6, ������: CAN
(long)(&co1_vars.co_transType),	//[1405h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO7COBID),	//[1406h.01h], ��������: COB-ID for RPDO7, �������: IRPDO7, ������: CAN
(long)(&co1_vars.co_transType),	//[1406h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO8COBID),	//[1407h.01h], ��������: COB-ID for RPDO8, �������: IRPDO8, ������: CAN
(long)(&co1_vars.co_transType),	//[1407h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_RPDO1_1Mapping),	//[1600h.01h], ��������: RPDO1-1 Mapping, �������: RPM11, ������: CAN
(long)(&co1_vars.co_RPDO1_2Mapping),	//[1600h.02h], ��������: RPDO1-2 Mapping, �������: RPM12, ������: CAN
(long)(&co1_vars.co_RPDO1_3Mapping),	//[1600h.03h], ��������: RPDO1-3 Mapping, �������: RPM13, ������: CAN
(long)(&co1_vars.co_RPDO1_4Mapping),	//[1600h.04h], ��������: RPDO1-4 Mapping, �������: RPM14, ������: CAN
(long)(&co1_vars.co_RPDO2_1Mapping),	//[1601h.01h], ��������: RPDO2-1 Mapping, �������: RPM21, ������: CAN
(long)(&co1_vars.co_RPDO2_2Mapping),	//[1601h.02h], ��������: RPDO2-2 Mapping, �������: RPM22, ������: CAN
(long)(&co1_vars.co_RPDO2_3Mapping),	//[1601h.03h], ��������: RPDO2-3 Mapping, �������: RPM23, ������: CAN
(long)(&co1_vars.co_RPDO2_4Mapping),	//[1601h.04h], ��������: RPDO2-4 Mapping, �������: RPM24, ������: CAN
(long)(&co1_vars.co_RPDO3_1Mapping),	//[1602h.01h], ��������: RPDO3-1 Mapping, �������: RPM31, ������: CAN
(long)(&co1_vars.co_RPDO3_2Mapping),	//[1602h.02h], ��������: RPDO3-2 Mapping, �������: RPM32, ������: CAN
(long)(&co1_vars.co_RPDO3_3Mapping),	//[1602h.03h], ��������: RPDO3-3 Mapping, �������: RPM33, ������: CAN
(long)(&co1_vars.co_RPDO3_4Mapping),	//[1602h.04h], ��������: RPDO3-4 Mapping, �������: RPM34, ������: CAN
(long)(&co1_vars.co_RPDO4_1Mapping),	//[1603h.01h], ��������: RPDO4-1 Mapping, �������: RPM41, ������: CAN
(long)(&co1_vars.co_RPDO4_2Mapping),	//[1603h.02h], ��������: RPDO4-2 Mapping, �������: RPM42, ������: CAN
(long)(&co1_vars.co_RPDO4_3Mapping),	//[1603h.03h], ��������: RPDO4-3 Mapping, �������: RPM43, ������: CAN
(long)(&co1_vars.co_RPDO4_4Mapping),	//[1603h.04h], ��������: RPDO4-4 Mapping, �������: RPM44, ������: CAN
(long)(&co1_vars.co_RPDO5_1Mapping),	//[1604h.01h], ��������: RPDO5-1 Mapping, �������: RPM51, ������: CAN
(long)(&co1_vars.co_RPDO5_2Mapping),	//[1604h.02h], ��������: RPDO5-2 Mapping, �������: RPM52, ������: CAN
(long)(&co1_vars.co_RPDO5_3Mapping),	//[1604h.03h], ��������: RPDO5-3 Mapping, �������: RPM53, ������: CAN
(long)(&co1_vars.co_RPDO5_4Mapping),	//[1604h.04h], ��������: RPDO5-4 Mapping, �������: RPM54, ������: CAN
(long)(&co1_vars.co_RPDO6_1Mapping),	//[1605h.01h], ��������: RPDO6-1 Mapping, �������: RPM61, ������: CAN
(long)(&co1_vars.co_RPDO6_2Mapping),	//[1605h.02h], ��������: RPDO6-2 Mapping, �������: RPM62, ������: CAN
(long)(&co1_vars.co_RPDO6_3Mapping),	//[1605h.03h], ��������: RPDO6-3 Mapping, �������: RPM63, ������: CAN
(long)(&co1_vars.co_RPDO6_4Mapping),	//[1605h.04h], ��������: RPDO6-4 Mapping, �������: RPM64, ������: CAN
(long)(&co1_vars.co_RPDO7_1Mapping),	//[1606h.01h], ��������: RPDO7-1 Mapping, �������: RPM71, ������: CAN
(long)(&co1_vars.co_RPDO7_2Mapping),	//[1606h.02h], ��������: RPDO7-2 Mapping, �������: RPM72, ������: CAN
(long)(&co1_vars.co_RPDO7_3Mapping),	//[1606h.03h], ��������: RPDO7-3 Mapping, �������: RPM73, ������: CAN
(long)(&co1_vars.co_RPDO7_4Mapping),	//[1606h.04h], ��������: RPDO7-4 Mapping, �������: RPM74, ������: CAN
(long)(&co1_vars.co_RPDO8_1Mapping),	//[1607h.01h], ��������: RPDO8-1 Mapping, �������: RPM81, ������: CAN
(long)(&co1_vars.co_RPDO8_2Mapping),	//[1607h.02h], ��������: RPDO8-2 Mapping, �������: RPM82, ������: CAN
(long)(&co1_vars.co_RPDO8_3Mapping),	//[1607h.03h], ��������: RPDO8-3 Mapping, �������: RPM83, ������: CAN
(long)(&co1_vars.co_RPDO8_4Mapping),	//[1607h.04h], ��������: RPDO8-4 Mapping, �������: RPM84, ������: CAN
(long)(&co1_vars.co_TPDO1COBID),	//[1800h.01h], ��������: COB-ID for TPDO1, �������: ITPDO1, ������: CAN
(long)(&co1_vars.co_transType),	//[1800h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO1ITime),	//[1800h.03h], ��������: Inhibit Time 1, �������: ITime1, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1800h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO1EventTimer),	//[1800h.05h], ��������: Event Timer 1, �������: EvTmr1, ������: CAN
(long)(&co1_vars.co_TPDO2COBID),	//[1801h.01h], ��������: COB-ID for TPDO2, �������: ITPDO2, ������: CAN
(long)(&co1_vars.co_transType),	//[1801h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO2ITime),	//[1801h.03h], ��������: Inhibit Time 2, �������: ITime2, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1801h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO2EventTimer),	//[1801h.05h], ��������: Event Timer 2, �������: EvTmr2, ������: CAN
(long)(&co1_vars.co_TPDO3COBID),	//[1802h.01h], ��������: COB-ID for TPDO3, �������: ITPDO3, ������: CAN
(long)(&co1_vars.co_transType),	//[1802h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO3ITime),	//[1802h.03h], ��������: Inhibit Time 3, �������: ITime3, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1802h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO3EventTimer),	//[1802h.05h], ��������: Event Timer 3, �������: EvTmr3, ������: CAN
(long)(&co1_vars.co_TPDO4COBID),	//[1803h.01h], ��������: COB-ID for TPDO4, �������: ITPDO4, ������: CAN
(long)(&co1_vars.co_transType),	//[1803h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO4ITime),	//[1803h.03h], ��������: Inhibit Time 4, �������: ITime4, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1803h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO4EventTimer),	//[1803h.05h], ��������: Event Timer 4, �������: EvTmr4, ������: CAN
(long)(&co1_vars.co_TPDO5COBID),	//[1804h.01h], ��������: COB-ID for TPDO5, �������: ITPDO5, ������: CAN
(long)(&co1_vars.co_transType),	//[1804h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO5ITime),	//[1804h.03h], ��������: Inhibit Time 5, �������: ITime5, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1804h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO5EventTimer),	//[1804h.05h], ��������: Event Timer 5, �������: EvTmr5, ������: CAN
(long)(&co1_vars.co_TPDO6COBID),	//[1805h.01h], ��������: COB-ID for TPDO6, �������: ITPDO6, ������: CAN
(long)(&co1_vars.co_transType),	//[1805h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO6ITime),	//[1805h.03h], ��������: Inhibit Time 6, �������: ITime6, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1805h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO6EventTimer),	//[1805h.05h], ��������: Event Timer 6, �������: EvTmr6, ������: CAN
(long)(&co1_vars.co_TPDO7COBID),	//[1806h.01h], ��������: COB-ID for TPDO7, �������: ITPDO7, ������: CAN
(long)(&co1_vars.co_transType),	//[1806h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO7ITime),	//[1806h.03h], ��������: Inhibit Time 7, �������: ITime7, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1806h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO7EventTimer),	//[1806h.05h], ��������: Event Timer 7, �������: EvTmr7, ������: CAN
(long)(&co1_vars.co_TPDO8COBID),	//[1807h.01h], ��������: COB-ID for TPDO8, �������: ITPDO8, ������: CAN
(long)(&co1_vars.co_transType),	//[1807h.02h], ��������: ��� ��������, �������: TransT, ������: CAN
(long)(&co1_vars.co_TPDO8ITime),	//[1807h.03h], ��������: Inhibit Time 8, �������: ITime8, ������: CAN
(long)(&co1_vars.co_compatEntry),	//[1807h.04h], ��������: Compatibility Entry, �������: CompEn, ������: CAN
(long)(&co1_vars.co_TPDO8EventTimer),	//[1807h.05h], ��������: Event Timer 8, �������: EvTmr8, ������: CAN
(long)(&co1_vars.co_TPDO1_1Mapping),	//[1A00h.01h], ��������: TPDO1-1 Mapping, �������: TPM11, ������: CAN
(long)(&co1_vars.co_TPDO1_2Mapping),	//[1A00h.02h], ��������: TPDO1-2 Mapping, �������: TPM12, ������: CAN
(long)(&co1_vars.co_TPDO1_3Mapping),	//[1A00h.03h], ��������: TPDO1-3 Mapping, �������: TPM13, ������: CAN
(long)(&co1_vars.co_TPDO1_4Mapping),	//[1A00h.04h], ��������: TPDO1-4 Mapping, �������: TPM14, ������: CAN
(long)(&co1_vars.co_TPDO2_1Mapping),	//[1A01h.01h], ��������: TPDO2-1 Mapping, �������: TPM21, ������: CAN
(long)(&co1_vars.co_TPDO2_2Mapping),	//[1A01h.02h], ��������: TPDO2-2 Mapping, �������: TPM22, ������: CAN
(long)(&co1_vars.co_TPDO2_3Mapping),	//[1A01h.03h], ��������: TPDO2-3 Mapping, �������: TPM23, ������: CAN
(long)(&co1_vars.co_TPDO2_4Mapping),	//[1A01h.04h], ��������: TPDO2-4 Mapping, �������: TPM24, ������: CAN
(long)(&co1_vars.co_TPDO3_1Mapping),	//[1A02h.01h], ��������: TPDO3-1 Mapping, �������: TPM31, ������: CAN
(long)(&co1_vars.co_TPDO3_2Mapping),	//[1A02h.02h], ��������: TPDO3-2 Mapping, �������: TPM32, ������: CAN
(long)(&co1_vars.co_TPDO3_3Mapping),	//[1A02h.03h], ��������: TPDO3-3 Mapping, �������: TPM33, ������: CAN
(long)(&co1_vars.co_TPDO3_4Mapping),	//[1A02h.04h], ��������: TPDO3-4 Mapping, �������: TPM34, ������: CAN
(long)(&co1_vars.co_TPDO4_1Mapping),	//[1A03h.01h], ��������: TPDO4-1 Mapping, �������: TPM41, ������: CAN
(long)(&co1_vars.co_TPDO4_2Mapping),	//[1A03h.02h], ��������: TPDO4-2 Mapping, �������: TPM42, ������: CAN
(long)(&co1_vars.co_TPDO4_3Mapping),	//[1A03h.03h], ��������: TPDO4-3 Mapping, �������: TPM43, ������: CAN
(long)(&co1_vars.co_TPDO4_4Mapping),	//[1A03h.04h], ��������: TPDO4-4 Mapping, �������: TPM44, ������: CAN
(long)(&co1_vars.co_TPDO5_1Mapping),	//[1A04h.01h], ��������: TPDO5-1 Mapping, �������: TPM51, ������: CAN
(long)(&co1_vars.co_TPDO5_2Mapping),	//[1A04h.02h], ��������: TPDO5-2 Mapping, �������: TPM52, ������: CAN
(long)(&co1_vars.co_TPDO5_3Mapping),	//[1A04h.03h], ��������: TPDO5-3 Mapping, �������: TPM53, ������: CAN
(long)(&co1_vars.co_TPDO5_4Mapping),	//[1A04h.04h], ��������: TPDO5-4 Mapping, �������: TPM54, ������: CAN
(long)(&co1_vars.co_TPDO6_1Mapping),	//[1A05h.01h], ��������: TPDO6-1 Mapping, �������: TPM61, ������: CAN
(long)(&co1_vars.co_TPDO6_2Mapping),	//[1A05h.02h], ��������: TPDO6-2 Mapping, �������: TPM62, ������: CAN
(long)(&co1_vars.co_TPDO6_3Mapping),	//[1A05h.03h], ��������: TPDO6-3 Mapping, �������: TPM63, ������: CAN
(long)(&co1_vars.co_TPDO6_4Mapping),	//[1A05h.04h], ��������: TPDO6-4 Mapping, �������: TPM64, ������: CAN
(long)(&co1_vars.co_TPDO7_1Mapping),	//[1A06h.01h], ��������: TPDO7-1 Mapping, �������: TPM71, ������: CAN
(long)(&co1_vars.co_TPDO7_2Mapping),	//[1A06h.02h], ��������: TPDO7-2 Mapping, �������: TPM72, ������: CAN
(long)(&co1_vars.co_TPDO7_3Mapping),	//[1A06h.03h], ��������: TPDO7-3 Mapping, �������: TPM73, ������: CAN
(long)(&co1_vars.co_TPDO7_4Mapping),	//[1A06h.04h], ��������: TPDO7-4 Mapping, �������: TPM74, ������: CAN
(long)(&co1_vars.co_TPDO8_1Mapping),	//[1A07h.01h], ��������: TPDO8-1 Mapping, �������: TPM81, ������: CAN
(long)(&co1_vars.co_TPDO8_2Mapping),	//[1A07h.02h], ��������: TPDO8-2 Mapping, �������: TPM82, ������: CAN
(long)(&co1_vars.co_TPDO8_3Mapping),	//[1A07h.03h], ��������: TPDO8-3 Mapping, �������: TPM83, ������: CAN
(long)(&co1_vars.co_TPDO8_4Mapping),	//[1A07h.04h], ��������: TPDO8-4 Mapping, �������: TPM84, ������: CAN
(long)(&co1_vars.co_nodeID),	//[2000h.00h], ��������: CAN NODE-ID, �������: NodeID, ������: CAN
(long)(&co1_vars.co_bitRate),	//[2001h.00h], ��������: CAN Bit Rate, �������: CANBR, ������: CAN, ���� � 0 �� 2: 0000000000000111b
(long)(&co1_vars.co_vendorID),	//[2002h.01h], ��������: ��� �������������, �������: VendID, ������: CAN
(long)(&co1_vars.co_productCode),	//[2002h.02h], ��������: ��� ��������, �������: PrCode, ������: CAN
(long)(&co1_vars.co_revisionNumber),	//[2002h.03h], ��������: ����� �������, �������: RevNum, ������: CAN
(long)(&co1_vars.co_serialNumber),	//[2002h.04h], ��������: �������� �����, �������: SerNum, ������: CAN
(long)(&co1_vars.co_specialData1),	//[2003h.01h], ��������: Special Data 1, �������: SpDat1, ������: CAN
(long)(&co1_vars.co_specialData2),	//[2003h.02h], ��������: Special Data 2, �������: SpDat2, ������: CAN
(long)(&co1_vars.co_specialData3),	//[2003h.03h], ��������: Special Data 3, �������: SpDat3, ������: CAN
(long)(&co1_vars.co_specialData4),	//[2003h.04h], ��������: Special Data 4, �������: SpDat4, ������: CAN
(long)(&co1_vars.co_secretCode),	//[2004h.00h], ��������: Secret Code, �������: Secret, ������: CAN
(long)(&co1_vars.co_protectBit),	//[2005h.00h], ��������: Protect Bit, �������: ProtBt, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_odHash[0]),	//[2007h.01h], ��������: md5_hash_0, �������: md5_hash_0, ������: CAN
(long)(&co1_odHash[1]),	//[2007h.02h], ��������: md5_hash_1, �������: md5_hash_1, ������: CAN
(long)(&co1_odHash[2]),	//[2007h.03h], ��������: md5_hash_2, �������: md5_hash_2, ������: CAN
(long)(&co1_odHash[3]),	//[2007h.04h], ��������: md5_hash_3, �������: md5_hash_3, ������: CAN
(long)(&co1_vars.co_heartbeatFlag0),	//[2010h.01h], ��������: Heartbeat Flag 0-31, �������: HFlag0, ������: CAN
(long)(&co1_vars.co_heartbeatFlag1),	//[2010h.02h], ��������: Heartbeat Flag 32-63, �������: HFlag1, ������: CAN
(long)(&co1_vars.co_heartbeatFlag2),	//[2010h.03h], ��������: Heartbeat Flag 64-95, �������: HFlag2, ������: CAN
(long)(&co1_vars.co_heartbeatFlag3),	//[2010h.04h], ��������: Heartbeat Flag 96-127, �������: HFlag3, ������: CAN
(long)(&co1_vars.co_heartbeatMask0),	//[2011h.01h], ��������: Heartbeat Mask 0-31, �������: HMask0, ������: CAN
(long)(&co1_vars.co_heartbeatMask1),	//[2011h.02h], ��������: Heartbeat Mask 32-63, �������: HMask1, ������: CAN
(long)(&co1_vars.co_heartbeatMask2),	//[2011h.03h], ��������: Heartbeat Mask 64-95, �������: HMask2, ������: CAN
(long)(&co1_vars.co_heartbeatMask3),	//[2011h.04h], ��������: Heartbeat Mask 96-127, �������: HMask3, ������: CAN
(long)(&co1_vars.co_heartbeatAutoStart),	//[2012h.00h], ��������: Heartbeat Autostart, �������: HBASta, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_vars.co_heartbeatAutoRecovery),	//[2014h.00h], ��������: Heartbeat Autorecovery, �������: HBARec, ������: CAN, ���� � 0 �� 0: 0000000000000001b
(long)(&co1_vars.co_nodeState),	//[2015h.00h], ��������: ��������� �������� CAN-Open, �������: State, ������: CAN
(long)(&co1_vars.co_emergencyErrorCode),	//[2016h.00h], ��������: Emergency Error Code, �������: EmErCo, ������: CAN
(long)(&co1_vars.co_deviceErrorState),	//[2017h.00h], ��������: Device Error State, �������: DeErSt, ������: CAN
(long)(&co1_vars.co_ODCommand),	//[2080h.01h], ��������: Object Dictionary Command, �������: ODComm, ������: CAN
(long)(&co1_vars.co_currentODIndex),	//[2080h.02h], ��������: Current OD Index, �������: ODCInd, ������: CAN
(long)(&co1_vars.co_currentODSubIndex),	//[2080h.03h], ��������: Current OD Sub-Index, �������: ODCSub, ������: CAN
(long)(&co1_vars.co_currentODEText),	//[2080h.04h], ��������: Current OD Element Text, �������: ODCTxt, ������: CAN
(long)(&co1_vars.co_currentODEFormat),	//[2080h.05h], ��������: Current OD Element Format, �������: ODCFrm, ������: CAN
(long)(&co1_vars.co_currentODEMin),	//[2080h.06h], ��������: Current OD Element Min, �������: ODCMin, ������: CAN
(long)(&co1_vars.co_currentODEMax),	//[2080h.07h], ��������: Current OD Element Max, �������: ODCMax, ������: CAN
(long)(&co1_vars.co_currentODEDefault),	//[2080h.08h], ��������: Current OD Element Default, �������: ODCDef, ������: CAN
(long)(&co1_vars.co_currentODEMinLow),	//[2080h.09h], ��������: Current OD Element MinLow, �������: ODCMiL, ������: CAN
(long)(&co1_vars.co_currentODEMaxLow),	//[2080h.0Ah], ��������: Current OD Element MaxLow, �������: ODCMaL, ������: CAN
(long)(&co1_vars.co_currentODEDefaultLow),	//[2080h.0Bh], ��������: Current OD Element Default Low, �������: ODCDeL, ������: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Ch], ��������: Current OD Element Address, �������: ODCAdr, ������: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Dh], ��������: Current OD Element Address, �������: ODCAdr, ������: CAN
(long)(&co1_vars.co_currentODEType),	//[2080h.0Eh], ��������: ������ ����������, �������: ������, ������: CAN
(long)(&co1_vars.co_odIndexSize),	//[2081h.00h], ��������: ���������� ��������, �������: ������, ������: CAN
(long)(&co1_vars.co_defaultIndex1),	//[2082h.01h], ��������: Default Index 1, �������: DfInd1, ������: CAN
(long)(&co1_vars.co_defaultIndex2),	//[2082h.02h], ��������: Default Index 2, �������: DfInd2, ������: CAN
(long)(&co1_vars.co_maskElement01),	//[2083h.01h], ��������: Mask Element, �������: MskEl0, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement01),	//[2083h.02h], ��������: Mask Element, �������: MskEl1, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement23),	//[2083h.03h], ��������: Mask Element, �������: MskEl2, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement23),	//[2083h.04h], ��������: Mask Element, �������: MskEl3, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement45),	//[2083h.05h], ��������: Mask Element, �������: MskEl4, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement45),	//[2083h.06h], ��������: Mask Element, �������: MskEl5, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement67),	//[2083h.07h], ��������: Mask Element, �������: MskEl6, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement67),	//[2083h.08h], ��������: Mask Element, �������: MskEl7, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElement89),	//[2083h.09h], ��������: Mask Element, �������: MskEl8, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElement89),	//[2083h.0Ah], ��������: Mask Element, �������: MskEl9, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Bh], ��������: Mask Element, �������: MskElA, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Ch], ��������: Mask Element, �������: MskElB, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Dh], ��������: Mask Element, �������: MskElC, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Eh], ��������: Mask Element, �������: MskElD, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_maskElementEF),	//[2083h.0Fh], ��������: Mask Element, �������: MskElE, ������: CAN, ���� � 0 �� 7: 0000000011111111b
(long)(&co1_vars.co_maskElementEF),	//[2083h.10h], ��������: Mask Element, �������: MskElF, ������: CAN, ���� � 8 �� 15: 1111111100000000b
(long)(&co1_vars.co_scaleNum0),	//[2100h.01h], ��������: Scale Number 0, �������: SN0, ������: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.02h], ��������: Scale Number 0 Format, �������: S0Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1),	//[2101h.01h], ��������: Scale Number 1, �������: SN1, ������: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.02h], ��������: Scale Number 1 Format, �������: S1Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum2),	//[2102h.01h], ��������: Scale Number 2, �������: SN2, ������: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.02h], ��������: Scale Number 2 Format, �������: S2Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum3),	//[2103h.01h], ��������: Scale Number 3, �������: SN3, ������: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.02h], ��������: Scale Number 3 Format, �������: S3Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum4),	//[2104h.01h], ��������: Scale Number 4, �������: SN4, ������: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.02h], ��������: Scale Number 4 Format, �������: S4Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum5),	//[2105h.01h], ��������: Scale Number 5, �������: SN5, ������: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.02h], ��������: Scale Number 5 Format, �������: S5Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum6),	//[2106h.01h], ��������: Scale Number 6, �������: SN6, ������: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.02h], ��������: Scale Number 6 Format, �������: S6Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum7),	//[2107h.01h], ��������: Scale Number 7, �������: SN7, ������: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.02h], ��������: Scale Number 7 Format, �������: S7Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum8),	//[2108h.01h], ��������: Scale Number 8, �������: SN8, ������: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.02h], ��������: Scale Number 8 Format, �������: S8Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum9),	//[2109h.01h], ��������: Scale Number 9, �������: SN9, ������: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.02h], ��������: Scale Number 9 Format, �������: S9Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumA),	//[210Ah.01h], ��������: Scale Number A, �������: SNA, ������: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.02h], ��������: Scale Number A Format, �������: SAFmt, ������: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumB),	//[210Bh.01h], ��������: Scale Number B, �������: SNB, ������: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.02h], ��������: Scale Number B Format, �������: SBFmt, ������: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumC),	//[210Ch.01h], ��������: Scale Number C, �������: SNC, ������: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.02h], ��������: Scale Number C Format, �������: SCFmt, ������: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumD),	//[210Dh.01h], ��������: Scale Number D, �������: SND, ������: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.02h], ��������: Scale Number D Format, �������: SDFmt, ������: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumE),	//[210Eh.01h], ��������: Scale Number E, �������: SNE, ������: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.02h], ��������: Scale Number E Format, �������: SEFmt, ������: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumF),	//[210Fh.01h], ��������: Scale Number F, �������: SNF, ������: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.02h], ��������: Scale Number F Format, �������: SFFmt, ������: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum10),	//[2110h.01h], ��������: Scale Number 10, �������: SN10, ������: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.02h], ��������: Scale Number 10 Format, �������: S10Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum11),	//[2111h.01h], ��������: Scale Number 11, �������: SN11, ������: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.02h], ��������: Scale Number 11 Format, �������: S11Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum12),	//[2112h.01h], ��������: Scale Number 12, �������: SN12, ������: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.02h], ��������: Scale Number 12 Format, �������: S12Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum13),	//[2113h.01h], ��������: Scale Number 13, �������: SN13, ������: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.02h], ��������: Scale Number 13 Format, �������: S13Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum14),	//[2114h.01h], ��������: Scale Number 14, �������: SN14, ������: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.02h], ��������: Scale Number 14 Format, �������: S14Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum15),	//[2115h.01h], ��������: Scale Number 15, �������: SN15, ������: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.02h], ��������: Scale Number 15Format, �������: S15Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum16),	//[2116h.01h], ��������: Scale Number 16, �������: SN16, ������: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.02h], ��������: Scale Number 16Format, �������: S16Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum17),	//[2117h.01h], ��������: Scale Number 17, �������: SN17, ������: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.02h], ��������: Scale Number 17Format, �������: S17Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum18),	//[2118h.01h], ��������: Scale Number 18, �������: SN18, ������: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.02h], ��������: Scale Number 18Format, �������: S18Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum19),	//[2119h.01h], ��������: Scale Number 19, �������: SN19, ������: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.02h], ��������: Scale Number 19Format, �������: S19Fmt, ������: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1A),	//[211Ah.01h], ��������: Scale Number 1A, �������: SN1A, ������: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.02h], ��������: Scale Number 1AFormat, �������: S1AFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1B),	//[211Bh.01h], ��������: Scale Number 1B, �������: SN1B, ������: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.02h], ��������: Scale Number 1BFormat, �������: S1BFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1C),	//[211Ch.01h], ��������: Scale Number 1C, �������: SN1C, ������: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.02h], ��������: Scale Number 1C Format, �������: S1CFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1D),	//[211Dh.01h], ��������: Scale Number 1D, �������: SN1D, ������: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.02h], ��������: Scale Number 1D Format, �������: S1DFmt, ������: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.03h], ��������: Scale Number Format Q, �������: Q-type, ������: CAN, ���� � 0 �� 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.04h], ��������: Scale Number Format NumOfFloat, �������: NFloat, ������: CAN, ���� � 5 �� 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.05h], ��������: Scale Number Format Prefix, �������: Prefix, ������: CAN, ���� � 7 �� 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.06h], ��������: Scale Number Format Units, �������: Units, ������: CAN, ���� � 10 �� 15: 1111110000000000b
(long)(&cmd.all),	//[2502h.01h], ��������: ����, �������: ����, ������: ����� ����������, ���� � 0 �� 0: 0000000000000001b
(long)(&cmd.all),	//[2502h.02h], ��������: ����, �������: ����, ������: ����� ����������, ���� � 1 �� 1: 0000000000000010b
(long)(&cmd.all),	//[2502h.03h], ��������: �������� ��������� ������, �������: ������, ������: ����� ����������, ���� � 2 �� 2: 0000000000000100b
(long)(&cmd.all),	//[2502h.04h], ��������: ����� ���������� CAN, �������: ���CAN, ������: ����� ����������
(long)(&drv_interface.req_data),	//[2506h.01h], ��������: ������� ������ �����, �������: OfflineCounterMax, ������: ��� �����
(long)(&drv_interface.ans_data),	//[2506h.02h], ��������: ������� ������ �����, �������: OfflineCounter, ������: ��� �����
(long)(&drv_interface.data_Low),	//[2506h.03h], ��������: data_Low, �������: data_L, ������: ��� �����
(long)(&drv_interface.data_High),	//[2506h.04h], ��������: data_High, �������: data_H, ������: ��� �����
(long)(&RTCclock.packed_time),	//[250Fh.00h], ��������: ���� ��������� �������, �������: RTC, ������: �����������
(long)(&sm_prot.Main_ErrorCode),	//[2532h.01h], ��������: ��� ������ MCB4, �������: ��� ������ MCB4, ������: ��� �����, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.Main_ErrorCode),	//[2532h.02h], ��������: ���������� ���� ������, �������: ���+, ������: ��� �����, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.Main_Flags),	//[2532h.03h], ��������: ��������� ������, �������: System, ������: ��� �����, ���� � 0 �� 0: 0000000000000001b
(long)(&disp_group_number),	//[2534h.01h], ��������: ����� ���� ��� ������ ����������, �������: � �� ��, ������: CAN
(long)(&VendorToken),	//[2600h.01h], ��������: VendorToken, �������: VendorToken, ������: ��� �����
(long)(&co1_vars.co_blockTransferCommand),	//[2700h.00h], ��������: Block Transfer Interpreter, �������: BT Interpreter, ������: CAN
(long)(&swu_vars),	//[2701h.01h], ��������: cmd, �������: cmd, ������: CAN
(long)(&swu_vars),	//[2701h.02h], ��������: status, �������: status, ������: CAN
(long)(&swu_vars),	//[2701h.03h], ��������: quest1, �������: quest1, ������: CAN
(long)(&swu_vars),	//[2701h.04h], ��������: quest2, �������: quest2, ������: CAN
(long)(&swu_vars),	//[2701h.05h], ��������: quest3, �������: quest3, ������: CAN
(long)(&swu_vars),	//[2701h.06h], ��������: quest4, �������: quest4, ������: CAN
(long)(&swu_vars),	//[2701h.07h], ��������: ans1, �������: ans1, ������: CAN
(long)(&swu_vars),	//[2701h.08h], ��������: ans2, �������: ans2, ������: CAN
(long)(&swu_vars),	//[2701h.09h], ��������: ans3, �������: ans3, ������: CAN
(long)(&swu_vars),	//[2701h.0Ah], ��������: ans4, �������: ans4, ������: CAN
(long)(&swu_vars),	//[2701h.0Bh], ��������: addr, �������: addr, ������: CAN
(long)(&swu_vars),	//[2701h.0Ch], ��������: CPU_ID, �������: CPU_ID, ������: CAN
(long)(&swu_vars),	//[2701h.0Dh], ��������: sector_mask, �������: sector_mask, ������: CAN
(long)(&swu_vars),	//[2701h.0Eh], ��������: version, �������: version, ������: CAN
(long)(&swu_vars),	//[2701h.0Fh], ��������: CRC, �������: CRC, ������: CAN
(long)(&drv_status.all),	//[3000h.00h], ��������: ������ ���������������, �������: ������, ������: �����������, ���� � 0 �� 5: 0000000000111111b
(long)(&msCounter),	//[3100h.01h], ��������: ������� ���������� 1 ���, �������: ��.������.1 ���, ������: ��������
(long)(&FastCounter),	//[3100h.02h], ��������: ������� ���������� 10 ���, �������: ��.������.10 ���, ������: ��������
(long)(&LoopCounter),	//[3100h.03h], ��������: BackgroundCounter, �������: BackgroundCounter, ������: ��������
(long)(&TIsr10),	//[3100h.04h], ��������: T_10���, �������: T_10���, ������: ��������
(long)(&TIsr1),	//[3100h.05h], ��������: T_1���, �������: T_1���, ������: ��������
(long)(&rmp.T),	//[5000h.01h], ��������: T ������� �� ��������, �������: rmpT, ������: ��
(long)(&rmp.input),	//[5000h.02h], ��������: ���� ��, �������: ������, ������: ��
(long)(&rmp.output),	//[5000h.03h], ��������: ����� ��, �������: �������, ������: ��
(long)(&pid_id.pid_ref_reg3),	//[5100h.01h], ��������: �������, �������: ���-�, ������: ���. ���� Id
(long)(&pid_id.pid_fdb_reg3),	//[5100h.02h], ��������: �������� �����, �������: ���.��, ������: ���. ���� Id
(long)(&pid_id.Kp_reg3),	//[5100h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���� Id
(long)(&pid_id.pid_out_max),	//[5100h.04h], ��������: �������� ������, �������: Max, ������: ���. ���� Id
(long)(&pid_id.pid_out_min),	//[5100h.05h], ��������: ������� ������, �������: Min, ������: ���. ���� Id
(long)(&pid_id.Ki_reg3),	//[5100h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���� Id
(long)(&pid_id.Kd_reg3),	//[5100h.07h], ��������: ����. �����. Kd, �������: Kd, ������: ���. ���� Id
(long)(&pid_id.Kc_reg3),	//[5100h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���� Id
(long)(&pid_id.e_reg3),	//[5100h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���� Id
(long)(&pid_id.pid_out_reg3),	//[5100h.0Ah], ��������: ����� ����������, �������: �����, ������: ���. ���� Id
(long)(&pid_id.up_reg3),	//[5100h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ���� Id
(long)(&pid_id.ui_reg3),	//[5100h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ���� Id
(long)(&pid_id.ud_reg3),	//[5100h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ���� Id
(long)(&pid_spd.pid_ref_reg3),	//[5101h.01h], ��������: �������, �������: pisref, ������: ���. ��������
(long)(&pid_spd.pid_fdb_reg3),	//[5101h.02h], ��������: �������� �����, �������: pisfbd, ������: ���. ��������
(long)(&pid_spd.Kp_reg3),	//[5101h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ��������
(long)(&pid_spd.pid_out_max),	//[5101h.04h], ��������: �������� ������, �������: Max, ������: ���. ��������
(long)(&pid_spd.pid_out_min),	//[5101h.05h], ��������: ������� ������, �������: Min, ������: ���. ��������
(long)(&pid_spd.Ki_reg3),	//[5101h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ��������
(long)(&pid_spd.Kd_reg3),	//[5101h.07h], ��������: ����. �����. Kd, �������: pisKd, ������: ���. ��������
(long)(&pid_spd.Kc_reg3),	//[5101h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ��������
(long)(&pid_spd.e_reg3),	//[5101h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ��������
(long)(&pid_spd.pid_out_reg3),	//[5101h.0Ah], ��������: ����� ����������, �������: pisout, ������: ���. ��������
(long)(&pid_spd.up_reg3),	//[5101h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ��������
(long)(&pid_spd.ui_reg3),	//[5101h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ��������
(long)(&pid_spd.ud_reg3),	//[5101h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ��������
(long)(&pid_spd.saterr_reg3),	//[5101h.0Eh], ��������: ���������� ���������, �������: ����. �����, ������: ���. ��������
(long)(&pid_iq.pid_ref_reg3),	//[5102h.01h], ��������: �������, �������: ���-��, ������: ���. ���� Iq
(long)(&pid_iq.pid_fdb_reg3),	//[5102h.02h], ��������: �������� �����, �������: ���.��, ������: ���. ���� Iq
(long)(&pid_iq.Kp_reg3),	//[5102h.03h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_max),	//[5102h.04h], ��������: �������� ������, �������: Max, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_min),	//[5102h.05h], ��������: ������� ������, �������: Min, ������: ���. ���� Iq
(long)(&pid_iq.Ki_reg3),	//[5102h.06h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���� Iq
(long)(&pid_iq.Kd_reg3),	//[5102h.07h], ��������: ����. �����. Kd, �������: Kd, ������: ���. ���� Iq
(long)(&pid_iq.Kc_reg3),	//[5102h.08h], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���� Iq
(long)(&pid_iq.e_reg3),	//[5102h.09h], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���� Iq
(long)(&pid_iq.pid_out_reg3),	//[5102h.0Ah], ��������: ����� ����������, �������: �����, ������: ���. ���� Iq
(long)(&pid_iq.up_reg3),	//[5102h.0Bh], ��������: ���.�������., �������: ���.�������., ������: ���. ���� Iq
(long)(&pid_iq.ui_reg3),	//[5102h.0Ch], ��������: ���.������., �������: ���.������., ������: ���. ���� Iq
(long)(&pid_iq.ud_reg3),	//[5102h.0Dh], ��������: ���.������., �������: ���.������., ������: ���. ���� Iq
(long)(&pid_pos.pid_ref_reg3),	//[5103h.01h], ��������: �������, �������: pisref, ������: ���. ���������
(long)(&pid_pos.pid_ref_reg3),	//[5103h.02h], ��������: �������, �������: pisref, ������: ���. ���������
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.03h], ��������: �������� �����, �������: pisfbd, ������: ���. ���������
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.04h], ��������: �������� �����, �������: pisfbd, ������: ���. ���������
(long)(&pid_pos.Kp_reg3),	//[5103h.05h], ��������: �������. �����. Kp, �������: Kp, ������: ���. ���������
(long)(&pid_pos.pid_out_max),	//[5103h.06h], ��������: �������� ������, �������: Max, ������: ���. ���������
(long)(&pid_pos.pid_out_min),	//[5103h.07h], ��������: ������� ������, �������: Min, ������: ���. ���������
(long)(&pid_pos.Ki_reg3),	//[5103h.08h], ��������: ������������ �����. Ki, �������: Ki, ������: ���. ���������
(long)(&pid_pos.Kd_reg3),	//[5103h.09h], ��������: ����. �����. Kd, �������: pisKd, ������: ���. ���������
(long)(&pid_pos.DiffDelim),	//[5103h.0Ah], ��������: �����. ����. �����, �������: �����. ����. �����, ������: ���. ���������
(long)(&pid_pos.Kf_d),	//[5103h.0Bh], ��������: ����. �������, �������: ����. �������, ������: ���. ���������
(long)(&pid_pos.Kc_reg3),	//[5103h.0Ch], ��������: ������.���������.�����������, �������: Kc, ������: ���. ���������
(long)(&pid_pos.DeadZone),	//[5103h.0Dh], ��������: ������� ����, �������: ������� ����, ������: ���. ���������
(long)(&pid_pos.e_reg3),	//[5103h.0Eh], ��������: ������ ��������������� ��������, �������: ������, ������: ���. ���������
(long)(&pid_spd.saterr_reg3),	//[5103h.0Fh], ��������: ���������� ���������, �������: ����. �����, ������: ���. ���������
(long)(&pid_pos.pid_out_reg3),	//[5103h.10h], ��������: ����� ����������, �������: pisout, ������: ���. ���������
(long)(&pid_pos.up_reg3),	//[5103h.11h], ��������: ���.�������., �������: ���.�������., ������: ���. ���������
(long)(&pid_pos.ui_reg3),	//[5103h.12h], ��������: ���.������., �������: ���.������., ������: ���. ���������
(long)(&pid_pos.ud_reg3),	//[5103h.13h], ��������: ���.������., �������: ���.������., ������: ���. ���������
(long)(&pid_pos.e_reg3_filterOut),	//[5103h.14h], ��������: ������ ������, �������: ������ ������, ������: ���. ���������
(long)(&pwm.UalphaRef),	//[5105h.01h], ��������: Ua���, �������: Ua���, ������: ���
(long)(&pwm.UbetaRef),	//[5105h.02h], ��������: Ub���, �������: Ub���, ������: ���
(long)(&pwm.U_lim),	//[5105h.03h], ��������: U_���, �������: U_���, ������: ���
(long)(&pwm.GammaA),	//[5105h.04h], ��������: GammaA, �������: GmA, ������: ���
(long)(&pwm.GammaB),	//[5105h.05h], ��������: GammaB, �������: GmB, ������: ���
(long)(&pwm.GammaC),	//[5105h.06h], ��������: GammaC, �������: GmC, ������: ���
(long)(&pwm.k_pwm),	//[5105h.07h], ��������: TPWM, �������: TPWM, ������: ���
(long)(&pwm.DeadBand),	//[5105h.08h], ��������: ������� ����� (���), �������: ����. �����, ������: ���
(long)(&pwm.MinGammaLimit),	//[5105h.09h], ��������: ����������� ���. ������., �������: GamLim, ������: ���
(long)(&pwm.UdCompK),	//[5105h.0Ah], ��������: ����. ����������� Ud, �������: Ud����K, ������: ���
(long)(&pwm.UdCompEnable),	//[5105h.0Bh], ��������: ����������� Ud, �������: Ud����, ������: ���, ���� � 0 �� 0: 0000000000000001b
(long)(&pwm.PWM_type),	//[5105h.0Ch], ��������: ��� ���, �������: ������, ������: ���, ���� � 0 �� 0: 0000000000000001b
(long)(&pwm.ULimitation),	//[5105h.0Dh], ��������: ULimitation, �������: ULimitation, ������: ���
(long)(&pwm.Frequency),	//[5105h.0Eh], ��������: ������� ���, �������: F���, ������: ���
(long)(&pwm.sector),	//[5105h.0Fh], ��������: ������, �������: ������, ������: ���
(long)(&pwm.U_mag),	//[5105h.10h], ��������: U_����, �������: U_����, ������: ���
(long)(&pwm.PDP_Fault),	//[5105h.11h], ��������: ����� ������, �������: F_bits, ������: ���
(long)(&sm_ctrl.state),	//[510Bh.01h], ��������: sm_state, �������: smstat, ������: �� sm_ctrl
(long)(&drv_status_code),	//[510Bh.02h], ��������: drv_status_code, �������: stcode, ������: �� sm_ctrl, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.bit_fault1),	//[510Eh.01h], ��������: ����� ������ 1, �������: bitF_1, ������: ������
(long)(&sm_prot.bit_fault2),	//[510Eh.02h], ��������: ����� ������ 2, �������: bitF_2, ������: ������
(long)(&sm_prot.mask_fault1),	//[510Eh.03h], ��������: ����� ������ 1L, �������: mask1L, ������: ������, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.mask_fault1),	//[510Eh.04h], ��������: ����� ������ 1H, �������: mask1H, ������: ������, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.mask_fault2),	//[510Eh.05h], ��������: ����� ������ 2L, �������: mask2L, ������: ������, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_prot.mask_fault2),	//[510Eh.06h], ��������: ����� ������  2H, �������: mask2H, ������: ������, ���� � 8 �� 15: 1111111100000000b
(long)(&sm_prot.Imax_protect),	//[510Eh.07h], ��������: ������������ ���, �������: ����.���, ������: ������
(long)(&sm_prot.Umax_protect),	//[510Eh.08h], ��������: ������������ ����������, �������: Ud_max, ������: ������
(long)(&sm_prot.Umin_protect),	//[510Eh.09h], ��������: ����������� ����������, �������: Ud_min, ������: ������
(long)(&sm_prot.speed_max),	//[510Eh.0Ah], ��������: ������������ ��������, �������: speed_max, ������: ������
(long)(&sm_prot.T_max),	//[510Eh.0Bh], ��������: ������������ �����������, �������: t_max, ������: ������
(long)(&refs.speed_ref),	//[5112h.01h], ��������: ��������, �������: ����_�, ������: �������
(long)(&refs.Iq_ref),	//[5112h.02h], ��������: ����. ��� ��, �������: ������, ������: �������
(long)(&refs.i_flux_ref),	//[5112h.03h], ��������: ��� ���������, �������: ������, ������: �������
(long)(&refs.theta_elec),	//[5112h.04h], ��������: theta_elec, �������: ������, ������: �������
(long)(&refs.uf_ref),	//[5112h.05h], ��������: �������� ���������� ��, �������: Uf_ref, ������: �������
(long)(&drv_params.p),	//[5113h.01h], ��������: ����� ��� �������, �������: ������, ������: �����. �����
(long)(&drv_params.I_nom),	//[5113h.02h], ��������: ����������� ���, �������: I�����, ������: �����. �����
(long)(&drv_params.U_nom),	//[5113h.03h], ��������: ����������� ���������� ����., �������: U�_���, ������: �����. �����
(long)(&drv_params.speed_nom),	//[5113h.04h], ��������: ����������� ��������, �������: �����������, ������: �����. �����
(long)(&drv_params.Udc_nom),	//[5113h.05h], ��������: ����������� ���������� ���, �������: Udc���, ������: �����. �����
(long)(&drv_params.Rs),	//[5113h.06h], ��������: Rs, �������: Rs, ������: �����. �����
(long)(&drv_params.Ls),	//[5113h.07h], ��������: Ls, �������: Ls, ������: �����. �����
(long)(&drv_params.freq_nom),	//[5113h.08h], ��������: ����������� �������, �������: ���.����., ������: �����. �����
(long)(&drv_params.sens_type),	//[5113h.09h], ��������: ��� ������� ���������, �������: Sens_type, ������: �����. �����, ���� � 0 �� 2: 0000000000000111b
(long)(&sw.HardwareType),	//[5114h.01h], ��������: ��� ���������� �����, �������: HardwareType, ������: ��������� ��, ���� � 0 �� 7: 0000000011111111b
(long)(&sm_ctrl.run_mode),	//[5114h.02h], ��������: ����� ������, �������: ������, ������: ��������� ��
(long)(&sw.AutoOffset),	//[5114h.03h], ��������: ��� ���� ����., �������: �������, ������: ��������� ��
(long)(&sw.Reboot),	//[5114h.04h], ��������: ������������, �������: ������������, ������: ��������� ��
(long)(&adc.Imeas_a_gain),	//[5116h.01h], ��������: ����������� ���� ���� �, �������: Ia����, ������: ���
(long)(&adc.Imeas_a_offset),	//[5116h.02h], ��������: �������� ���� ���� �, �������: Ia����, ������: ���
(long)(&adc.Imeas_a),	//[5116h.03h], ��������: ��� ���� �, �������: Ia_���, ������: ���
(long)(&adc.Imeas_b_gain),	//[5116h.04h], ��������: ����������� ���� ���� �, �������: Ib����, ������: ���
(long)(&adc.Imeas_b_offset),	//[5116h.05h], ��������: �������� ���� ���� �, �������: Ib����, ������: ���
(long)(&adc.Imeas_b),	//[5116h.06h], ��������: ��� ���� �, �������: Ib_���, ������: ���
(long)(&adc.Imeas_c_gain),	//[5116h.07h], ��������: ����������� ���� ���� C, �������: Ic����, ������: ���
(long)(&adc.Imeas_c_offset),	//[5116h.08h], ��������: �������� ���� ���� C, �������: Ic����, ������: ���
(long)(&adc.Imeas_c),	//[5116h.09h], ��������: ��� ���� �, �������: Ic_���, ������: ���
(long)(&adc.Imeas_d_gain),	//[5116h.0Ah], ��������: ����������� ���� ���� D, �������: Id����, ������: ���
(long)(&adc.Imeas_d_offset),	//[5116h.0Bh], ��������: �������� ���� ���� D, �������: Id����, ������: ���
(long)(&adc.Imeas_d),	//[5116h.0Ch], ��������: ��� ���� D, �������: Id_���, ������: ���
(long)(&adc.Udc_meas_gain),	//[5116h.0Dh], ��������: ����������� ���������� ���, �������: Ud����, ������: ���
(long)(&adc.Udc_meas_offset),	//[5116h.0Eh], ��������: �������� ������. ���, �������: Ud����, ������: ���
(long)(&adc.Udc_meas),	//[5116h.0Fh], ��������: ���������� ���, �������: Ud, ������: ���
(long)(&adc.T_meas_gain),	//[5116h.10h], ��������: ����������� �����������, �������: t_gain, ������: ���
(long)(&adc.T_meas),	//[5116h.11h], ��������: �����������, �������: t, ������: ���
(long)(&adc.ref_meas_gain),	//[5116h.12h], ��������: ����������� �������� �����, �������: ADC_ext_gain, ������: ���
(long)(&adc.ref_meas_offset),	//[5116h.13h], ��������: �������� �������� �����, �������: ADC_ext_offset, ������: ���
(long)(&adc.ref_meas),	//[5116h.14h], ��������: ������� ���������� ���� 1, �������: ADC_ext1, ������: ���
(long)(&vhz.freq),	//[511Ah.01h], ��������: �������� �������, �������: F_���, ������: ������ U-f
(long)(&vhz.vout),	//[511Ah.02h], ��������: �������� ����������, �������: U_���, ������: ������ U-f
(long)(&vhz.FL),	//[511Ah.03h], ��������: ������� ������� �������, �������: f [0], ������: ������ U-f
(long)(&vhz.Vmin),	//[511Ah.04h], ��������: ������� ������� ����������, �������: U [0], ������: ������ U-f
(long)(&vhz.FH),	//[511Ah.05h], ��������: ������ ������� �������, �������: f [1], ������: ������ U-f
(long)(&vhz.Vmax),	//[511Ah.06h], ��������: ������ ������� ����������, �������: U [1], ������: ������ U-f
(long)(&vhz.Fmax),	//[511Ah.07h], ��������: ������������ �������, �������: f max, ������: ������ U-f
(long)(&cur_par.speed),	//[5138h.01h], ��������: ��������, �������: ����, ������: �����������
(long)(&cur_par.power),	//[5138h.02h], ��������: ���. ��������, �������: ������, ������: �����������
(long)(&cur_par.Is),	//[5138h.03h], ��������: ��� �������, �������: �����, ������: �����������
(long)(&cur_par.ThetaRefCurr),	//[5138h.04h], ��������: ���������, �������: ���������, ������: �����������
(long)(&cur_par.ThetaCurr),	//[5138h.05h], ��������: ������, �������: ������, ������: �����������
(long)(&cur_par.IsRef),	//[5138h.06h], ��������: ��� ������� ���, �������: ��������, ������: �����������
(long)(&global_time.PowerOn_time_min),	//[5138h.07h], ��������: ����� ����������� ���������, ���, �������: Power On Time, ������: �����������
(long)(&dlog.mode_reset),	//[5150h.01h], ��������: dlog.mode_reset, �������: mode, ������: dlog
(long)(&dlog.control),	//[5150h.02h], ��������: dlog.control, �������: dlcont, ������: dlog
(long)(&dlog.ind_subind[0]),	//[5150h.03h], ��������: dlog.ind_subind1, �������: dlisi1, ������: dlog
(long)(&dlog.ind_subind[1]),	//[5150h.04h], ��������: dlog.ind_subind2, �������: dlisi2, ������: dlog
(long)(&dlog.ind_subind[2]),	//[5150h.05h], ��������: dlog.ind_subind3, �������: dlisi3, ������: dlog
(long)(&dlog.ind_subind[3]),	//[5150h.06h], ��������: dlog.ind_subind4, �������: dlisi4, ������: dlog
(long)(&dlog.StartBits),	//[5150h.07h], ��������: StartBitL, �������: StrtBL, ������: dlog, ���� � 0 �� 7: 0000000011111111b
(long)(&dlog.StartBits),	//[5150h.08h], ��������: StartBitH, �������: StrtBH, ������: dlog, ���� � 8 �� 15: 1111111100000000b
(long)(&dlog.OneShotOperation),	//[5150h.09h], ��������: OneShotOperation, �������: OneShotOp, ������: dlog, ���� � 0 �� 0: 0000000000000001b
(long)(&dlog.trig_shift),	//[5150h.0Ah], ��������: ���������� ����� �����������, �������: N �������., ������: dlog
(long)(&dlog.sampling_rate),	//[5150h.0Bh], ��������: ������� ����������, �������: dlogFreq, ������: dlog
(long)(&dlog.next_value_var),	//[5151h.00h], ��������: dlog.next_value_var, �������: dlnval, ������: dlog
(long)(&posspeedEqep.resolution),	//[5152h.01h], ��������: ���-�� ��������, �������: ���-�� ��������, ������: ���-�������
(long)(&posspeedEqep.indexEnable),	//[5152h.02h], ��������: ������� ������, �������: ������� ������, ������: ���-�������, ���� � 2 �� 2: 0000000000000100b
(long)(&posspeedEqep.posCnt),	//[5152h.03h], ��������: ����������.���� � ������, �������: ����������.���� � ��, ������: ���-�������
(long)(&posspeedEqep.speed_elec),	//[5152h.04h], ��������: ��������, �������: ��������, ������: ���-�������
(long)(&posspeedEqep.theta_elec),	//[5152h.05h], ��������: ����. ������., �������: ����. ������., ������: ���-�������
(long)(&posspeedEqep.thetaMech),	//[5152h.06h], ��������: ���� ���., �������: ���� ���., ������: ���-�������
(long)(&posspeedEqep.GPIOsValue),	//[5152h.07h], ��������: GPIOsValue, �������: GPIOsValue, ������: ���-�������
(long)(&posspeedEqep.RevolutionCounter),	//[5152h.08h], ��������: ����� ��������, �������: revolCounter, ������: ���-�������
(long)(&DPReCAP.Angle),	//[5155h.01h], ��������: ������, �������: ������, ������: ���-����
(long)(&DPReCAP.speed),	//[5155h.02h], ��������: ��������, �������: ��������, ������: ���-����
(long)(&DPReCAP.speedMIN),	//[5155h.03h], ��������: ������� ��������, �������: ������� ��������, ������: ���-����
(long)(&DPReCAP.Angle6),	//[5155h.04h], ��������: ������6, �������: ������6, ������: ���-����
(long)(&DPReCAP.DPReCAP_FLG1.all),	//[5155h.05h], ��������: ���-������� ���, �������: ���-������� ���, ������: ���-����, ���� � 0 �� 0: 0000000000000001b
(long)(&DPReCAP.milsecREF),	//[5155h.06h], ��������: ������� ��������� ��������, �������: ������� ��������� ��, ������: ���-����
(long)(&DPReCAP.speedMinREF),	//[5155h.07h], ��������: �������� ���., �������: �������� ���., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt),	//[5155h.08h], ��������: ������ ������, �������: ������ ������, ������: ���-����
(long)(&DPReCAP.DPReCAP_CODE.all),	//[5155h.09h], ��������: ���������� �����, �������: �����, ������: ���-����, ���� � 0 �� 2: 0000000000000111b
(long)(&DPReCAP.AngleOffset),	//[5155h.0Ah], ��������: ��������, �������: ������, ������: ���-����
(long)(&DPReCAP.ErrorLevel),	//[5155h.0Bh], ��������: ������� �����, �������: ������� �����, ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt1),	//[5155h.0Ch], ��������: ������ 1 ������, �������: ����_1_�., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt2),	//[5155h.0Dh], ��������: ������ 2 ������, �������: ����_2_�., ������: ���-����
(long)(&DPReCAP.CAP_WrongEdgeCnt3),	//[5155h.0Eh], ��������: ������ 3 ������, �������: ����_3_�., ������: ���-����
(long)(&DPReCAP.Direction),	//[5155h.0Fh], ��������: ����������� ��������, �������: ������, ������: ���-����, ���� � 2 �� 2: 0000000000000100b
(long)(&DPReCAP.WrongCodeCounterLimitPerSec),	//[5155h.10h], ��������: ����.����� ������ ���, �������: ����.��.���, ������: ���-����
(long)(&DPReCAP.WrongCodeCounter),	//[5155h.11h], ��������: ���-�� ������ �������� ������������������, �������: ������ ����������., ������: ���-����
(long)(&CounterCAP_isr),	//[5155h.12h], ��������: ������� ���������� �� ������, �������: ����.Rx.Int., ������: ���-����
(long)(&cap0_counter),	//[5155h.13h], ��������: ������� ���������� CAP1, �������: ��.������.CAP1, ������: ���-����
(long)(&cap1_counter),	//[5155h.14h], ��������: ������� ���������� CAP2, �������: ��.������.CAP2, ������: ���-����
(long)(&cap2_counter),	//[5155h.15h], ��������: ������� ���������� CAP3, �������: ��.������.CAP3, ������: ���-����
(long)(&Debug1),	//[5174h.01h], ��������: DebugL1, �������: DebugL1, ������: ��� �������
(long)(&Debug1),	//[5174h.02h], ��������: DebugL1, �������: DebugL1, ������: ��� �������
(long)(&Debug2),	//[5174h.03h], ��������: DebugL2, �������: DebugL2, ������: ��� �������
(long)(&Debug2),	//[5174h.04h], ��������: DebugL2, �������: DebugL2, ������: ��� �������
(long)(&Debug3),	//[5174h.05h], ��������: DebugI3, �������: DebugI3, ������: ��� �������
(long)(&Debug3),	//[5174h.06h], ��������: DebugI3, �������: DebugI3, ������: ��� �������
(long)(&Debug4),	//[5174h.07h], ��������: DebugI4, �������: DebugI4, ������: ��� �������
(long)(&Debug4),	//[5174h.08h], ��������: DebugI4, �������: DebugI4, ������: ��� �������
(long)(&DebugW1),	//[5174h.09h], ��������: DebugW1, �������: DebugW1, ������: ��� �������
(long)(&DebugW1),	//[5174h.0Ah], ��������: DebugW1, �������: DebugW1, ������: ��� �������
(long)(&DebugW2),	//[5174h.0Bh], ��������: DebugW2, �������: DebugW2, ������: ��� �������
(long)(&DebugW2),	//[5174h.0Ch], ��������: DebugW2, �������: DebugW2, ������: ��� �������
(long)(&DebugW3),	//[5174h.0Dh], ��������: DebugW3, �������: DebugW3, ������: ��� �������
(long)(&DebugW3),	//[5174h.0Eh], ��������: DebugW3, �������: DebugW3, ������: ��� �������
(long)(&DebugW4),	//[5174h.0Fh], ��������: DebugW4, �������: DebugW4, ������: ��� �������
(long)(&DebugW4),	//[5174h.10h], ��������: DebugW4, �������: DebugW4, ������: ��� �������
(long)(&udControl.StateOn),	//[5B05h.01h], ��������: ������� ��������� ����, �������: Relay_state, ������: ������� ����� ���
(long)(&udControl.Timeout_on),	//[5B05h.02h], ��������: ������� ��������� ����, ��, �������: relay on-delay, ������: ������� ����� ���
(long)(&udControl.U_on),	//[5B05h.03h], ��������: ���������� ���������, �, �������: on-voltage, ������: ������� ����� ���
(long)(&udControl.U_off),	//[5B05h.04h], ��������: ���������� ����������, �, �������: off-voltage, ������: ������� ����� ���
(long)(&udControl.deriv_time_ZPT),	//[5B05h.05h], ��������: ����������� ���������� ���, �������: derivative_voltage, ������: ������� ����� ���
(long)(&udControl.deriv_const),	//[5B05h.06h], ��������: ������� �� ����������� ���, �������: derivative_const, ������: ������� ����� ���
(long)(&FanControl.StateOn),	//[5B06h.01h], ��������: ������� ��������� �����������, �������: fan_state, ������: ������� ����������
(long)(&FanControl.T_on),	//[5B06h.02h], ��������: ����������� ��������� �����������, �������: t_on, ������: ������� ����������
(long)(&FanControl.T_off),	//[5B06h.03h], ��������: ����������� ���������� �����������, �������: t_off, ������: ������� ����������
(long)(&FanControl.T_alarm),	//[5B06h.04h], ��������: ����������� ������ �������������� � ���������, �������: t_alarm, ������: ������� ����������
};

// ������� � ���������, ���������, � ������� ����������� ���������
Uint16 const CO1_OD_TBL2[] = {

//[1000h.00h]
3200,	// ������
1,	// ����� ������, ��������: ��� ����������
0,	// �������� ��� ������� � ��������

//[1001h.00h]
2176,	// ������
2,	// ����� ������, ��������: ������� ������
1,	// �������� ��� ������� � ��������

//[1002h.00h]
3200,	// ������
3,	// ����� ������, ��������: Manufacturer Status Register
2,	// �������� ��� ������� � ��������

//[1014h.00h]
3200,	// ������
4,	// ����� ������, ��������: COB-ID Emergency Object
3,	// �������� ��� ������� � ��������

// �������� ��������� 1016h, �������=CHBT
1,	// ���-�� �����������
5,	// ����� ������
3,	// ����� ������

//[1016h.01h]
35968,	// ������
5,	// ����� ������, ��������: ����� �������� ��������� Heartbeat
4,	// �������� ��� ������� � ��������
(Uint16)(2000),	// ���� �� �����.
(((Uint32)2000)>>16),	// ���� �� �����.

//[1017h.00h]
35456,	// ������
6,	// ����� ������, ��������: ������ ��������� ��������� Heartbeat
5,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1018h, �������=IdObj
4,	// ���-�� �����������
7,	// ����� ������
1,	// ����� ������

//[1018h.01h]
3200,	// ������
8,	// ����� ������, ��������: ��� �������������
6,	// �������� ��� ������� � ��������

//[1018h.02h]
3200,	// ������
9,	// ����� ������, ��������: ��� ��������
7,	// �������� ��� ������� � ��������

//[1018h.03h]
3200,	// ������
10,	// ����� ������, ��������: ����� �������
8,	// �������� ��� ������� � ��������

//[1018h.04h]
3200,	// ������
11,	// ����� ������, ��������: �������� �����
9,	// �������� ��� ������� � ��������

// �������� ��������� 1200h, �������=SSDOP
2,	// ���-�� �����������
12,	// ����� ������
1,	// ����� ������

//[1200h.01h]
3200,	// ������
13,	// ����� ������, ��������: COB-ID Client->Server(rx)
10,	// �������� ��� ������� � ��������

//[1200h.02h]
3200,	// ������
14,	// ����� ������, ��������: COB-ID Server->Client(tx)
11,	// �������� ��� ������� � ��������

// �������� ��������� 1280h, �������=CSDOP
3,	// ���-�� �����������
15,	// ����� ������
1,	// ����� ������

//[1280h.01h]
3200,	// ������
16,	// ����� ������, ��������: COB-ID Client->Server(tx)
12,	// �������� ��� ������� � ��������

//[1280h.02h]
3200,	// ������
17,	// ����� ������, ��������: COB-ID Server->Client(rx)
13,	// �������� ��� ������� � ��������

//[1280h.03h]
2176,	// ������
18,	// ����� ������, ��������: NODE-ID on SDO server
14,	// �������� ��� ������� � ��������

// �������� ��������� 1400h, �������=RPDO1P
2,	// ���-�� �����������
19,	// ����� ������
3,	// ����� ������

//[1400h.01h]
35968,	// ������
20,	// ����� ������, ��������: COB-ID for RPDO1
15,	// �������� ��� ������� � ��������
(Uint16)(0x180),	// ���� �� �����.
(((Uint32)0x180)>>16),	// ���� �� �����.

//[1400h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
16,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1401h, �������=RPDO2P
2,	// ���-�� �����������
22,	// ����� ������
3,	// ����� ������

//[1401h.01h]
35968,	// ������
23,	// ����� ������, ��������: COB-ID for RPDO2
17,	// �������� ��� ������� � ��������
(Uint16)(0x280),	// ���� �� �����.
(((Uint32)0x280)>>16),	// ���� �� �����.

//[1401h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
18,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1402h, �������=RPDO3P
2,	// ���-�� �����������
24,	// ����� ������
3,	// ����� ������

//[1402h.01h]
35968,	// ������
25,	// ����� ������, ��������: COB-ID for RPDO3
19,	// �������� ��� ������� � ��������
(Uint16)(0x0401),	// ���� �� �����.
(((Uint32)0x0401)>>16),	// ���� �� �����.

//[1402h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
20,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1403h, �������=RPDO4P
2,	// ���-�� �����������
26,	// ����� ������
3,	// ����� ������

//[1403h.01h]
35968,	// ������
27,	// ����� ������, ��������: COB-ID for RPDO4
21,	// �������� ��� ������� � ��������
(Uint16)(0x0501),	// ���� �� �����.
(((Uint32)0x0501)>>16),	// ���� �� �����.

//[1403h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
22,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1404h, �������=RPDO5P
2,	// ���-�� �����������
28,	// ����� ������
3,	// ����� ������

//[1404h.01h]
35968,	// ������
29,	// ����� ������, ��������: COB-ID for RPDO5
23,	// �������� ��� ������� � ��������
(Uint16)(0x0501),	// ���� �� �����.
(((Uint32)0x0501)>>16),	// ���� �� �����.

//[1404h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
24,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1405h, �������=RPDO6P
2,	// ���-�� �����������
30,	// ����� ������
3,	// ����� ������

//[1405h.01h]
35968,	// ������
31,	// ����� ������, ��������: COB-ID for RPDO6
25,	// �������� ��� ������� � ��������
(Uint16)(0x0501),	// ���� �� �����.
(((Uint32)0x0501)>>16),	// ���� �� �����.

//[1405h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
26,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1406h, �������=RPDO7P
2,	// ���-�� �����������
32,	// ����� ������
3,	// ����� ������

//[1406h.01h]
35968,	// ������
33,	// ����� ������, ��������: COB-ID for RPDO7
27,	// �������� ��� ������� � ��������
(Uint16)(0x0501),	// ���� �� �����.
(((Uint32)0x0501)>>16),	// ���� �� �����.

//[1406h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
28,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1407h, �������=RPDO8P
2,	// ���-�� �����������
34,	// ����� ������
3,	// ����� ������

//[1407h.01h]
35968,	// ������
35,	// ����� ������, ��������: COB-ID for RPDO8
29,	// �������� ��� ������� � ��������
(Uint16)(0x0501),	// ���� �� �����.
(((Uint32)0x0501)>>16),	// ���� �� �����.

//[1407h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
30,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 1600h, �������=RPDO1M
4,	// ���-�� �����������
36,	// ����� ������
3,	// ����� ������

//[1600h.01h]
35968,	// ������
37,	// ����� ������, ��������: RPDO1-1 Mapping
31,	// �������� ��� ������� � ��������
(Uint16)(0x511E0500),	// ���� �� �����.
(((Uint32)0x511E0500)>>16),	// ���� �� �����.

//[1600h.02h]
35968,	// ������
38,	// ����� ������, ��������: RPDO1-2 Mapping
32,	// �������� ��� ������� � ��������
(Uint16)(0x511E0600),	// ���� �� �����.
(((Uint32)0x511E0600)>>16),	// ���� �� �����.

//[1600h.03h]
35968,	// ������
39,	// ����� ������, ��������: RPDO1-3 Mapping
33,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1600h.04h]
35968,	// ������
40,	// ����� ������, ��������: RPDO1-4 Mapping
34,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1601h, �������=RPDO2M
4,	// ���-�� �����������
41,	// ����� ������
3,	// ����� ������

//[1601h.01h]
35968,	// ������
42,	// ����� ������, ��������: RPDO2-1 Mapping
35,	// �������� ��� ������� � ��������
(Uint16)(0x511E0700),	// ���� �� �����.
(((Uint32)0x511E0700)>>16),	// ���� �� �����.

//[1601h.02h]
35968,	// ������
43,	// ����� ������, ��������: RPDO2-2 Mapping
36,	// �������� ��� ������� � ��������
(Uint16)(0x511E0800),	// ���� �� �����.
(((Uint32)0x511E0800)>>16),	// ���� �� �����.

//[1601h.03h]
35968,	// ������
44,	// ����� ������, ��������: RPDO2-3 Mapping
37,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1601h.04h]
35968,	// ������
45,	// ����� ������, ��������: RPDO2-4 Mapping
38,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1602h, �������=RPDO3M
4,	// ���-�� �����������
46,	// ����� ������
3,	// ����� ������

//[1602h.01h]
35968,	// ������
47,	// ����� ������, ��������: RPDO3-1 Mapping
39,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1602h.02h]
35968,	// ������
48,	// ����� ������, ��������: RPDO3-2 Mapping
40,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1602h.03h]
35968,	// ������
49,	// ����� ������, ��������: RPDO3-3 Mapping
41,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1602h.04h]
35968,	// ������
50,	// ����� ������, ��������: RPDO3-4 Mapping
42,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1603h, �������=RPDO4M
4,	// ���-�� �����������
51,	// ����� ������
3,	// ����� ������

//[1603h.01h]
35968,	// ������
52,	// ����� ������, ��������: RPDO4-1 Mapping
43,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1603h.02h]
35968,	// ������
53,	// ����� ������, ��������: RPDO4-2 Mapping
44,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1603h.03h]
35968,	// ������
54,	// ����� ������, ��������: RPDO4-3 Mapping
45,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1603h.04h]
35968,	// ������
55,	// ����� ������, ��������: RPDO4-4 Mapping
46,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1604h, �������=RPDO5M
4,	// ���-�� �����������
56,	// ����� ������
3,	// ����� ������

//[1604h.01h]
35968,	// ������
57,	// ����� ������, ��������: RPDO5-1 Mapping
47,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1604h.02h]
35968,	// ������
58,	// ����� ������, ��������: RPDO5-2 Mapping
48,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1604h.03h]
35968,	// ������
59,	// ����� ������, ��������: RPDO5-3 Mapping
49,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1604h.04h]
35968,	// ������
60,	// ����� ������, ��������: RPDO5-4 Mapping
50,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1605h, �������=RPDO6M
4,	// ���-�� �����������
61,	// ����� ������
3,	// ����� ������

//[1605h.01h]
35968,	// ������
62,	// ����� ������, ��������: RPDO6-1 Mapping
51,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1605h.02h]
35968,	// ������
63,	// ����� ������, ��������: RPDO6-2 Mapping
52,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1605h.03h]
35968,	// ������
64,	// ����� ������, ��������: RPDO6-3 Mapping
53,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1605h.04h]
35968,	// ������
65,	// ����� ������, ��������: RPDO6-4 Mapping
54,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1606h, �������=RPDO7M
4,	// ���-�� �����������
66,	// ����� ������
3,	// ����� ������

//[1606h.01h]
35968,	// ������
67,	// ����� ������, ��������: RPDO7-1 Mapping
55,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1606h.02h]
35968,	// ������
68,	// ����� ������, ��������: RPDO7-2 Mapping
56,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1606h.03h]
35968,	// ������
69,	// ����� ������, ��������: RPDO7-3 Mapping
57,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1606h.04h]
35968,	// ������
70,	// ����� ������, ��������: RPDO7-4 Mapping
58,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1607h, �������=RPDO8M
4,	// ���-�� �����������
71,	// ����� ������
3,	// ����� ������

//[1607h.01h]
35968,	// ������
72,	// ����� ������, ��������: RPDO8-1 Mapping
59,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1607h.02h]
35968,	// ������
73,	// ����� ������, ��������: RPDO8-2 Mapping
60,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1607h.03h]
35968,	// ������
74,	// ����� ������, ��������: RPDO8-3 Mapping
61,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1607h.04h]
35968,	// ������
75,	// ����� ������, ��������: RPDO8-4 Mapping
62,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1800h, �������=TPDO1P
5,	// ���-�� �����������
76,	// ����� ������
2,	// ����� ������

//[1800h.01h]
3200,	// ������
77,	// ����� ������, ��������: COB-ID for TPDO1
63,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1800h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
64,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1800h.03h]
35456,	// ������
78,	// ����� ������, ��������: Inhibit Time 1
65,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1800h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
66,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1800h.05h]
35456,	// ������
80,	// ����� ������, ��������: Event Timer 1
67,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

// �������� ��������� 1801h, �������=TPDO2P
5,	// ���-�� �����������
81,	// ����� ������
2,	// ����� ������

//[1801h.01h]
3200,	// ������
82,	// ����� ������, ��������: COB-ID for TPDO2
68,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1801h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
69,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1801h.03h]
35456,	// ������
83,	// ����� ������, ��������: Inhibit Time 2
70,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1801h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
71,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1801h.05h]
35456,	// ������
84,	// ����� ������, ��������: Event Timer 2
72,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1802h, �������=TPDO3P
5,	// ���-�� �����������
85,	// ����� ������
2,	// ����� ������

//[1802h.01h]
3200,	// ������
86,	// ����� ������, ��������: COB-ID for TPDO3
73,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1802h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
74,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1802h.03h]
35456,	// ������
87,	// ����� ������, ��������: Inhibit Time 3
75,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1802h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
76,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1802h.05h]
35456,	// ������
88,	// ����� ������, ��������: Event Timer 3
77,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1803h, �������=TPDO4P
5,	// ���-�� �����������
89,	// ����� ������
2,	// ����� ������

//[1803h.01h]
3200,	// ������
90,	// ����� ������, ��������: COB-ID for TPDO4
78,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1803h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
79,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1803h.03h]
35456,	// ������
91,	// ����� ������, ��������: Inhibit Time 4
80,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1803h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
81,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1803h.05h]
35456,	// ������
92,	// ����� ������, ��������: Event Timer 4
82,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1804h, �������=TPDO5P
5,	// ���-�� �����������
93,	// ����� ������
2,	// ����� ������

//[1804h.01h]
3200,	// ������
94,	// ����� ������, ��������: COB-ID for TPDO5
83,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1804h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
84,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1804h.03h]
35456,	// ������
95,	// ����� ������, ��������: Inhibit Time 5
85,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1804h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
86,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1804h.05h]
35456,	// ������
96,	// ����� ������, ��������: Event Timer 5
87,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1805h, �������=TPDO6P
5,	// ���-�� �����������
97,	// ����� ������
2,	// ����� ������

//[1805h.01h]
3200,	// ������
98,	// ����� ������, ��������: COB-ID for TPDO6
88,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1805h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
89,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1805h.03h]
35456,	// ������
99,	// ����� ������, ��������: Inhibit Time 6
90,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1805h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
91,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1805h.05h]
35456,	// ������
100,	// ����� ������, ��������: Event Timer 6
92,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1806h, �������=TPDO7P
5,	// ���-�� �����������
101,	// ����� ������
2,	// ����� ������

//[1806h.01h]
3200,	// ������
102,	// ����� ������, ��������: COB-ID for TPDO7
93,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1806h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
94,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1806h.03h]
35456,	// ������
103,	// ����� ������, ��������: Inhibit Time 7
95,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1806h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
96,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1806h.05h]
35456,	// ������
104,	// ����� ������, ��������: Event Timer 7
97,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1807h, �������=TPDO8P
5,	// ���-�� �����������
105,	// ����� ������
2,	// ����� ������

//[1807h.01h]
3200,	// ������
106,	// ����� ������, ��������: COB-ID for TPDO8
98,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1807h.02h]
2176,	// ������
21,	// ����� ������, ��������: ��� ��������
99,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[1807h.03h]
35456,	// ������
107,	// ����� ������, ��������: Inhibit Time 8
100,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.

//[1807h.04h]
18560,	// ������
79,	// ����� ������, ��������: Compatibility Entry
101,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[1807h.05h]
35456,	// ������
108,	// ����� ������, ��������: Event Timer 8
102,	// �������� ��� ������� � ��������
(Uint16)(1000),	// ���� �� �����.

// �������� ��������� 1A00h, �������=TPDO1M
4,	// ���-�� �����������
109,	// ����� ������
3,	// ����� ������

//[1A00h.01h]
35968,	// ������
110,	// ����� ������, ��������: TPDO1-1 Mapping
103,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A00h.02h]
35968,	// ������
111,	// ����� ������, ��������: TPDO1-2 Mapping
104,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A00h.03h]
35968,	// ������
112,	// ����� ������, ��������: TPDO1-3 Mapping
105,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A00h.04h]
35968,	// ������
113,	// ����� ������, ��������: TPDO1-4 Mapping
106,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A01h, �������=TPDO2M
4,	// ���-�� �����������
114,	// ����� ������
3,	// ����� ������

//[1A01h.01h]
35968,	// ������
115,	// ����� ������, ��������: TPDO2-1 Mapping
107,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A01h.02h]
35968,	// ������
116,	// ����� ������, ��������: TPDO2-2 Mapping
108,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A01h.03h]
35968,	// ������
117,	// ����� ������, ��������: TPDO2-3 Mapping
109,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A01h.04h]
35968,	// ������
118,	// ����� ������, ��������: TPDO2-4 Mapping
110,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A02h, �������=TPDO3M
4,	// ���-�� �����������
119,	// ����� ������
3,	// ����� ������

//[1A02h.01h]
35968,	// ������
120,	// ����� ������, ��������: TPDO3-1 Mapping
111,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A02h.02h]
35968,	// ������
121,	// ����� ������, ��������: TPDO3-2 Mapping
112,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A02h.03h]
35968,	// ������
122,	// ����� ������, ��������: TPDO3-3 Mapping
113,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A02h.04h]
35968,	// ������
123,	// ����� ������, ��������: TPDO3-4 Mapping
114,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A03h, �������=TPDO4M
4,	// ���-�� �����������
124,	// ����� ������
3,	// ����� ������

//[1A03h.01h]
35968,	// ������
125,	// ����� ������, ��������: TPDO4-1 Mapping
115,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A03h.02h]
35968,	// ������
126,	// ����� ������, ��������: TPDO4-2 Mapping
116,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A03h.03h]
35968,	// ������
127,	// ����� ������, ��������: TPDO4-3 Mapping
117,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A03h.04h]
35968,	// ������
128,	// ����� ������, ��������: TPDO4-4 Mapping
118,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A04h, �������=TPDO5M
4,	// ���-�� �����������
129,	// ����� ������
3,	// ����� ������

//[1A04h.01h]
35968,	// ������
130,	// ����� ������, ��������: TPDO5-1 Mapping
119,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A04h.02h]
35968,	// ������
131,	// ����� ������, ��������: TPDO5-2 Mapping
120,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A04h.03h]
35968,	// ������
132,	// ����� ������, ��������: TPDO5-3 Mapping
121,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A04h.04h]
35968,	// ������
133,	// ����� ������, ��������: TPDO5-4 Mapping
122,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A05h, �������=TPDO6M
4,	// ���-�� �����������
134,	// ����� ������
3,	// ����� ������

//[1A05h.01h]
35968,	// ������
135,	// ����� ������, ��������: TPDO6-1 Mapping
123,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A05h.02h]
35968,	// ������
136,	// ����� ������, ��������: TPDO6-2 Mapping
124,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A05h.03h]
35968,	// ������
137,	// ����� ������, ��������: TPDO6-3 Mapping
125,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A05h.04h]
35968,	// ������
138,	// ����� ������, ��������: TPDO6-4 Mapping
126,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A06h, �������=TPDO7M
4,	// ���-�� �����������
139,	// ����� ������
3,	// ����� ������

//[1A06h.01h]
35968,	// ������
140,	// ����� ������, ��������: TPDO7-1 Mapping
127,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A06h.02h]
35968,	// ������
141,	// ����� ������, ��������: TPDO7-2 Mapping
128,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A06h.03h]
35968,	// ������
142,	// ����� ������, ��������: TPDO7-3 Mapping
129,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A06h.04h]
35968,	// ������
143,	// ����� ������, ��������: TPDO7-4 Mapping
130,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 1A07h, �������=TPDO8M
4,	// ���-�� �����������
144,	// ����� ������
3,	// ����� ������

//[1A07h.01h]
35968,	// ������
145,	// ����� ������, ��������: TPDO8-1 Mapping
131,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A07h.02h]
35968,	// ������
146,	// ����� ������, ��������: TPDO8-2 Mapping
132,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A07h.03h]
35968,	// ������
147,	// ����� ������, ��������: TPDO8-3 Mapping
133,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[1A07h.04h]
35968,	// ������
148,	// ����� ������, ��������: TPDO8-4 Mapping
134,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2000h.00h]
35328,	// ������
149,	// ����� ������, ��������: CAN NODE-ID
135,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
(Uint16)(1),	// �������
(Uint16)(127),	// ��������

//[2001h.00h]
41008,	// ������
150,	// ����� ������, ��������: CAN Bit Rate
136,	// �������� ��� ������� � ��������
(Uint16)(3),	// ���� �� �����.

// �������� ��������� 2002h, �������=IdObj
4,	// ���-�� �����������
7,	// ����� ������
1,	// ����� ������

//[2002h.01h]
3200,	// ������
8,	// ����� ������, ��������: ��� �������������
137,	// �������� ��� ������� � ��������

//[2002h.02h]
3200,	// ������
9,	// ����� ������, ��������: ��� ��������
138,	// �������� ��� ������� � ��������

//[2002h.03h]
3200,	// ������
10,	// ����� ������, ��������: ����� �������
139,	// �������� ��� ������� � ��������

//[2002h.04h]
3200,	// ������
11,	// ����� ������, ��������: �������� �����
140,	// �������� ��� ������� � ��������

// �������� ��������� 2003h, �������=SpData
4,	// ���-�� �����������
151,	// ����� ������
1,	// ����� ������

//[2003h.01h]
2688,	// ������
152,	// ����� ������, ��������: Special Data 1
141,	// �������� ��� ������� � ��������

//[2003h.02h]
2688,	// ������
153,	// ����� ������, ��������: Special Data 2
142,	// �������� ��� ������� � ��������

//[2003h.03h]
2688,	// ������
154,	// ����� ������, ��������: Special Data 3
143,	// �������� ��� ������� � ��������

//[2003h.04h]
2688,	// ������
155,	// ����� ������, ��������: Special Data 4
144,	// �������� ��� ������� � ��������

//[2004h.00h]
35968,	// ������
156,	// ����� ������, ��������: Secret Code
145,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2005h.00h]
8208,	// ������
157,	// ����� ������, ��������: Protect Bit
146,	// �������� ��� ������� � ��������

// �������� ��������� 2007h, �������=OD_md5_hash
4,	// ���-�� �����������
158,	// ����� ������
1,	// ����� ������

//[2007h.01h]
3200,	// ������
159,	// ����� ������, ��������: md5_hash_0
147,	// �������� ��� ������� � ��������

//[2007h.02h]
3200,	// ������
160,	// ����� ������, ��������: md5_hash_1
148,	// �������� ��� ������� � ��������

//[2007h.03h]
3200,	// ������
161,	// ����� ������, ��������: md5_hash_2
149,	// �������� ��� ������� � ��������

//[2007h.04h]
3200,	// ������
162,	// ����� ������, ��������: md5_hash_3
150,	// �������� ��� ������� � ��������

// �������� ��������� 2010h, �������=HBFlag
4,	// ���-�� �����������
163,	// ����� ������
1,	// ����� ������

//[2010h.01h]
3200,	// ������
164,	// ����� ������, ��������: Heartbeat Flag 0-31
151,	// �������� ��� ������� � ��������

//[2010h.02h]
3200,	// ������
165,	// ����� ������, ��������: Heartbeat Flag 32-63
152,	// �������� ��� ������� � ��������

//[2010h.03h]
3200,	// ������
166,	// ����� ������, ��������: Heartbeat Flag 64-95
153,	// �������� ��� ������� � ��������

//[2010h.04h]
3200,	// ������
167,	// ����� ������, ��������: Heartbeat Flag 96-127
154,	// �������� ��� ������� � ��������

// �������� ��������� 2011h, �������=HBMask
4,	// ���-�� �����������
168,	// ����� ������
3,	// ����� ������

//[2011h.01h]
35968,	// ������
169,	// ����� ������, ��������: Heartbeat Mask 0-31
155,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2011h.02h]
35968,	// ������
170,	// ����� ������, ��������: Heartbeat Mask 32-63
156,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2011h.03h]
35968,	// ������
171,	// ����� ������, ��������: Heartbeat Mask 64-95
157,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2011h.04h]
35968,	// ������
172,	// ����� ������, ��������: Heartbeat Mask 96-127
158,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2012h.00h]
40976,	// ������
173,	// ����� ������, ��������: Heartbeat Autostart
159,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2014h.00h]
40976,	// ������
174,	// ����� ������, ��������: Heartbeat Autorecovery
160,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2015h.00h]
2176,	// ������
175,	// ����� ������, ��������: ��������� �������� CAN-Open
161,	// �������� ��� ������� � ��������

//[2016h.00h]
2688,	// ������
176,	// ����� ������, ��������: Emergency Error Code
162,	// �������� ��� ������� � ��������

//[2017h.00h]
3200,	// ������
177,	// ����� ������, ��������: Device Error State
163,	// �������� ��� ������� � ��������

// �������� ��������� 2080h, �������=ODComW
14,	// ���-�� �����������
178,	// ����� ������
2,	// ����� ������

//[2080h.01h]
19072,	// ������
179,	// ����� ������, ��������: Object Dictionary Command
164,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2080h.02h]
19072,	// ������
180,	// ����� ������, ��������: Current OD Index
165,	// �������� ��� ������� � ��������
(Uint16)(0x2000),	// ���� �� �����.

//[2080h.03h]
19072,	// ������
181,	// ����� ������, ��������: Current OD Sub-Index
166,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2080h.04h]
2688,	// ������
182,	// ����� ������, ��������: Current OD Element Text
167,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.05h]
2688,	// ������
183,	// ����� ������, ��������: Current OD Element Format
168,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.06h]
2688,	// ������
184,	// ����� ������, ��������: Current OD Element Min
169,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.07h]
2688,	// ������
185,	// ����� ������, ��������: Current OD Element Max
170,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.08h]
2688,	// ������
186,	// ����� ������, ��������: Current OD Element Default
171,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.09h]
2688,	// ������
187,	// ����� ������, ��������: Current OD Element MinLow
172,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.0Ah]
2688,	// ������
188,	// ����� ������, ��������: Current OD Element MaxLow
173,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.0Bh]
2688,	// ������
189,	// ����� ������, ��������: Current OD Element Default Low
174,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.0Ch]
2688,	// ������
190,	// ����� ������, ��������: Current OD Element Address
175,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.0Dh]
2688,	// ������
190,	// ����� ������, ��������: Current OD Element Address
176,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2080h.0Eh]
2688,	// ������
191,	// ����� ������, ��������: ������ ����������
177,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2081h.00h]
2688,	// ������
192,	// ����� ������, ��������: ���������� ��������
178,	// �������� ��� ������� � ��������

// �������� ��������� 2082h, �������=DefInd
2,	// ���-�� �����������
193,	// ����� ������
3,	// ����� ������

//[2082h.01h]
19584,	// ������
194,	// ����� ������, ��������: Default Index 1
179,	// �������� ��� ������� � ��������
(Uint16)(0x30000000),	// ���� �� �����.
(((Uint32)0x30000000)>>16),	// ���� �� �����.

//[2082h.02h]
19584,	// ������
195,	// ����� ������, ��������: Default Index 2
180,	// �������� ��� ������� � ��������
(Uint16)(0x30000000),	// ���� �� �����.
(((Uint32)0x30000000)>>16),	// ���� �� �����.

// �������� ��������� 2083h, �������=ProfML
16,	// ���-�� �����������
196,	// ����� ������
2,	// ����� ������

//[2083h.01h]
24704,	// ������
197,	// ����� ������, ��������: Mask Element
181,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.02h]
24712,	// ������
198,	// ����� ������, ��������: Mask Element
182,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.03h]
24704,	// ������
199,	// ����� ������, ��������: Mask Element
183,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.04h]
24712,	// ������
200,	// ����� ������, ��������: Mask Element
184,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.05h]
24704,	// ������
201,	// ����� ������, ��������: Mask Element
185,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.06h]
24712,	// ������
202,	// ����� ������, ��������: Mask Element
186,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.07h]
24704,	// ������
203,	// ����� ������, ��������: Mask Element
187,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.08h]
24712,	// ������
204,	// ����� ������, ��������: Mask Element
188,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.09h]
24704,	// ������
205,	// ����� ������, ��������: Mask Element
189,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Ah]
24712,	// ������
206,	// ����� ������, ��������: Mask Element
190,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Bh]
24704,	// ������
207,	// ����� ������, ��������: Mask Element
191,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Ch]
24712,	// ������
208,	// ����� ������, ��������: Mask Element
192,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Dh]
24704,	// ������
209,	// ����� ������, ��������: Mask Element
193,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Eh]
24712,	// ������
210,	// ����� ������, ��������: Mask Element
194,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.0Fh]
24704,	// ������
211,	// ����� ������, ��������: Mask Element
195,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2083h.10h]
24712,	// ������
212,	// ����� ������, ��������: Mask Element
196,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 2100h, �������=SNR0
6,	// ���-�� �����������
213,	// ����� ������
2,	// ����� ������

//[2100h.01h]
2688,	// ������
214,	// ����� ������, ��������: Scale Number 0
197,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2100h.02h]
19072,	// ������
215,	// ����� ������, ��������: Scale Number 0 Format
198,	// �������� ��� ������� � ��������
(Uint16)(32),	// ���� �� �����.

//[2100h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
199,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2100h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
200,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2100h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
201,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2100h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
202,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 2101h, �������=SNR1
6,	// ���-�� �����������
220,	// ����� ������
2,	// ����� ������

//[2101h.01h]
2688,	// ������
221,	// ����� ������, ��������: Scale Number 1
203,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2101h.02h]
19072,	// ������
222,	// ����� ������, ��������: Scale Number 1 Format
204,	// �������� ��� ������� � ��������
(Uint16)(4128),	// ���� �� �����.

//[2101h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
205,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2101h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
206,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2101h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
207,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2101h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
208,	// �������� ��� ������� � ��������
(Uint16)(4),	// ���� �� �����.

// �������� ��������� 2102h, �������=SNR2
6,	// ���-�� �����������
223,	// ����� ������
2,	// ����� ������

//[2102h.01h]
2688,	// ������
224,	// ����� ������, ��������: Scale Number 2
209,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2102h.02h]
19072,	// ������
225,	// ����� ������, ��������: Scale Number 2 Format
210,	// �������� ��� ������� � ��������
(Uint16)(3136),	// ���� �� �����.

//[2102h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
211,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2102h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
212,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2102h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
213,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2102h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
214,	// �������� ��� ������� � ��������
(Uint16)(3),	// ���� �� �����.

// �������� ��������� 2103h, �������=SNR3
6,	// ���-�� �����������
226,	// ����� ������
2,	// ����� ������

//[2103h.01h]
2688,	// ������
227,	// ����� ������, ��������: Scale Number 3
215,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2103h.02h]
19072,	// ������
228,	// ����� ������, ��������: Scale Number 3 Format
216,	// �������� ��� ������� � ��������
(Uint16)(2112),	// ���� �� �����.

//[2103h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
217,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2103h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
218,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2103h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
219,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2103h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
220,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

// �������� ��������� 2104h, �������=SNR4
6,	// ���-�� �����������
229,	// ����� ������
2,	// ����� ������

//[2104h.01h]
2688,	// ������
230,	// ����� ������, ��������: Scale Number 4
221,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2104h.02h]
19072,	// ������
231,	// ����� ������, ��������: Scale Number 4 Format
222,	// �������� ��� ������� � ��������
(Uint16)(1056),	// ���� �� �����.

//[2104h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
223,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2104h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
224,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2104h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
225,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2104h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
226,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

// �������� ��������� 2105h, �������=SNR5
6,	// ���-�� �����������
232,	// ����� ������
2,	// ����� ������

//[2105h.01h]
2688,	// ������
233,	// ����� ������, ��������: Scale Number 5
227,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2105h.02h]
19072,	// ������
234,	// ����� ������, ��������: Scale Number 5 Format
228,	// �������� ��� ������� � ��������
(Uint16)(1056),	// ���� �� �����.

//[2105h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
229,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2105h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
230,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2105h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
231,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2105h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
232,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

// �������� ��������� 2106h, �������=SNR6
6,	// ���-�� �����������
235,	// ����� ������
2,	// ����� ������

//[2106h.01h]
2688,	// ������
236,	// ����� ������, ��������: Scale Number 6
233,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2106h.02h]
19072,	// ������
237,	// ����� ������, ��������: Scale Number 6 Format
234,	// �������� ��� ������� � ��������
(Uint16)(1088),	// ���� �� �����.

//[2106h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
235,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2106h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
236,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2106h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
237,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2106h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
238,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

// �������� ��������� 2107h, �������=SNR7
6,	// ���-�� �����������
238,	// ����� ������
2,	// ����� ������

//[2107h.01h]
2688,	// ������
239,	// ����� ������, ��������: Scale Number 7
239,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2107h.02h]
19072,	// ������
240,	// ����� ������, ��������: Scale Number 7 Format
240,	// �������� ��� ������� � ��������
(Uint16)(2112),	// ���� �� �����.

//[2107h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
241,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2107h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
242,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2107h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
243,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2107h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
244,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

// �������� ��������� 2108h, �������=SNR8
6,	// ���-�� �����������
241,	// ����� ������
2,	// ����� ������

//[2108h.01h]
2688,	// ������
242,	// ����� ������, ��������: Scale Number 8
245,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2108h.02h]
19072,	// ������
243,	// ����� ������, ��������: Scale Number 8 Format
246,	// �������� ��� ������� � ��������
(Uint16)(9286),	// ���� �� �����.

//[2108h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
247,	// �������� ��� ������� � ��������
(Uint16)(6),	// ���� �� �����.

//[2108h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
248,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2108h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
249,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2108h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
250,	// �������� ��� ������� � ��������
(Uint16)(9),	// ���� �� �����.

// �������� ��������� 2109h, �������=SNR9
6,	// ���-�� �����������
244,	// ����� ������
2,	// ����� ������

//[2109h.01h]
2688,	// ������
245,	// ����� ������, ��������: Scale Number 9
251,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2109h.02h]
19072,	// ������
246,	// ����� ������, ��������: Scale Number 9 Format
252,	// �������� ��� ������� � ��������
(Uint16)(5184),	// ���� �� �����.

//[2109h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
253,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2109h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
254,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2109h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
255,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2109h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
256,	// �������� ��� ������� � ��������
(Uint16)(5),	// ���� �� �����.

// �������� ��������� 210Ah, �������=SNRA
6,	// ���-�� �����������
247,	// ����� ������
2,	// ����� ������

//[210Ah.01h]
2688,	// ������
248,	// ����� ������, ��������: Scale Number A
257,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Ah.02h]
19072,	// ������
249,	// ����� ������, ��������: Scale Number A Format
258,	// �������� ��� ������� � ��������
(Uint16)(12320),	// ���� �� �����.

//[210Ah.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
259,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Ah.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
260,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[210Ah.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
261,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Ah.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
262,	// �������� ��� ������� � ��������
(Uint16)(12),	// ���� �� �����.

// �������� ��������� 210Bh, �������=SNRB
6,	// ���-�� �����������
250,	// ����� ������
2,	// ����� ������

//[210Bh.01h]
2688,	// ������
251,	// ����� ������, ��������: Scale Number B
263,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Bh.02h]
19072,	// ������
252,	// ����� ������, ��������: Scale Number B Format
264,	// �������� ��� ������� � ��������
(Uint16)(6144),	// ���� �� �����.

//[210Bh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
265,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Bh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
266,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Bh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
267,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Bh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
268,	// �������� ��� ������� � ��������
(Uint16)(6),	// ���� �� �����.

// �������� ��������� 210Ch, �������=SNRC
6,	// ���-�� �����������
253,	// ����� ������
2,	// ����� ������

//[210Ch.01h]
2688,	// ������
254,	// ����� ������, ��������: Scale Number C
269,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Ch.02h]
19072,	// ������
255,	// ����� ������, ��������: Scale Number C Format
270,	// �������� ��� ������� � ��������
(Uint16)(7168),	// ���� �� �����.

//[210Ch.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
271,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Ch.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
272,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Ch.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
273,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Ch.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
274,	// �������� ��� ������� � ��������
(Uint16)(7),	// ���� �� �����.

// �������� ��������� 210Dh, �������=SNRD
6,	// ���-�� �����������
256,	// ����� ������
2,	// ����� ������

//[210Dh.01h]
2688,	// ������
257,	// ����� ������, ��������: Scale Number D
275,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Dh.02h]
19072,	// ������
258,	// ����� ������, ��������: Scale Number D Format
276,	// �������� ��� ������� � ��������
(Uint16)(2048),	// ���� �� �����.

//[210Dh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
277,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Dh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
278,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Dh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
279,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Dh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
280,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

// �������� ��������� 210Eh, �������=SNRE
6,	// ���-�� �����������
259,	// ����� ������
2,	// ����� ������

//[210Eh.01h]
2688,	// ������
260,	// ����� ������, ��������: Scale Number E
281,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Eh.02h]
19072,	// ������
261,	// ����� ������, ��������: Scale Number E Format
282,	// �������� ��� ������� � ��������
(Uint16)(1024),	// ���� �� �����.

//[210Eh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
283,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Eh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
284,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Eh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
285,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Eh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
286,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

// �������� ��������� 210Fh, �������=SNRF
6,	// ���-�� �����������
262,	// ����� ������
2,	// ����� ������

//[210Fh.01h]
2688,	// ������
263,	// ����� ������, ��������: Scale Number F
287,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[210Fh.02h]
19072,	// ������
264,	// ����� ������, ��������: Scale Number F Format
288,	// �������� ��� ������� � ��������
(Uint16)(96),	// ���� �� �����.

//[210Fh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
289,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Fh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
290,	// �������� ��� ������� � ��������
(Uint16)(3),	// ���� �� �����.

//[210Fh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
291,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[210Fh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
292,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 2110h, �������=SNR10
6,	// ���-�� �����������
265,	// ����� ������
2,	// ����� ������

//[2110h.01h]
2688,	// ������
266,	// ����� ������, ��������: Scale Number 10
293,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2110h.02h]
19072,	// ������
267,	// ����� ������, ��������: Scale Number 10 Format
294,	// �������� ��� ������� � ��������
(Uint16)(3136),	// ���� �� �����.

//[2110h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
295,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2110h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
296,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2110h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
297,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2110h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
298,	// �������� ��� ������� � ��������
(Uint16)(3),	// ���� �� �����.

// �������� ��������� 2111h, �������=SNR11
6,	// ���-�� �����������
268,	// ����� ������
2,	// ����� ������

//[2111h.01h]
2688,	// ������
269,	// ����� ������, ��������: Scale Number 11
299,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2111h.02h]
19072,	// ������
270,	// ����� ������, ��������: Scale Number 11 Format
300,	// �������� ��� ������� � ��������
(Uint16)(9408),	// ���� �� �����.

//[2111h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
301,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2111h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
302,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2111h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
303,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2111h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
304,	// �������� ��� ������� � ��������
(Uint16)(9),	// ���� �� �����.

// �������� ��������� 2112h, �������=SNR12
6,	// ���-�� �����������
271,	// ����� ������
2,	// ����� ������

//[2112h.01h]
2688,	// ������
272,	// ����� ������, ��������: Scale Number 12
305,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2112h.02h]
19072,	// ������
273,	// ����� ������, ��������: Scale Number 12 Format
306,	// �������� ��� ������� � ��������
(Uint16)(9414),	// ���� �� �����.

//[2112h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
307,	// �������� ��� ������� � ��������
(Uint16)(6),	// ���� �� �����.

//[2112h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
308,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2112h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
309,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2112h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
310,	// �������� ��� ������� � ��������
(Uint16)(9),	// ���� �� �����.

// �������� ��������� 2113h, �������=SNR13
6,	// ���-�� �����������
274,	// ����� ������
2,	// ����� ������

//[2113h.01h]
2688,	// ������
275,	// ����� ������, ��������: Scale Number 13
311,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2113h.02h]
19072,	// ������
276,	// ����� ������, ��������: Scale Number 13 Format
312,	// �������� ��� ������� � ��������
(Uint16)(12352),	// ���� �� �����.

//[2113h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
313,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2113h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
314,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2113h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
315,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2113h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
316,	// �������� ��� ������� � ��������
(Uint16)(12),	// ���� �� �����.

// �������� ��������� 2114h, �������=SNR14
6,	// ���-�� �����������
277,	// ����� ������
2,	// ����� ������

//[2114h.01h]
2688,	// ������
278,	// ����� ������, ��������: Scale Number 14
317,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2114h.02h]
19072,	// ������
279,	// ����� ������, ��������: Scale Number 14 Format
318,	// �������� ��� ������� � ��������
(Uint16)(13344),	// ���� �� �����.

//[2114h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
319,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2114h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
320,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

//[2114h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
321,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2114h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
322,	// �������� ��� ������� � ��������
(Uint16)(13),	// ���� �� �����.

// �������� ��������� 2115h, �������=SNR15
6,	// ���-�� �����������
280,	// ����� ������
2,	// ����� ������

//[2115h.01h]
2688,	// ������
281,	// ����� ������, ��������: Scale Number 15
323,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2115h.02h]
19072,	// ������
282,	// ����� ������, ��������: Scale Number 15Format
324,	// �������� ��� ������� � ��������
(Uint16)(10240),	// ���� �� �����.

//[2115h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
325,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2115h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
326,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2115h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
327,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2115h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
328,	// �������� ��� ������� � ��������
(Uint16)(10),	// ���� �� �����.

// �������� ��������� 2116h, �������=SNR16
6,	// ���-�� �����������
283,	// ����� ������
2,	// ����� ������

//[2116h.01h]
2688,	// ������
284,	// ����� ������, ��������: Scale Number 16
329,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2116h.02h]
19072,	// ������
285,	// ����� ������, ��������: Scale Number 16Format
330,	// �������� ��� ������� � ��������
(Uint16)(14400),	// ���� �� �����.

//[2116h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
331,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2116h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
332,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2116h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
333,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2116h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
334,	// �������� ��� ������� � ��������
(Uint16)(14),	// ���� �� �����.

// �������� ��������� 2117h, �������=SNR17
6,	// ���-�� �����������
286,	// ����� ������
2,	// ����� ������

//[2117h.01h]
2688,	// ������
287,	// ����� ������, ��������: Scale Number 17
335,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2117h.02h]
19072,	// ������
288,	// ����� ������, ��������: Scale Number 17Format
336,	// �������� ��� ������� � ��������
(Uint16)(15430),	// ���� �� �����.

//[2117h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
337,	// �������� ��� ������� � ��������
(Uint16)(6),	// ���� �� �����.

//[2117h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
338,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2117h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
339,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2117h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
340,	// �������� ��� ������� � ��������
(Uint16)(15),	// ���� �� �����.

// �������� ��������� 2118h, �������=SNR18
6,	// ���-�� �����������
289,	// ����� ������
2,	// ����� ������

//[2118h.01h]
2688,	// ������
290,	// ����� ������, ��������: Scale Number 18
341,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2118h.02h]
19072,	// ������
291,	// ����� ������, ��������: Scale Number 18Format
342,	// �������� ��� ������� � ��������
(Uint16)(16448),	// ���� �� �����.

//[2118h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
343,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2118h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
344,	// �������� ��� ������� � ��������
(Uint16)(2),	// ���� �� �����.

//[2118h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
345,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2118h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
346,	// �������� ��� ������� � ��������
(Uint16)(16),	// ���� �� �����.

// �������� ��������� 2119h, �������=SNR19
6,	// ���-�� �����������
292,	// ����� ������
2,	// ����� ������

//[2119h.01h]
2688,	// ������
293,	// ����� ������, ��������: Scale Number 19
347,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[2119h.02h]
19072,	// ������
294,	// ����� ������, ��������: Scale Number 19Format
348,	// �������� ��� ������� � ��������
(Uint16)(13312),	// ���� �� �����.

//[2119h.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
349,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2119h.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
350,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2119h.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
351,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[2119h.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
352,	// �������� ��� ������� � ��������
(Uint16)(13),	// ���� �� �����.

// �������� ��������� 211Ah, �������=SNR1A
6,	// ���-�� �����������
295,	// ����� ������
2,	// ����� ������

//[211Ah.01h]
2688,	// ������
296,	// ����� ������, ��������: Scale Number 1A
353,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[211Ah.02h]
19072,	// ������
297,	// ����� ������, ��������: Scale Number 1AFormat
354,	// �������� ��� ������� � ��������
(Uint16)(14336),	// ���� �� �����.

//[211Ah.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
355,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ah.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
356,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ah.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
357,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ah.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
358,	// �������� ��� ������� � ��������
(Uint16)(14),	// ���� �� �����.

// �������� ��������� 211Bh, �������=SNR1B
6,	// ���-�� �����������
298,	// ����� ������
2,	// ����� ������

//[211Bh.01h]
2688,	// ������
299,	// ����� ������, ��������: Scale Number 1B
359,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[211Bh.02h]
19072,	// ������
300,	// ����� ������, ��������: Scale Number 1BFormat
360,	// �������� ��� ������� � ��������
(Uint16)(12384),	// ���� �� �����.

//[211Bh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
361,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Bh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
362,	// �������� ��� ������� � ��������
(Uint16)(3),	// ���� �� �����.

//[211Bh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
363,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Bh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
364,	// �������� ��� ������� � ��������
(Uint16)(12),	// ���� �� �����.

// �������� ��������� 211Ch, �������=SNR1C
6,	// ���-�� �����������
301,	// ����� ������
2,	// ����� ������

//[211Ch.01h]
2688,	// ������
302,	// ����� ������, ��������: Scale Number 1C
365,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[211Ch.02h]
19072,	// ������
303,	// ����� ������, ��������: Scale Number 1C Format
366,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ch.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
367,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ch.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
368,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ch.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
369,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Ch.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
370,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 211Dh, �������=SNR1D
6,	// ���-�� �����������
304,	// ����� ������
2,	// ����� ������

//[211Dh.01h]
2688,	// ������
305,	// ����� ������, ��������: Scale Number 1D
371,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[211Dh.02h]
19072,	// ������
306,	// ����� ������, ��������: Scale Number 1D Format
372,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Dh.03h]
25168,	// ������
216,	// ����� ������, ��������: Scale Number Format Q
373,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Dh.04h]
25125,	// ������
217,	// ����� ������, ��������: Scale Number Format NumOfFloat
374,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Dh.05h]
24631,	// ������
218,	// ����� ������, ��������: Scale Number Format Prefix
375,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

//[211Dh.06h]
24682,	// ������
219,	// ����� ������, ��������: Scale Number Format Units
376,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 2502h, �������=���CAN
4,	// ���-�� �����������
307,	// ����� ������
4,	// ����� ������

//[2502h.01h]
24592,	// ������
308,	// ����� ������, ��������: ����
377,	// �������� ��� ������� � ��������
(Uint16)(256),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[2502h.02h]
24593,	// ������
309,	// ����� ������, ��������: ����
378,	// �������� ��� ������� � ��������
(Uint16)(256),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[2502h.03h]
24594,	// ������
310,	// ����� ������, ��������: �������� ��������� ������
379,	// �������� ��� ������� � ��������
(Uint16)(256),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[2502h.04h]
18944,	// ������
307,	// ����� ������, ��������: ����� ���������� CAN
380,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(1),	// ��������

// �������� ��������� 2506h, �������=interf
4,	// ���-�� �����������
756,	// ����� ������
3,	// ����� ������

//[2506h.01h]
19584,	// ������
581,	// ����� ������, ��������: ������� ������ �����
381,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2506h.02h]
19584,	// ������
582,	// ����� ������, ��������: ������� ������ �����
382,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2506h.03h]
19584,	// ������
754,	// ����� ������, ��������: data_Low
383,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[2506h.04h]
19584,	// ������
753,	// ����� ������, ��������: data_High
384,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[250Fh.00h]
19584,	// ������
311,	// ����� ������, ��������: ���� ��������� �������
385,	// �������� ��� ������� � ��������
(Uint16)(438392299),	// ���� �� �����.
(((Uint32)438392299)>>16),	// ���� �� �����.

// �������� ��������� 2532h, �������=System
3,	// ���-�� �����������
312,	// ����� ������
1,	// ����� ������

//[2532h.01h]
8320,	// ������
313,	// ����� ������, ��������: ��� ������ MCB4
386,	// �������� ��� ������� � ��������

//[2532h.02h]
8328,	// ������
314,	// ����� ������, ��������: ���������� ���� ������
387,	// �������� ��� ������� � ��������

//[2532h.03h]
8208,	// ������
312,	// ����� ������, ��������: ��������� ������
388,	// �������� ��� ������� � ��������

// �������� ��������� 2534h, �������=������. ��
1,	// ���-�� �����������
315,	// ����� ������
2,	// ����� ������

//[2534h.01h]
19072,	// ������
316,	// ����� ������, ��������: ����� ���� ��� ������ ����������
389,	// �������� ��� ������� � ��������
(Uint16)(15),	// ���� �� �����.

// �������� ��������� 2600h, �������=VendorToken
1,	// ���-�� �����������
577,	// ����� ������
3,	// ����� ������

//[2600h.01h]
19584,	// ������
577,	// ����� ������, ��������: VendorToken
390,	// �������� ��� ������� � ��������
(Uint16)(0x33333333),	// ���� �� �����.
(((Uint32)0x33333333)>>16),	// ���� �� �����.

//[2700h.00h]
19072,	// ������
596,	// ����� ������, ��������: Block Transfer Interpreter
391,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.

// �������� ��������� 2701h, �������=CAN programming
15,	// ���-�� �����������
597,	// ����� ������
7,	// ����� ������

//[2701h.01h]
19456,	// ������
598,	// ����� ������, ��������: cmd
392,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.02h]
19456,	// ������
599,	// ����� ������, ��������: status
393,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.03h]
19456,	// ������
600,	// ����� ������, ��������: quest1
394,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.04h]
19456,	// ������
601,	// ����� ������, ��������: quest2
395,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.05h]
19456,	// ������
602,	// ����� ������, ��������: quest3
396,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.06h]
19456,	// ������
603,	// ����� ������, ��������: quest4
397,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.07h]
19456,	// ������
604,	// ����� ������, ��������: ans1
398,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.08h]
19456,	// ������
605,	// ����� ������, ��������: ans2
399,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.09h]
19456,	// ������
606,	// ����� ������, ��������: ans3
400,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Ah]
19456,	// ������
607,	// ����� ������, ��������: ans4
401,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Bh]
19456,	// ������
608,	// ����� ������, ��������: addr
402,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Ch]
19456,	// ������
609,	// ����� ������, ��������: CPU_ID
403,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Dh]
19456,	// ������
610,	// ����� ������, ��������: sector_mask
404,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Eh]
19456,	// ������
611,	// ����� ������, ��������: version
405,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[2701h.0Fh]
19584,	// ������
612,	// ����� ������, ��������: CRC
406,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[3000h.00h]
8288,	// ������
317,	// ����� ������, ��������: ������ ���������������
407,	// �������� ��� ������� � ��������

// �������� ��������� 3100h, �������=System
5,	// ���-�� �����������
312,	// ����� ������
3,	// ����� ������

//[3100h.01h]
3200,	// ������
318,	// ����� ������, ��������: ������� ���������� 1 ���
408,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[3100h.02h]
3200,	// ������
319,	// ����� ������, ��������: ������� ���������� 10 ���
409,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[3100h.03h]
2688,	// ������
320,	// ����� ������, ��������: BackgroundCounter
410,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[3100h.04h]
19584,	// ������
321,	// ����� ������, ��������: T_10���
411,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

//[3100h.05h]
19584,	// ������
322,	// ����� ������, ��������: T_1���
412,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.

// �������� ��������� 5000h, �������=��
3,	// ���-�� �����������
323,	// ����� ������
7,	// ����� ������

//[5000h.01h]
38200,	// ������
324,	// ����� ������, ��������: T ������� �� ��������
413,	// �������� ��� ������� � ��������
(Uint16)(16777216),	// ���� �� �����.
(((Uint32)16777216)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(_IQ(120.0)),	// ��������
(((Uint32)_IQ(120.0))>>16),	// ��������

//[5000h.02h]
5784,	// ������
325,	// ����� ������, ��������: ���� ��
414,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5000h.03h]
5784,	// ������
326,	// ����� ������, ��������: ����� ��
415,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5100h, �������=���_id
13,	// ���-�� �����������
327,	// ����� ������
7,	// ����� ������

//[5100h.01h]
5272,	// ������
328,	// ����� ������, ��������: �������
416,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.02h]
5272,	// ������
329,	// ����� ������, ��������: �������� �����
417,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.03h]
22008,	// ������
330,	// ����� ������, ��������: �������. �����. Kp
418,	// �������� ��� ������� � ��������
(Uint16)(335544),	// ���� �� �����.
(((Uint32)335544)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5100h.04h]
21624,	// ������
331,	// ����� ������, ��������: �������� ������
419,	// �������� ��� ������� � ��������
(Uint16)(16777216),	// ���� �� �����.
(((Uint32)16777216)>>16),	// ���� �� �����.
(Uint16)(_IQ(-1.0)),	// �������
(((Uint32)_IQ(-1.0))>>16),	// �������
(Uint16)(_IQ(1.0)),	// ��������
(((Uint32)_IQ(1.0))>>16),	// ��������

//[5100h.05h]
21624,	// ������
332,	// ����� ������, ��������: ������� ������
420,	// �������� ��� ������� � ��������
(Uint16)(-16777216),	// ���� �� �����.
(((Uint32)-16777216)>>16),	// ���� �� �����.
(Uint16)(_IQ(-1.0)),	// �������
(((Uint32)_IQ(-1.0))>>16),	// �������
(Uint16)(_IQ(1.0)),	// ��������
(((Uint32)_IQ(1.0))>>16),	// ��������

//[5100h.06h]
22008,	// ������
333,	// ����� ������, ��������: ������������ �����. Ki
421,	// �������� ��� ������� � ��������
(Uint16)(2684354),	// ���� �� �����.
(((Uint32)2684354)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5100h.07h]
22008,	// ������
334,	// ����� ������, ��������: ����. �����. Kd
422,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5100h.08h]
22008,	// ������
335,	// ����� ������, ��������: ������.���������.�����������
423,	// �������� ��� ������� � ��������
(Uint16)(8388608),	// ���� �� �����.
(((Uint32)8388608)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5100h.09h]
5272,	// ������
336,	// ����� ������, ��������: ������ ��������������� ��������
424,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.0Ah]
5240,	// ������
337,	// ����� ������, ��������: ����� ����������
425,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.0Bh]
5240,	// ������
338,	// ����� ������, ��������: ���.�������.
426,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.0Ch]
5240,	// ������
339,	// ����� ������, ��������: ���.������.
427,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5100h.0Dh]
5240,	// ������
340,	// ����� ������, ��������: ���.������.
428,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5101h, �������=������
14,	// ���-�� �����������
341,	// ����� ������
7,	// ����� ������

//[5101h.01h]
5784,	// ������
342,	// ����� ������, ��������: �������
429,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.02h]
5784,	// ������
343,	// ����� ������, ��������: �������� �����
430,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.03h]
22008,	// ������
330,	// ����� ������, ��������: �������. �����. Kp
431,	// �������� ��� ������� � ��������
(Uint16)(3355443),	// ���� �� �����.
(((Uint32)3355443)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.04h]
21656,	// ������
331,	// ����� ������, ��������: �������� ������
432,	// �������� ��� ������� � ��������
(Uint16)(13421772),	// ���� �� �����.
(((Uint32)13421772)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.05h]
21656,	// ������
332,	// ����� ������, ��������: ������� ������
433,	// �������� ��� ������� � ��������
(Uint16)(-13421772),	// ���� �� �����.
(((Uint32)-13421772)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.06h]
22008,	// ������
333,	// ����� ������, ��������: ������������ �����. Ki
434,	// �������� ��� ������� � ��������
(Uint16)(16777),	// ���� �� �����.
(((Uint32)16777)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.07h]
22008,	// ������
344,	// ����� ������, ��������: ����. �����. Kd
435,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.08h]
22008,	// ������
335,	// ����� ������, ��������: ������.���������.�����������
436,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5101h.09h]
5784,	// ������
336,	// ����� ������, ��������: ������ ��������������� ��������
437,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.0Ah]
5272,	// ������
345,	// ����� ������, ��������: ����� ����������
438,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.0Bh]
5272,	// ������
338,	// ����� ������, ��������: ���.�������.
439,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.0Ch]
5272,	// ������
339,	// ����� ������, ��������: ���.������.
440,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.0Dh]
5272,	// ������
340,	// ����� ������, ��������: ���.������.
441,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5101h.0Eh]
5272,	// ������
346,	// ����� ������, ��������: ���������� ���������
442,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5102h, �������=���_iq
13,	// ���-�� �����������
347,	// ����� ������
7,	// ����� ������

//[5102h.01h]
5272,	// ������
348,	// ����� ������, ��������: �������
443,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.02h]
5272,	// ������
349,	// ����� ������, ��������: �������� �����
444,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.03h]
22008,	// ������
350,	// ����� ������, ��������: �������. �����. Kp
445,	// �������� ��� ������� � ��������
(Uint16)(335544),	// ���� �� �����.
(((Uint32)335544)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5102h.04h]
21624,	// ������
351,	// ����� ������, ��������: �������� ������
446,	// �������� ��� ������� � ��������
(Uint16)(16777216),	// ���� �� �����.
(((Uint32)16777216)>>16),	// ���� �� �����.
(Uint16)(_IQ(-1.0)),	// �������
(((Uint32)_IQ(-1.0))>>16),	// �������
(Uint16)(_IQ(1.0)),	// ��������
(((Uint32)_IQ(1.0))>>16),	// ��������

//[5102h.05h]
21624,	// ������
352,	// ����� ������, ��������: ������� ������
447,	// �������� ��� ������� � ��������
(Uint16)(-16777216),	// ���� �� �����.
(((Uint32)-16777216)>>16),	// ���� �� �����.
(Uint16)(_IQ(-1.0)),	// �������
(((Uint32)_IQ(-1.0))>>16),	// �������
(Uint16)(_IQ(1.0)),	// ��������
(((Uint32)_IQ(1.0))>>16),	// ��������

//[5102h.06h]
22008,	// ������
353,	// ����� ������, ��������: ������������ �����. Ki
448,	// �������� ��� ������� � ��������
(Uint16)(2684354),	// ���� �� �����.
(((Uint32)2684354)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5102h.07h]
22008,	// ������
354,	// ����� ������, ��������: ����. �����. Kd
449,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5102h.08h]
22008,	// ������
335,	// ����� ������, ��������: ������.���������.�����������
450,	// �������� ��� ������� � ��������
(Uint16)(8388608),	// ���� �� �����.
(((Uint32)8388608)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5102h.09h]
5272,	// ������
336,	// ����� ������, ��������: ������ ��������������� ��������
451,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.0Ah]
5240,	// ������
355,	// ����� ������, ��������: ����� ����������
452,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.0Bh]
5240,	// ������
338,	// ����� ������, ��������: ���.�������.
453,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.0Ch]
5240,	// ������
339,	// ����� ������, ��������: ���.������.
454,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5102h.0Dh]
5240,	// ������
340,	// ����� ������, ��������: ���.������.
455,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5103h, �������=pos_reg
20,	// ���-�� �����������
356,	// ����� ������
7,	// ����� ������

//[5103h.01h]
19840,	// ������
342,	// ����� ������, ��������: �������
456,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.02h]
22136,	// ������
342,	// ����� ������, ��������: �������
457,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.03h]
5752,	// ������
343,	// ����� ������, ��������: �������� �����
458,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.04h]
3456,	// ������
343,	// ����� ������, ��������: �������� �����
459,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.05h]
22008,	// ������
330,	// ����� ������, ��������: �������. �����. Kp
460,	// �������� ��� ������� � ��������
(Uint16)(1174405120),	// ���� �� �����.
(((Uint32)1174405120)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.06h]
22168,	// ������
331,	// ����� ������, ��������: �������� ������
461,	// �������� ��� ������� � ��������
(Uint16)(100663296),	// ���� �� �����.
(((Uint32)100663296)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.07h]
22168,	// ������
332,	// ����� ������, ��������: ������� ������
462,	// �������� ��� ������� � ��������
(Uint16)(-100663296),	// ���� �� �����.
(((Uint32)-100663296)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.08h]
22008,	// ������
333,	// ����� ������, ��������: ������������ �����. Ki
463,	// �������� ��� ������� � ��������
(Uint16)(83886),	// ���� �� �����.
(((Uint32)83886)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.09h]
22008,	// ������
344,	// ����� ������, ��������: ����. �����. Kd
464,	// �������� ��� ������� � ��������
(Uint16)(167772160),	// ���� �� �����.
(((Uint32)167772160)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.0Ah]
19840,	// ������
357,	// ����� ������, ��������: �����. ����. �����
465,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.0Bh]
22008,	// ������
358,	// ����� ������, ��������: ����. �������
466,	// �������� ��� ������� � ��������
(Uint16)(8388608),	// ���� �� �����.
(((Uint32)8388608)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.0Ch]
22008,	// ������
335,	// ����� ������, ��������: ������.���������.�����������
467,	// �������� ��� ������� � ��������
(Uint16)(8388608),	// ���� �� �����.
(((Uint32)8388608)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.0Dh]
22136,	// ������
359,	// ����� ������, ��������: ������� ����
468,	// �������� ��� ������� � ��������
(Uint16)(13981),	// ���� �� �����.
(((Uint32)13981)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5103h.0Eh]
5752,	// ������
336,	// ����� ������, ��������: ������ ��������������� ��������
469,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.0Fh]
5624,	// ������
346,	// ����� ������, ��������: ���������� ���������
470,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.10h]
5784,	// ������
345,	// ����� ������, ��������: ����� ����������
471,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.11h]
5784,	// ������
338,	// ����� ������, ��������: ���.�������.
472,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.12h]
5784,	// ������
339,	// ����� ������, ��������: ���.������.
473,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.13h]
5784,	// ������
340,	// ����� ������, ��������: ���.������.
474,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5103h.14h]
5752,	// ������
360,	// ����� ������, ��������: ������ ������
475,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5105h, �������=���
17,	// ���-�� �����������
362,	// ����� ������
7,	// ����� ������

//[5105h.01h]
5240,	// ������
363,	// ����� ������, ��������: Ua���
476,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.02h]
5240,	// ������
364,	// ����� ������, ��������: Ub���
477,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.03h]
21528,	// ������
365,	// ����� ������, ��������: U_���
478,	// �������� ��� ������� � ��������
(Uint16)(14529069),	// ���� �� �����.
(((Uint32)14529069)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0x01000000),	// ��������
(((Uint32)0x01000000)>>16),	// ��������

//[5105h.04h]
2688,	// ������
366,	// ����� ������, ��������: GammaA
479,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.05h]
2688,	// ������
367,	// ����� ������, ��������: GammaB
480,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.06h]
2688,	// ������
368,	// ����� ������, ��������: GammaC
481,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.07h]
2688,	// ������
369,	// ����� ������, ��������: TPWM
482,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.08h]
24056,	// ������
370,	// ����� ������, ��������: ������� ����� (���)
483,	// �������� ��� ������� � ��������
(Uint16)(3355443),	// ���� �� �����.
(((Uint32)3355443)>>16),	// ���� �� �����.
(Uint16)(_IQ(2.0)),	// �������
(((Uint32)_IQ(2.0))>>16),	// �������
(Uint16)(_IQ(10.0)),	// ��������
(((Uint32)_IQ(10.0))>>16),	// ��������

//[5105h.09h]
24056,	// ������
371,	// ����� ������, ��������: ����������� ���. ������.
484,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(_IQ(10)),	// ��������
(((Uint32)_IQ(10))>>16),	// ��������

//[5105h.0Ah]
21528,	// ������
372,	// ����� ������, ��������: ����. ����������� Ud
485,	// �������� ��� ������� � ��������
(Uint16)(16777216),	// ���� �� �����.
(((Uint32)16777216)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5105h.0Bh]
24592,	// ������
373,	// ����� ������, ��������: ����������� Ud
486,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.0Ch]
24592,	// ������
374,	// ����� ������, ��������: ��� ���
487,	// �������� ��� ������� � ��������
(Uint16)(257),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.0Dh]
2816,	// ������
375,	// ����� ������, ��������: ULimitation
488,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.0Eh]
21994,	// ������
376,	// ����� ������, ��������: ������� ���
489,	// �������� ��� ������� � ��������
(Uint16)(20480),	// ���� �� �����.
(((Uint32)20480)>>16),	// ���� �� �����.
(Uint16)(2048),	// �������
(((Uint32)2048)>>16),	// �������
(Uint16)(10240),	// ��������
(((Uint32)10240)>>16),	// ��������

//[5105h.0Fh]
2944,	// ������
377,	// ����� ������, ��������: ������
490,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.10h]
5240,	// ������
378,	// ����� ������, ��������: U_����
491,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5105h.11h]
2688,	// ������
379,	// ����� ������, ��������: ����� ������
492,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 510Bh, �������=smctrl
2,	// ���-�� �����������
380,	// ����� ������
2,	// ����� ������

//[510Bh.01h]
2944,	// ������
381,	// ����� ������, ��������: sm_state
493,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.

//[510Bh.02h]
24704,	// ������
382,	// ����� ������, ��������: drv_status_code
494,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.

// �������� ��������� 510Eh, �������=������
11,	// ���-�� �����������
383,	// ����� ������
7,	// ����� ������

//[510Eh.01h]
19072,	// ������
384,	// ����� ������, ��������: ����� ������ 1
495,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.02h]
19072,	// ������
385,	// ����� ������, ��������: ����� ������ 2
496,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.03h]
24960,	// ������
386,	// ����� ������, ��������: ����� ������ 1L
497,	// �������� ��� ������� � ��������
(Uint16)(255),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.04h]
24968,	// ������
387,	// ����� ������, ��������: ����� ������ 1H
498,	// �������� ��� ������� � ��������
(Uint16)(255),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.05h]
24960,	// ������
388,	// ����� ������, ��������: ����� ������ 2L
499,	// �������� ��� ������� � ��������
(Uint16)(255),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.06h]
24968,	// ������
389,	// ����� ������, ��������: ����� ������  2H
500,	// �������� ��� ������� � ��������
(Uint16)(255),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[510Eh.07h]
21656,	// ������
390,	// ����� ������, ��������: ������������ ���
501,	// �������� ��� ������� � ��������
(Uint16)(16777216),	// ���� �� �����.
(((Uint32)16777216)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[510Eh.08h]
21752,	// ������
391,	// ����� ������, ��������: ������������ ����������
502,	// �������� ��� ������� � ��������
(Uint16)(18454938),	// ���� �� �����.
(((Uint32)18454938)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[510Eh.09h]
21752,	// ������
392,	// ����� ������, ��������: ����������� ����������
503,	// �������� ��� ������� � ��������
(Uint16)(6990506),	// ���� �� �����.
(((Uint32)6990506)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[510Eh.0Ah]
22168,	// ������
393,	// ����� ������, ��������: ������������ ��������
504,	// �������� ��� ������� � ��������
(Uint16)(100663296),	// ���� �� �����.
(((Uint32)100663296)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[510Eh.0Bh]
21848,	// ������
639,	// ����� ������, ��������: ������������ �����������
505,	// �������� ��� ������� � ��������
(Uint16)(75497472),	// ���� �� �����.
(((Uint32)75497472)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

// �������� ��������� 5112h, �������=������
5,	// ���-�� �����������
394,	// ����� ������
7,	// ����� ������

//[5112h.01h]
22168,	// ������
395,	// ����� ������, ��������: ��������
506,	// �������� ��� ������� � ��������
(Uint16)(335544),	// ���� �� �����.
(((Uint32)335544)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5112h.02h]
21656,	// ������
396,	// ����� ������, ��������: ����. ��� ��
507,	// �������� ��� ������� � ��������
(Uint16)(3355443),	// ���� �� �����.
(((Uint32)3355443)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5112h.03h]
21656,	// ������
397,	// ����� ������, ��������: ��� ���������
508,	// �������� ��� ������� � ��������
(Uint16)(3355443),	// ���� �� �����.
(((Uint32)3355443)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5112h.04h]
22136,	// ������
398,	// ����� ������, ��������: theta_elec
509,	// �������� ��� ������� � ��������
(Uint16)(720992),	// ���� �� �����.
(((Uint32)720992)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5112h.05h]
21752,	// ������
559,	// ����� ������, ��������: �������� ���������� ��
510,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

// �������� ��������� 5113h, �������=�����
9,	// ���-�� �����������
399,	// ����� ������
7,	// ����� ������

//[5113h.01h]
19200,	// ������
400,	// ����� ������, ��������: ����� ��� �������
511,	// �������� ��� ������� � ��������
(Uint16)(4),	// ���� �� �����.
(Uint16)(1),	// �������
(Uint16)(50),	// ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.02h]
20928,	// ������
401,	// ����� ������, ��������: ����������� ���
512,	// �������� ��� ������� � ��������
(Uint16)(5),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.03h]
4512,	// ������
402,	// ����� ������, ��������: ����������� ���������� ����.
513,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.04h]
21280,	// ������
403,	// ����� ������, ��������: ����������� ��������
514,	// �������� ��� ������� � ��������
(Uint16)(500),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.05h]
20896,	// ������
404,	// ����� ������, ��������: ����������� ���������� ���
515,	// �������� ��� ������� � ��������
(Uint16)(36),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(1000),	// ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.06h]
22264,	// ������
405,	// ����� ������, ��������: Rs
516,	// �������� ��� ������� � ��������
(Uint16)(1048576),	// ���� �� �����.
(((Uint32)1048576)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5113h.07h]
22296,	// ������
406,	// ����� ������, ��������: Ls
517,	// �������� ��� ������� � ��������
(Uint16)(16777),	// ���� �� �����.
(((Uint32)16777)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5113h.08h]
4608,	// ������
407,	// ����� ������, ��������: ����������� �������
518,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5113h.09h]
24624,	// ������
408,	// ����� ������, ��������: ��� ������� ���������
519,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5114h, �������=������
4,	// ���-�� �����������
409,	// ����� ������
4,	// ����� ������

//[5114h.01h]
8320,	// ������
410,	// ����� ������, ��������: ��� ���������� �����
520,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5114h.02h]
19072,	// ������
411,	// ����� ������, ��������: ����� ������
521,	// �������� ��� ������� � ��������
(Uint16)(4),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5114h.03h]
19072,	// ������
413,	// ����� ������, ��������: ��� ���� ����.
522,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5114h.04h]
18944,	// ������
414,	// ����� ������, ��������: ������������
523,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(1),	// ��������

// �������� ��������� 5116h, �������=���
20,	// ���-�� �����������
415,	// ����� ������
4,	// ����� ������

//[5116h.01h]
20928,	// ������
416,	// ����� ������, ��������: ����������� ���� ���� �
524,	// �������� ��� ������� � ��������
(Uint16)(40),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.02h]
20480,	// ������
417,	// ����� ������, ��������: �������� ���� ���� �
525,	// �������� ��� ������� � ��������
(Uint16)(62706),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.03h]
5272,	// ������
418,	// ����� ������, ��������: ��� ���� �
526,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.04h]
20928,	// ������
419,	// ����� ������, ��������: ����������� ���� ���� �
527,	// �������� ��� ������� � ��������
(Uint16)(40),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.05h]
20480,	// ������
420,	// ����� ������, ��������: �������� ���� ���� �
528,	// �������� ��� ������� � ��������
(Uint16)(62251),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.06h]
5272,	// ������
421,	// ����� ������, ��������: ��� ���� �
529,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.07h]
20928,	// ������
422,	// ����� ������, ��������: ����������� ���� ���� C
530,	// �������� ��� ������� � ��������
(Uint16)(40),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.08h]
20480,	// ������
423,	// ����� ������, ��������: �������� ���� ���� C
531,	// �������� ��� ������� � ��������
(Uint16)(62836),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.09h]
5272,	// ������
424,	// ����� ������, ��������: ��� ���� �
532,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.0Ah]
20928,	// ������
585,	// ����� ������, ��������: ����������� ���� ���� D
533,	// �������� ��� ������� � ��������
(Uint16)(40),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.0Bh]
20480,	// ������
586,	// ����� ������, ��������: �������� ���� ���� D
534,	// �������� ��� ������� � ��������
(Uint16)(62836),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.0Ch]
5272,	// ������
587,	// ����� ������, ��������: ��� ���� D
535,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.0Dh]
20896,	// ������
425,	// ����� ������, ��������: ����������� ���������� ���
536,	// �������� ��� ������� � ��������
(Uint16)(66),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.0Eh]
20480,	// ������
426,	// ����� ������, ��������: �������� ������. ���
537,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.0Fh]
5368,	// ������
427,	// ����� ������, ��������: ���������� ���
538,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.10h]
21344,	// ������
633,	// ����� ������, ��������: ����������� �����������
539,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.11h]
5464,	// ������
634,	// ����� ������, ��������: �����������
540,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5116h.12h]
20480,	// ������
642,	// ����� ������, ��������: ����������� �������� �����
541,	// �������� ��� ������� � ��������
(Uint16)(100),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.13h]
20480,	// ������
643,	// ����� ������, ��������: �������� �������� �����
542,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(Uint16)(0),	// �������
(Uint16)(0),	// ��������

//[5116h.14h]
5176,	// ������
641,	// ����� ������, ��������: ������� ���������� ���� 1
543,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 511Ah, �������=����� U(f) (��)
7,	// ���-�� �����������
428,	// ����� ������
7,	// ����� ������

//[511Ah.01h]
5784,	// ������
429,	// ����� ������, ��������: �������� �������
544,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[511Ah.02h]
5240,	// ������
430,	// ����� ������, ��������: �������� ����������
545,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[511Ah.03h]
22168,	// ������
431,	// ����� ������, ��������: ������� ������� �������
546,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[511Ah.04h]
21624,	// ������
432,	// ����� ������, ��������: ������� ������� ����������
547,	// �������� ��� ������� � ��������
(Uint16)(419430),	// ���� �� �����.
(((Uint32)419430)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[511Ah.05h]
22168,	// ������
433,	// ����� ������, ��������: ������ ������� �������
548,	// �������� ��� ������� � ��������
(Uint16)(100663296),	// ���� �� �����.
(((Uint32)100663296)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[511Ah.06h]
21624,	// ������
434,	// ����� ������, ��������: ������ ������� ����������
549,	// �������� ��� ������� � ��������
(Uint16)(12582912),	// ���� �� �����.
(((Uint32)12582912)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[511Ah.07h]
22168,	// ������
435,	// ����� ������, ��������: ������������ �������
550,	// �������� ��� ������� � ��������
(Uint16)(100663296),	// ���� �� �����.
(((Uint32)100663296)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

// �������� ��������� 5138h, �������=������
7,	// ���-�� �����������
436,	// ����� ������
1,	// ����� ������

//[5138h.01h]
5784,	// ������
437,	// ����� ������, ��������: ��������
551,	// �������� ��� ������� � ��������

//[5138h.02h]
5400,	// ������
438,	// ����� ������, ��������: ���. ��������
552,	// �������� ��� ������� � ��������

//[5138h.03h]
5272,	// ������
439,	// ����� ������, ��������: ��� �������
553,	// �������� ��� ������� � ��������

//[5138h.04h]
5752,	// ������
440,	// ����� ������, ��������: ���������
554,	// �������� ��� ������� � ��������

//[5138h.05h]
5752,	// ������
441,	// ����� ������, ��������: ������
555,	// �������� ��� ������� � ��������

//[5138h.06h]
5272,	// ������
442,	// ����� ������, ��������: ��� ������� ���
556,	// �������� ��� ������� � ��������

//[5138h.07h]
7520,	// ������
613,	// ����� ������, ��������: ����� ����������� ���������, ���
557,	// �������� ��� ������� � ��������

// �������� ��������� 5150h, �������=dlog
11,	// ���-�� �����������
443,	// ����� ������
7,	// ����� ������

//[5150h.01h]
19072,	// ������
444,	// ����� ������, ��������: dlog.mode_reset
558,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.02h]
19584,	// ������
445,	// ����� ������, ��������: dlog.control
559,	// �������� ��� ������� � ��������
(Uint16)(192),	// ���� �� �����.
(((Uint32)192)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.03h]
19584,	// ������
446,	// ����� ������, ��������: dlog.ind_subind1
560,	// �������� ��� ������� � ��������
(Uint16)(1359151123),	// ���� �� �����.
(((Uint32)1359151123)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.04h]
19584,	// ������
447,	// ����� ������, ��������: dlog.ind_subind2
561,	// �������� ��� ������� � ��������
(Uint16)(1359085569),	// ���� �� �����.
(((Uint32)1359085569)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.05h]
19584,	// ������
448,	// ����� ������, ��������: dlog.ind_subind3
562,	// �������� ��� ������� � ��������
(Uint16)(1359151122),	// ���� �� �����.
(((Uint32)1359151122)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.06h]
19584,	// ������
449,	// ����� ������, ��������: dlog.ind_subind4
563,	// �������� ��� ������� � ��������
(Uint16)(1359020033),	// ���� �� �����.
(((Uint32)1359020033)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.07h]
24960,	// ������
450,	// ����� ������, ��������: StartBitL
564,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.08h]
24968,	// ������
451,	// ����� ������, ��������: StartBitH
565,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.09h]
24592,	// ������
452,	// ����� ������, ��������: OneShotOperation
566,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5150h.0Ah]
23608,	// ������
453,	// ����� ������, ��������: ���������� ����� �����������
567,	// �������� ��� ������� � ��������
(Uint16)(6710886),	// ���� �� �����.
(((Uint32)6710886)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5150h.0Bh]
3200,	// ������
644,	// ����� ������, ��������: ������� ����������
568,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5151h.00h]
19840,	// ������
454,	// ����� ������, ��������: dlog.next_value_var
569,	// �������� ��� ������� � ��������
(Uint16)(50461787),	// ���� �� �����.
(((Uint32)50461787)>>16),	// ���� �� �����.

// �������� ��������� 5152h, �������=�������
8,	// ���-�� �����������
455,	// ����� ������
3,	// ����� ������

//[5152h.01h]
19584,	// ������
456,	// ����� ������, ��������: ���-�� ��������
570,	// �������� ��� ������� � ��������
(Uint16)(2500),	// ���� �� �����.
(((Uint32)2500)>>16),	// ���� �� �����.

//[5152h.02h]
24594,	// ������
457,	// ����� ������, ��������: ������� ������
571,	// �������� ��� ������� � ��������
(Uint16)(1),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.03h]
3200,	// ������
460,	// ����� ������, ��������: ����������.���� � ������
572,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.04h]
5784,	// ������
461,	// ����� ������, ��������: ��������
573,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.05h]
5752,	// ������
462,	// ����� ������, ��������: ����. ������.
574,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.06h]
5752,	// ������
463,	// ����� ������, ��������: ���� ���.
575,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.07h]
2688,	// ������
467,	// ����� ������, ��������: GPIOsValue
576,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5152h.08h]
19328,	// ������
471,	// ����� ������, ��������: ����� ��������
577,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5155h, �������=������ �����
21,	// ���-�� �����������
475,	// ����� ������
7,	// ����� ������

//[5155h.01h]
5752,	// ������
441,	// ����� ������, ��������: ������
578,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.02h]
5784,	// ������
461,	// ����� ������, ��������: ��������
579,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.03h]
22168,	// ������
476,	// ����� ������, ��������: ������� ��������
580,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5155h.04h]
5752,	// ������
477,	// ����� ������, ��������: ������6
581,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.05h]
24592,	// ������
478,	// ����� ������, ��������: ���-������� ���
582,	// �������� ��� ������� � ��������
(Uint16)(81),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.06h]
19584,	// ������
479,	// ����� ������, ��������: ������� ��������� ��������
583,	// �������� ��� ������� � ��������
(Uint16)(500),	// ���� �� �����.
(((Uint32)500)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.07h]
5784,	// ������
480,	// ����� ������, ��������: �������� ���.
584,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.08h]
2688,	// ������
481,	// ����� ������, ��������: ������ ������
585,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.09h]
8496,	// ������
482,	// ����� ������, ��������: ���������� �����
586,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.0Ah]
22136,	// ������
459,	// ����� ������, ��������: ��������
587,	// �������� ��� ������� � ��������
(Uint16)(4869970),	// ���� �� �����.
(((Uint32)4869970)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5155h.0Bh]
2688,	// ������
483,	// ����� ������, ��������: ������� �����
588,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.0Ch]
2688,	// ������
484,	// ����� ������, ��������: ������ 1 ������
589,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.0Dh]
2688,	// ������
485,	// ����� ������, ��������: ������ 2 ������
590,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.0Eh]
2688,	// ������
486,	// ����� ������, ��������: ������ 3 ������
591,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.0Fh]
24850,	// ������
487,	// ����� ������, ��������: ����������� ��������
592,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.10h]
19072,	// ������
488,	// ����� ������, ��������: ����.����� ������ ���
593,	// �������� ��� ������� � ��������
(Uint16)(10),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.11h]
2688,	// ������
489,	// ����� ������, ��������: ���-�� ������ �������� ������������������
594,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.12h]
2688,	// ������
490,	// ����� ������, ��������: ������� ���������� �� ������
595,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.13h]
2688,	// ������
491,	// ����� ������, ��������: ������� ���������� CAP1
596,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.14h]
2688,	// ������
492,	// ����� ������, ��������: ������� ���������� CAP2
597,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5155h.15h]
2688,	// ������
493,	// ����� ������, ��������: ������� ���������� CAP3
598,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5174h, �������=��� �������
16,	// ���-�� �����������
497,	// ����� ������
7,	// ����� ������

//[5174h.01h]
5624,	// ������
498,	// ����� ������, ��������: DebugL1
599,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.02h]
3456,	// ������
498,	// ����� ������, ��������: DebugL1
600,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.03h]
5624,	// ������
499,	// ����� ������, ��������: DebugL2
601,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.04h]
3456,	// ������
499,	// ����� ������, ��������: DebugL2
602,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.05h]
2688,	// ������
500,	// ����� ������, ��������: DebugI3
603,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.06h]
2944,	// ������
500,	// ����� ������, ��������: DebugI3
604,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.07h]
2688,	// ������
501,	// ����� ������, ��������: DebugI4
605,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.08h]
2944,	// ������
501,	// ����� ������, ��������: DebugI4
606,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.09h]
22008,	// ������
502,	// ����� ������, ��������: DebugW1
607,	// �������� ��� ������� � ��������
(Uint16)(16777),	// ���� �� �����.
(((Uint32)16777)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5174h.0Ah]
19840,	// ������
502,	// ����� ������, ��������: DebugW1
608,	// �������� ��� ������� � ��������
(Uint16)(16777),	// ���� �� �����.
(((Uint32)16777)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.0Bh]
22008,	// ������
503,	// ����� ������, ��������: DebugW2
609,	// �������� ��� ������� � ��������
(Uint16)(-190048),	// ���� �� �����.
(((Uint32)-190048)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5174h.0Ch]
19840,	// ������
503,	// ����� ������, ��������: DebugW2
610,	// �������� ��� ������� � ��������
(Uint16)(-190048),	// ���� �� �����.
(((Uint32)-190048)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.0Dh]
22008,	// ������
504,	// ����� ������, ��������: DebugW3
611,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5174h.0Eh]
19840,	// ������
504,	// ����� ������, ��������: DebugW3
612,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5174h.0Fh]
22008,	// ������
505,	// ����� ������, ��������: DebugW4
613,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5174h.10h]
19840,	// ������
505,	// ����� ������, ��������: DebugW4
614,	// �������� ��� ������� � ��������
(Uint16)(0),	// ���� �� �����.
(((Uint32)0)>>16),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

// �������� ��������� 5B05h, �������=smooth_charge
6,	// ���-�� �����������
626,	// ����� ������
7,	// ����� ������

//[5B05h.01h]
2176,	// ������
631,	// ����� ������, ��������: ������� ��������� ����
615,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5B05h.02h]
19072,	// ������
627,	// ����� ������, ��������: ������� ��������� ����, ��
616,	// �������� ��� ������� � ��������
(Uint16)(2000),	// ���� �� �����.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5B05h.03h]
23800,	// ������
628,	// ����� ������, ��������: ���������� ���������, �
617,	// �������� ��� ������� � ��������
(Uint16)(15099494),	// ���� �� �����.
(((Uint32)15099494)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5B05h.04h]
23800,	// ������
629,	// ����� ������, ��������: ���������� ����������, �
618,	// �������� ��� ������� � ��������
(Uint16)(11744051),	// ���� �� �����.
(((Uint32)11744051)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5B05h.05h]
5624,	// ������
630,	// ����� ������, ��������: ����������� ���������� ���
619,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5B05h.06h]
22008,	// ������
632,	// ����� ������, ��������: ������� �� ����������� ���
620,	// �������� ��� ������� � ��������
(Uint16)(8388608),	// ���� �� �����.
(((Uint32)8388608)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

// �������� ��������� 5B06h, �������=cool_syst
4,	// ���-�� �����������
635,	// ����� ������
7,	// ����� ������

//[5B06h.01h]
2688,	// ������
636,	// ����� ������, ��������: ������� ��������� �����������
621,	// �������� ��� ������� � ��������
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.
0,	// ����������� ����� ��� ������. ������. ������.

//[5B06h.02h]
21848,	// ������
637,	// ����� ������, ��������: ����������� ��������� �����������
622,	// �������� ��� ������� � ��������
(Uint16)(41943040),	// ���� �� �����.
(((Uint32)41943040)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5B06h.03h]
21848,	// ������
638,	// ����� ������, ��������: ����������� ���������� �����������
623,	// �������� ��� ������� � ��������
(Uint16)(25165824),	// ���� �� �����.
(((Uint32)25165824)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������

//[5B06h.04h]
21848,	// ������
640,	// ����� ������, ��������: ����������� ������ �������������� � ���������
624,	// �������� ��� ������� � ��������
(Uint16)(67108864),	// ���� �� �����.
(((Uint32)67108864)>>16),	// ���� �� �����.
(Uint16)(0),	// �������
(((Uint32)0)>>16),	// �������
(Uint16)(0),	// ��������
(((Uint32)0)>>16),	// ��������
};

// ������� ������������ ������� � �������� ��� ������� � ��������
int16 const CO1_OD_TBL1[] = { 
4096,	// ������
0,	// �������� ��� ������� � ��������
4097,	// ������
3,	// �������� ��� ������� � ��������
4098,	// ������
6,	// �������� ��� ������� � ��������
4116,	// ������
9,	// �������� ��� ������� � ��������
4118,	// ������
12,	// �������� ��� ������� � ��������
4119,	// ������
20,	// �������� ��� ������� � ��������
4120,	// ������
24,	// �������� ��� ������� � ��������
4608,	// ������
39,	// �������� ��� ������� � ��������
4736,	// ������
48,	// �������� ��� ������� � ��������
5120,	// ������
60,	// �������� ��� ������� � ��������
5121,	// ������
73,	// �������� ��� ������� � ��������
5122,	// ������
86,	// �������� ��� ������� � ��������
5123,	// ������
99,	// �������� ��� ������� � ��������
5124,	// ������
112,	// �������� ��� ������� � ��������
5125,	// ������
125,	// �������� ��� ������� � ��������
5126,	// ������
138,	// �������� ��� ������� � ��������
5127,	// ������
151,	// �������� ��� ������� � ��������
5632,	// ������
164,	// �������� ��� ������� � ��������
5633,	// ������
187,	// �������� ��� ������� � ��������
5634,	// ������
210,	// �������� ��� ������� � ��������
5635,	// ������
233,	// �������� ��� ������� � ��������
5636,	// ������
256,	// �������� ��� ������� � ��������
5637,	// ������
279,	// �������� ��� ������� � ��������
5638,	// ������
302,	// �������� ��� ������� � ��������
5639,	// ������
325,	// �������� ��� ������� � ��������
6144,	// ������
348,	// �������� ��� ������� � ��������
6145,	// ������
371,	// �������� ��� ������� � ��������
6146,	// ������
394,	// �������� ��� ������� � ��������
6147,	// ������
417,	// �������� ��� ������� � ��������
6148,	// ������
440,	// �������� ��� ������� � ��������
6149,	// ������
463,	// �������� ��� ������� � ��������
6150,	// ������
486,	// �������� ��� ������� � ��������
6151,	// ������
509,	// �������� ��� ������� � ��������
6656,	// ������
532,	// �������� ��� ������� � ��������
6657,	// ������
555,	// �������� ��� ������� � ��������
6658,	// ������
578,	// �������� ��� ������� � ��������
6659,	// ������
601,	// �������� ��� ������� � ��������
6660,	// ������
624,	// �������� ��� ������� � ��������
6661,	// ������
647,	// �������� ��� ������� � ��������
6662,	// ������
670,	// �������� ��� ������� � ��������
6663,	// ������
693,	// �������� ��� ������� � ��������
8192,	// ������
716,	// �������� ��� ������� � ��������
8193,	// ������
722,	// �������� ��� ������� � ��������
8194,	// ������
726,	// �������� ��� ������� � ��������
8195,	// ������
741,	// �������� ��� ������� � ��������
8196,	// ������
756,	// �������� ��� ������� � ��������
8197,	// ������
761,	// �������� ��� ������� � ��������
8199,	// ������
764,	// �������� ��� ������� � ��������
8208,	// ������
779,	// �������� ��� ������� � ��������
8209,	// ������
794,	// �������� ��� ������� � ��������
8210,	// ������
817,	// �������� ��� ������� � ��������
8212,	// ������
821,	// �������� ��� ������� � ��������
8213,	// ������
825,	// �������� ��� ������� � ��������
8214,	// ������
828,	// �������� ��� ������� � ��������
8215,	// ������
831,	// �������� ��� ������� � ��������
8320,	// ������
834,	// �������� ��� ������� � ��������
8321,	// ������
893,	// �������� ��� ������� � ��������
8322,	// ������
896,	// �������� ��� ������� � ��������
8323,	// ������
909,	// �������� ��� ������� � ��������
8448,	// ������
976,	// �������� ��� ������� � ��������
8449,	// ������
1003,	// �������� ��� ������� � ��������
8450,	// ������
1030,	// �������� ��� ������� � ��������
8451,	// ������
1057,	// �������� ��� ������� � ��������
8452,	// ������
1084,	// �������� ��� ������� � ��������
8453,	// ������
1111,	// �������� ��� ������� � ��������
8454,	// ������
1138,	// �������� ��� ������� � ��������
8455,	// ������
1165,	// �������� ��� ������� � ��������
8456,	// ������
1192,	// �������� ��� ������� � ��������
8457,	// ������
1219,	// �������� ��� ������� � ��������
8458,	// ������
1246,	// �������� ��� ������� � ��������
8459,	// ������
1273,	// �������� ��� ������� � ��������
8460,	// ������
1300,	// �������� ��� ������� � ��������
8461,	// ������
1327,	// �������� ��� ������� � ��������
8462,	// ������
1354,	// �������� ��� ������� � ��������
8463,	// ������
1381,	// �������� ��� ������� � ��������
8464,	// ������
1408,	// �������� ��� ������� � ��������
8465,	// ������
1435,	// �������� ��� ������� � ��������
8466,	// ������
1462,	// �������� ��� ������� � ��������
8467,	// ������
1489,	// �������� ��� ������� � ��������
8468,	// ������
1516,	// �������� ��� ������� � ��������
8469,	// ������
1543,	// �������� ��� ������� � ��������
8470,	// ������
1570,	// �������� ��� ������� � ��������
8471,	// ������
1597,	// �������� ��� ������� � ��������
8472,	// ������
1624,	// �������� ��� ������� � ��������
8473,	// ������
1651,	// �������� ��� ������� � ��������
8474,	// ������
1678,	// �������� ��� ������� � ��������
8475,	// ������
1705,	// �������� ��� ������� � ��������
8476,	// ������
1732,	// �������� ��� ������� � ��������
8477,	// ������
1759,	// �������� ��� ������� � ��������
9474,	// ������
1786,	// �������� ��� ������� � ��������
9478,	// ������
1813,	// �������� ��� ������� � ��������
9487,	// ������
1836,	// �������� ��� ������� � ��������
9522,	// ������
1841,	// �������� ��� ������� � ��������
9524,	// ������
1853,	// �������� ��� ������� � ��������
9728,	// ������
1860,	// �������� ��� ������� � ��������
9984,	// ������
1868,	// �������� ��� ������� � ��������
9985,	// ������
1872,	// �������� ��� ������� � ��������
12288,	// ������
2010,	// �������� ��� ������� � ��������
12544,	// ������
2013,	// �������� ��� ������� � ��������
20480,	// ������
2041,	// �������� ��� ������� � ��������
20736,	// ������
2071,	// �������� ��� ������� � ��������
20737,	// ������
2191,	// �������� ��� ������� � ��������
20738,	// ������
2320,	// �������� ��� ������� � ��������
20739,	// ������
2440,	// �������� ��� ������� � ��������
20741,	// ������
2623,	// �������� ��� ������� � ��������
20747,	// ������
2779,	// �������� ��� ������� � ��������
20750,	// ������
2790,	// �������� ��� ������� � ��������
20754,	// ������
2892,	// �������� ��� ������� � ��������
20755,	// ������
2940,	// �������� ��� ������� � ��������
20756,	// ������
3024,	// �������� ��� ������� � ��������
20758,	// ������
3051,	// �������� ��� ������� � ��������
20762,	// ������
3174,	// �������� ��� ������� � ��������
20792,	// ������
3240,	// �������� ��� ������� � ��������
20816,	// ������
3264,	// �������� ��� ������� � ��������
20817,	// ������
3366,	// �������� ��� ������� � ��������
20818,	// ������
3371,	// �������� ��� ������� � ��������
20821,	// ������
3414,	// �������� ��� ������� � ��������
20852,	// ������
3606,	// �������� ��� ������� � ��������
23301,	// ������
3753,	// �������� ��� ������� � ��������
23302,	// ������
3810,	// �������� ��� ������� � ��������
};
Uint16 const co1_SPIrange1rw = CO1_SPI_START_ADDR+0;
Uint16 const co1_SPIrange1rwCRC = CO1_SPI_START_ADDR+8;
Uint16 const co1_SPIrange1rwp = CO1_SPI_START_ADDR+10;
Uint16 const co1_SPIrange1rwpCRC = CO1_SPI_START_ADDR+336;
Uint16 const co1_SPIrange1rwps = CO1_SPI_START_ADDR+338;
Uint16 const co1_SPIrange1rwpsCRC = CO1_SPI_START_ADDR+338;
Uint16 const co1_SPIrange2rw = CO1_SPI_START_ADDR+340;
Uint16 const co1_SPIrange2rwCRC = CO1_SPI_START_ADDR+643;
Uint16 const co1_SPIrange2rwp = CO1_SPI_START_ADDR+645;
Uint16 const co1_SPIrange2rwpCRC = CO1_SPI_START_ADDR+670;
Uint16 const co1_SPIrange2rwps = CO1_SPI_START_ADDR+672;
Uint16 const co1_SPIrange2rwpsCRC = CO1_SPI_START_ADDR+672;
Uint16 const co1_SPIrange3rw = CO1_SPI_START_ADDR+674;
Uint16 const co1_SPIrange3rwCRC = CO1_SPI_START_ADDR+682;
Uint16 const co1_SPIrange3rwp = CO1_SPI_START_ADDR+684;
Uint16 const co1_SPIrange3rwpCRC = CO1_SPI_START_ADDR+684;
Uint16 const co1_SPIrange3rwps = CO1_SPI_START_ADDR+686;
Uint16 const co1_SPIrange3rwpsCRC = CO1_SPI_START_ADDR+686;
Uint16 const co1_SPIrange4rw = CO1_SPI_START_ADDR+688;
Uint16 const co1_SPIrange4rwCRC = CO1_SPI_START_ADDR+688;
Uint16 const co1_SPIrange4rwp = CO1_SPI_START_ADDR+690;
Uint16 const co1_SPIrange4rwpCRC = CO1_SPI_START_ADDR+690;
Uint16 const co1_SPIrange4rwps = CO1_SPI_START_ADDR+692;
Uint16 const co1_SPIrange4rwpsCRC = CO1_SPI_START_ADDR+692;
Uint16 const co1_SPIrange5rw = CO1_SPI_START_ADDR+694;
Uint16 const co1_SPIrange5rwCRC = CO1_SPI_START_ADDR+1064;
Uint16 const co1_SPIrange5rwp = CO1_SPI_START_ADDR+1066;
Uint16 const co1_SPIrange5rwpCRC = CO1_SPI_START_ADDR+1070;
Uint16 const co1_SPIrange5rwps = CO1_SPI_START_ADDR+1072;
Uint16 const co1_SPIrange5rwpsCRC = CO1_SPI_START_ADDR+1072;
Uint16 const co1_SPIrange6rw = CO1_SPI_START_ADDR+1074;
Uint16 const co1_SPIrange6rwCRC = CO1_SPI_START_ADDR+1074;
Uint16 const co1_SPIrange6rwp = CO1_SPI_START_ADDR+1076;
Uint16 const co1_SPIrange6rwpCRC = CO1_SPI_START_ADDR+1076;
Uint16 const co1_SPIrange6rwps = CO1_SPI_START_ADDR+1078;
Uint16 const co1_SPIrange6rwpsCRC = CO1_SPI_START_ADDR+1078;
Uint16 const co1_first1000 = 0;
Uint16 const co1_first2000 = 82;
Uint16 const co1_first3000 = 194;
Uint16 const co1_first4000 = 198;
Uint16 const co1_first5000 = 198;
Uint16 const co1_first6000 = 238;
// ������� �����
Uint16 const CO1_TYPE_DEF_TABLE[] = {
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
    (Uint16)4,\
    (Uint16)5,\
    (Uint16)0,\
    (Uint16)-1,\
    (Uint16)0,\
    (Uint16)4,\
    (Uint16)0,\
    (Uint16)4,\
    (Uint16)4,\
    (Uint16)-1,\
    (Uint16)40,\
    (Uint16)17,\
    (Uint16)6,\
    (Uint16)8,\
    (Uint16)7,\
    (Uint16)9,\
    (Uint16)15,\
    (Uint16)36,\
    (Uint16)16,\
    (Uint16)1,\
    (Uint16)13,\
    (Uint16)12,\
    (Uint16)14,\
    (Uint16)18,\
    (Uint16)-1,\
    (Uint16)28,\
    (Uint16)28,\
    (Uint16)24,\
    (Uint16)23,\
    (Uint16)27,\
    (Uint16)46,\
    (Uint16)45,\
};
// ������� CALLBACK-�������
//**************************************************************
long const CO1_OD_CALLBACK_TBL[]={
0, // 1000h.00h
0, // 1001h.00h
0, // 1002h.00h
0, // 1014h.00h
0, // 1016h.00h
0, // 1017h.00h
0, // 1018h.00h
0, // 1200h.00h
0, // 1280h.00h
0, // 1400h.00h
0, // 1401h.00h
0, // 1402h.00h
0, // 1403h.00h
0, // 1404h.00h
0, // 1405h.00h
0, // 1406h.00h
0, // 1407h.00h
0, // 1600h.00h
0, // 1601h.00h
0, // 1602h.00h
0, // 1603h.00h
0, // 1604h.00h
0, // 1605h.00h
0, // 1606h.00h
0, // 1607h.00h
0, // 1800h.00h
0, // 1801h.00h
0, // 1802h.00h
0, // 1803h.00h
0, // 1804h.00h
0, // 1805h.00h
0, // 1806h.00h
0, // 1807h.00h
0, // 1A00h.00h
0, // 1A01h.00h
0, // 1A02h.00h
0, // 1A03h.00h
0, // 1A04h.00h
0, // 1A05h.00h
0, // 1A06h.00h
0, // 1A07h.00h
0, // 2000h.00h
0, // 2001h.00h
0, // 2002h.00h
0, // 2003h.00h
0, // 2004h.00h
0, // 2005h.00h
0, // 2007h.00h
0, // 2010h.00h
0, // 2011h.00h
0, // 2012h.00h
0, // 2014h.00h
0, // 2015h.00h
0, // 2016h.00h
0, // 2017h.00h
0, // 2080h.00h
0, // 2081h.00h
0, // 2082h.00h
0, // 2083h.00h
0, // 2100h.00h
0, // 2101h.00h
0, // 2102h.00h
0, // 2103h.00h
0, // 2104h.00h
0, // 2105h.00h
0, // 2106h.00h
0, // 2107h.00h
0, // 2108h.00h
0, // 2109h.00h
0, // 210Ah.00h
0, // 210Bh.00h
0, // 210Ch.00h
0, // 210Dh.00h
0, // 210Eh.00h
0, // 210Fh.00h
0, // 2110h.00h
0, // 2111h.00h
0, // 2112h.00h
0, // 2113h.00h
0, // 2114h.00h
0, // 2115h.00h
0, // 2116h.00h
0, // 2117h.00h
0, // 2118h.00h
0, // 2119h.00h
0, // 211Ah.00h
0, // 211Bh.00h
0, // 211Ch.00h
0, // 211Dh.00h
0, // 2502h.00h
0, // 2506h.00h
(long)((void(*)(long))callback_RTC), // 250Fh.00h
0, // 2532h.00h
0, // 2534h.00h
0, // 2600h.00h
(long)((void(*)(long))co1_callback_BTcmd), // 2700h.00h
0, // 2701h.00h
0, // 3000h.00h
0, // 3100h.00h
0, // 5000h.00h
0, // 5100h.00h
0, // 5101h.00h
0, // 5102h.00h
0, // 5103h.00h
0, // 5105h.00h
0, // 510Bh.00h
0, // 510Eh.00h
0, // 5112h.00h
0, // 5113h.00h
0, // 5114h.00h
0, // 5116h.00h
0, // 511Ah.00h
0, // 5138h.00h
0, // 5150h.00h
(long)((void(*)(long))callback_dlog), // 5151h.00h
0, // 5152h.00h
0, // 5155h.00h
0, // 5174h.00h
0, // 5B05h.00h
0, // 5B06h.00h
};

// ������ ������ ��� �������� CANopen ����������� �����������
#if defined(COOD_LINKS__6000)
long const CO1_LINKS[]={(long)&co1_numOfInd,
                        (long)&CO1_OD_TBL1,
                        (long)&CO1_OD_TBL2,
                        (long)&CO1_OD_TBL3,
                        (long)&CO1_TYPE_DEF_TABLE,
                        (long)&CO1_OD_CALLBACK_TBL,
                        (long)&co1_SPIrange1rw,
                        (long)&co1_SPIrange1rwCRC,
                        (long)&co1_SPIrange1rwp,
                        (long)&co1_SPIrange1rwpCRC,
                        (long)&co1_SPIrange1rwps,
                        (long)&co1_SPIrange1rwpsCRC,
                        (long)&co1_SPIrange2rw,
                        (long)&co1_SPIrange2rwCRC,
                        (long)&co1_SPIrange2rwp,
                        (long)&co1_SPIrange2rwpCRC,
                        (long)&co1_SPIrange2rwps,
                        (long)&co1_SPIrange2rwpsCRC,
                        (long)&co1_SPIrange3rw,
                        (long)&co1_SPIrange3rwCRC,
                        (long)&co1_SPIrange3rwp,
                        (long)&co1_SPIrange3rwpCRC,
                        (long)&co1_SPIrange3rwps,
                        (long)&co1_SPIrange3rwpsCRC,
                        (long)&co1_SPIrange4rw,
                        (long)&co1_SPIrange4rwCRC,
                        (long)&co1_SPIrange4rwp,
                        (long)&co1_SPIrange4rwpCRC,
                        (long)&co1_SPIrange4rwps,
                        (long)&co1_SPIrange4rwpsCRC,
                        (long)&co1_SPIrange5rw,
                        (long)&co1_SPIrange5rwCRC,
                        (long)&co1_SPIrange5rwp,
                        (long)&co1_SPIrange5rwpCRC,
                        (long)&co1_SPIrange5rwps,
                        (long)&co1_SPIrange5rwpsCRC,
                        (long)&co1_SPIrange6rw,
                        (long)&co1_SPIrange6rwCRC,
                        (long)&co1_SPIrange6rwp,
                        (long)&co1_SPIrange6rwpCRC,
                        (long)&co1_SPIrange6rwps,
                        (long)&co1_SPIrange6rwpsCRC,
                        (long)&co1_first1000,
                        (long)&co1_first2000,
                        (long)&co1_first3000,
                        (long)&co1_first4000,
                        (long)&co1_first5000,
                        (long)&co1_first6000
};

STATIC_ASSERT(((sizeof(CO1_LINKS)/sizeof(CO1_LINKS[0])) == (COOD_LINKS__6000 + 1)),m);

#elif defined(COOD_LINKS__5000)
long const CO1_LINKS[]={(long)&co1_numOfInd,
                        (long)&CO1_OD_TBL1,
                        (long)&CO1_OD_TBL2,
                        (long)&CO1_OD_TBL3,
                        (long)&CO1_TYPE_DEF_TABLE,
                        (long)&CO1_OD_CALLBACK_TBL,
                        (long)&co1_SPIrange1rw,
                        (long)&co1_SPIrange1rwCRC,
                        (long)&co1_SPIrange1rwp,
                        (long)&co1_SPIrange1rwpCRC,
                        (long)&co1_SPIrange1rwps,
                        (long)&co1_SPIrange1rwpsCRC,
                        (long)&co1_SPIrange2rw,
                        (long)&co1_SPIrange2rwCRC,
                        (long)&co1_SPIrange2rwp,
                        (long)&co1_SPIrange2rwpCRC,
                        (long)&co1_SPIrange2rwps,
                        (long)&co1_SPIrange2rwpsCRC,
                        (long)&co1_SPIrange3rw,
                        (long)&co1_SPIrange3rwCRC,
                        (long)&co1_SPIrange3rwp,
                        (long)&co1_SPIrange3rwpCRC,
                        (long)&co1_SPIrange3rwps,
                        (long)&co1_SPIrange3rwpsCRC,
                        (long)&co1_SPIrange4rw,
                        (long)&co1_SPIrange4rwCRC,
                        (long)&co1_SPIrange4rwp,
                        (long)&co1_SPIrange4rwpCRC,
                        (long)&co1_SPIrange4rwps,
                        (long)&co1_SPIrange4rwpsCRC,
                        (long)&co1_SPIrange5rw,
                        (long)&co1_SPIrange5rwCRC,
                        (long)&co1_SPIrange5rwp,
                        (long)&co1_SPIrange5rwpCRC,
                        (long)&co1_SPIrange5rwps,
                        (long)&co1_SPIrange5rwpsCRC,
                        (long)&co1_first1000,
                        (long)&co1_first2000,
                        (long)&co1_first3000,
                        (long)&co1_first4000,
                        (long)&co1_first5000
};

STATIC_ASSERT(((sizeof(CO1_LINKS)/sizeof(CO1_LINKS[0])) == (COOD_LINKS__5000 + 1)),m);
#endif
