// Файл: cood1.c
// Профиль: C:\Users\Favarit\workspace_v8\project\MCB4_DEMO\Profiles\MCD4_DEMO_profile.xml
// Конфигурация: Базовый профиль
// Дата создания: 25.04.2023 12:51:39
// Пользователь: default
// COODEdit Basic v.7.5.3
#include "DSP.h"
#include "main.h"
#include "cood1.h"
#include "co_ODvars.h"

// всего 120 индексов в словаре
// всего 726 элементов в словаре
Uint16 const co1_numOfInd = 120;
// Номер перечесления для групп
Uint16 const co1_groupEnum = 15;
// Хэш-сумма:
Uint32 const co1_odHash[4] = {0x12DEEF44, 0xA33490A9, 0xF5B40F87, 0xF23B68F2};
// Таблица с адресами переменных
long const CO1_OD_TBL3[] = {
(long)(&co1_vars.co_deviceType),	//[1000h.00h], Название: Тип устройства, ТекстПУ: Device Type, Группа: CAN
(long)(&co1_vars.co_errorRegister),	//[1001h.00h], Название: Регистр ошибок, ТекстПУ: ErrReg, Группа: CAN
(long)(&co1_vars.co_deviceState),	//[1002h.00h], Название: Manufacturer Status Register, ТекстПУ: DevSta, Группа: CAN
(long)(&co1_vars.co_emcyCOBID),	//[1014h.00h], Название: COB-ID Emergency Object, ТекстПУ: eCOBID, Группа: CAN
(long)(&co1_vars.co_CHBT),	//[1016h.01h], Название: Время ожидания сообщения Heartbeat, ТекстПУ: CHBT, Группа: CAN
(long)(&co1_vars.co_PHBT),	//[1017h.00h], Название: Период генерации сообщения Heartbeat, ТекстПУ: PHBT, Группа: CAN
(long)(&co1_vars.co_vendorID),	//[1018h.01h], Название: Код производителя, ТекстПУ: VendID, Группа: CAN
(long)(&co1_vars.co_productCode),	//[1018h.02h], Название: Код продукта, ТекстПУ: PrCode, Группа: CAN
(long)(&co1_vars.co_revisionNumber),	//[1018h.03h], Название: Номер ревизии, ТекстПУ: RevNum, Группа: CAN
(long)(&co1_vars.co_serialNumber),	//[1018h.04h], Название: Серийный номер, ТекстПУ: SerNum, Группа: CAN
(long)(&co1_vars.co_csrxCOBID),	//[1200h.01h], Название: COB-ID Client->Server(rx), ТекстПУ: CSRXID, Группа: CAN
(long)(&co1_vars.co_sctxCOBID),	//[1200h.02h], Название: COB-ID Server->Client(tx), ТекстПУ: SCTXID, Группа: CAN
(long)(&co1_vars.co_cstxCOBID),	//[1280h.01h], Название: COB-ID Client->Server(tx), ТекстПУ: CSTXID, Группа: CAN
(long)(&co1_vars.co_scrxCOBID),	//[1280h.02h], Название: COB-ID Server->Client(rx), ТекстПУ: SCRXID, Группа: CAN
(long)(&co1_vars.co_ssNODEID),	//[1280h.03h], Название: NODE-ID on SDO server, ТекстПУ: SDOSID, Группа: CAN
(long)(&co1_vars.co_RPDO1COBID),	//[1400h.01h], Название: COB-ID for RPDO1, ТекстПУ: IRPDO1, Группа: CAN
(long)(&co1_vars.co_transType),	//[1400h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO2COBID),	//[1401h.01h], Название: COB-ID for RPDO2, ТекстПУ: IRPDO2, Группа: CAN
(long)(&co1_vars.co_transType),	//[1401h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO3COBID),	//[1402h.01h], Название: COB-ID for RPDO3, ТекстПУ: IRPDO3, Группа: CAN
(long)(&co1_vars.co_transType),	//[1402h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO4COBID),	//[1403h.01h], Название: COB-ID for RPDO4, ТекстПУ: IRPDO4, Группа: CAN
(long)(&co1_vars.co_transType),	//[1403h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO5COBID),	//[1404h.01h], Название: COB-ID for RPDO5, ТекстПУ: IRPDO5, Группа: CAN
(long)(&co1_vars.co_transType),	//[1404h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO6COBID),	//[1405h.01h], Название: COB-ID for RPDO6, ТекстПУ: IRPDO6, Группа: CAN
(long)(&co1_vars.co_transType),	//[1405h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO7COBID),	//[1406h.01h], Название: COB-ID for RPDO7, ТекстПУ: IRPDO7, Группа: CAN
(long)(&co1_vars.co_transType),	//[1406h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO8COBID),	//[1407h.01h], Название: COB-ID for RPDO8, ТекстПУ: IRPDO8, Группа: CAN
(long)(&co1_vars.co_transType),	//[1407h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_RPDO1_1Mapping),	//[1600h.01h], Название: RPDO1-1 Mapping, ТекстПУ: RPM11, Группа: CAN
(long)(&co1_vars.co_RPDO1_2Mapping),	//[1600h.02h], Название: RPDO1-2 Mapping, ТекстПУ: RPM12, Группа: CAN
(long)(&co1_vars.co_RPDO1_3Mapping),	//[1600h.03h], Название: RPDO1-3 Mapping, ТекстПУ: RPM13, Группа: CAN
(long)(&co1_vars.co_RPDO1_4Mapping),	//[1600h.04h], Название: RPDO1-4 Mapping, ТекстПУ: RPM14, Группа: CAN
(long)(&co1_vars.co_RPDO2_1Mapping),	//[1601h.01h], Название: RPDO2-1 Mapping, ТекстПУ: RPM21, Группа: CAN
(long)(&co1_vars.co_RPDO2_2Mapping),	//[1601h.02h], Название: RPDO2-2 Mapping, ТекстПУ: RPM22, Группа: CAN
(long)(&co1_vars.co_RPDO2_3Mapping),	//[1601h.03h], Название: RPDO2-3 Mapping, ТекстПУ: RPM23, Группа: CAN
(long)(&co1_vars.co_RPDO2_4Mapping),	//[1601h.04h], Название: RPDO2-4 Mapping, ТекстПУ: RPM24, Группа: CAN
(long)(&co1_vars.co_RPDO3_1Mapping),	//[1602h.01h], Название: RPDO3-1 Mapping, ТекстПУ: RPM31, Группа: CAN
(long)(&co1_vars.co_RPDO3_2Mapping),	//[1602h.02h], Название: RPDO3-2 Mapping, ТекстПУ: RPM32, Группа: CAN
(long)(&co1_vars.co_RPDO3_3Mapping),	//[1602h.03h], Название: RPDO3-3 Mapping, ТекстПУ: RPM33, Группа: CAN
(long)(&co1_vars.co_RPDO3_4Mapping),	//[1602h.04h], Название: RPDO3-4 Mapping, ТекстПУ: RPM34, Группа: CAN
(long)(&co1_vars.co_RPDO4_1Mapping),	//[1603h.01h], Название: RPDO4-1 Mapping, ТекстПУ: RPM41, Группа: CAN
(long)(&co1_vars.co_RPDO4_2Mapping),	//[1603h.02h], Название: RPDO4-2 Mapping, ТекстПУ: RPM42, Группа: CAN
(long)(&co1_vars.co_RPDO4_3Mapping),	//[1603h.03h], Название: RPDO4-3 Mapping, ТекстПУ: RPM43, Группа: CAN
(long)(&co1_vars.co_RPDO4_4Mapping),	//[1603h.04h], Название: RPDO4-4 Mapping, ТекстПУ: RPM44, Группа: CAN
(long)(&co1_vars.co_RPDO5_1Mapping),	//[1604h.01h], Название: RPDO5-1 Mapping, ТекстПУ: RPM51, Группа: CAN
(long)(&co1_vars.co_RPDO5_2Mapping),	//[1604h.02h], Название: RPDO5-2 Mapping, ТекстПУ: RPM52, Группа: CAN
(long)(&co1_vars.co_RPDO5_3Mapping),	//[1604h.03h], Название: RPDO5-3 Mapping, ТекстПУ: RPM53, Группа: CAN
(long)(&co1_vars.co_RPDO5_4Mapping),	//[1604h.04h], Название: RPDO5-4 Mapping, ТекстПУ: RPM54, Группа: CAN
(long)(&co1_vars.co_RPDO6_1Mapping),	//[1605h.01h], Название: RPDO6-1 Mapping, ТекстПУ: RPM61, Группа: CAN
(long)(&co1_vars.co_RPDO6_2Mapping),	//[1605h.02h], Название: RPDO6-2 Mapping, ТекстПУ: RPM62, Группа: CAN
(long)(&co1_vars.co_RPDO6_3Mapping),	//[1605h.03h], Название: RPDO6-3 Mapping, ТекстПУ: RPM63, Группа: CAN
(long)(&co1_vars.co_RPDO6_4Mapping),	//[1605h.04h], Название: RPDO6-4 Mapping, ТекстПУ: RPM64, Группа: CAN
(long)(&co1_vars.co_RPDO7_1Mapping),	//[1606h.01h], Название: RPDO7-1 Mapping, ТекстПУ: RPM71, Группа: CAN
(long)(&co1_vars.co_RPDO7_2Mapping),	//[1606h.02h], Название: RPDO7-2 Mapping, ТекстПУ: RPM72, Группа: CAN
(long)(&co1_vars.co_RPDO7_3Mapping),	//[1606h.03h], Название: RPDO7-3 Mapping, ТекстПУ: RPM73, Группа: CAN
(long)(&co1_vars.co_RPDO7_4Mapping),	//[1606h.04h], Название: RPDO7-4 Mapping, ТекстПУ: RPM74, Группа: CAN
(long)(&co1_vars.co_RPDO8_1Mapping),	//[1607h.01h], Название: RPDO8-1 Mapping, ТекстПУ: RPM81, Группа: CAN
(long)(&co1_vars.co_RPDO8_2Mapping),	//[1607h.02h], Название: RPDO8-2 Mapping, ТекстПУ: RPM82, Группа: CAN
(long)(&co1_vars.co_RPDO8_3Mapping),	//[1607h.03h], Название: RPDO8-3 Mapping, ТекстПУ: RPM83, Группа: CAN
(long)(&co1_vars.co_RPDO8_4Mapping),	//[1607h.04h], Название: RPDO8-4 Mapping, ТекстПУ: RPM84, Группа: CAN
(long)(&co1_vars.co_TPDO1COBID),	//[1800h.01h], Название: COB-ID for TPDO1, ТекстПУ: ITPDO1, Группа: CAN
(long)(&co1_vars.co_transType),	//[1800h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO1ITime),	//[1800h.03h], Название: Inhibit Time 1, ТекстПУ: ITime1, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1800h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO1EventTimer),	//[1800h.05h], Название: Event Timer 1, ТекстПУ: EvTmr1, Группа: CAN
(long)(&co1_vars.co_TPDO2COBID),	//[1801h.01h], Название: COB-ID for TPDO2, ТекстПУ: ITPDO2, Группа: CAN
(long)(&co1_vars.co_transType),	//[1801h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO2ITime),	//[1801h.03h], Название: Inhibit Time 2, ТекстПУ: ITime2, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1801h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO2EventTimer),	//[1801h.05h], Название: Event Timer 2, ТекстПУ: EvTmr2, Группа: CAN
(long)(&co1_vars.co_TPDO3COBID),	//[1802h.01h], Название: COB-ID for TPDO3, ТекстПУ: ITPDO3, Группа: CAN
(long)(&co1_vars.co_transType),	//[1802h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO3ITime),	//[1802h.03h], Название: Inhibit Time 3, ТекстПУ: ITime3, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1802h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO3EventTimer),	//[1802h.05h], Название: Event Timer 3, ТекстПУ: EvTmr3, Группа: CAN
(long)(&co1_vars.co_TPDO4COBID),	//[1803h.01h], Название: COB-ID for TPDO4, ТекстПУ: ITPDO4, Группа: CAN
(long)(&co1_vars.co_transType),	//[1803h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO4ITime),	//[1803h.03h], Название: Inhibit Time 4, ТекстПУ: ITime4, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1803h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO4EventTimer),	//[1803h.05h], Название: Event Timer 4, ТекстПУ: EvTmr4, Группа: CAN
(long)(&co1_vars.co_TPDO5COBID),	//[1804h.01h], Название: COB-ID for TPDO5, ТекстПУ: ITPDO5, Группа: CAN
(long)(&co1_vars.co_transType),	//[1804h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO5ITime),	//[1804h.03h], Название: Inhibit Time 5, ТекстПУ: ITime5, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1804h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO5EventTimer),	//[1804h.05h], Название: Event Timer 5, ТекстПУ: EvTmr5, Группа: CAN
(long)(&co1_vars.co_TPDO6COBID),	//[1805h.01h], Название: COB-ID for TPDO6, ТекстПУ: ITPDO6, Группа: CAN
(long)(&co1_vars.co_transType),	//[1805h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO6ITime),	//[1805h.03h], Название: Inhibit Time 6, ТекстПУ: ITime6, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1805h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO6EventTimer),	//[1805h.05h], Название: Event Timer 6, ТекстПУ: EvTmr6, Группа: CAN
(long)(&co1_vars.co_TPDO7COBID),	//[1806h.01h], Название: COB-ID for TPDO7, ТекстПУ: ITPDO7, Группа: CAN
(long)(&co1_vars.co_transType),	//[1806h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO7ITime),	//[1806h.03h], Название: Inhibit Time 7, ТекстПУ: ITime7, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1806h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO7EventTimer),	//[1806h.05h], Название: Event Timer 7, ТекстПУ: EvTmr7, Группа: CAN
(long)(&co1_vars.co_TPDO8COBID),	//[1807h.01h], Название: COB-ID for TPDO8, ТекстПУ: ITPDO8, Группа: CAN
(long)(&co1_vars.co_transType),	//[1807h.02h], Название: Тип передачи, ТекстПУ: TransT, Группа: CAN
(long)(&co1_vars.co_TPDO8ITime),	//[1807h.03h], Название: Inhibit Time 8, ТекстПУ: ITime8, Группа: CAN
(long)(&co1_vars.co_compatEntry),	//[1807h.04h], Название: Compatibility Entry, ТекстПУ: CompEn, Группа: CAN
(long)(&co1_vars.co_TPDO8EventTimer),	//[1807h.05h], Название: Event Timer 8, ТекстПУ: EvTmr8, Группа: CAN
(long)(&co1_vars.co_TPDO1_1Mapping),	//[1A00h.01h], Название: TPDO1-1 Mapping, ТекстПУ: TPM11, Группа: CAN
(long)(&co1_vars.co_TPDO1_2Mapping),	//[1A00h.02h], Название: TPDO1-2 Mapping, ТекстПУ: TPM12, Группа: CAN
(long)(&co1_vars.co_TPDO1_3Mapping),	//[1A00h.03h], Название: TPDO1-3 Mapping, ТекстПУ: TPM13, Группа: CAN
(long)(&co1_vars.co_TPDO1_4Mapping),	//[1A00h.04h], Название: TPDO1-4 Mapping, ТекстПУ: TPM14, Группа: CAN
(long)(&co1_vars.co_TPDO2_1Mapping),	//[1A01h.01h], Название: TPDO2-1 Mapping, ТекстПУ: TPM21, Группа: CAN
(long)(&co1_vars.co_TPDO2_2Mapping),	//[1A01h.02h], Название: TPDO2-2 Mapping, ТекстПУ: TPM22, Группа: CAN
(long)(&co1_vars.co_TPDO2_3Mapping),	//[1A01h.03h], Название: TPDO2-3 Mapping, ТекстПУ: TPM23, Группа: CAN
(long)(&co1_vars.co_TPDO2_4Mapping),	//[1A01h.04h], Название: TPDO2-4 Mapping, ТекстПУ: TPM24, Группа: CAN
(long)(&co1_vars.co_TPDO3_1Mapping),	//[1A02h.01h], Название: TPDO3-1 Mapping, ТекстПУ: TPM31, Группа: CAN
(long)(&co1_vars.co_TPDO3_2Mapping),	//[1A02h.02h], Название: TPDO3-2 Mapping, ТекстПУ: TPM32, Группа: CAN
(long)(&co1_vars.co_TPDO3_3Mapping),	//[1A02h.03h], Название: TPDO3-3 Mapping, ТекстПУ: TPM33, Группа: CAN
(long)(&co1_vars.co_TPDO3_4Mapping),	//[1A02h.04h], Название: TPDO3-4 Mapping, ТекстПУ: TPM34, Группа: CAN
(long)(&co1_vars.co_TPDO4_1Mapping),	//[1A03h.01h], Название: TPDO4-1 Mapping, ТекстПУ: TPM41, Группа: CAN
(long)(&co1_vars.co_TPDO4_2Mapping),	//[1A03h.02h], Название: TPDO4-2 Mapping, ТекстПУ: TPM42, Группа: CAN
(long)(&co1_vars.co_TPDO4_3Mapping),	//[1A03h.03h], Название: TPDO4-3 Mapping, ТекстПУ: TPM43, Группа: CAN
(long)(&co1_vars.co_TPDO4_4Mapping),	//[1A03h.04h], Название: TPDO4-4 Mapping, ТекстПУ: TPM44, Группа: CAN
(long)(&co1_vars.co_TPDO5_1Mapping),	//[1A04h.01h], Название: TPDO5-1 Mapping, ТекстПУ: TPM51, Группа: CAN
(long)(&co1_vars.co_TPDO5_2Mapping),	//[1A04h.02h], Название: TPDO5-2 Mapping, ТекстПУ: TPM52, Группа: CAN
(long)(&co1_vars.co_TPDO5_3Mapping),	//[1A04h.03h], Название: TPDO5-3 Mapping, ТекстПУ: TPM53, Группа: CAN
(long)(&co1_vars.co_TPDO5_4Mapping),	//[1A04h.04h], Название: TPDO5-4 Mapping, ТекстПУ: TPM54, Группа: CAN
(long)(&co1_vars.co_TPDO6_1Mapping),	//[1A05h.01h], Название: TPDO6-1 Mapping, ТекстПУ: TPM61, Группа: CAN
(long)(&co1_vars.co_TPDO6_2Mapping),	//[1A05h.02h], Название: TPDO6-2 Mapping, ТекстПУ: TPM62, Группа: CAN
(long)(&co1_vars.co_TPDO6_3Mapping),	//[1A05h.03h], Название: TPDO6-3 Mapping, ТекстПУ: TPM63, Группа: CAN
(long)(&co1_vars.co_TPDO6_4Mapping),	//[1A05h.04h], Название: TPDO6-4 Mapping, ТекстПУ: TPM64, Группа: CAN
(long)(&co1_vars.co_TPDO7_1Mapping),	//[1A06h.01h], Название: TPDO7-1 Mapping, ТекстПУ: TPM71, Группа: CAN
(long)(&co1_vars.co_TPDO7_2Mapping),	//[1A06h.02h], Название: TPDO7-2 Mapping, ТекстПУ: TPM72, Группа: CAN
(long)(&co1_vars.co_TPDO7_3Mapping),	//[1A06h.03h], Название: TPDO7-3 Mapping, ТекстПУ: TPM73, Группа: CAN
(long)(&co1_vars.co_TPDO7_4Mapping),	//[1A06h.04h], Название: TPDO7-4 Mapping, ТекстПУ: TPM74, Группа: CAN
(long)(&co1_vars.co_TPDO8_1Mapping),	//[1A07h.01h], Название: TPDO8-1 Mapping, ТекстПУ: TPM81, Группа: CAN
(long)(&co1_vars.co_TPDO8_2Mapping),	//[1A07h.02h], Название: TPDO8-2 Mapping, ТекстПУ: TPM82, Группа: CAN
(long)(&co1_vars.co_TPDO8_3Mapping),	//[1A07h.03h], Название: TPDO8-3 Mapping, ТекстПУ: TPM83, Группа: CAN
(long)(&co1_vars.co_TPDO8_4Mapping),	//[1A07h.04h], Название: TPDO8-4 Mapping, ТекстПУ: TPM84, Группа: CAN
(long)(&co1_vars.co_nodeID),	//[2000h.00h], Название: CAN NODE-ID, ТекстПУ: NodeID, Группа: CAN
(long)(&co1_vars.co_bitRate),	//[2001h.00h], Название: CAN Bit Rate, ТекстПУ: CANBR, Группа: CAN, биты с 0 по 2: 0000000000000111b
(long)(&co1_vars.co_vendorID),	//[2002h.01h], Название: Код производителя, ТекстПУ: VendID, Группа: CAN
(long)(&co1_vars.co_productCode),	//[2002h.02h], Название: Код продукта, ТекстПУ: PrCode, Группа: CAN
(long)(&co1_vars.co_revisionNumber),	//[2002h.03h], Название: Номер ревизии, ТекстПУ: RevNum, Группа: CAN
(long)(&co1_vars.co_serialNumber),	//[2002h.04h], Название: Серийный номер, ТекстПУ: SerNum, Группа: CAN
(long)(&co1_vars.co_specialData1),	//[2003h.01h], Название: Special Data 1, ТекстПУ: SpDat1, Группа: CAN
(long)(&co1_vars.co_specialData2),	//[2003h.02h], Название: Special Data 2, ТекстПУ: SpDat2, Группа: CAN
(long)(&co1_vars.co_specialData3),	//[2003h.03h], Название: Special Data 3, ТекстПУ: SpDat3, Группа: CAN
(long)(&co1_vars.co_specialData4),	//[2003h.04h], Название: Special Data 4, ТекстПУ: SpDat4, Группа: CAN
(long)(&co1_vars.co_secretCode),	//[2004h.00h], Название: Secret Code, ТекстПУ: Secret, Группа: CAN
(long)(&co1_vars.co_protectBit),	//[2005h.00h], Название: Protect Bit, ТекстПУ: ProtBt, Группа: CAN, биты с 0 по 0: 0000000000000001b
(long)(&co1_odHash[0]),	//[2007h.01h], Название: md5_hash_0, ТекстПУ: md5_hash_0, Группа: CAN
(long)(&co1_odHash[1]),	//[2007h.02h], Название: md5_hash_1, ТекстПУ: md5_hash_1, Группа: CAN
(long)(&co1_odHash[2]),	//[2007h.03h], Название: md5_hash_2, ТекстПУ: md5_hash_2, Группа: CAN
(long)(&co1_odHash[3]),	//[2007h.04h], Название: md5_hash_3, ТекстПУ: md5_hash_3, Группа: CAN
(long)(&co1_vars.co_heartbeatFlag0),	//[2010h.01h], Название: Heartbeat Flag 0-31, ТекстПУ: HFlag0, Группа: CAN
(long)(&co1_vars.co_heartbeatFlag1),	//[2010h.02h], Название: Heartbeat Flag 32-63, ТекстПУ: HFlag1, Группа: CAN
(long)(&co1_vars.co_heartbeatFlag2),	//[2010h.03h], Название: Heartbeat Flag 64-95, ТекстПУ: HFlag2, Группа: CAN
(long)(&co1_vars.co_heartbeatFlag3),	//[2010h.04h], Название: Heartbeat Flag 96-127, ТекстПУ: HFlag3, Группа: CAN
(long)(&co1_vars.co_heartbeatMask0),	//[2011h.01h], Название: Heartbeat Mask 0-31, ТекстПУ: HMask0, Группа: CAN
(long)(&co1_vars.co_heartbeatMask1),	//[2011h.02h], Название: Heartbeat Mask 32-63, ТекстПУ: HMask1, Группа: CAN
(long)(&co1_vars.co_heartbeatMask2),	//[2011h.03h], Название: Heartbeat Mask 64-95, ТекстПУ: HMask2, Группа: CAN
(long)(&co1_vars.co_heartbeatMask3),	//[2011h.04h], Название: Heartbeat Mask 96-127, ТекстПУ: HMask3, Группа: CAN
(long)(&co1_vars.co_heartbeatAutoStart),	//[2012h.00h], Название: Heartbeat Autostart, ТекстПУ: HBASta, Группа: CAN, биты с 0 по 0: 0000000000000001b
(long)(&co1_vars.co_heartbeatAutoRecovery),	//[2014h.00h], Название: Heartbeat Autorecovery, ТекстПУ: HBARec, Группа: CAN, биты с 0 по 0: 0000000000000001b
(long)(&co1_vars.co_nodeState),	//[2015h.00h], Название: Состояние драйвера CAN-Open, ТекстПУ: State, Группа: CAN
(long)(&co1_vars.co_emergencyErrorCode),	//[2016h.00h], Название: Emergency Error Code, ТекстПУ: EmErCo, Группа: CAN
(long)(&co1_vars.co_deviceErrorState),	//[2017h.00h], Название: Device Error State, ТекстПУ: DeErSt, Группа: CAN
(long)(&co1_vars.co_ODCommand),	//[2080h.01h], Название: Object Dictionary Command, ТекстПУ: ODComm, Группа: CAN
(long)(&co1_vars.co_currentODIndex),	//[2080h.02h], Название: Current OD Index, ТекстПУ: ODCInd, Группа: CAN
(long)(&co1_vars.co_currentODSubIndex),	//[2080h.03h], Название: Current OD Sub-Index, ТекстПУ: ODCSub, Группа: CAN
(long)(&co1_vars.co_currentODEText),	//[2080h.04h], Название: Current OD Element Text, ТекстПУ: ODCTxt, Группа: CAN
(long)(&co1_vars.co_currentODEFormat),	//[2080h.05h], Название: Current OD Element Format, ТекстПУ: ODCFrm, Группа: CAN
(long)(&co1_vars.co_currentODEMin),	//[2080h.06h], Название: Current OD Element Min, ТекстПУ: ODCMin, Группа: CAN
(long)(&co1_vars.co_currentODEMax),	//[2080h.07h], Название: Current OD Element Max, ТекстПУ: ODCMax, Группа: CAN
(long)(&co1_vars.co_currentODEDefault),	//[2080h.08h], Название: Current OD Element Default, ТекстПУ: ODCDef, Группа: CAN
(long)(&co1_vars.co_currentODEMinLow),	//[2080h.09h], Название: Current OD Element MinLow, ТекстПУ: ODCMiL, Группа: CAN
(long)(&co1_vars.co_currentODEMaxLow),	//[2080h.0Ah], Название: Current OD Element MaxLow, ТекстПУ: ODCMaL, Группа: CAN
(long)(&co1_vars.co_currentODEDefaultLow),	//[2080h.0Bh], Название: Current OD Element Default Low, ТекстПУ: ODCDeL, Группа: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Ch], Название: Current OD Element Address, ТекстПУ: ODCAdr, Группа: CAN
(long)(&co1_vars.co_currentODEAddrLow),	//[2080h.0Dh], Название: Current OD Element Address, ТекстПУ: ODCAdr, Группа: CAN
(long)(&co1_vars.co_currentODEType),	//[2080h.0Eh], Название: Группа параметров, ТекстПУ: Группа, Группа: CAN
(long)(&co1_vars.co_odIndexSize),	//[2081h.00h], Название: Количество индексов, ТекстПУ: КолИнд, Группа: CAN
(long)(&co1_vars.co_defaultIndex1),	//[2082h.01h], Название: Default Index 1, ТекстПУ: DfInd1, Группа: CAN
(long)(&co1_vars.co_defaultIndex2),	//[2082h.02h], Название: Default Index 2, ТекстПУ: DfInd2, Группа: CAN
(long)(&co1_vars.co_maskElement01),	//[2083h.01h], Название: Mask Element, ТекстПУ: MskEl0, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElement01),	//[2083h.02h], Название: Mask Element, ТекстПУ: MskEl1, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElement23),	//[2083h.03h], Название: Mask Element, ТекстПУ: MskEl2, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElement23),	//[2083h.04h], Название: Mask Element, ТекстПУ: MskEl3, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElement45),	//[2083h.05h], Название: Mask Element, ТекстПУ: MskEl4, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElement45),	//[2083h.06h], Название: Mask Element, ТекстПУ: MskEl5, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElement67),	//[2083h.07h], Название: Mask Element, ТекстПУ: MskEl6, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElement67),	//[2083h.08h], Название: Mask Element, ТекстПУ: MskEl7, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElement89),	//[2083h.09h], Название: Mask Element, ТекстПУ: MskEl8, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElement89),	//[2083h.0Ah], Название: Mask Element, ТекстПУ: MskEl9, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Bh], Название: Mask Element, ТекстПУ: MskElA, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElementAB),	//[2083h.0Ch], Название: Mask Element, ТекстПУ: MskElB, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Dh], Название: Mask Element, ТекстПУ: MskElC, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElementCD),	//[2083h.0Eh], Название: Mask Element, ТекстПУ: MskElD, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_maskElementEF),	//[2083h.0Fh], Название: Mask Element, ТекстПУ: MskElE, Группа: CAN, биты с 0 по 7: 0000000011111111b
(long)(&co1_vars.co_maskElementEF),	//[2083h.10h], Название: Mask Element, ТекстПУ: MskElF, Группа: CAN, биты с 8 по 15: 1111111100000000b
(long)(&co1_vars.co_scaleNum0),	//[2100h.01h], Название: Scale Number 0, ТекстПУ: SN0, Группа: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.02h], Название: Scale Number 0 Format, ТекстПУ: S0Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum0Format),	//[2100h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1),	//[2101h.01h], Название: Scale Number 1, ТекстПУ: SN1, Группа: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.02h], Название: Scale Number 1 Format, ТекстПУ: S1Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1Format),	//[2101h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum2),	//[2102h.01h], Название: Scale Number 2, ТекстПУ: SN2, Группа: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.02h], Название: Scale Number 2 Format, ТекстПУ: S2Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum2Format),	//[2102h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum3),	//[2103h.01h], Название: Scale Number 3, ТекстПУ: SN3, Группа: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.02h], Название: Scale Number 3 Format, ТекстПУ: S3Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum3Format),	//[2103h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum4),	//[2104h.01h], Название: Scale Number 4, ТекстПУ: SN4, Группа: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.02h], Название: Scale Number 4 Format, ТекстПУ: S4Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum4Format),	//[2104h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum5),	//[2105h.01h], Название: Scale Number 5, ТекстПУ: SN5, Группа: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.02h], Название: Scale Number 5 Format, ТекстПУ: S5Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum5Format),	//[2105h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum6),	//[2106h.01h], Название: Scale Number 6, ТекстПУ: SN6, Группа: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.02h], Название: Scale Number 6 Format, ТекстПУ: S6Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum6Format),	//[2106h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum7),	//[2107h.01h], Название: Scale Number 7, ТекстПУ: SN7, Группа: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.02h], Название: Scale Number 7 Format, ТекстПУ: S7Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum7Format),	//[2107h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum8),	//[2108h.01h], Название: Scale Number 8, ТекстПУ: SN8, Группа: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.02h], Название: Scale Number 8 Format, ТекстПУ: S8Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum8Format),	//[2108h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum9),	//[2109h.01h], Название: Scale Number 9, ТекстПУ: SN9, Группа: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.02h], Название: Scale Number 9 Format, ТекстПУ: S9Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum9Format),	//[2109h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumA),	//[210Ah.01h], Название: Scale Number A, ТекстПУ: SNA, Группа: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.02h], Название: Scale Number A Format, ТекстПУ: SAFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumAFormat),	//[210Ah.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumB),	//[210Bh.01h], Название: Scale Number B, ТекстПУ: SNB, Группа: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.02h], Название: Scale Number B Format, ТекстПУ: SBFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumBFormat),	//[210Bh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumC),	//[210Ch.01h], Название: Scale Number C, ТекстПУ: SNC, Группа: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.02h], Название: Scale Number C Format, ТекстПУ: SCFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumCFormat),	//[210Ch.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumD),	//[210Dh.01h], Название: Scale Number D, ТекстПУ: SND, Группа: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.02h], Название: Scale Number D Format, ТекстПУ: SDFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumDFormat),	//[210Dh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumE),	//[210Eh.01h], Название: Scale Number E, ТекстПУ: SNE, Группа: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.02h], Название: Scale Number E Format, ТекстПУ: SEFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumEFormat),	//[210Eh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNumF),	//[210Fh.01h], Название: Scale Number F, ТекстПУ: SNF, Группа: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.02h], Название: Scale Number F Format, ТекстПУ: SFFmt, Группа: CAN
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNumFFormat),	//[210Fh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum10),	//[2110h.01h], Название: Scale Number 10, ТекстПУ: SN10, Группа: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.02h], Название: Scale Number 10 Format, ТекстПУ: S10Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum10Format),	//[2110h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum11),	//[2111h.01h], Название: Scale Number 11, ТекстПУ: SN11, Группа: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.02h], Название: Scale Number 11 Format, ТекстПУ: S11Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum11Format),	//[2111h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum12),	//[2112h.01h], Название: Scale Number 12, ТекстПУ: SN12, Группа: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.02h], Название: Scale Number 12 Format, ТекстПУ: S12Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum12Format),	//[2112h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum13),	//[2113h.01h], Название: Scale Number 13, ТекстПУ: SN13, Группа: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.02h], Название: Scale Number 13 Format, ТекстПУ: S13Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum13Format),	//[2113h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum14),	//[2114h.01h], Название: Scale Number 14, ТекстПУ: SN14, Группа: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.02h], Название: Scale Number 14 Format, ТекстПУ: S14Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum14Format),	//[2114h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum15),	//[2115h.01h], Название: Scale Number 15, ТекстПУ: SN15, Группа: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.02h], Название: Scale Number 15Format, ТекстПУ: S15Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum15Format),	//[2115h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum16),	//[2116h.01h], Название: Scale Number 16, ТекстПУ: SN16, Группа: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.02h], Название: Scale Number 16Format, ТекстПУ: S16Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum16Format),	//[2116h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum17),	//[2117h.01h], Название: Scale Number 17, ТекстПУ: SN17, Группа: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.02h], Название: Scale Number 17Format, ТекстПУ: S17Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum17Format),	//[2117h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum18),	//[2118h.01h], Название: Scale Number 18, ТекстПУ: SN18, Группа: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.02h], Название: Scale Number 18Format, ТекстПУ: S18Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum18Format),	//[2118h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum19),	//[2119h.01h], Название: Scale Number 19, ТекстПУ: SN19, Группа: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.02h], Название: Scale Number 19Format, ТекстПУ: S19Fmt, Группа: CAN
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum19Format),	//[2119h.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1A),	//[211Ah.01h], Название: Scale Number 1A, ТекстПУ: SN1A, Группа: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.02h], Название: Scale Number 1AFormat, ТекстПУ: S1AFmt, Группа: CAN
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1AFormat),	//[211Ah.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1B),	//[211Bh.01h], Название: Scale Number 1B, ТекстПУ: SN1B, Группа: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.02h], Название: Scale Number 1BFormat, ТекстПУ: S1BFmt, Группа: CAN
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1BFormat),	//[211Bh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1C),	//[211Ch.01h], Название: Scale Number 1C, ТекстПУ: SN1C, Группа: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.02h], Название: Scale Number 1C Format, ТекстПУ: S1CFmt, Группа: CAN
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1CFormat),	//[211Ch.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&co1_vars.co_scaleNum1D),	//[211Dh.01h], Название: Scale Number 1D, ТекстПУ: SN1D, Группа: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.02h], Название: Scale Number 1D Format, ТекстПУ: S1DFmt, Группа: CAN
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.03h], Название: Scale Number Format Q, ТекстПУ: Q-type, Группа: CAN, биты с 0 по 4: 0000000000011111b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.04h], Название: Scale Number Format NumOfFloat, ТекстПУ: NFloat, Группа: CAN, биты с 5 по 6: 0000000001100000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.05h], Название: Scale Number Format Prefix, ТекстПУ: Prefix, Группа: CAN, биты с 7 по 9: 0000001110000000b
(long)(&co1_vars.co_scaleNum1DFormat),	//[211Dh.06h], Название: Scale Number Format Units, ТекстПУ: Units, Группа: CAN, биты с 10 по 15: 1111110000000000b
(long)(&cmd.all),	//[2502h.01h], Название: Пуск, ТекстПУ: Пуск, Группа: Слово управления, биты с 0 по 0: 0000000000000001b
(long)(&cmd.all),	//[2502h.02h], Название: Стоп, ТекстПУ: Стоп, Группа: Слово управления, биты с 1 по 1: 0000000000000010b
(long)(&cmd.all),	//[2502h.03h], Название: Сбросить состояние Аварии, ТекстПУ: СбрАвр, Группа: Слово управления, биты с 2 по 2: 0000000000000100b
(long)(&cmd.all),	//[2502h.04h], Название: Слово управления CAN, ТекстПУ: КмдCAN, Группа: Слово управления
(long)(&drv_interface.req_data),	//[2506h.01h], Название: Таймаут потери связи, ТекстПУ: OfflineCounterMax, Группа: ВНЕ ГРУПП
(long)(&drv_interface.ans_data),	//[2506h.02h], Название: Счетчик потери связи, ТекстПУ: OfflineCounter, Группа: ВНЕ ГРУПП
(long)(&drv_interface.data_Low),	//[2506h.03h], Название: data_Low, ТекстПУ: data_L, Группа: ВНЕ ГРУПП
(long)(&drv_interface.data_High),	//[2506h.04h], Название: data_High, ТекстПУ: data_H, Группа: ВНЕ ГРУПП
(long)(&RTCclock.packed_time),	//[250Fh.00h], Название: Часы реального времени, ТекстПУ: RTC, Группа: Наблюдаемые
(long)(&sm_prot.Main_ErrorCode),	//[2532h.01h], Название: Код аварии MCB4, ТекстПУ: Код аварии MCB4, Группа: ВНЕ ГРУПП, биты с 0 по 7: 0000000011111111b
(long)(&sm_prot.Main_ErrorCode),	//[2532h.02h], Название: Расширение кода аварии, ТекстПУ: Авр+, Группа: ВНЕ ГРУПП, биты с 8 по 15: 1111111100000000b
(long)(&sm_prot.Main_Flags),	//[2532h.03h], Название: Системный объект, ТекстПУ: System, Группа: ВНЕ ГРУПП, биты с 0 по 0: 0000000000000001b
(long)(&disp_group_number),	//[2534h.01h], Название: Номер груп для пульта управления, ТекстПУ: № гр ПУ, Группа: CAN
(long)(&VendorToken),	//[2600h.01h], Название: VendorToken, ТекстПУ: VendorToken, Группа: ВНЕ ГРУПП
(long)(&co1_vars.co_blockTransferCommand),	//[2700h.00h], Название: Block Transfer Interpreter, ТекстПУ: BT Interpreter, Группа: CAN
(long)(&swu_vars),	//[2701h.01h], Название: cmd, ТекстПУ: cmd, Группа: CAN
(long)(&swu_vars),	//[2701h.02h], Название: status, ТекстПУ: status, Группа: CAN
(long)(&swu_vars),	//[2701h.03h], Название: quest1, ТекстПУ: quest1, Группа: CAN
(long)(&swu_vars),	//[2701h.04h], Название: quest2, ТекстПУ: quest2, Группа: CAN
(long)(&swu_vars),	//[2701h.05h], Название: quest3, ТекстПУ: quest3, Группа: CAN
(long)(&swu_vars),	//[2701h.06h], Название: quest4, ТекстПУ: quest4, Группа: CAN
(long)(&swu_vars),	//[2701h.07h], Название: ans1, ТекстПУ: ans1, Группа: CAN
(long)(&swu_vars),	//[2701h.08h], Название: ans2, ТекстПУ: ans2, Группа: CAN
(long)(&swu_vars),	//[2701h.09h], Название: ans3, ТекстПУ: ans3, Группа: CAN
(long)(&swu_vars),	//[2701h.0Ah], Название: ans4, ТекстПУ: ans4, Группа: CAN
(long)(&swu_vars),	//[2701h.0Bh], Название: addr, ТекстПУ: addr, Группа: CAN
(long)(&swu_vars),	//[2701h.0Ch], Название: CPU_ID, ТекстПУ: CPU_ID, Группа: CAN
(long)(&swu_vars),	//[2701h.0Dh], Название: sector_mask, ТекстПУ: sector_mask, Группа: CAN
(long)(&swu_vars),	//[2701h.0Eh], Название: version, ТекстПУ: version, Группа: CAN
(long)(&swu_vars),	//[2701h.0Fh], Название: CRC, ТекстПУ: CRC, Группа: CAN
(long)(&drv_status.all),	//[3000h.00h], Название: Статус преобразователя, ТекстПУ: Статус, Группа: Наблюдаемые, биты с 0 по 5: 0000000000111111b
(long)(&msCounter),	//[3100h.01h], Название: Счётчик прерываний 1 кГц, ТекстПУ: Сч.прерыв.1 кГц, Группа: Счетчики
(long)(&FastCounter),	//[3100h.02h], Название: Счётчик прерываний 10 кГц, ТекстПУ: Сч.прерыв.10 кГц, Группа: Счетчики
(long)(&LoopCounter),	//[3100h.03h], Название: BackgroundCounter, ТекстПУ: BackgroundCounter, Группа: Счетчики
(long)(&TIsr10),	//[3100h.04h], Название: T_10кГц, ТекстПУ: T_10кГц, Группа: Счетчики
(long)(&TIsr1),	//[3100h.05h], Название: T_1кГц, ТекстПУ: T_1кГц, Группа: Счетчики
(long)(&rmp.T),	//[5000h.01h], Название: T разгона до номинала, ТекстПУ: rmpT, Группа: ЗИ
(long)(&rmp.input),	//[5000h.02h], Название: Вход ЗИ, ТекстПУ: ВходЗИ, Группа: ЗИ
(long)(&rmp.output),	//[5000h.03h], Название: Выход ЗИ, ТекстПУ: ВыходЗИ, Группа: ЗИ
(long)(&pid_id.pid_ref_reg3),	//[5100h.01h], Название: Задание, ТекстПУ: Зад-е, Группа: Рег. тока Id
(long)(&pid_id.pid_fdb_reg3),	//[5100h.02h], Название: Обратная связь, ТекстПУ: Обр.Св, Группа: Рег. тока Id
(long)(&pid_id.Kp_reg3),	//[5100h.03h], Название: Пропорц. коэфф. Kp, ТекстПУ: Kp, Группа: Рег. тока Id
(long)(&pid_id.pid_out_max),	//[5100h.04h], Название: Максимум выхода, ТекстПУ: Max, Группа: Рег. тока Id
(long)(&pid_id.pid_out_min),	//[5100h.05h], Название: Минимум выхода, ТекстПУ: Min, Группа: Рег. тока Id
(long)(&pid_id.Ki_reg3),	//[5100h.06h], Название: Интегральный коэфф. Ki, ТекстПУ: Ki, Группа: Рег. тока Id
(long)(&pid_id.Kd_reg3),	//[5100h.07h], Название: Дифф. коэфф. Kd, ТекстПУ: Kd, Группа: Рег. тока Id
(long)(&pid_id.Kc_reg3),	//[5100h.08h], Название: Интегр.корректир.коэффициент, ТекстПУ: Kc, Группа: Рег. тока Id
(long)(&pid_id.e_reg3),	//[5100h.09h], Название: Ошибка рассогласования сигналов, ТекстПУ: Ошибка, Группа: Рег. тока Id
(long)(&pid_id.pid_out_reg3),	//[5100h.0Ah], Название: Выход регулятора, ТекстПУ: Выход, Группа: Рег. тока Id
(long)(&pid_id.up_reg3),	//[5100h.0Bh], Название: Вых.Пропорц., ТекстПУ: Вых.Пропорц., Группа: Рег. тока Id
(long)(&pid_id.ui_reg3),	//[5100h.0Ch], Название: Вых.Интегр., ТекстПУ: Вых.Интегр., Группа: Рег. тока Id
(long)(&pid_id.ud_reg3),	//[5100h.0Dh], Название: Вых.Диффер., ТекстПУ: Вых.Диффер., Группа: Рег. тока Id
(long)(&pid_spd.pid_ref_reg3),	//[5101h.01h], Название: Задание, ТекстПУ: pisref, Группа: Рег. скорости
(long)(&pid_spd.pid_fdb_reg3),	//[5101h.02h], Название: Обратная связь, ТекстПУ: pisfbd, Группа: Рег. скорости
(long)(&pid_spd.Kp_reg3),	//[5101h.03h], Название: Пропорц. коэфф. Kp, ТекстПУ: Kp, Группа: Рег. скорости
(long)(&pid_spd.pid_out_max),	//[5101h.04h], Название: Максимум выхода, ТекстПУ: Max, Группа: Рег. скорости
(long)(&pid_spd.pid_out_min),	//[5101h.05h], Название: Минимум выхода, ТекстПУ: Min, Группа: Рег. скорости
(long)(&pid_spd.Ki_reg3),	//[5101h.06h], Название: Интегральный коэфф. Ki, ТекстПУ: Ki, Группа: Рег. скорости
(long)(&pid_spd.Kd_reg3),	//[5101h.07h], Название: Дифф. коэфф. Kd, ТекстПУ: pisKd, Группа: Рег. скорости
(long)(&pid_spd.Kc_reg3),	//[5101h.08h], Название: Интегр.корректир.коэффициент, ТекстПУ: Kc, Группа: Рег. скорости
(long)(&pid_spd.e_reg3),	//[5101h.09h], Название: Ошибка рассогласования сигналов, ТекстПУ: Ошибка, Группа: Рег. скорости
(long)(&pid_spd.pid_out_reg3),	//[5101h.0Ah], Название: Выход регулятора, ТекстПУ: pisout, Группа: Рег. скорости
(long)(&pid_spd.up_reg3),	//[5101h.0Bh], Название: Вых.Пропорц., ТекстПУ: Вых.Пропорц., Группа: Рег. скорости
(long)(&pid_spd.ui_reg3),	//[5101h.0Ch], Название: Вых.Интегр., ТекстПУ: Вых.Интегр., Группа: Рег. скорости
(long)(&pid_spd.ud_reg3),	//[5101h.0Dh], Название: Вых.Диффер., ТекстПУ: Вых.Диффер., Группа: Рег. скорости
(long)(&pid_spd.saterr_reg3),	//[5101h.0Eh], Название: Превышение насыщения, ТекстПУ: Прев. насыщ, Группа: Рег. скорости
(long)(&pid_iq.pid_ref_reg3),	//[5102h.01h], Название: Задание, ТекстПУ: Зад-ие, Группа: Рег. тока Iq
(long)(&pid_iq.pid_fdb_reg3),	//[5102h.02h], Название: Обратная связь, ТекстПУ: Обр.Св, Группа: Рег. тока Iq
(long)(&pid_iq.Kp_reg3),	//[5102h.03h], Название: Пропорц. коэфф. Kp, ТекстПУ: Kp, Группа: Рег. тока Iq
(long)(&pid_iq.pid_out_max),	//[5102h.04h], Название: Максимум выхода, ТекстПУ: Max, Группа: Рег. тока Iq
(long)(&pid_iq.pid_out_min),	//[5102h.05h], Название: Минимум выхода, ТекстПУ: Min, Группа: Рег. тока Iq
(long)(&pid_iq.Ki_reg3),	//[5102h.06h], Название: Интегральный коэфф. Ki, ТекстПУ: Ki, Группа: Рег. тока Iq
(long)(&pid_iq.Kd_reg3),	//[5102h.07h], Название: Дифф. коэфф. Kd, ТекстПУ: Kd, Группа: Рег. тока Iq
(long)(&pid_iq.Kc_reg3),	//[5102h.08h], Название: Интегр.корректир.коэффициент, ТекстПУ: Kc, Группа: Рег. тока Iq
(long)(&pid_iq.e_reg3),	//[5102h.09h], Название: Ошибка рассогласования сигналов, ТекстПУ: Ошибка, Группа: Рег. тока Iq
(long)(&pid_iq.pid_out_reg3),	//[5102h.0Ah], Название: Выход регулятора, ТекстПУ: Выход, Группа: Рег. тока Iq
(long)(&pid_iq.up_reg3),	//[5102h.0Bh], Название: Вых.Пропорц., ТекстПУ: Вых.Пропорц., Группа: Рег. тока Iq
(long)(&pid_iq.ui_reg3),	//[5102h.0Ch], Название: Вых.Интегр., ТекстПУ: Вых.Интегр., Группа: Рег. тока Iq
(long)(&pid_iq.ud_reg3),	//[5102h.0Dh], Название: Вых.Диффер., ТекстПУ: Вых.Диффер., Группа: Рег. тока Iq
(long)(&pid_pos.pid_ref_reg3),	//[5103h.01h], Название: Задание, ТекстПУ: pisref, Группа: Рег. положения
(long)(&pid_pos.pid_ref_reg3),	//[5103h.02h], Название: Задание, ТекстПУ: pisref, Группа: Рег. положения
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.03h], Название: Обратная связь, ТекстПУ: pisfbd, Группа: Рег. положения
(long)(&pid_pos.pid_fdb_reg3),	//[5103h.04h], Название: Обратная связь, ТекстПУ: pisfbd, Группа: Рег. положения
(long)(&pid_pos.Kp_reg3),	//[5103h.05h], Название: Пропорц. коэфф. Kp, ТекстПУ: Kp, Группа: Рег. положения
(long)(&pid_pos.pid_out_max),	//[5103h.06h], Название: Максимум выхода, ТекстПУ: Max, Группа: Рег. положения
(long)(&pid_pos.pid_out_min),	//[5103h.07h], Название: Минимум выхода, ТекстПУ: Min, Группа: Рег. положения
(long)(&pid_pos.Ki_reg3),	//[5103h.08h], Название: Интегральный коэфф. Ki, ТекстПУ: Ki, Группа: Рег. положения
(long)(&pid_pos.Kd_reg3),	//[5103h.09h], Название: Дифф. коэфф. Kd, ТекстПУ: pisKd, Группа: Рег. положения
(long)(&pid_pos.DiffDelim),	//[5103h.0Ah], Название: Делит. дифф. части, ТекстПУ: Делит. дифф. части, Группа: Рег. положения
(long)(&pid_pos.Kf_d),	//[5103h.0Bh], Название: Коэф. фильтра, ТекстПУ: Коэф. фильтра, Группа: Рег. положения
(long)(&pid_pos.Kc_reg3),	//[5103h.0Ch], Название: Интегр.корректир.коэффициент, ТекстПУ: Kc, Группа: Рег. положения
(long)(&pid_pos.DeadZone),	//[5103h.0Dh], Название: Мертвая зона, ТекстПУ: Мертвая зона, Группа: Рег. положения
(long)(&pid_pos.e_reg3),	//[5103h.0Eh], Название: Ошибка рассогласования сигналов, ТекстПУ: Ошибка, Группа: Рег. положения
(long)(&pid_spd.saterr_reg3),	//[5103h.0Fh], Название: Превышение насыщения, ТекстПУ: Прев. насыщ, Группа: Рег. положения
(long)(&pid_pos.pid_out_reg3),	//[5103h.10h], Название: Выход регулятора, ТекстПУ: pisout, Группа: Рег. положения
(long)(&pid_pos.up_reg3),	//[5103h.11h], Название: Вых.Пропорц., ТекстПУ: Вых.Пропорц., Группа: Рег. положения
(long)(&pid_pos.ui_reg3),	//[5103h.12h], Название: Вых.Интегр., ТекстПУ: Вых.Интегр., Группа: Рег. положения
(long)(&pid_pos.ud_reg3),	//[5103h.13h], Название: Вых.Диффер., ТекстПУ: Вых.Диффер., Группа: Рег. положения
(long)(&pid_pos.e_reg3_filterOut),	//[5103h.14h], Название: Фильтр ошибки, ТекстПУ: Фильтр ошибки, Группа: Рег. положения
(long)(&pwm.UalphaRef),	//[5105h.01h], Название: UaЗад, ТекстПУ: UaЗад, Группа: ШИМ
(long)(&pwm.UbetaRef),	//[5105h.02h], Название: UbЗад, ТекстПУ: UbЗад, Группа: ШИМ
(long)(&pwm.U_lim),	//[5105h.03h], Название: U_огр, ТекстПУ: U_огр, Группа: ШИМ
(long)(&pwm.GammaA),	//[5105h.04h], Название: GammaA, ТекстПУ: GmA, Группа: ШИМ
(long)(&pwm.GammaB),	//[5105h.05h], Название: GammaB, ТекстПУ: GmB, Группа: ШИМ
(long)(&pwm.GammaC),	//[5105h.06h], Название: GammaC, ТекстПУ: GmC, Группа: ШИМ
(long)(&pwm.k_pwm),	//[5105h.07h], Название: TPWM, ТекстПУ: TPWM, Группа: ШИМ
(long)(&pwm.DeadBand),	//[5105h.08h], Название: Мертвое время (мкс), ТекстПУ: Мерт. время, Группа: ШИМ
(long)(&pwm.MinGammaLimit),	//[5105h.09h], Название: Ограничение мин. скважн., ТекстПУ: GamLim, Группа: ШИМ
(long)(&pwm.UdCompK),	//[5105h.0Ah], Название: Коэф. компенсации Ud, ТекстПУ: UdКомпK, Группа: ШИМ
(long)(&pwm.UdCompEnable),	//[5105h.0Bh], Название: Компенсация Ud, ТекстПУ: UdКомп, Группа: ШИМ, биты с 0 по 0: 0000000000000001b
(long)(&pwm.PWM_type),	//[5105h.0Ch], Название: Тип ШИМ, ТекстПУ: ТипШИМ, Группа: ШИМ, биты с 0 по 0: 0000000000000001b
(long)(&pwm.ULimitation),	//[5105h.0Dh], Название: ULimitation, ТекстПУ: ULimitation, Группа: ШИМ
(long)(&pwm.Frequency),	//[5105h.0Eh], Название: Частота ШИМ, ТекстПУ: Fшим, Группа: ШИМ
(long)(&pwm.sector),	//[5105h.0Fh], Название: Сектор, ТекстПУ: Сектор, Группа: ШИМ
(long)(&pwm.U_mag),	//[5105h.10h], Название: U_ампл, ТекстПУ: U_ампл, Группа: ШИМ
(long)(&pwm.PDP_Fault),	//[5105h.11h], Название: Флаги аварий, ТекстПУ: F_bits, Группа: ШИМ
(long)(&sm_ctrl.state),	//[510Bh.01h], Название: sm_state, ТекстПУ: smstat, Группа: ДА sm_ctrl
(long)(&drv_status_code),	//[510Bh.02h], Название: drv_status_code, ТекстПУ: stcode, Группа: ДА sm_ctrl, биты с 0 по 7: 0000000011111111b
(long)(&sm_prot.bit_fault1),	//[510Eh.01h], Название: Флаги аварий 1, ТекстПУ: bitF_1, Группа: Защиты
(long)(&sm_prot.bit_fault2),	//[510Eh.02h], Название: Флаги аварий 2, ТекстПУ: bitF_2, Группа: Защиты
(long)(&sm_prot.mask_fault1),	//[510Eh.03h], Название: Маска аварий 1L, ТекстПУ: mask1L, Группа: Защиты, биты с 0 по 7: 0000000011111111b
(long)(&sm_prot.mask_fault1),	//[510Eh.04h], Название: Маска аварий 1H, ТекстПУ: mask1H, Группа: Защиты, биты с 8 по 15: 1111111100000000b
(long)(&sm_prot.mask_fault2),	//[510Eh.05h], Название: Маска аварий 2L, ТекстПУ: mask2L, Группа: Защиты, биты с 0 по 7: 0000000011111111b
(long)(&sm_prot.mask_fault2),	//[510Eh.06h], Название: Маска аварий  2H, ТекстПУ: mask2H, Группа: Защиты, биты с 8 по 15: 1111111100000000b
(long)(&sm_prot.Imax_protect),	//[510Eh.07h], Название: Максимальный ток, ТекстПУ: Макс.Ток, Группа: Защиты
(long)(&sm_prot.Umax_protect),	//[510Eh.08h], Название: Максимальное напряжение, ТекстПУ: Ud_max, Группа: Защиты
(long)(&sm_prot.Umin_protect),	//[510Eh.09h], Название: Минимальное напряжение, ТекстПУ: Ud_min, Группа: Защиты
(long)(&sm_prot.speed_max),	//[510Eh.0Ah], Название: Максимальная скорость, ТекстПУ: speed_max, Группа: Защиты
(long)(&sm_prot.T_max),	//[510Eh.0Bh], Название: Максимальная температура, ТекстПУ: t_max, Группа: Защиты
(long)(&refs.speed_ref),	//[5112h.01h], Название: Скорость, ТекстПУ: Скор_з, Группа: Задания
(long)(&refs.Iq_ref),	//[5112h.02h], Название: Макс. ток ВУ, ТекстПУ: ТокСТз, Группа: Задания
(long)(&refs.i_flux_ref),	//[5112h.03h], Название: Ток удержания, ТекстПУ: ТокУПз, Группа: Задания
(long)(&refs.theta_elec),	//[5112h.04h], Название: theta_elec, ТекстПУ: элекУг, Группа: Задания
(long)(&refs.uf_ref),	//[5112h.05h], Название: Заданное напряжение ОВ, ТекстПУ: Uf_ref, Группа: Задания
(long)(&drv_params.p),	//[5113h.01h], Название: Число пар полюсов, ТекстПУ: ПарПол, Группа: Базов. парам
(long)(&drv_params.I_nom),	//[5113h.02h], Название: Номинальный ток, ТекстПУ: IпчНом, Группа: Базов. парам
(long)(&drv_params.U_nom),	//[5113h.03h], Название: Номинальное напряжение фазн., ТекстПУ: Uф_ном, Группа: Базов. парам
(long)(&drv_params.speed_nom),	//[5113h.04h], Название: Номинальная скорость, ТекстПУ: СкоростьНом, Группа: Базов. парам
(long)(&drv_params.Udc_nom),	//[5113h.05h], Название: Номинальное напряжение ЗПТ, ТекстПУ: UdcНом, Группа: Базов. парам
(long)(&drv_params.Rs),	//[5113h.06h], Название: Rs, ТекстПУ: Rs, Группа: Базов. парам
(long)(&drv_params.Ls),	//[5113h.07h], Название: Ls, ТекстПУ: Ls, Группа: Базов. парам
(long)(&drv_params.freq_nom),	//[5113h.08h], Название: Номинальная частота, ТекстПУ: Ном.част., Группа: Базов. парам
(long)(&drv_params.sens_type),	//[5113h.09h], Название: Тип датчика положения, ТекстПУ: Sens_type, Группа: Базов. парам, биты с 0 по 2: 0000000000000111b
(long)(&sw.HardwareType),	//[5114h.01h], Название: Тип аппаратной части, ТекстПУ: HardwareType, Группа: Настройки СУ, биты с 0 по 7: 0000000011111111b
(long)(&sm_ctrl.run_mode),	//[5114h.02h], Название: Режим работы, ТекстПУ: РежРаб, Группа: Настройки СУ
(long)(&sw.AutoOffset),	//[5114h.03h], Название: АЦП авто смещ., ТекстПУ: АЦПсмещ, Группа: Настройки СУ
(long)(&sw.Reboot),	//[5114h.04h], Название: Перезагрузка, ТекстПУ: Перезагрузка, Группа: Настройки СУ
(long)(&adc.Imeas_a_gain),	//[5116h.01h], Название: Коэффициент тока фазы А, ТекстПУ: IaУсил, Группа: АЦП
(long)(&adc.Imeas_a_offset),	//[5116h.02h], Название: Смещение тока фазы А, ТекстПУ: IaСмещ, Группа: АЦП
(long)(&adc.Imeas_a),	//[5116h.03h], Название: Ток фазы А, ТекстПУ: Ia_мгн, Группа: АЦП
(long)(&adc.Imeas_b_gain),	//[5116h.04h], Название: Коэффициент тока фазы В, ТекстПУ: IbУсил, Группа: АЦП
(long)(&adc.Imeas_b_offset),	//[5116h.05h], Название: Смещение тока фазы В, ТекстПУ: IbСмещ, Группа: АЦП
(long)(&adc.Imeas_b),	//[5116h.06h], Название: Ток фазы В, ТекстПУ: Ib_мгн, Группа: АЦП
(long)(&adc.Imeas_c_gain),	//[5116h.07h], Название: Коэффициент тока фазы C, ТекстПУ: IcУсил, Группа: АЦП
(long)(&adc.Imeas_c_offset),	//[5116h.08h], Название: Смещение тока фазы C, ТекстПУ: IcСмещ, Группа: АЦП
(long)(&adc.Imeas_c),	//[5116h.09h], Название: Ток фазы С, ТекстПУ: Ic_мгн, Группа: АЦП
(long)(&adc.Imeas_d_gain),	//[5116h.0Ah], Название: Коэффициент тока фазы D, ТекстПУ: IdУсил, Группа: АЦП
(long)(&adc.Imeas_d_offset),	//[5116h.0Bh], Название: Смещение тока фазы D, ТекстПУ: IdСмещ, Группа: АЦП
(long)(&adc.Imeas_d),	//[5116h.0Ch], Название: Ток фазы D, ТекстПУ: Id_мгн, Группа: АЦП
(long)(&adc.Udc_meas_gain),	//[5116h.0Dh], Название: Коэффициент напряжения ЗПТ, ТекстПУ: UdУсил, Группа: АЦП
(long)(&adc.Udc_meas_offset),	//[5116h.0Eh], Название: Смещение напряж. ЗПТ, ТекстПУ: Udсмещ, Группа: АЦП
(long)(&adc.Udc_meas),	//[5116h.0Fh], Название: Напряжение ЗПТ, ТекстПУ: Ud, Группа: АЦП
(long)(&adc.T_meas_gain),	//[5116h.10h], Название: Коэффициент температуры, ТекстПУ: t_gain, Группа: АЦП
(long)(&adc.T_meas),	//[5116h.11h], Название: Температура, ТекстПУ: t, Группа: АЦП
(long)(&adc.ref_meas_gain),	//[5116h.12h], Название: Коэффициент внешнего входа, ТекстПУ: ADC_ext_gain, Группа: АЦП
(long)(&adc.ref_meas_offset),	//[5116h.13h], Название: Смещение внешнего входа, ТекстПУ: ADC_ext_offset, Группа: АЦП
(long)(&adc.ref_meas),	//[5116h.14h], Название: Внешний аналоговый вход 1, ТекстПУ: ADC_ext1, Группа: АЦП
(long)(&vhz.freq),	//[511Ah.01h], Название: Выходная частота, ТекстПУ: F_вых, Группа: Кривая U-f
(long)(&vhz.vout),	//[511Ah.02h], Название: Выходное напряжение, ТекстПУ: U_вых, Группа: Кривая U-f
(long)(&vhz.FL),	//[511Ah.03h], Название: Нулевая опроная частота, ТекстПУ: f [0], Группа: Кривая U-f
(long)(&vhz.Vmin),	//[511Ah.04h], Название: Нулевое опорное напряжение, ТекстПУ: U [0], Группа: Кривая U-f
(long)(&vhz.FH),	//[511Ah.05h], Название: Первая опорная частота, ТекстПУ: f [1], Группа: Кривая U-f
(long)(&vhz.Vmax),	//[511Ah.06h], Название: Первое опорное напряжение, ТекстПУ: U [1], Группа: Кривая U-f
(long)(&vhz.Fmax),	//[511Ah.07h], Название: Максимальная частота, ТекстПУ: f max, Группа: Кривая U-f
(long)(&cur_par.speed),	//[5138h.01h], Название: Скорость, ТекстПУ: скор, Группа: Наблюдаемые
(long)(&cur_par.power),	//[5138h.02h], Название: Акт. мощность, ТекстПУ: АктМощ, Группа: Наблюдаемые
(long)(&cur_par.Is),	//[5138h.03h], Название: Ток статора, ТекстПУ: ТокСт, Группа: Наблюдаемые
(long)(&cur_par.ThetaRefCurr),	//[5138h.04h], Название: ЭлУголЗад, ТекстПУ: ЭлУголЗад, Группа: Наблюдаемые
(long)(&cur_par.ThetaCurr),	//[5138h.05h], Название: ЭлУгол, ТекстПУ: ЭлУгол, Группа: Наблюдаемые
(long)(&cur_par.IsRef),	//[5138h.06h], Название: Ток статора зад, ТекстПУ: ТокСтЗад, Группа: Наблюдаемые
(long)(&global_time.PowerOn_time_min),	//[5138h.07h], Название: Время запитанного состояния, мин, ТекстПУ: Power On Time, Группа: Наблюдаемые
(long)(&dlog.mode_reset),	//[5150h.01h], Название: dlog.mode_reset, ТекстПУ: mode, Группа: dlog
(long)(&dlog.control),	//[5150h.02h], Название: dlog.control, ТекстПУ: dlcont, Группа: dlog
(long)(&dlog.ind_subind[0]),	//[5150h.03h], Название: dlog.ind_subind1, ТекстПУ: dlisi1, Группа: dlog
(long)(&dlog.ind_subind[1]),	//[5150h.04h], Название: dlog.ind_subind2, ТекстПУ: dlisi2, Группа: dlog
(long)(&dlog.ind_subind[2]),	//[5150h.05h], Название: dlog.ind_subind3, ТекстПУ: dlisi3, Группа: dlog
(long)(&dlog.ind_subind[3]),	//[5150h.06h], Название: dlog.ind_subind4, ТекстПУ: dlisi4, Группа: dlog
(long)(&dlog.StartBits),	//[5150h.07h], Название: StartBitL, ТекстПУ: StrtBL, Группа: dlog, биты с 0 по 7: 0000000011111111b
(long)(&dlog.StartBits),	//[5150h.08h], Название: StartBitH, ТекстПУ: StrtBH, Группа: dlog, биты с 8 по 15: 1111111100000000b
(long)(&dlog.OneShotOperation),	//[5150h.09h], Название: OneShotOperation, ТекстПУ: OneShotOp, Группа: dlog, биты с 0 по 0: 0000000000000001b
(long)(&dlog.trig_shift),	//[5150h.0Ah], Название: Количество точек предыстории, ТекстПУ: N предыст., Группа: dlog
(long)(&dlog.sampling_rate),	//[5150h.0Bh], Название: Частота даталогера, ТекстПУ: dlogFreq, Группа: dlog
(long)(&dlog.next_value_var),	//[5151h.00h], Название: dlog.next_value_var, ТекстПУ: dlnval, Группа: dlog
(long)(&posspeedEqep.resolution),	//[5152h.01h], Название: Кол-во периодов, ТекстПУ: Кол-во периодов, Группа: ДПР-Энкодер
(long)(&posspeedEqep.indexEnable),	//[5152h.02h], Название: Наличие репера, ТекстПУ: Наличие репера, Группа: ДПР-Энкодер, биты с 2 по 2: 0000000000000100b
(long)(&posspeedEqep.posCnt),	//[5152h.03h], Название: Механическ.угол в метках, ТекстПУ: Механическ.угол в ме, Группа: ДПР-Энкодер
(long)(&posspeedEqep.speed_elec),	//[5152h.04h], Название: Скорость, ТекстПУ: Скорость, Группа: ДПР-Энкодер
(long)(&posspeedEqep.theta_elec),	//[5152h.05h], Название: Угол. электр., ТекстПУ: Угол. электр., Группа: ДПР-Энкодер
(long)(&posspeedEqep.thetaMech),	//[5152h.06h], Название: Угол мех., ТекстПУ: Угол мех., Группа: ДПР-Энкодер
(long)(&posspeedEqep.GPIOsValue),	//[5152h.07h], Название: GPIOsValue, ТекстПУ: GPIOsValue, Группа: ДПР-Энкодер
(long)(&posspeedEqep.RevolutionCounter),	//[5152h.08h], Название: Число оборотов, ТекстПУ: revolCounter, Группа: ДПР-Энкодер
(long)(&DPReCAP.Angle),	//[5155h.01h], Название: ЭлУгол, ТекстПУ: ЭлУгол, Группа: ДПР-Холл
(long)(&DPReCAP.speed),	//[5155h.02h], Название: Скорость, ТекстПУ: Скорость, Группа: ДПР-Холл
(long)(&DPReCAP.speedMIN),	//[5155h.03h], Название: Уставка Скорости, ТекстПУ: Уставка Скорости, Группа: ДПР-Холл
(long)(&DPReCAP.Angle6),	//[5155h.04h], Название: ЭлУгол6, ТекстПУ: ЭлУгол6, Группа: ДПР-Холл
(long)(&DPReCAP.DPReCAP_FLG1.all),	//[5155h.05h], Название: Инт-полятор вкл, ТекстПУ: Инт-полятор вкл, Группа: ДПР-Холл, биты с 0 по 0: 0000000000000001b
(long)(&DPReCAP.milsecREF),	//[5155h.06h], Название: Уставка обнуления скорости, ТекстПУ: Уставка обнуления ск, Группа: ДПР-Холл
(long)(&DPReCAP.speedMinREF),	//[5155h.07h], Название: Скорость Мин., ТекстПУ: Скорость Мин., Группа: ДПР-Холл
(long)(&DPReCAP.CAP_WrongEdgeCnt),	//[5155h.08h], Название: Ложные фронты, ТекстПУ: Ложные фронты, Группа: ДПР-Холл
(long)(&DPReCAP.DPReCAP_CODE.all),	//[5155h.09h], Название: Дискретные входы, ТекстПУ: Входы, Группа: ДПР-Холл, биты с 0 по 2: 0000000000000111b
(long)(&DPReCAP.AngleOffset),	//[5155h.0Ah], Название: СмещУгол, ТекстПУ: СмещУг, Группа: ДПР-Холл
(long)(&DPReCAP.ErrorLevel),	//[5155h.0Bh], Название: Уровень помех, ТекстПУ: Уровень помех, Группа: ДПР-Холл
(long)(&DPReCAP.CAP_WrongEdgeCnt1),	//[5155h.0Ch], Название: Ошибка 1 канала, ТекстПУ: Ошиб_1_к., Группа: ДПР-Холл
(long)(&DPReCAP.CAP_WrongEdgeCnt2),	//[5155h.0Dh], Название: Ошибка 2 канала, ТекстПУ: Ошиб_2_к., Группа: ДПР-Холл
(long)(&DPReCAP.CAP_WrongEdgeCnt3),	//[5155h.0Eh], Название: Ошибка 3 канала, ТекстПУ: Ошиб_3_к., Группа: ДПР-Холл
(long)(&DPReCAP.Direction),	//[5155h.0Fh], Название: Направление вращения, ТекстПУ: НапрВр, Группа: ДПР-Холл, биты с 2 по 2: 0000000000000100b
(long)(&DPReCAP.WrongCodeCounterLimitPerSec),	//[5155h.10h], Название: Макс.число ошибок ДПР, ТекстПУ: Макс.ош.ДПР, Группа: ДПР-Холл
(long)(&DPReCAP.WrongCodeCounter),	//[5155h.11h], Название: Кол-во ошибок неверной последовательности, ТекстПУ: Ошибки последоват., Группа: ДПР-Холл
(long)(&CounterCAP_isr),	//[5155h.12h], Название: Счётчик прерываний по приему, ТекстПУ: Счёт.Rx.Int., Группа: ДПР-Холл
(long)(&cap0_counter),	//[5155h.13h], Название: Счётчик прерываний CAP1, ТекстПУ: Сч.прерыв.CAP1, Группа: ДПР-Холл
(long)(&cap1_counter),	//[5155h.14h], Название: Счётчик прерываний CAP2, ТекстПУ: Сч.прерыв.CAP2, Группа: ДПР-Холл
(long)(&cap2_counter),	//[5155h.15h], Название: Счётчик прерываний CAP3, ТекстПУ: Сч.прерыв.CAP3, Группа: ДПР-Холл
(long)(&Debug1),	//[5174h.01h], Название: DebugL1, ТекстПУ: DebugL1, Группа: Для отладки
(long)(&Debug1),	//[5174h.02h], Название: DebugL1, ТекстПУ: DebugL1, Группа: Для отладки
(long)(&Debug2),	//[5174h.03h], Название: DebugL2, ТекстПУ: DebugL2, Группа: Для отладки
(long)(&Debug2),	//[5174h.04h], Название: DebugL2, ТекстПУ: DebugL2, Группа: Для отладки
(long)(&Debug3),	//[5174h.05h], Название: DebugI3, ТекстПУ: DebugI3, Группа: Для отладки
(long)(&Debug3),	//[5174h.06h], Название: DebugI3, ТекстПУ: DebugI3, Группа: Для отладки
(long)(&Debug4),	//[5174h.07h], Название: DebugI4, ТекстПУ: DebugI4, Группа: Для отладки
(long)(&Debug4),	//[5174h.08h], Название: DebugI4, ТекстПУ: DebugI4, Группа: Для отладки
(long)(&DebugW1),	//[5174h.09h], Название: DebugW1, ТекстПУ: DebugW1, Группа: Для отладки
(long)(&DebugW1),	//[5174h.0Ah], Название: DebugW1, ТекстПУ: DebugW1, Группа: Для отладки
(long)(&DebugW2),	//[5174h.0Bh], Название: DebugW2, ТекстПУ: DebugW2, Группа: Для отладки
(long)(&DebugW2),	//[5174h.0Ch], Название: DebugW2, ТекстПУ: DebugW2, Группа: Для отладки
(long)(&DebugW3),	//[5174h.0Dh], Название: DebugW3, ТекстПУ: DebugW3, Группа: Для отладки
(long)(&DebugW3),	//[5174h.0Eh], Название: DebugW3, ТекстПУ: DebugW3, Группа: Для отладки
(long)(&DebugW4),	//[5174h.0Fh], Название: DebugW4, ТекстПУ: DebugW4, Группа: Для отладки
(long)(&DebugW4),	//[5174h.10h], Название: DebugW4, ТекстПУ: DebugW4, Группа: Для отладки
(long)(&udControl.StateOn),	//[5B05h.01h], Название: Текущее состояние реле, ТекстПУ: Relay_state, Группа: Плавный заряд ЗПТ
(long)(&udControl.Timeout_on),	//[5B05h.02h], Название: Задежка включения реле, мс, ТекстПУ: relay on-delay, Группа: Плавный заряд ЗПТ
(long)(&udControl.U_on),	//[5B05h.03h], Название: Напряжение включения, В, ТекстПУ: on-voltage, Группа: Плавный заряд ЗПТ
(long)(&udControl.U_off),	//[5B05h.04h], Название: Напряжение выключения, В, ТекстПУ: off-voltage, Группа: Плавный заряд ЗПТ
(long)(&udControl.deriv_time_ZPT),	//[5B05h.05h], Название: Производная напряжения ЗПТ, ТекстПУ: derivative_voltage, Группа: Плавный заряд ЗПТ
(long)(&udControl.deriv_const),	//[5B05h.06h], Название: Уставка по производной ЗПТ, ТекстПУ: derivative_const, Группа: Плавный заряд ЗПТ
(long)(&FanControl.StateOn),	//[5B06h.01h], Название: Текущее состояние вентилятора, ТекстПУ: fan_state, Группа: Система охлаждения
(long)(&FanControl.T_on),	//[5B06h.02h], Название: Температура включения вентилятора, ТекстПУ: t_on, Группа: Система охлаждения
(long)(&FanControl.T_off),	//[5B06h.03h], Название: Температура выключения вентилятора, ТекстПУ: t_off, Группа: Система охлаждения
(long)(&FanControl.T_alarm),	//[5B06h.04h], Название: Температура вывода предупреждения о перегреве, ТекстПУ: t_alarm, Группа: Система охлаждения
};

// Таблица с форматами, дефолтами, и другими параметрами элементов
Uint16 const CO1_OD_TBL2[] = {

//[1000h.00h]
3200,	// формат
1,	// номер текста, название: Тип устройства
0,	// смещение для таблицы с адресами

//[1001h.00h]
2176,	// формат
2,	// номер текста, название: Регистр ошибок
1,	// смещение для таблицы с адресами

//[1002h.00h]
3200,	// формат
3,	// номер текста, название: Manufacturer Status Register
2,	// смещение для таблицы с адресами

//[1014h.00h]
3200,	// формат
4,	// номер текста, название: COB-ID Emergency Object
3,	// смещение для таблицы с адресами

// Корневой подындекс 1016h, ТекстПУ=CHBT
1,	// кол-во подындексов
5,	// номер текста
3,	// такой длиной

//[1016h.01h]
35968,	// формат
5,	// номер текста, название: Время ожидания сообщения Heartbeat
4,	// смещение для таблицы с адресами
(Uint16)(2000),	// знач по умолч.
(((Uint32)2000)>>16),	// знач по умолч.

//[1017h.00h]
35456,	// формат
6,	// номер текста, название: Период генерации сообщения Heartbeat
5,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1018h, ТекстПУ=IdObj
4,	// кол-во подындексов
7,	// номер текста
1,	// такой длиной

//[1018h.01h]
3200,	// формат
8,	// номер текста, название: Код производителя
6,	// смещение для таблицы с адресами

//[1018h.02h]
3200,	// формат
9,	// номер текста, название: Код продукта
7,	// смещение для таблицы с адресами

//[1018h.03h]
3200,	// формат
10,	// номер текста, название: Номер ревизии
8,	// смещение для таблицы с адресами

//[1018h.04h]
3200,	// формат
11,	// номер текста, название: Серийный номер
9,	// смещение для таблицы с адресами

// Корневой подындекс 1200h, ТекстПУ=SSDOP
2,	// кол-во подындексов
12,	// номер текста
1,	// такой длиной

//[1200h.01h]
3200,	// формат
13,	// номер текста, название: COB-ID Client->Server(rx)
10,	// смещение для таблицы с адресами

//[1200h.02h]
3200,	// формат
14,	// номер текста, название: COB-ID Server->Client(tx)
11,	// смещение для таблицы с адресами

// Корневой подындекс 1280h, ТекстПУ=CSDOP
3,	// кол-во подындексов
15,	// номер текста
1,	// такой длиной

//[1280h.01h]
3200,	// формат
16,	// номер текста, название: COB-ID Client->Server(tx)
12,	// смещение для таблицы с адресами

//[1280h.02h]
3200,	// формат
17,	// номер текста, название: COB-ID Server->Client(rx)
13,	// смещение для таблицы с адресами

//[1280h.03h]
2176,	// формат
18,	// номер текста, название: NODE-ID on SDO server
14,	// смещение для таблицы с адресами

// Корневой подындекс 1400h, ТекстПУ=RPDO1P
2,	// кол-во подындексов
19,	// номер текста
3,	// такой длиной

//[1400h.01h]
35968,	// формат
20,	// номер текста, название: COB-ID for RPDO1
15,	// смещение для таблицы с адресами
(Uint16)(0x180),	// знач по умолч.
(((Uint32)0x180)>>16),	// знач по умолч.

//[1400h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
16,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1401h, ТекстПУ=RPDO2P
2,	// кол-во подындексов
22,	// номер текста
3,	// такой длиной

//[1401h.01h]
35968,	// формат
23,	// номер текста, название: COB-ID for RPDO2
17,	// смещение для таблицы с адресами
(Uint16)(0x280),	// знач по умолч.
(((Uint32)0x280)>>16),	// знач по умолч.

//[1401h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
18,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1402h, ТекстПУ=RPDO3P
2,	// кол-во подындексов
24,	// номер текста
3,	// такой длиной

//[1402h.01h]
35968,	// формат
25,	// номер текста, название: COB-ID for RPDO3
19,	// смещение для таблицы с адресами
(Uint16)(0x0401),	// знач по умолч.
(((Uint32)0x0401)>>16),	// знач по умолч.

//[1402h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
20,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1403h, ТекстПУ=RPDO4P
2,	// кол-во подындексов
26,	// номер текста
3,	// такой длиной

//[1403h.01h]
35968,	// формат
27,	// номер текста, название: COB-ID for RPDO4
21,	// смещение для таблицы с адресами
(Uint16)(0x0501),	// знач по умолч.
(((Uint32)0x0501)>>16),	// знач по умолч.

//[1403h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
22,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1404h, ТекстПУ=RPDO5P
2,	// кол-во подындексов
28,	// номер текста
3,	// такой длиной

//[1404h.01h]
35968,	// формат
29,	// номер текста, название: COB-ID for RPDO5
23,	// смещение для таблицы с адресами
(Uint16)(0x0501),	// знач по умолч.
(((Uint32)0x0501)>>16),	// знач по умолч.

//[1404h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
24,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1405h, ТекстПУ=RPDO6P
2,	// кол-во подындексов
30,	// номер текста
3,	// такой длиной

//[1405h.01h]
35968,	// формат
31,	// номер текста, название: COB-ID for RPDO6
25,	// смещение для таблицы с адресами
(Uint16)(0x0501),	// знач по умолч.
(((Uint32)0x0501)>>16),	// знач по умолч.

//[1405h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
26,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1406h, ТекстПУ=RPDO7P
2,	// кол-во подындексов
32,	// номер текста
3,	// такой длиной

//[1406h.01h]
35968,	// формат
33,	// номер текста, название: COB-ID for RPDO7
27,	// смещение для таблицы с адресами
(Uint16)(0x0501),	// знач по умолч.
(((Uint32)0x0501)>>16),	// знач по умолч.

//[1406h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
28,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1407h, ТекстПУ=RPDO8P
2,	// кол-во подындексов
34,	// номер текста
3,	// такой длиной

//[1407h.01h]
35968,	// формат
35,	// номер текста, название: COB-ID for RPDO8
29,	// смещение для таблицы с адресами
(Uint16)(0x0501),	// знач по умолч.
(((Uint32)0x0501)>>16),	// знач по умолч.

//[1407h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
30,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 1600h, ТекстПУ=RPDO1M
4,	// кол-во подындексов
36,	// номер текста
3,	// такой длиной

//[1600h.01h]
35968,	// формат
37,	// номер текста, название: RPDO1-1 Mapping
31,	// смещение для таблицы с адресами
(Uint16)(0x511E0500),	// знач по умолч.
(((Uint32)0x511E0500)>>16),	// знач по умолч.

//[1600h.02h]
35968,	// формат
38,	// номер текста, название: RPDO1-2 Mapping
32,	// смещение для таблицы с адресами
(Uint16)(0x511E0600),	// знач по умолч.
(((Uint32)0x511E0600)>>16),	// знач по умолч.

//[1600h.03h]
35968,	// формат
39,	// номер текста, название: RPDO1-3 Mapping
33,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1600h.04h]
35968,	// формат
40,	// номер текста, название: RPDO1-4 Mapping
34,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1601h, ТекстПУ=RPDO2M
4,	// кол-во подындексов
41,	// номер текста
3,	// такой длиной

//[1601h.01h]
35968,	// формат
42,	// номер текста, название: RPDO2-1 Mapping
35,	// смещение для таблицы с адресами
(Uint16)(0x511E0700),	// знач по умолч.
(((Uint32)0x511E0700)>>16),	// знач по умолч.

//[1601h.02h]
35968,	// формат
43,	// номер текста, название: RPDO2-2 Mapping
36,	// смещение для таблицы с адресами
(Uint16)(0x511E0800),	// знач по умолч.
(((Uint32)0x511E0800)>>16),	// знач по умолч.

//[1601h.03h]
35968,	// формат
44,	// номер текста, название: RPDO2-3 Mapping
37,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1601h.04h]
35968,	// формат
45,	// номер текста, название: RPDO2-4 Mapping
38,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1602h, ТекстПУ=RPDO3M
4,	// кол-во подындексов
46,	// номер текста
3,	// такой длиной

//[1602h.01h]
35968,	// формат
47,	// номер текста, название: RPDO3-1 Mapping
39,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1602h.02h]
35968,	// формат
48,	// номер текста, название: RPDO3-2 Mapping
40,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1602h.03h]
35968,	// формат
49,	// номер текста, название: RPDO3-3 Mapping
41,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1602h.04h]
35968,	// формат
50,	// номер текста, название: RPDO3-4 Mapping
42,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1603h, ТекстПУ=RPDO4M
4,	// кол-во подындексов
51,	// номер текста
3,	// такой длиной

//[1603h.01h]
35968,	// формат
52,	// номер текста, название: RPDO4-1 Mapping
43,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1603h.02h]
35968,	// формат
53,	// номер текста, название: RPDO4-2 Mapping
44,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1603h.03h]
35968,	// формат
54,	// номер текста, название: RPDO4-3 Mapping
45,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1603h.04h]
35968,	// формат
55,	// номер текста, название: RPDO4-4 Mapping
46,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1604h, ТекстПУ=RPDO5M
4,	// кол-во подындексов
56,	// номер текста
3,	// такой длиной

//[1604h.01h]
35968,	// формат
57,	// номер текста, название: RPDO5-1 Mapping
47,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1604h.02h]
35968,	// формат
58,	// номер текста, название: RPDO5-2 Mapping
48,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1604h.03h]
35968,	// формат
59,	// номер текста, название: RPDO5-3 Mapping
49,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1604h.04h]
35968,	// формат
60,	// номер текста, название: RPDO5-4 Mapping
50,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1605h, ТекстПУ=RPDO6M
4,	// кол-во подындексов
61,	// номер текста
3,	// такой длиной

//[1605h.01h]
35968,	// формат
62,	// номер текста, название: RPDO6-1 Mapping
51,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1605h.02h]
35968,	// формат
63,	// номер текста, название: RPDO6-2 Mapping
52,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1605h.03h]
35968,	// формат
64,	// номер текста, название: RPDO6-3 Mapping
53,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1605h.04h]
35968,	// формат
65,	// номер текста, название: RPDO6-4 Mapping
54,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1606h, ТекстПУ=RPDO7M
4,	// кол-во подындексов
66,	// номер текста
3,	// такой длиной

//[1606h.01h]
35968,	// формат
67,	// номер текста, название: RPDO7-1 Mapping
55,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1606h.02h]
35968,	// формат
68,	// номер текста, название: RPDO7-2 Mapping
56,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1606h.03h]
35968,	// формат
69,	// номер текста, название: RPDO7-3 Mapping
57,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1606h.04h]
35968,	// формат
70,	// номер текста, название: RPDO7-4 Mapping
58,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1607h, ТекстПУ=RPDO8M
4,	// кол-во подындексов
71,	// номер текста
3,	// такой длиной

//[1607h.01h]
35968,	// формат
72,	// номер текста, название: RPDO8-1 Mapping
59,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1607h.02h]
35968,	// формат
73,	// номер текста, название: RPDO8-2 Mapping
60,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1607h.03h]
35968,	// формат
74,	// номер текста, название: RPDO8-3 Mapping
61,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1607h.04h]
35968,	// формат
75,	// номер текста, название: RPDO8-4 Mapping
62,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1800h, ТекстПУ=TPDO1P
5,	// кол-во подындексов
76,	// номер текста
2,	// такой длиной

//[1800h.01h]
3200,	// формат
77,	// номер текста, название: COB-ID for TPDO1
63,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1800h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
64,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1800h.03h]
35456,	// формат
78,	// номер текста, название: Inhibit Time 1
65,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1800h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
66,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1800h.05h]
35456,	// формат
80,	// номер текста, название: Event Timer 1
67,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

// Корневой подындекс 1801h, ТекстПУ=TPDO2P
5,	// кол-во подындексов
81,	// номер текста
2,	// такой длиной

//[1801h.01h]
3200,	// формат
82,	// номер текста, название: COB-ID for TPDO2
68,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1801h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
69,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1801h.03h]
35456,	// формат
83,	// номер текста, название: Inhibit Time 2
70,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1801h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
71,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1801h.05h]
35456,	// формат
84,	// номер текста, название: Event Timer 2
72,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1802h, ТекстПУ=TPDO3P
5,	// кол-во подындексов
85,	// номер текста
2,	// такой длиной

//[1802h.01h]
3200,	// формат
86,	// номер текста, название: COB-ID for TPDO3
73,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1802h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
74,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1802h.03h]
35456,	// формат
87,	// номер текста, название: Inhibit Time 3
75,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1802h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
76,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1802h.05h]
35456,	// формат
88,	// номер текста, название: Event Timer 3
77,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1803h, ТекстПУ=TPDO4P
5,	// кол-во подындексов
89,	// номер текста
2,	// такой длиной

//[1803h.01h]
3200,	// формат
90,	// номер текста, название: COB-ID for TPDO4
78,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1803h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
79,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1803h.03h]
35456,	// формат
91,	// номер текста, название: Inhibit Time 4
80,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1803h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
81,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1803h.05h]
35456,	// формат
92,	// номер текста, название: Event Timer 4
82,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1804h, ТекстПУ=TPDO5P
5,	// кол-во подындексов
93,	// номер текста
2,	// такой длиной

//[1804h.01h]
3200,	// формат
94,	// номер текста, название: COB-ID for TPDO5
83,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1804h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
84,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1804h.03h]
35456,	// формат
95,	// номер текста, название: Inhibit Time 5
85,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1804h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
86,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1804h.05h]
35456,	// формат
96,	// номер текста, название: Event Timer 5
87,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1805h, ТекстПУ=TPDO6P
5,	// кол-во подындексов
97,	// номер текста
2,	// такой длиной

//[1805h.01h]
3200,	// формат
98,	// номер текста, название: COB-ID for TPDO6
88,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1805h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
89,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1805h.03h]
35456,	// формат
99,	// номер текста, название: Inhibit Time 6
90,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1805h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
91,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1805h.05h]
35456,	// формат
100,	// номер текста, название: Event Timer 6
92,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1806h, ТекстПУ=TPDO7P
5,	// кол-во подындексов
101,	// номер текста
2,	// такой длиной

//[1806h.01h]
3200,	// формат
102,	// номер текста, название: COB-ID for TPDO7
93,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1806h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
94,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1806h.03h]
35456,	// формат
103,	// номер текста, название: Inhibit Time 7
95,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1806h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
96,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1806h.05h]
35456,	// формат
104,	// номер текста, название: Event Timer 7
97,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1807h, ТекстПУ=TPDO8P
5,	// кол-во подындексов
105,	// номер текста
2,	// такой длиной

//[1807h.01h]
3200,	// формат
106,	// номер текста, название: COB-ID for TPDO8
98,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1807h.02h]
2176,	// формат
21,	// номер текста, название: Тип передачи
99,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[1807h.03h]
35456,	// формат
107,	// номер текста, название: Inhibit Time 8
100,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.

//[1807h.04h]
18560,	// формат
79,	// номер текста, название: Compatibility Entry
101,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[1807h.05h]
35456,	// формат
108,	// номер текста, название: Event Timer 8
102,	// смещение для таблицы с адресами
(Uint16)(1000),	// знач по умолч.

// Корневой подындекс 1A00h, ТекстПУ=TPDO1M
4,	// кол-во подындексов
109,	// номер текста
3,	// такой длиной

//[1A00h.01h]
35968,	// формат
110,	// номер текста, название: TPDO1-1 Mapping
103,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A00h.02h]
35968,	// формат
111,	// номер текста, название: TPDO1-2 Mapping
104,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A00h.03h]
35968,	// формат
112,	// номер текста, название: TPDO1-3 Mapping
105,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A00h.04h]
35968,	// формат
113,	// номер текста, название: TPDO1-4 Mapping
106,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A01h, ТекстПУ=TPDO2M
4,	// кол-во подындексов
114,	// номер текста
3,	// такой длиной

//[1A01h.01h]
35968,	// формат
115,	// номер текста, название: TPDO2-1 Mapping
107,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A01h.02h]
35968,	// формат
116,	// номер текста, название: TPDO2-2 Mapping
108,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A01h.03h]
35968,	// формат
117,	// номер текста, название: TPDO2-3 Mapping
109,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A01h.04h]
35968,	// формат
118,	// номер текста, название: TPDO2-4 Mapping
110,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A02h, ТекстПУ=TPDO3M
4,	// кол-во подындексов
119,	// номер текста
3,	// такой длиной

//[1A02h.01h]
35968,	// формат
120,	// номер текста, название: TPDO3-1 Mapping
111,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A02h.02h]
35968,	// формат
121,	// номер текста, название: TPDO3-2 Mapping
112,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A02h.03h]
35968,	// формат
122,	// номер текста, название: TPDO3-3 Mapping
113,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A02h.04h]
35968,	// формат
123,	// номер текста, название: TPDO3-4 Mapping
114,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A03h, ТекстПУ=TPDO4M
4,	// кол-во подындексов
124,	// номер текста
3,	// такой длиной

//[1A03h.01h]
35968,	// формат
125,	// номер текста, название: TPDO4-1 Mapping
115,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A03h.02h]
35968,	// формат
126,	// номер текста, название: TPDO4-2 Mapping
116,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A03h.03h]
35968,	// формат
127,	// номер текста, название: TPDO4-3 Mapping
117,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A03h.04h]
35968,	// формат
128,	// номер текста, название: TPDO4-4 Mapping
118,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A04h, ТекстПУ=TPDO5M
4,	// кол-во подындексов
129,	// номер текста
3,	// такой длиной

//[1A04h.01h]
35968,	// формат
130,	// номер текста, название: TPDO5-1 Mapping
119,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A04h.02h]
35968,	// формат
131,	// номер текста, название: TPDO5-2 Mapping
120,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A04h.03h]
35968,	// формат
132,	// номер текста, название: TPDO5-3 Mapping
121,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A04h.04h]
35968,	// формат
133,	// номер текста, название: TPDO5-4 Mapping
122,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A05h, ТекстПУ=TPDO6M
4,	// кол-во подындексов
134,	// номер текста
3,	// такой длиной

//[1A05h.01h]
35968,	// формат
135,	// номер текста, название: TPDO6-1 Mapping
123,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A05h.02h]
35968,	// формат
136,	// номер текста, название: TPDO6-2 Mapping
124,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A05h.03h]
35968,	// формат
137,	// номер текста, название: TPDO6-3 Mapping
125,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A05h.04h]
35968,	// формат
138,	// номер текста, название: TPDO6-4 Mapping
126,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A06h, ТекстПУ=TPDO7M
4,	// кол-во подындексов
139,	// номер текста
3,	// такой длиной

//[1A06h.01h]
35968,	// формат
140,	// номер текста, название: TPDO7-1 Mapping
127,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A06h.02h]
35968,	// формат
141,	// номер текста, название: TPDO7-2 Mapping
128,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A06h.03h]
35968,	// формат
142,	// номер текста, название: TPDO7-3 Mapping
129,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A06h.04h]
35968,	// формат
143,	// номер текста, название: TPDO7-4 Mapping
130,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 1A07h, ТекстПУ=TPDO8M
4,	// кол-во подындексов
144,	// номер текста
3,	// такой длиной

//[1A07h.01h]
35968,	// формат
145,	// номер текста, название: TPDO8-1 Mapping
131,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A07h.02h]
35968,	// формат
146,	// номер текста, название: TPDO8-2 Mapping
132,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A07h.03h]
35968,	// формат
147,	// номер текста, название: TPDO8-3 Mapping
133,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[1A07h.04h]
35968,	// формат
148,	// номер текста, название: TPDO8-4 Mapping
134,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2000h.00h]
35328,	// формат
149,	// номер текста, название: CAN NODE-ID
135,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
(Uint16)(1),	// минимум
(Uint16)(127),	// максимум

//[2001h.00h]
41008,	// формат
150,	// номер текста, название: CAN Bit Rate
136,	// смещение для таблицы с адресами
(Uint16)(3),	// знач по умолч.

// Корневой подындекс 2002h, ТекстПУ=IdObj
4,	// кол-во подындексов
7,	// номер текста
1,	// такой длиной

//[2002h.01h]
3200,	// формат
8,	// номер текста, название: Код производителя
137,	// смещение для таблицы с адресами

//[2002h.02h]
3200,	// формат
9,	// номер текста, название: Код продукта
138,	// смещение для таблицы с адресами

//[2002h.03h]
3200,	// формат
10,	// номер текста, название: Номер ревизии
139,	// смещение для таблицы с адресами

//[2002h.04h]
3200,	// формат
11,	// номер текста, название: Серийный номер
140,	// смещение для таблицы с адресами

// Корневой подындекс 2003h, ТекстПУ=SpData
4,	// кол-во подындексов
151,	// номер текста
1,	// такой длиной

//[2003h.01h]
2688,	// формат
152,	// номер текста, название: Special Data 1
141,	// смещение для таблицы с адресами

//[2003h.02h]
2688,	// формат
153,	// номер текста, название: Special Data 2
142,	// смещение для таблицы с адресами

//[2003h.03h]
2688,	// формат
154,	// номер текста, название: Special Data 3
143,	// смещение для таблицы с адресами

//[2003h.04h]
2688,	// формат
155,	// номер текста, название: Special Data 4
144,	// смещение для таблицы с адресами

//[2004h.00h]
35968,	// формат
156,	// номер текста, название: Secret Code
145,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2005h.00h]
8208,	// формат
157,	// номер текста, название: Protect Bit
146,	// смещение для таблицы с адресами

// Корневой подындекс 2007h, ТекстПУ=OD_md5_hash
4,	// кол-во подындексов
158,	// номер текста
1,	// такой длиной

//[2007h.01h]
3200,	// формат
159,	// номер текста, название: md5_hash_0
147,	// смещение для таблицы с адресами

//[2007h.02h]
3200,	// формат
160,	// номер текста, название: md5_hash_1
148,	// смещение для таблицы с адресами

//[2007h.03h]
3200,	// формат
161,	// номер текста, название: md5_hash_2
149,	// смещение для таблицы с адресами

//[2007h.04h]
3200,	// формат
162,	// номер текста, название: md5_hash_3
150,	// смещение для таблицы с адресами

// Корневой подындекс 2010h, ТекстПУ=HBFlag
4,	// кол-во подындексов
163,	// номер текста
1,	// такой длиной

//[2010h.01h]
3200,	// формат
164,	// номер текста, название: Heartbeat Flag 0-31
151,	// смещение для таблицы с адресами

//[2010h.02h]
3200,	// формат
165,	// номер текста, название: Heartbeat Flag 32-63
152,	// смещение для таблицы с адресами

//[2010h.03h]
3200,	// формат
166,	// номер текста, название: Heartbeat Flag 64-95
153,	// смещение для таблицы с адресами

//[2010h.04h]
3200,	// формат
167,	// номер текста, название: Heartbeat Flag 96-127
154,	// смещение для таблицы с адресами

// Корневой подындекс 2011h, ТекстПУ=HBMask
4,	// кол-во подындексов
168,	// номер текста
3,	// такой длиной

//[2011h.01h]
35968,	// формат
169,	// номер текста, название: Heartbeat Mask 0-31
155,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2011h.02h]
35968,	// формат
170,	// номер текста, название: Heartbeat Mask 32-63
156,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2011h.03h]
35968,	// формат
171,	// номер текста, название: Heartbeat Mask 64-95
157,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2011h.04h]
35968,	// формат
172,	// номер текста, название: Heartbeat Mask 96-127
158,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2012h.00h]
40976,	// формат
173,	// номер текста, название: Heartbeat Autostart
159,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2014h.00h]
40976,	// формат
174,	// номер текста, название: Heartbeat Autorecovery
160,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2015h.00h]
2176,	// формат
175,	// номер текста, название: Состояние драйвера CAN-Open
161,	// смещение для таблицы с адресами

//[2016h.00h]
2688,	// формат
176,	// номер текста, название: Emergency Error Code
162,	// смещение для таблицы с адресами

//[2017h.00h]
3200,	// формат
177,	// номер текста, название: Device Error State
163,	// смещение для таблицы с адресами

// Корневой подындекс 2080h, ТекстПУ=ODComW
14,	// кол-во подындексов
178,	// номер текста
2,	// такой длиной

//[2080h.01h]
19072,	// формат
179,	// номер текста, название: Object Dictionary Command
164,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2080h.02h]
19072,	// формат
180,	// номер текста, название: Current OD Index
165,	// смещение для таблицы с адресами
(Uint16)(0x2000),	// знач по умолч.

//[2080h.03h]
19072,	// формат
181,	// номер текста, название: Current OD Sub-Index
166,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2080h.04h]
2688,	// формат
182,	// номер текста, название: Current OD Element Text
167,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.05h]
2688,	// формат
183,	// номер текста, название: Current OD Element Format
168,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.06h]
2688,	// формат
184,	// номер текста, название: Current OD Element Min
169,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.07h]
2688,	// формат
185,	// номер текста, название: Current OD Element Max
170,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.08h]
2688,	// формат
186,	// номер текста, название: Current OD Element Default
171,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.09h]
2688,	// формат
187,	// номер текста, название: Current OD Element MinLow
172,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.0Ah]
2688,	// формат
188,	// номер текста, название: Current OD Element MaxLow
173,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.0Bh]
2688,	// формат
189,	// номер текста, название: Current OD Element Default Low
174,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.0Ch]
2688,	// формат
190,	// номер текста, название: Current OD Element Address
175,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.0Dh]
2688,	// формат
190,	// номер текста, название: Current OD Element Address
176,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2080h.0Eh]
2688,	// формат
191,	// номер текста, название: Группа параметров
177,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2081h.00h]
2688,	// формат
192,	// номер текста, название: Количество индексов
178,	// смещение для таблицы с адресами

// Корневой подындекс 2082h, ТекстПУ=DefInd
2,	// кол-во подындексов
193,	// номер текста
3,	// такой длиной

//[2082h.01h]
19584,	// формат
194,	// номер текста, название: Default Index 1
179,	// смещение для таблицы с адресами
(Uint16)(0x30000000),	// знач по умолч.
(((Uint32)0x30000000)>>16),	// знач по умолч.

//[2082h.02h]
19584,	// формат
195,	// номер текста, название: Default Index 2
180,	// смещение для таблицы с адресами
(Uint16)(0x30000000),	// знач по умолч.
(((Uint32)0x30000000)>>16),	// знач по умолч.

// Корневой подындекс 2083h, ТекстПУ=ProfML
16,	// кол-во подындексов
196,	// номер текста
2,	// такой длиной

//[2083h.01h]
24704,	// формат
197,	// номер текста, название: Mask Element
181,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.02h]
24712,	// формат
198,	// номер текста, название: Mask Element
182,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.03h]
24704,	// формат
199,	// номер текста, название: Mask Element
183,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.04h]
24712,	// формат
200,	// номер текста, название: Mask Element
184,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.05h]
24704,	// формат
201,	// номер текста, название: Mask Element
185,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.06h]
24712,	// формат
202,	// номер текста, название: Mask Element
186,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.07h]
24704,	// формат
203,	// номер текста, название: Mask Element
187,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.08h]
24712,	// формат
204,	// номер текста, название: Mask Element
188,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.09h]
24704,	// формат
205,	// номер текста, название: Mask Element
189,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Ah]
24712,	// формат
206,	// номер текста, название: Mask Element
190,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Bh]
24704,	// формат
207,	// номер текста, название: Mask Element
191,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Ch]
24712,	// формат
208,	// номер текста, название: Mask Element
192,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Dh]
24704,	// формат
209,	// номер текста, название: Mask Element
193,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Eh]
24712,	// формат
210,	// номер текста, название: Mask Element
194,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.0Fh]
24704,	// формат
211,	// номер текста, название: Mask Element
195,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2083h.10h]
24712,	// формат
212,	// номер текста, название: Mask Element
196,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 2100h, ТекстПУ=SNR0
6,	// кол-во подындексов
213,	// номер текста
2,	// такой длиной

//[2100h.01h]
2688,	// формат
214,	// номер текста, название: Scale Number 0
197,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2100h.02h]
19072,	// формат
215,	// номер текста, название: Scale Number 0 Format
198,	// смещение для таблицы с адресами
(Uint16)(32),	// знач по умолч.

//[2100h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
199,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2100h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
200,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2100h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
201,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2100h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
202,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 2101h, ТекстПУ=SNR1
6,	// кол-во подындексов
220,	// номер текста
2,	// такой длиной

//[2101h.01h]
2688,	// формат
221,	// номер текста, название: Scale Number 1
203,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2101h.02h]
19072,	// формат
222,	// номер текста, название: Scale Number 1 Format
204,	// смещение для таблицы с адресами
(Uint16)(4128),	// знач по умолч.

//[2101h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
205,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2101h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
206,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2101h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
207,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2101h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
208,	// смещение для таблицы с адресами
(Uint16)(4),	// знач по умолч.

// Корневой подындекс 2102h, ТекстПУ=SNR2
6,	// кол-во подындексов
223,	// номер текста
2,	// такой длиной

//[2102h.01h]
2688,	// формат
224,	// номер текста, название: Scale Number 2
209,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2102h.02h]
19072,	// формат
225,	// номер текста, название: Scale Number 2 Format
210,	// смещение для таблицы с адресами
(Uint16)(3136),	// знач по умолч.

//[2102h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
211,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2102h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
212,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2102h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
213,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2102h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
214,	// смещение для таблицы с адресами
(Uint16)(3),	// знач по умолч.

// Корневой подындекс 2103h, ТекстПУ=SNR3
6,	// кол-во подындексов
226,	// номер текста
2,	// такой длиной

//[2103h.01h]
2688,	// формат
227,	// номер текста, название: Scale Number 3
215,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2103h.02h]
19072,	// формат
228,	// номер текста, название: Scale Number 3 Format
216,	// смещение для таблицы с адресами
(Uint16)(2112),	// знач по умолч.

//[2103h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
217,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2103h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
218,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2103h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
219,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2103h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
220,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

// Корневой подындекс 2104h, ТекстПУ=SNR4
6,	// кол-во подындексов
229,	// номер текста
2,	// такой длиной

//[2104h.01h]
2688,	// формат
230,	// номер текста, название: Scale Number 4
221,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2104h.02h]
19072,	// формат
231,	// номер текста, название: Scale Number 4 Format
222,	// смещение для таблицы с адресами
(Uint16)(1056),	// знач по умолч.

//[2104h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
223,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2104h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
224,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2104h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
225,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2104h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
226,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

// Корневой подындекс 2105h, ТекстПУ=SNR5
6,	// кол-во подындексов
232,	// номер текста
2,	// такой длиной

//[2105h.01h]
2688,	// формат
233,	// номер текста, название: Scale Number 5
227,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2105h.02h]
19072,	// формат
234,	// номер текста, название: Scale Number 5 Format
228,	// смещение для таблицы с адресами
(Uint16)(1056),	// знач по умолч.

//[2105h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
229,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2105h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
230,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2105h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
231,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2105h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
232,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

// Корневой подындекс 2106h, ТекстПУ=SNR6
6,	// кол-во подындексов
235,	// номер текста
2,	// такой длиной

//[2106h.01h]
2688,	// формат
236,	// номер текста, название: Scale Number 6
233,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2106h.02h]
19072,	// формат
237,	// номер текста, название: Scale Number 6 Format
234,	// смещение для таблицы с адресами
(Uint16)(1088),	// знач по умолч.

//[2106h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
235,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2106h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
236,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2106h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
237,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2106h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
238,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

// Корневой подындекс 2107h, ТекстПУ=SNR7
6,	// кол-во подындексов
238,	// номер текста
2,	// такой длиной

//[2107h.01h]
2688,	// формат
239,	// номер текста, название: Scale Number 7
239,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2107h.02h]
19072,	// формат
240,	// номер текста, название: Scale Number 7 Format
240,	// смещение для таблицы с адресами
(Uint16)(2112),	// знач по умолч.

//[2107h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
241,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2107h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
242,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2107h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
243,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2107h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
244,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

// Корневой подындекс 2108h, ТекстПУ=SNR8
6,	// кол-во подындексов
241,	// номер текста
2,	// такой длиной

//[2108h.01h]
2688,	// формат
242,	// номер текста, название: Scale Number 8
245,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2108h.02h]
19072,	// формат
243,	// номер текста, название: Scale Number 8 Format
246,	// смещение для таблицы с адресами
(Uint16)(9286),	// знач по умолч.

//[2108h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
247,	// смещение для таблицы с адресами
(Uint16)(6),	// знач по умолч.

//[2108h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
248,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2108h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
249,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2108h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
250,	// смещение для таблицы с адресами
(Uint16)(9),	// знач по умолч.

// Корневой подындекс 2109h, ТекстПУ=SNR9
6,	// кол-во подындексов
244,	// номер текста
2,	// такой длиной

//[2109h.01h]
2688,	// формат
245,	// номер текста, название: Scale Number 9
251,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2109h.02h]
19072,	// формат
246,	// номер текста, название: Scale Number 9 Format
252,	// смещение для таблицы с адресами
(Uint16)(5184),	// знач по умолч.

//[2109h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
253,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2109h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
254,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2109h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
255,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2109h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
256,	// смещение для таблицы с адресами
(Uint16)(5),	// знач по умолч.

// Корневой подындекс 210Ah, ТекстПУ=SNRA
6,	// кол-во подындексов
247,	// номер текста
2,	// такой длиной

//[210Ah.01h]
2688,	// формат
248,	// номер текста, название: Scale Number A
257,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Ah.02h]
19072,	// формат
249,	// номер текста, название: Scale Number A Format
258,	// смещение для таблицы с адресами
(Uint16)(12320),	// знач по умолч.

//[210Ah.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
259,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Ah.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
260,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[210Ah.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
261,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Ah.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
262,	// смещение для таблицы с адресами
(Uint16)(12),	// знач по умолч.

// Корневой подындекс 210Bh, ТекстПУ=SNRB
6,	// кол-во подындексов
250,	// номер текста
2,	// такой длиной

//[210Bh.01h]
2688,	// формат
251,	// номер текста, название: Scale Number B
263,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Bh.02h]
19072,	// формат
252,	// номер текста, название: Scale Number B Format
264,	// смещение для таблицы с адресами
(Uint16)(6144),	// знач по умолч.

//[210Bh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
265,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Bh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
266,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Bh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
267,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Bh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
268,	// смещение для таблицы с адресами
(Uint16)(6),	// знач по умолч.

// Корневой подындекс 210Ch, ТекстПУ=SNRC
6,	// кол-во подындексов
253,	// номер текста
2,	// такой длиной

//[210Ch.01h]
2688,	// формат
254,	// номер текста, название: Scale Number C
269,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Ch.02h]
19072,	// формат
255,	// номер текста, название: Scale Number C Format
270,	// смещение для таблицы с адресами
(Uint16)(7168),	// знач по умолч.

//[210Ch.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
271,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Ch.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
272,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Ch.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
273,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Ch.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
274,	// смещение для таблицы с адресами
(Uint16)(7),	// знач по умолч.

// Корневой подындекс 210Dh, ТекстПУ=SNRD
6,	// кол-во подындексов
256,	// номер текста
2,	// такой длиной

//[210Dh.01h]
2688,	// формат
257,	// номер текста, название: Scale Number D
275,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Dh.02h]
19072,	// формат
258,	// номер текста, название: Scale Number D Format
276,	// смещение для таблицы с адресами
(Uint16)(2048),	// знач по умолч.

//[210Dh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
277,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Dh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
278,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Dh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
279,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Dh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
280,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

// Корневой подындекс 210Eh, ТекстПУ=SNRE
6,	// кол-во подындексов
259,	// номер текста
2,	// такой длиной

//[210Eh.01h]
2688,	// формат
260,	// номер текста, название: Scale Number E
281,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Eh.02h]
19072,	// формат
261,	// номер текста, название: Scale Number E Format
282,	// смещение для таблицы с адресами
(Uint16)(1024),	// знач по умолч.

//[210Eh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
283,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Eh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
284,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Eh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
285,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Eh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
286,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

// Корневой подындекс 210Fh, ТекстПУ=SNRF
6,	// кол-во подындексов
262,	// номер текста
2,	// такой длиной

//[210Fh.01h]
2688,	// формат
263,	// номер текста, название: Scale Number F
287,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[210Fh.02h]
19072,	// формат
264,	// номер текста, название: Scale Number F Format
288,	// смещение для таблицы с адресами
(Uint16)(96),	// знач по умолч.

//[210Fh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
289,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Fh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
290,	// смещение для таблицы с адресами
(Uint16)(3),	// знач по умолч.

//[210Fh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
291,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[210Fh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
292,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 2110h, ТекстПУ=SNR10
6,	// кол-во подындексов
265,	// номер текста
2,	// такой длиной

//[2110h.01h]
2688,	// формат
266,	// номер текста, название: Scale Number 10
293,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2110h.02h]
19072,	// формат
267,	// номер текста, название: Scale Number 10 Format
294,	// смещение для таблицы с адресами
(Uint16)(3136),	// знач по умолч.

//[2110h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
295,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2110h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
296,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2110h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
297,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2110h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
298,	// смещение для таблицы с адресами
(Uint16)(3),	// знач по умолч.

// Корневой подындекс 2111h, ТекстПУ=SNR11
6,	// кол-во подындексов
268,	// номер текста
2,	// такой длиной

//[2111h.01h]
2688,	// формат
269,	// номер текста, название: Scale Number 11
299,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2111h.02h]
19072,	// формат
270,	// номер текста, название: Scale Number 11 Format
300,	// смещение для таблицы с адресами
(Uint16)(9408),	// знач по умолч.

//[2111h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
301,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2111h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
302,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2111h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
303,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2111h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
304,	// смещение для таблицы с адресами
(Uint16)(9),	// знач по умолч.

// Корневой подындекс 2112h, ТекстПУ=SNR12
6,	// кол-во подындексов
271,	// номер текста
2,	// такой длиной

//[2112h.01h]
2688,	// формат
272,	// номер текста, название: Scale Number 12
305,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2112h.02h]
19072,	// формат
273,	// номер текста, название: Scale Number 12 Format
306,	// смещение для таблицы с адресами
(Uint16)(9414),	// знач по умолч.

//[2112h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
307,	// смещение для таблицы с адресами
(Uint16)(6),	// знач по умолч.

//[2112h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
308,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2112h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
309,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2112h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
310,	// смещение для таблицы с адресами
(Uint16)(9),	// знач по умолч.

// Корневой подындекс 2113h, ТекстПУ=SNR13
6,	// кол-во подындексов
274,	// номер текста
2,	// такой длиной

//[2113h.01h]
2688,	// формат
275,	// номер текста, название: Scale Number 13
311,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2113h.02h]
19072,	// формат
276,	// номер текста, название: Scale Number 13 Format
312,	// смещение для таблицы с адресами
(Uint16)(12352),	// знач по умолч.

//[2113h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
313,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2113h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
314,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2113h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
315,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2113h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
316,	// смещение для таблицы с адресами
(Uint16)(12),	// знач по умолч.

// Корневой подындекс 2114h, ТекстПУ=SNR14
6,	// кол-во подындексов
277,	// номер текста
2,	// такой длиной

//[2114h.01h]
2688,	// формат
278,	// номер текста, название: Scale Number 14
317,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2114h.02h]
19072,	// формат
279,	// номер текста, название: Scale Number 14 Format
318,	// смещение для таблицы с адресами
(Uint16)(13344),	// знач по умолч.

//[2114h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
319,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2114h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
320,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

//[2114h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
321,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2114h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
322,	// смещение для таблицы с адресами
(Uint16)(13),	// знач по умолч.

// Корневой подындекс 2115h, ТекстПУ=SNR15
6,	// кол-во подындексов
280,	// номер текста
2,	// такой длиной

//[2115h.01h]
2688,	// формат
281,	// номер текста, название: Scale Number 15
323,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2115h.02h]
19072,	// формат
282,	// номер текста, название: Scale Number 15Format
324,	// смещение для таблицы с адресами
(Uint16)(10240),	// знач по умолч.

//[2115h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
325,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2115h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
326,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2115h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
327,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2115h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
328,	// смещение для таблицы с адресами
(Uint16)(10),	// знач по умолч.

// Корневой подындекс 2116h, ТекстПУ=SNR16
6,	// кол-во подындексов
283,	// номер текста
2,	// такой длиной

//[2116h.01h]
2688,	// формат
284,	// номер текста, название: Scale Number 16
329,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2116h.02h]
19072,	// формат
285,	// номер текста, название: Scale Number 16Format
330,	// смещение для таблицы с адресами
(Uint16)(14400),	// знач по умолч.

//[2116h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
331,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2116h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
332,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2116h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
333,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2116h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
334,	// смещение для таблицы с адресами
(Uint16)(14),	// знач по умолч.

// Корневой подындекс 2117h, ТекстПУ=SNR17
6,	// кол-во подындексов
286,	// номер текста
2,	// такой длиной

//[2117h.01h]
2688,	// формат
287,	// номер текста, название: Scale Number 17
335,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2117h.02h]
19072,	// формат
288,	// номер текста, название: Scale Number 17Format
336,	// смещение для таблицы с адресами
(Uint16)(15430),	// знач по умолч.

//[2117h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
337,	// смещение для таблицы с адресами
(Uint16)(6),	// знач по умолч.

//[2117h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
338,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2117h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
339,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2117h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
340,	// смещение для таблицы с адресами
(Uint16)(15),	// знач по умолч.

// Корневой подындекс 2118h, ТекстПУ=SNR18
6,	// кол-во подындексов
289,	// номер текста
2,	// такой длиной

//[2118h.01h]
2688,	// формат
290,	// номер текста, название: Scale Number 18
341,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2118h.02h]
19072,	// формат
291,	// номер текста, название: Scale Number 18Format
342,	// смещение для таблицы с адресами
(Uint16)(16448),	// знач по умолч.

//[2118h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
343,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2118h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
344,	// смещение для таблицы с адресами
(Uint16)(2),	// знач по умолч.

//[2118h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
345,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2118h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
346,	// смещение для таблицы с адресами
(Uint16)(16),	// знач по умолч.

// Корневой подындекс 2119h, ТекстПУ=SNR19
6,	// кол-во подындексов
292,	// номер текста
2,	// такой длиной

//[2119h.01h]
2688,	// формат
293,	// номер текста, название: Scale Number 19
347,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[2119h.02h]
19072,	// формат
294,	// номер текста, название: Scale Number 19Format
348,	// смещение для таблицы с адресами
(Uint16)(13312),	// знач по умолч.

//[2119h.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
349,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2119h.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
350,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2119h.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
351,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[2119h.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
352,	// смещение для таблицы с адресами
(Uint16)(13),	// знач по умолч.

// Корневой подындекс 211Ah, ТекстПУ=SNR1A
6,	// кол-во подындексов
295,	// номер текста
2,	// такой длиной

//[211Ah.01h]
2688,	// формат
296,	// номер текста, название: Scale Number 1A
353,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[211Ah.02h]
19072,	// формат
297,	// номер текста, название: Scale Number 1AFormat
354,	// смещение для таблицы с адресами
(Uint16)(14336),	// знач по умолч.

//[211Ah.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
355,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ah.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
356,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ah.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
357,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ah.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
358,	// смещение для таблицы с адресами
(Uint16)(14),	// знач по умолч.

// Корневой подындекс 211Bh, ТекстПУ=SNR1B
6,	// кол-во подындексов
298,	// номер текста
2,	// такой длиной

//[211Bh.01h]
2688,	// формат
299,	// номер текста, название: Scale Number 1B
359,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[211Bh.02h]
19072,	// формат
300,	// номер текста, название: Scale Number 1BFormat
360,	// смещение для таблицы с адресами
(Uint16)(12384),	// знач по умолч.

//[211Bh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
361,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Bh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
362,	// смещение для таблицы с адресами
(Uint16)(3),	// знач по умолч.

//[211Bh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
363,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Bh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
364,	// смещение для таблицы с адресами
(Uint16)(12),	// знач по умолч.

// Корневой подындекс 211Ch, ТекстПУ=SNR1C
6,	// кол-во подындексов
301,	// номер текста
2,	// такой длиной

//[211Ch.01h]
2688,	// формат
302,	// номер текста, название: Scale Number 1C
365,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[211Ch.02h]
19072,	// формат
303,	// номер текста, название: Scale Number 1C Format
366,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ch.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
367,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ch.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
368,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ch.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
369,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Ch.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
370,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 211Dh, ТекстПУ=SNR1D
6,	// кол-во подындексов
304,	// номер текста
2,	// такой длиной

//[211Dh.01h]
2688,	// формат
305,	// номер текста, название: Scale Number 1D
371,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[211Dh.02h]
19072,	// формат
306,	// номер текста, название: Scale Number 1D Format
372,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Dh.03h]
25168,	// формат
216,	// номер текста, название: Scale Number Format Q
373,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Dh.04h]
25125,	// формат
217,	// номер текста, название: Scale Number Format NumOfFloat
374,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Dh.05h]
24631,	// формат
218,	// номер текста, название: Scale Number Format Prefix
375,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

//[211Dh.06h]
24682,	// формат
219,	// номер текста, название: Scale Number Format Units
376,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 2502h, ТекстПУ=КмдCAN
4,	// кол-во подындексов
307,	// номер текста
4,	// такой длиной

//[2502h.01h]
24592,	// формат
308,	// номер текста, название: Пуск
377,	// смещение для таблицы с адресами
(Uint16)(256),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[2502h.02h]
24593,	// формат
309,	// номер текста, название: Стоп
378,	// смещение для таблицы с адресами
(Uint16)(256),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[2502h.03h]
24594,	// формат
310,	// номер текста, название: Сбросить состояние Аварии
379,	// смещение для таблицы с адресами
(Uint16)(256),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[2502h.04h]
18944,	// формат
307,	// номер текста, название: Слово управления CAN
380,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(1),	// максимум

// Корневой подындекс 2506h, ТекстПУ=interf
4,	// кол-во подындексов
756,	// номер текста
3,	// такой длиной

//[2506h.01h]
19584,	// формат
581,	// номер текста, название: Таймаут потери связи
381,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2506h.02h]
19584,	// формат
582,	// номер текста, название: Счетчик потери связи
382,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2506h.03h]
19584,	// формат
754,	// номер текста, название: data_Low
383,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[2506h.04h]
19584,	// формат
753,	// номер текста, название: data_High
384,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[250Fh.00h]
19584,	// формат
311,	// номер текста, название: Часы реального времени
385,	// смещение для таблицы с адресами
(Uint16)(438392299),	// знач по умолч.
(((Uint32)438392299)>>16),	// знач по умолч.

// Корневой подындекс 2532h, ТекстПУ=System
3,	// кол-во подындексов
312,	// номер текста
1,	// такой длиной

//[2532h.01h]
8320,	// формат
313,	// номер текста, название: Код аварии MCB4
386,	// смещение для таблицы с адресами

//[2532h.02h]
8328,	// формат
314,	// номер текста, название: Расширение кода аварии
387,	// смещение для таблицы с адресами

//[2532h.03h]
8208,	// формат
312,	// номер текста, название: Системный объект
388,	// смещение для таблицы с адресами

// Корневой подындекс 2534h, ТекстПУ=Конфиг. ПУ
1,	// кол-во подындексов
315,	// номер текста
2,	// такой длиной

//[2534h.01h]
19072,	// формат
316,	// номер текста, название: Номер груп для пульта управления
389,	// смещение для таблицы с адресами
(Uint16)(15),	// знач по умолч.

// Корневой подындекс 2600h, ТекстПУ=VendorToken
1,	// кол-во подындексов
577,	// номер текста
3,	// такой длиной

//[2600h.01h]
19584,	// формат
577,	// номер текста, название: VendorToken
390,	// смещение для таблицы с адресами
(Uint16)(0x33333333),	// знач по умолч.
(((Uint32)0x33333333)>>16),	// знач по умолч.

//[2700h.00h]
19072,	// формат
596,	// номер текста, название: Block Transfer Interpreter
391,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.

// Корневой подындекс 2701h, ТекстПУ=CAN programming
15,	// кол-во подындексов
597,	// номер текста
7,	// такой длиной

//[2701h.01h]
19456,	// формат
598,	// номер текста, название: cmd
392,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.02h]
19456,	// формат
599,	// номер текста, название: status
393,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.03h]
19456,	// формат
600,	// номер текста, название: quest1
394,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.04h]
19456,	// формат
601,	// номер текста, название: quest2
395,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.05h]
19456,	// формат
602,	// номер текста, название: quest3
396,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.06h]
19456,	// формат
603,	// номер текста, название: quest4
397,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.07h]
19456,	// формат
604,	// номер текста, название: ans1
398,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.08h]
19456,	// формат
605,	// номер текста, название: ans2
399,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.09h]
19456,	// формат
606,	// номер текста, название: ans3
400,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Ah]
19456,	// формат
607,	// номер текста, название: ans4
401,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Bh]
19456,	// формат
608,	// номер текста, название: addr
402,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Ch]
19456,	// формат
609,	// номер текста, название: CPU_ID
403,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Dh]
19456,	// формат
610,	// номер текста, название: sector_mask
404,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Eh]
19456,	// формат
611,	// номер текста, название: version
405,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[2701h.0Fh]
19584,	// формат
612,	// номер текста, название: CRC
406,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[3000h.00h]
8288,	// формат
317,	// номер текста, название: Статус преобразователя
407,	// смещение для таблицы с адресами

// Корневой подындекс 3100h, ТекстПУ=System
5,	// кол-во подындексов
312,	// номер текста
3,	// такой длиной

//[3100h.01h]
3200,	// формат
318,	// номер текста, название: Счётчик прерываний 1 кГц
408,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[3100h.02h]
3200,	// формат
319,	// номер текста, название: Счётчик прерываний 10 кГц
409,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[3100h.03h]
2688,	// формат
320,	// номер текста, название: BackgroundCounter
410,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[3100h.04h]
19584,	// формат
321,	// номер текста, название: T_10кГц
411,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

//[3100h.05h]
19584,	// формат
322,	// номер текста, название: T_1кГц
412,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.

// Корневой подындекс 5000h, ТекстПУ=ЗИ
3,	// кол-во подындексов
323,	// номер текста
7,	// такой длиной

//[5000h.01h]
38200,	// формат
324,	// номер текста, название: T разгона до номинала
413,	// смещение для таблицы с адресами
(Uint16)(16777216),	// знач по умолч.
(((Uint32)16777216)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(_IQ(120.0)),	// максимум
(((Uint32)_IQ(120.0))>>16),	// максимум

//[5000h.02h]
5784,	// формат
325,	// номер текста, название: Вход ЗИ
414,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5000h.03h]
5784,	// формат
326,	// номер текста, название: Выход ЗИ
415,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5100h, ТекстПУ=Рег_id
13,	// кол-во подындексов
327,	// номер текста
7,	// такой длиной

//[5100h.01h]
5272,	// формат
328,	// номер текста, название: Задание
416,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.02h]
5272,	// формат
329,	// номер текста, название: Обратная связь
417,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.03h]
22008,	// формат
330,	// номер текста, название: Пропорц. коэфф. Kp
418,	// смещение для таблицы с адресами
(Uint16)(335544),	// знач по умолч.
(((Uint32)335544)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5100h.04h]
21624,	// формат
331,	// номер текста, название: Максимум выхода
419,	// смещение для таблицы с адресами
(Uint16)(16777216),	// знач по умолч.
(((Uint32)16777216)>>16),	// знач по умолч.
(Uint16)(_IQ(-1.0)),	// минимум
(((Uint32)_IQ(-1.0))>>16),	// минимум
(Uint16)(_IQ(1.0)),	// максимум
(((Uint32)_IQ(1.0))>>16),	// максимум

//[5100h.05h]
21624,	// формат
332,	// номер текста, название: Минимум выхода
420,	// смещение для таблицы с адресами
(Uint16)(-16777216),	// знач по умолч.
(((Uint32)-16777216)>>16),	// знач по умолч.
(Uint16)(_IQ(-1.0)),	// минимум
(((Uint32)_IQ(-1.0))>>16),	// минимум
(Uint16)(_IQ(1.0)),	// максимум
(((Uint32)_IQ(1.0))>>16),	// максимум

//[5100h.06h]
22008,	// формат
333,	// номер текста, название: Интегральный коэфф. Ki
421,	// смещение для таблицы с адресами
(Uint16)(2684354),	// знач по умолч.
(((Uint32)2684354)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5100h.07h]
22008,	// формат
334,	// номер текста, название: Дифф. коэфф. Kd
422,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5100h.08h]
22008,	// формат
335,	// номер текста, название: Интегр.корректир.коэффициент
423,	// смещение для таблицы с адресами
(Uint16)(8388608),	// знач по умолч.
(((Uint32)8388608)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5100h.09h]
5272,	// формат
336,	// номер текста, название: Ошибка рассогласования сигналов
424,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.0Ah]
5240,	// формат
337,	// номер текста, название: Выход регулятора
425,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.0Bh]
5240,	// формат
338,	// номер текста, название: Вых.Пропорц.
426,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.0Ch]
5240,	// формат
339,	// номер текста, название: Вых.Интегр.
427,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5100h.0Dh]
5240,	// формат
340,	// номер текста, название: Вых.Диффер.
428,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5101h, ТекстПУ=РегСкр
14,	// кол-во подындексов
341,	// номер текста
7,	// такой длиной

//[5101h.01h]
5784,	// формат
342,	// номер текста, название: Задание
429,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.02h]
5784,	// формат
343,	// номер текста, название: Обратная связь
430,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.03h]
22008,	// формат
330,	// номер текста, название: Пропорц. коэфф. Kp
431,	// смещение для таблицы с адресами
(Uint16)(3355443),	// знач по умолч.
(((Uint32)3355443)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.04h]
21656,	// формат
331,	// номер текста, название: Максимум выхода
432,	// смещение для таблицы с адресами
(Uint16)(13421772),	// знач по умолч.
(((Uint32)13421772)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.05h]
21656,	// формат
332,	// номер текста, название: Минимум выхода
433,	// смещение для таблицы с адресами
(Uint16)(-13421772),	// знач по умолч.
(((Uint32)-13421772)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.06h]
22008,	// формат
333,	// номер текста, название: Интегральный коэфф. Ki
434,	// смещение для таблицы с адресами
(Uint16)(16777),	// знач по умолч.
(((Uint32)16777)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.07h]
22008,	// формат
344,	// номер текста, название: Дифф. коэфф. Kd
435,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.08h]
22008,	// формат
335,	// номер текста, название: Интегр.корректир.коэффициент
436,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5101h.09h]
5784,	// формат
336,	// номер текста, название: Ошибка рассогласования сигналов
437,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.0Ah]
5272,	// формат
345,	// номер текста, название: Выход регулятора
438,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.0Bh]
5272,	// формат
338,	// номер текста, название: Вых.Пропорц.
439,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.0Ch]
5272,	// формат
339,	// номер текста, название: Вых.Интегр.
440,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.0Dh]
5272,	// формат
340,	// номер текста, название: Вых.Диффер.
441,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5101h.0Eh]
5272,	// формат
346,	// номер текста, название: Превышение насыщения
442,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5102h, ТекстПУ=Рег_iq
13,	// кол-во подындексов
347,	// номер текста
7,	// такой длиной

//[5102h.01h]
5272,	// формат
348,	// номер текста, название: Задание
443,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.02h]
5272,	// формат
349,	// номер текста, название: Обратная связь
444,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.03h]
22008,	// формат
350,	// номер текста, название: Пропорц. коэфф. Kp
445,	// смещение для таблицы с адресами
(Uint16)(335544),	// знач по умолч.
(((Uint32)335544)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5102h.04h]
21624,	// формат
351,	// номер текста, название: Максимум выхода
446,	// смещение для таблицы с адресами
(Uint16)(16777216),	// знач по умолч.
(((Uint32)16777216)>>16),	// знач по умолч.
(Uint16)(_IQ(-1.0)),	// минимум
(((Uint32)_IQ(-1.0))>>16),	// минимум
(Uint16)(_IQ(1.0)),	// максимум
(((Uint32)_IQ(1.0))>>16),	// максимум

//[5102h.05h]
21624,	// формат
352,	// номер текста, название: Минимум выхода
447,	// смещение для таблицы с адресами
(Uint16)(-16777216),	// знач по умолч.
(((Uint32)-16777216)>>16),	// знач по умолч.
(Uint16)(_IQ(-1.0)),	// минимум
(((Uint32)_IQ(-1.0))>>16),	// минимум
(Uint16)(_IQ(1.0)),	// максимум
(((Uint32)_IQ(1.0))>>16),	// максимум

//[5102h.06h]
22008,	// формат
353,	// номер текста, название: Интегральный коэфф. Ki
448,	// смещение для таблицы с адресами
(Uint16)(2684354),	// знач по умолч.
(((Uint32)2684354)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5102h.07h]
22008,	// формат
354,	// номер текста, название: Дифф. коэфф. Kd
449,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5102h.08h]
22008,	// формат
335,	// номер текста, название: Интегр.корректир.коэффициент
450,	// смещение для таблицы с адресами
(Uint16)(8388608),	// знач по умолч.
(((Uint32)8388608)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5102h.09h]
5272,	// формат
336,	// номер текста, название: Ошибка рассогласования сигналов
451,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.0Ah]
5240,	// формат
355,	// номер текста, название: Выход регулятора
452,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.0Bh]
5240,	// формат
338,	// номер текста, название: Вых.Пропорц.
453,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.0Ch]
5240,	// формат
339,	// номер текста, название: Вых.Интегр.
454,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5102h.0Dh]
5240,	// формат
340,	// номер текста, название: Вых.Диффер.
455,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5103h, ТекстПУ=pos_reg
20,	// кол-во подындексов
356,	// номер текста
7,	// такой длиной

//[5103h.01h]
19840,	// формат
342,	// номер текста, название: Задание
456,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.02h]
22136,	// формат
342,	// номер текста, название: Задание
457,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.03h]
5752,	// формат
343,	// номер текста, название: Обратная связь
458,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.04h]
3456,	// формат
343,	// номер текста, название: Обратная связь
459,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.05h]
22008,	// формат
330,	// номер текста, название: Пропорц. коэфф. Kp
460,	// смещение для таблицы с адресами
(Uint16)(1174405120),	// знач по умолч.
(((Uint32)1174405120)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.06h]
22168,	// формат
331,	// номер текста, название: Максимум выхода
461,	// смещение для таблицы с адресами
(Uint16)(100663296),	// знач по умолч.
(((Uint32)100663296)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.07h]
22168,	// формат
332,	// номер текста, название: Минимум выхода
462,	// смещение для таблицы с адресами
(Uint16)(-100663296),	// знач по умолч.
(((Uint32)-100663296)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.08h]
22008,	// формат
333,	// номер текста, название: Интегральный коэфф. Ki
463,	// смещение для таблицы с адресами
(Uint16)(83886),	// знач по умолч.
(((Uint32)83886)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.09h]
22008,	// формат
344,	// номер текста, название: Дифф. коэфф. Kd
464,	// смещение для таблицы с адресами
(Uint16)(167772160),	// знач по умолч.
(((Uint32)167772160)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.0Ah]
19840,	// формат
357,	// номер текста, название: Делит. дифф. части
465,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.0Bh]
22008,	// формат
358,	// номер текста, название: Коэф. фильтра
466,	// смещение для таблицы с адресами
(Uint16)(8388608),	// знач по умолч.
(((Uint32)8388608)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.0Ch]
22008,	// формат
335,	// номер текста, название: Интегр.корректир.коэффициент
467,	// смещение для таблицы с адресами
(Uint16)(8388608),	// знач по умолч.
(((Uint32)8388608)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.0Dh]
22136,	// формат
359,	// номер текста, название: Мертвая зона
468,	// смещение для таблицы с адресами
(Uint16)(13981),	// знач по умолч.
(((Uint32)13981)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5103h.0Eh]
5752,	// формат
336,	// номер текста, название: Ошибка рассогласования сигналов
469,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.0Fh]
5624,	// формат
346,	// номер текста, название: Превышение насыщения
470,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.10h]
5784,	// формат
345,	// номер текста, название: Выход регулятора
471,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.11h]
5784,	// формат
338,	// номер текста, название: Вых.Пропорц.
472,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.12h]
5784,	// формат
339,	// номер текста, название: Вых.Интегр.
473,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.13h]
5784,	// формат
340,	// номер текста, название: Вых.Диффер.
474,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5103h.14h]
5752,	// формат
360,	// номер текста, название: Фильтр ошибки
475,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5105h, ТекстПУ=ШИМ
17,	// кол-во подындексов
362,	// номер текста
7,	// такой длиной

//[5105h.01h]
5240,	// формат
363,	// номер текста, название: UaЗад
476,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.02h]
5240,	// формат
364,	// номер текста, название: UbЗад
477,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.03h]
21528,	// формат
365,	// номер текста, название: U_огр
478,	// смещение для таблицы с адресами
(Uint16)(14529069),	// знач по умолч.
(((Uint32)14529069)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0x01000000),	// максимум
(((Uint32)0x01000000)>>16),	// максимум

//[5105h.04h]
2688,	// формат
366,	// номер текста, название: GammaA
479,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.05h]
2688,	// формат
367,	// номер текста, название: GammaB
480,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.06h]
2688,	// формат
368,	// номер текста, название: GammaC
481,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.07h]
2688,	// формат
369,	// номер текста, название: TPWM
482,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.08h]
24056,	// формат
370,	// номер текста, название: Мертвое время (мкс)
483,	// смещение для таблицы с адресами
(Uint16)(3355443),	// знач по умолч.
(((Uint32)3355443)>>16),	// знач по умолч.
(Uint16)(_IQ(2.0)),	// минимум
(((Uint32)_IQ(2.0))>>16),	// минимум
(Uint16)(_IQ(10.0)),	// максимум
(((Uint32)_IQ(10.0))>>16),	// максимум

//[5105h.09h]
24056,	// формат
371,	// номер текста, название: Ограничение мин. скважн.
484,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(_IQ(10)),	// максимум
(((Uint32)_IQ(10))>>16),	// максимум

//[5105h.0Ah]
21528,	// формат
372,	// номер текста, название: Коэф. компенсации Ud
485,	// смещение для таблицы с адресами
(Uint16)(16777216),	// знач по умолч.
(((Uint32)16777216)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5105h.0Bh]
24592,	// формат
373,	// номер текста, название: Компенсация Ud
486,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.0Ch]
24592,	// формат
374,	// номер текста, название: Тип ШИМ
487,	// смещение для таблицы с адресами
(Uint16)(257),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.0Dh]
2816,	// формат
375,	// номер текста, название: ULimitation
488,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.0Eh]
21994,	// формат
376,	// номер текста, название: Частота ШИМ
489,	// смещение для таблицы с адресами
(Uint16)(20480),	// знач по умолч.
(((Uint32)20480)>>16),	// знач по умолч.
(Uint16)(2048),	// минимум
(((Uint32)2048)>>16),	// минимум
(Uint16)(10240),	// максимум
(((Uint32)10240)>>16),	// максимум

//[5105h.0Fh]
2944,	// формат
377,	// номер текста, название: Сектор
490,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.10h]
5240,	// формат
378,	// номер текста, название: U_ампл
491,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5105h.11h]
2688,	// формат
379,	// номер текста, название: Флаги аварий
492,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 510Bh, ТекстПУ=smctrl
2,	// кол-во подындексов
380,	// номер текста
2,	// такой длиной

//[510Bh.01h]
2944,	// формат
381,	// номер текста, название: sm_state
493,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.

//[510Bh.02h]
24704,	// формат
382,	// номер текста, название: drv_status_code
494,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.

// Корневой подындекс 510Eh, ТекстПУ=Защиты
11,	// кол-во подындексов
383,	// номер текста
7,	// такой длиной

//[510Eh.01h]
19072,	// формат
384,	// номер текста, название: Флаги аварий 1
495,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.02h]
19072,	// формат
385,	// номер текста, название: Флаги аварий 2
496,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.03h]
24960,	// формат
386,	// номер текста, название: Маска аварий 1L
497,	// смещение для таблицы с адресами
(Uint16)(255),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.04h]
24968,	// формат
387,	// номер текста, название: Маска аварий 1H
498,	// смещение для таблицы с адресами
(Uint16)(255),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.05h]
24960,	// формат
388,	// номер текста, название: Маска аварий 2L
499,	// смещение для таблицы с адресами
(Uint16)(255),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.06h]
24968,	// формат
389,	// номер текста, название: Маска аварий  2H
500,	// смещение для таблицы с адресами
(Uint16)(255),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[510Eh.07h]
21656,	// формат
390,	// номер текста, название: Максимальный ток
501,	// смещение для таблицы с адресами
(Uint16)(16777216),	// знач по умолч.
(((Uint32)16777216)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[510Eh.08h]
21752,	// формат
391,	// номер текста, название: Максимальное напряжение
502,	// смещение для таблицы с адресами
(Uint16)(18454938),	// знач по умолч.
(((Uint32)18454938)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[510Eh.09h]
21752,	// формат
392,	// номер текста, название: Минимальное напряжение
503,	// смещение для таблицы с адресами
(Uint16)(6990506),	// знач по умолч.
(((Uint32)6990506)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[510Eh.0Ah]
22168,	// формат
393,	// номер текста, название: Максимальная скорость
504,	// смещение для таблицы с адресами
(Uint16)(100663296),	// знач по умолч.
(((Uint32)100663296)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[510Eh.0Bh]
21848,	// формат
639,	// номер текста, название: Максимальная температура
505,	// смещение для таблицы с адресами
(Uint16)(75497472),	// знач по умолч.
(((Uint32)75497472)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

// Корневой подындекс 5112h, ТекстПУ=ЗадПар
5,	// кол-во подындексов
394,	// номер текста
7,	// такой длиной

//[5112h.01h]
22168,	// формат
395,	// номер текста, название: Скорость
506,	// смещение для таблицы с адресами
(Uint16)(335544),	// знач по умолч.
(((Uint32)335544)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5112h.02h]
21656,	// формат
396,	// номер текста, название: Макс. ток ВУ
507,	// смещение для таблицы с адресами
(Uint16)(3355443),	// знач по умолч.
(((Uint32)3355443)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5112h.03h]
21656,	// формат
397,	// номер текста, название: Ток удержания
508,	// смещение для таблицы с адресами
(Uint16)(3355443),	// знач по умолч.
(((Uint32)3355443)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5112h.04h]
22136,	// формат
398,	// номер текста, название: theta_elec
509,	// смещение для таблицы с адресами
(Uint16)(720992),	// знач по умолч.
(((Uint32)720992)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5112h.05h]
21752,	// формат
559,	// номер текста, название: Заданное напряжение ОВ
510,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

// Корневой подындекс 5113h, ТекстПУ=ПарДв
9,	// кол-во подындексов
399,	// номер текста
7,	// такой длиной

//[5113h.01h]
19200,	// формат
400,	// номер текста, название: Число пар полюсов
511,	// смещение для таблицы с адресами
(Uint16)(4),	// знач по умолч.
(Uint16)(1),	// минимум
(Uint16)(50),	// максимум
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.02h]
20928,	// формат
401,	// номер текста, название: Номинальный ток
512,	// смещение для таблицы с адресами
(Uint16)(5),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.03h]
4512,	// формат
402,	// номер текста, название: Номинальное напряжение фазн.
513,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.04h]
21280,	// формат
403,	// номер текста, название: Номинальная скорость
514,	// смещение для таблицы с адресами
(Uint16)(500),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.05h]
20896,	// формат
404,	// номер текста, название: Номинальное напряжение ЗПТ
515,	// смещение для таблицы с адресами
(Uint16)(36),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(1000),	// максимум
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.06h]
22264,	// формат
405,	// номер текста, название: Rs
516,	// смещение для таблицы с адресами
(Uint16)(1048576),	// знач по умолч.
(((Uint32)1048576)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5113h.07h]
22296,	// формат
406,	// номер текста, название: Ls
517,	// смещение для таблицы с адресами
(Uint16)(16777),	// знач по умолч.
(((Uint32)16777)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5113h.08h]
4608,	// формат
407,	// номер текста, название: Номинальная частота
518,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5113h.09h]
24624,	// формат
408,	// номер текста, название: Тип датчика положения
519,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5114h, ТекстПУ=СистПр
4,	// кол-во подындексов
409,	// номер текста
4,	// такой длиной

//[5114h.01h]
8320,	// формат
410,	// номер текста, название: Тип аппаратной части
520,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5114h.02h]
19072,	// формат
411,	// номер текста, название: Режим работы
521,	// смещение для таблицы с адресами
(Uint16)(4),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5114h.03h]
19072,	// формат
413,	// номер текста, название: АЦП авто смещ.
522,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5114h.04h]
18944,	// формат
414,	// номер текста, название: Перезагрузка
523,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(1),	// максимум

// Корневой подындекс 5116h, ТекстПУ=АЦП
20,	// кол-во подындексов
415,	// номер текста
4,	// такой длиной

//[5116h.01h]
20928,	// формат
416,	// номер текста, название: Коэффициент тока фазы А
524,	// смещение для таблицы с адресами
(Uint16)(40),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.02h]
20480,	// формат
417,	// номер текста, название: Смещение тока фазы А
525,	// смещение для таблицы с адресами
(Uint16)(62706),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.03h]
5272,	// формат
418,	// номер текста, название: Ток фазы А
526,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.04h]
20928,	// формат
419,	// номер текста, название: Коэффициент тока фазы В
527,	// смещение для таблицы с адресами
(Uint16)(40),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.05h]
20480,	// формат
420,	// номер текста, название: Смещение тока фазы В
528,	// смещение для таблицы с адресами
(Uint16)(62251),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.06h]
5272,	// формат
421,	// номер текста, название: Ток фазы В
529,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.07h]
20928,	// формат
422,	// номер текста, название: Коэффициент тока фазы C
530,	// смещение для таблицы с адресами
(Uint16)(40),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.08h]
20480,	// формат
423,	// номер текста, название: Смещение тока фазы C
531,	// смещение для таблицы с адресами
(Uint16)(62836),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.09h]
5272,	// формат
424,	// номер текста, название: Ток фазы С
532,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.0Ah]
20928,	// формат
585,	// номер текста, название: Коэффициент тока фазы D
533,	// смещение для таблицы с адресами
(Uint16)(40),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.0Bh]
20480,	// формат
586,	// номер текста, название: Смещение тока фазы D
534,	// смещение для таблицы с адресами
(Uint16)(62836),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.0Ch]
5272,	// формат
587,	// номер текста, название: Ток фазы D
535,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.0Dh]
20896,	// формат
425,	// номер текста, название: Коэффициент напряжения ЗПТ
536,	// смещение для таблицы с адресами
(Uint16)(66),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.0Eh]
20480,	// формат
426,	// номер текста, название: Смещение напряж. ЗПТ
537,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.0Fh]
5368,	// формат
427,	// номер текста, название: Напряжение ЗПТ
538,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.10h]
21344,	// формат
633,	// номер текста, название: Коэффициент температуры
539,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.11h]
5464,	// формат
634,	// номер текста, название: Температура
540,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5116h.12h]
20480,	// формат
642,	// номер текста, название: Коэффициент внешнего входа
541,	// смещение для таблицы с адресами
(Uint16)(100),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.13h]
20480,	// формат
643,	// номер текста, название: Смещение внешнего входа
542,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(Uint16)(0),	// минимум
(Uint16)(0),	// максимум

//[5116h.14h]
5176,	// формат
641,	// номер текста, название: Внешний аналоговый вход 1
543,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 511Ah, ТекстПУ=Закон U(f) (АД)
7,	// кол-во подындексов
428,	// номер текста
7,	// такой длиной

//[511Ah.01h]
5784,	// формат
429,	// номер текста, название: Выходная частота
544,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[511Ah.02h]
5240,	// формат
430,	// номер текста, название: Выходное напряжение
545,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[511Ah.03h]
22168,	// формат
431,	// номер текста, название: Нулевая опроная частота
546,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[511Ah.04h]
21624,	// формат
432,	// номер текста, название: Нулевое опорное напряжение
547,	// смещение для таблицы с адресами
(Uint16)(419430),	// знач по умолч.
(((Uint32)419430)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[511Ah.05h]
22168,	// формат
433,	// номер текста, название: Первая опорная частота
548,	// смещение для таблицы с адресами
(Uint16)(100663296),	// знач по умолч.
(((Uint32)100663296)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[511Ah.06h]
21624,	// формат
434,	// номер текста, название: Первое опорное напряжение
549,	// смещение для таблицы с адресами
(Uint16)(12582912),	// знач по умолч.
(((Uint32)12582912)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[511Ah.07h]
22168,	// формат
435,	// номер текста, название: Максимальная частота
550,	// смещение для таблицы с адресами
(Uint16)(100663296),	// знач по умолч.
(((Uint32)100663296)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

// Корневой подындекс 5138h, ТекстПУ=текЗнч
7,	// кол-во подындексов
436,	// номер текста
1,	// такой длиной

//[5138h.01h]
5784,	// формат
437,	// номер текста, название: Скорость
551,	// смещение для таблицы с адресами

//[5138h.02h]
5400,	// формат
438,	// номер текста, название: Акт. мощность
552,	// смещение для таблицы с адресами

//[5138h.03h]
5272,	// формат
439,	// номер текста, название: Ток статора
553,	// смещение для таблицы с адресами

//[5138h.04h]
5752,	// формат
440,	// номер текста, название: ЭлУголЗад
554,	// смещение для таблицы с адресами

//[5138h.05h]
5752,	// формат
441,	// номер текста, название: ЭлУгол
555,	// смещение для таблицы с адресами

//[5138h.06h]
5272,	// формат
442,	// номер текста, название: Ток статора зад
556,	// смещение для таблицы с адресами

//[5138h.07h]
7520,	// формат
613,	// номер текста, название: Время запитанного состояния, мин
557,	// смещение для таблицы с адресами

// Корневой подындекс 5150h, ТекстПУ=dlog
11,	// кол-во подындексов
443,	// номер текста
7,	// такой длиной

//[5150h.01h]
19072,	// формат
444,	// номер текста, название: dlog.mode_reset
558,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.02h]
19584,	// формат
445,	// номер текста, название: dlog.control
559,	// смещение для таблицы с адресами
(Uint16)(192),	// знач по умолч.
(((Uint32)192)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.03h]
19584,	// формат
446,	// номер текста, название: dlog.ind_subind1
560,	// смещение для таблицы с адресами
(Uint16)(1359151123),	// знач по умолч.
(((Uint32)1359151123)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.04h]
19584,	// формат
447,	// номер текста, название: dlog.ind_subind2
561,	// смещение для таблицы с адресами
(Uint16)(1359085569),	// знач по умолч.
(((Uint32)1359085569)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.05h]
19584,	// формат
448,	// номер текста, название: dlog.ind_subind3
562,	// смещение для таблицы с адресами
(Uint16)(1359151122),	// знач по умолч.
(((Uint32)1359151122)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.06h]
19584,	// формат
449,	// номер текста, название: dlog.ind_subind4
563,	// смещение для таблицы с адресами
(Uint16)(1359020033),	// знач по умолч.
(((Uint32)1359020033)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.07h]
24960,	// формат
450,	// номер текста, название: StartBitL
564,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.08h]
24968,	// формат
451,	// номер текста, название: StartBitH
565,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.09h]
24592,	// формат
452,	// номер текста, название: OneShotOperation
566,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5150h.0Ah]
23608,	// формат
453,	// номер текста, название: Количество точек предыстории
567,	// смещение для таблицы с адресами
(Uint16)(6710886),	// знач по умолч.
(((Uint32)6710886)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5150h.0Bh]
3200,	// формат
644,	// номер текста, название: Частота даталогера
568,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5151h.00h]
19840,	// формат
454,	// номер текста, название: dlog.next_value_var
569,	// смещение для таблицы с адресами
(Uint16)(50461787),	// знач по умолч.
(((Uint32)50461787)>>16),	// знач по умолч.

// Корневой подындекс 5152h, ТекстПУ=Энкодер
8,	// кол-во подындексов
455,	// номер текста
3,	// такой длиной

//[5152h.01h]
19584,	// формат
456,	// номер текста, название: Кол-во периодов
570,	// смещение для таблицы с адресами
(Uint16)(2500),	// знач по умолч.
(((Uint32)2500)>>16),	// знач по умолч.

//[5152h.02h]
24594,	// формат
457,	// номер текста, название: Наличие репера
571,	// смещение для таблицы с адресами
(Uint16)(1),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.03h]
3200,	// формат
460,	// номер текста, название: Механическ.угол в метках
572,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.04h]
5784,	// формат
461,	// номер текста, название: Скорость
573,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.05h]
5752,	// формат
462,	// номер текста, название: Угол. электр.
574,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.06h]
5752,	// формат
463,	// номер текста, название: Угол мех.
575,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.07h]
2688,	// формат
467,	// номер текста, название: GPIOsValue
576,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5152h.08h]
19328,	// формат
471,	// номер текста, название: Число оборотов
577,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5155h, ТекстПУ=Датчик Холла
21,	// кол-во подындексов
475,	// номер текста
7,	// такой длиной

//[5155h.01h]
5752,	// формат
441,	// номер текста, название: ЭлУгол
578,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.02h]
5784,	// формат
461,	// номер текста, название: Скорость
579,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.03h]
22168,	// формат
476,	// номер текста, название: Уставка Скорости
580,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5155h.04h]
5752,	// формат
477,	// номер текста, название: ЭлУгол6
581,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.05h]
24592,	// формат
478,	// номер текста, название: Инт-полятор вкл
582,	// смещение для таблицы с адресами
(Uint16)(81),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.06h]
19584,	// формат
479,	// номер текста, название: Уставка обнуления скорости
583,	// смещение для таблицы с адресами
(Uint16)(500),	// знач по умолч.
(((Uint32)500)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.07h]
5784,	// формат
480,	// номер текста, название: Скорость Мин.
584,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.08h]
2688,	// формат
481,	// номер текста, название: Ложные фронты
585,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.09h]
8496,	// формат
482,	// номер текста, название: Дискретные входы
586,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.0Ah]
22136,	// формат
459,	// номер текста, название: СмещУгол
587,	// смещение для таблицы с адресами
(Uint16)(4869970),	// знач по умолч.
(((Uint32)4869970)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5155h.0Bh]
2688,	// формат
483,	// номер текста, название: Уровень помех
588,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.0Ch]
2688,	// формат
484,	// номер текста, название: Ошибка 1 канала
589,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.0Dh]
2688,	// формат
485,	// номер текста, название: Ошибка 2 канала
590,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.0Eh]
2688,	// формат
486,	// номер текста, название: Ошибка 3 канала
591,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.0Fh]
24850,	// формат
487,	// номер текста, название: Направление вращения
592,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.10h]
19072,	// формат
488,	// номер текста, название: Макс.число ошибок ДПР
593,	// смещение для таблицы с адресами
(Uint16)(10),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.11h]
2688,	// формат
489,	// номер текста, название: Кол-во ошибок неверной последовательности
594,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.12h]
2688,	// формат
490,	// номер текста, название: Счётчик прерываний по приему
595,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.13h]
2688,	// формат
491,	// номер текста, название: Счётчик прерываний CAP1
596,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.14h]
2688,	// формат
492,	// номер текста, название: Счётчик прерываний CAP2
597,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5155h.15h]
2688,	// формат
493,	// номер текста, название: Счётчик прерываний CAP3
598,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5174h, ТекстПУ=Для отладки
16,	// кол-во подындексов
497,	// номер текста
7,	// такой длиной

//[5174h.01h]
5624,	// формат
498,	// номер текста, название: DebugL1
599,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.02h]
3456,	// формат
498,	// номер текста, название: DebugL1
600,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.03h]
5624,	// формат
499,	// номер текста, название: DebugL2
601,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.04h]
3456,	// формат
499,	// номер текста, название: DebugL2
602,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.05h]
2688,	// формат
500,	// номер текста, название: DebugI3
603,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.06h]
2944,	// формат
500,	// номер текста, название: DebugI3
604,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.07h]
2688,	// формат
501,	// номер текста, название: DebugI4
605,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.08h]
2944,	// формат
501,	// номер текста, название: DebugI4
606,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.09h]
22008,	// формат
502,	// номер текста, название: DebugW1
607,	// смещение для таблицы с адресами
(Uint16)(16777),	// знач по умолч.
(((Uint32)16777)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5174h.0Ah]
19840,	// формат
502,	// номер текста, название: DebugW1
608,	// смещение для таблицы с адресами
(Uint16)(16777),	// знач по умолч.
(((Uint32)16777)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.0Bh]
22008,	// формат
503,	// номер текста, название: DebugW2
609,	// смещение для таблицы с адресами
(Uint16)(-190048),	// знач по умолч.
(((Uint32)-190048)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5174h.0Ch]
19840,	// формат
503,	// номер текста, название: DebugW2
610,	// смещение для таблицы с адресами
(Uint16)(-190048),	// знач по умолч.
(((Uint32)-190048)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.0Dh]
22008,	// формат
504,	// номер текста, название: DebugW3
611,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5174h.0Eh]
19840,	// формат
504,	// номер текста, название: DebugW3
612,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5174h.0Fh]
22008,	// формат
505,	// номер текста, название: DebugW4
613,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5174h.10h]
19840,	// формат
505,	// номер текста, название: DebugW4
614,	// смещение для таблицы с адресами
(Uint16)(0),	// знач по умолч.
(((Uint32)0)>>16),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

// Корневой подындекс 5B05h, ТекстПУ=smooth_charge
6,	// кол-во подындексов
626,	// номер текста
7,	// такой длиной

//[5B05h.01h]
2176,	// формат
631,	// номер текста, название: Текущее состояние реле
615,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5B05h.02h]
19072,	// формат
627,	// номер текста, название: Задежка включения реле, мс
616,	// смещение для таблицы с адресами
(Uint16)(2000),	// знач по умолч.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5B05h.03h]
23800,	// формат
628,	// номер текста, название: Напряжение включения, В
617,	// смещение для таблицы с адресами
(Uint16)(15099494),	// знач по умолч.
(((Uint32)15099494)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5B05h.04h]
23800,	// формат
629,	// номер текста, название: Напряжение выключения, В
618,	// смещение для таблицы с адресами
(Uint16)(11744051),	// знач по умолч.
(((Uint32)11744051)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5B05h.05h]
5624,	// формат
630,	// номер текста, название: Производная напряжения ЗПТ
619,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5B05h.06h]
22008,	// формат
632,	// номер текста, название: Уставка по производной ЗПТ
620,	// смещение для таблицы с адресами
(Uint16)(8388608),	// знач по умолч.
(((Uint32)8388608)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

// Корневой подындекс 5B06h, ТекстПУ=cool_syst
4,	// кол-во подындексов
635,	// номер текста
7,	// такой длиной

//[5B06h.01h]
2688,	// формат
636,	// номер текста, название: Текущее состояние вентилятора
621,	// смещение для таблицы с адресами
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.
0,	// заполнитель места под одинак. размер. подинд.

//[5B06h.02h]
21848,	// формат
637,	// номер текста, название: Температура включения вентилятора
622,	// смещение для таблицы с адресами
(Uint16)(41943040),	// знач по умолч.
(((Uint32)41943040)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5B06h.03h]
21848,	// формат
638,	// номер текста, название: Температура выключения вентилятора
623,	// смещение для таблицы с адресами
(Uint16)(25165824),	// знач по умолч.
(((Uint32)25165824)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум

//[5B06h.04h]
21848,	// формат
640,	// номер текста, название: Температура вывода предупреждения о перегреве
624,	// смещение для таблицы с адресами
(Uint16)(67108864),	// знач по умолч.
(((Uint32)67108864)>>16),	// знач по умолч.
(Uint16)(0),	// минимум
(((Uint32)0)>>16),	// минимум
(Uint16)(0),	// максимум
(((Uint32)0)>>16),	// максимум
};

// Таблица соответствия индекса и смещения для таблицы с адресами
int16 const CO1_OD_TBL1[] = { 
4096,	// индекс
0,	// смещение для таблицы с адресами
4097,	// индекс
3,	// смещение для таблицы с адресами
4098,	// индекс
6,	// смещение для таблицы с адресами
4116,	// индекс
9,	// смещение для таблицы с адресами
4118,	// индекс
12,	// смещение для таблицы с адресами
4119,	// индекс
20,	// смещение для таблицы с адресами
4120,	// индекс
24,	// смещение для таблицы с адресами
4608,	// индекс
39,	// смещение для таблицы с адресами
4736,	// индекс
48,	// смещение для таблицы с адресами
5120,	// индекс
60,	// смещение для таблицы с адресами
5121,	// индекс
73,	// смещение для таблицы с адресами
5122,	// индекс
86,	// смещение для таблицы с адресами
5123,	// индекс
99,	// смещение для таблицы с адресами
5124,	// индекс
112,	// смещение для таблицы с адресами
5125,	// индекс
125,	// смещение для таблицы с адресами
5126,	// индекс
138,	// смещение для таблицы с адресами
5127,	// индекс
151,	// смещение для таблицы с адресами
5632,	// индекс
164,	// смещение для таблицы с адресами
5633,	// индекс
187,	// смещение для таблицы с адресами
5634,	// индекс
210,	// смещение для таблицы с адресами
5635,	// индекс
233,	// смещение для таблицы с адресами
5636,	// индекс
256,	// смещение для таблицы с адресами
5637,	// индекс
279,	// смещение для таблицы с адресами
5638,	// индекс
302,	// смещение для таблицы с адресами
5639,	// индекс
325,	// смещение для таблицы с адресами
6144,	// индекс
348,	// смещение для таблицы с адресами
6145,	// индекс
371,	// смещение для таблицы с адресами
6146,	// индекс
394,	// смещение для таблицы с адресами
6147,	// индекс
417,	// смещение для таблицы с адресами
6148,	// индекс
440,	// смещение для таблицы с адресами
6149,	// индекс
463,	// смещение для таблицы с адресами
6150,	// индекс
486,	// смещение для таблицы с адресами
6151,	// индекс
509,	// смещение для таблицы с адресами
6656,	// индекс
532,	// смещение для таблицы с адресами
6657,	// индекс
555,	// смещение для таблицы с адресами
6658,	// индекс
578,	// смещение для таблицы с адресами
6659,	// индекс
601,	// смещение для таблицы с адресами
6660,	// индекс
624,	// смещение для таблицы с адресами
6661,	// индекс
647,	// смещение для таблицы с адресами
6662,	// индекс
670,	// смещение для таблицы с адресами
6663,	// индекс
693,	// смещение для таблицы с адресами
8192,	// индекс
716,	// смещение для таблицы с адресами
8193,	// индекс
722,	// смещение для таблицы с адресами
8194,	// индекс
726,	// смещение для таблицы с адресами
8195,	// индекс
741,	// смещение для таблицы с адресами
8196,	// индекс
756,	// смещение для таблицы с адресами
8197,	// индекс
761,	// смещение для таблицы с адресами
8199,	// индекс
764,	// смещение для таблицы с адресами
8208,	// индекс
779,	// смещение для таблицы с адресами
8209,	// индекс
794,	// смещение для таблицы с адресами
8210,	// индекс
817,	// смещение для таблицы с адресами
8212,	// индекс
821,	// смещение для таблицы с адресами
8213,	// индекс
825,	// смещение для таблицы с адресами
8214,	// индекс
828,	// смещение для таблицы с адресами
8215,	// индекс
831,	// смещение для таблицы с адресами
8320,	// индекс
834,	// смещение для таблицы с адресами
8321,	// индекс
893,	// смещение для таблицы с адресами
8322,	// индекс
896,	// смещение для таблицы с адресами
8323,	// индекс
909,	// смещение для таблицы с адресами
8448,	// индекс
976,	// смещение для таблицы с адресами
8449,	// индекс
1003,	// смещение для таблицы с адресами
8450,	// индекс
1030,	// смещение для таблицы с адресами
8451,	// индекс
1057,	// смещение для таблицы с адресами
8452,	// индекс
1084,	// смещение для таблицы с адресами
8453,	// индекс
1111,	// смещение для таблицы с адресами
8454,	// индекс
1138,	// смещение для таблицы с адресами
8455,	// индекс
1165,	// смещение для таблицы с адресами
8456,	// индекс
1192,	// смещение для таблицы с адресами
8457,	// индекс
1219,	// смещение для таблицы с адресами
8458,	// индекс
1246,	// смещение для таблицы с адресами
8459,	// индекс
1273,	// смещение для таблицы с адресами
8460,	// индекс
1300,	// смещение для таблицы с адресами
8461,	// индекс
1327,	// смещение для таблицы с адресами
8462,	// индекс
1354,	// смещение для таблицы с адресами
8463,	// индекс
1381,	// смещение для таблицы с адресами
8464,	// индекс
1408,	// смещение для таблицы с адресами
8465,	// индекс
1435,	// смещение для таблицы с адресами
8466,	// индекс
1462,	// смещение для таблицы с адресами
8467,	// индекс
1489,	// смещение для таблицы с адресами
8468,	// индекс
1516,	// смещение для таблицы с адресами
8469,	// индекс
1543,	// смещение для таблицы с адресами
8470,	// индекс
1570,	// смещение для таблицы с адресами
8471,	// индекс
1597,	// смещение для таблицы с адресами
8472,	// индекс
1624,	// смещение для таблицы с адресами
8473,	// индекс
1651,	// смещение для таблицы с адресами
8474,	// индекс
1678,	// смещение для таблицы с адресами
8475,	// индекс
1705,	// смещение для таблицы с адресами
8476,	// индекс
1732,	// смещение для таблицы с адресами
8477,	// индекс
1759,	// смещение для таблицы с адресами
9474,	// индекс
1786,	// смещение для таблицы с адресами
9478,	// индекс
1813,	// смещение для таблицы с адресами
9487,	// индекс
1836,	// смещение для таблицы с адресами
9522,	// индекс
1841,	// смещение для таблицы с адресами
9524,	// индекс
1853,	// смещение для таблицы с адресами
9728,	// индекс
1860,	// смещение для таблицы с адресами
9984,	// индекс
1868,	// смещение для таблицы с адресами
9985,	// индекс
1872,	// смещение для таблицы с адресами
12288,	// индекс
2010,	// смещение для таблицы с адресами
12544,	// индекс
2013,	// смещение для таблицы с адресами
20480,	// индекс
2041,	// смещение для таблицы с адресами
20736,	// индекс
2071,	// смещение для таблицы с адресами
20737,	// индекс
2191,	// смещение для таблицы с адресами
20738,	// индекс
2320,	// смещение для таблицы с адресами
20739,	// индекс
2440,	// смещение для таблицы с адресами
20741,	// индекс
2623,	// смещение для таблицы с адресами
20747,	// индекс
2779,	// смещение для таблицы с адресами
20750,	// индекс
2790,	// смещение для таблицы с адресами
20754,	// индекс
2892,	// смещение для таблицы с адресами
20755,	// индекс
2940,	// смещение для таблицы с адресами
20756,	// индекс
3024,	// смещение для таблицы с адресами
20758,	// индекс
3051,	// смещение для таблицы с адресами
20762,	// индекс
3174,	// смещение для таблицы с адресами
20792,	// индекс
3240,	// смещение для таблицы с адресами
20816,	// индекс
3264,	// смещение для таблицы с адресами
20817,	// индекс
3366,	// смещение для таблицы с адресами
20818,	// индекс
3371,	// смещение для таблицы с адресами
20821,	// индекс
3414,	// смещение для таблицы с адресами
20852,	// индекс
3606,	// смещение для таблицы с адресами
23301,	// индекс
3753,	// смещение для таблицы с адресами
23302,	// индекс
3810,	// смещение для таблицы с адресами
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
// Таблица групп
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
// Таблица CALLBACK-функций
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

// Массив ссылок для драйвера CANopen двухядерных процессоров
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
