//Файл: cood.c
//Профиль: C:\SolarIDEws\SolarControl\cood_INVERTER.xml
//Дата созданиЯ: 19.10.2023 10:27:12
//Пользователь: default
#include "DSP.h"
#include "main.h"
#include "cood2.h"
#include "co_ODvars.h"

// всего 136 индексов в словаре
// всего 1019 элементов в словаре
Uint16 const co2_numOfInd = 136;
//Номер перечеслениЯ длЯ групп
Uint16 const co2_groupEnum = 15;
//Хэш-сумма:
Uint32 const co2_odHash[4] = {0xEC6610D0, 0x7C9DB4C5, 0xD1691444, 0x5CE16BC4};
//Таблица с адресами переменных

long const CO2_OD_TBL3[] = { (long)(&co2_vars.co_deviceType), //[1000h.00h], Название=Тип устройства, ТекстПУ=Device Type, EngText=Device Type, группа=CAN
(long)(&co2_vars.co_errorRegister), //[1001h.00h], Название=Регистр ошибок, ТекстПУ=ErrReg, EngText=Error Register, группа=CAN
(long)(&co2_vars.co_deviceState), //[1002h.00h], Название=Manufacturer Status Register, ТекстПУ=DevSta, EngText=Manufacturer Status Register, группа=CAN
(long)(&co2_vars.co_emcyCOBID), //[1014h.00h], Название=COB-ID Emergency Object, ТекстПУ=eCOBID, EngText=COB-ID Emergency Object, группа=CAN
(long)(&co2_vars.co_CHBT), //[1016h.01h], Название=Время ожидания сообщения Heartbeat, ТекстПУ=CHBT, EngText=Consumer Heartbeat Time, группа=CAN
(long)(&co2_vars.co_PHBT), //[1017h.00h], Название=Период генерации сообщения Heartbeat, ТекстПУ=PHBT, EngText=Producer Heartbeat Time, группа=CAN
(long)(&co2_vars.co_vendorID), //[1018h.01h], Название=Код производителя, ТекстПУ=VendID, EngText=Vendor ID, группа=CAN
(long)(&co2_vars.co_productCode), //[1018h.02h], Название=Код продукта, ТекстПУ=PrCode, EngText=Product Code, группа=CAN
(long)(&co2_vars.co_revisionNumber), //[1018h.03h], Название=Номер ревизии, ТекстПУ=RevNum, EngText=Revision Number, группа=CAN
(long)(&co2_vars.co_serialNumber), //[1018h.04h], Название=Серийный номер, ТекстПУ=SerNum, EngText=Serial Number, группа=CAN
(long)(&co2_vars.co_csrxCOBID), //[1200h.01h], Название=COB-ID Client->Server(rx), ТекстПУ=CSRXID, EngText=COB-ID Client->Server(rx), группа=CAN
(long)(&co2_vars.co_sctxCOBID), //[1200h.02h], Название=COB-ID Server->Client(tx), ТекстПУ=SCTXID, EngText=COB-ID Server->Client(tx), группа=CAN
(long)(&co2_vars.co_cstxCOBID), //[1280h.01h], Название=COB-ID Client->Server(tx), ТекстПУ=CSTXID, EngText=COB-ID Client->Server(tx), группа=CAN
(long)(&co2_vars.co_scrxCOBID), //[1280h.02h], Название=COB-ID Server->Client(rx), ТекстПУ=SCRXID, EngText=COB-ID Server->Client(rx), группа=CAN
(long)(&co2_vars.co_ssNODEID), //[1280h.03h], Название=NODE-ID on SDO server, ТекстПУ=SDOSID, EngText=NODE-ID on SDO server, группа=CAN
(long)(&co2_vars.co_RPDO1COBID), //[1400h.01h], Название=COB-ID for RPDO1, ТекстПУ=IRPDO1, EngText=COB-ID for RPDO1, группа=CAN
(long)(&co2_vars.co_transType), //[1400h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO2COBID), //[1401h.01h], Название=COB-ID for RPDO2, ТекстПУ=IRPDO2, EngText=COB-ID for RPDO2, группа=CAN
(long)(&co2_vars.co_transType), //[1401h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO3COBID), //[1402h.01h], Название=COB-ID for RPDO3, ТекстПУ=IRPDO3, EngText=COB-ID for RPDO3, группа=CAN
(long)(&co2_vars.co_transType), //[1402h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO4COBID), //[1403h.01h], Название=COB-ID for RPDO4, ТекстПУ=IRPDO4, EngText=COB-ID for RPDO4, группа=CAN
(long)(&co2_vars.co_transType), //[1403h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO5COBID), //[1404h.01h], Название=COB-ID for RPDO5, ТекстПУ=IRPDO5, EngText=COB-ID for RPDO5, группа=CAN
(long)(&co2_vars.co_transType), //[1404h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO6COBID), //[1405h.01h], Название=COB-ID for RPDO6, ТекстПУ=IRPDO6, EngText=COB-ID for RPDO6, группа=CAN
(long)(&co2_vars.co_transType), //[1405h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO7COBID), //[1406h.01h], Название=COB-ID for RPDO7, ТекстПУ=IRPDO7, EngText=COB-ID for RPDO7, группа=CAN
(long)(&co2_vars.co_transType), //[1406h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO8COBID), //[1407h.01h], Название=COB-ID for RPDO8, ТекстПУ=IRPDO8, EngText=COB-ID for RPDO8, группа=CAN
(long)(&co2_vars.co_transType), //[1407h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_RPDO1_1Mapping), //[1600h.01h], Название=RPDO1-1 Mapping, ТекстПУ=RPM11, EngText=RPDO1-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO1_2Mapping), //[1600h.02h], Название=RPDO1-2 Mapping, ТекстПУ=RPM12, EngText=RPDO1-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO1_3Mapping), //[1600h.03h], Название=RPDO1-3 Mapping, ТекстПУ=RPM13, EngText=RPDO1-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO1_4Mapping), //[1600h.04h], Название=RPDO1-4 Mapping, ТекстПУ=RPM14, EngText=RPDO1-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO2_1Mapping), //[1601h.01h], Название=RPDO2-1 Mapping, ТекстПУ=RPM21, EngText=RPDO2-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO2_2Mapping), //[1601h.02h], Название=RPDO2-2 Mapping, ТекстПУ=RPM22, EngText=RPDO2-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO2_3Mapping), //[1601h.03h], Название=RPDO2-3 Mapping, ТекстПУ=RPM23, EngText=RPDO2-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO2_4Mapping), //[1601h.04h], Название=RPDO2-4 Mapping, ТекстПУ=RPM24, EngText=RPDO2-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO3_1Mapping), //[1602h.01h], Название=RPDO3-1 Mapping, ТекстПУ=RPM31, EngText=RPDO3-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO3_2Mapping), //[1602h.02h], Название=RPDO3-2 Mapping, ТекстПУ=RPM32, EngText=RPDO3-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO3_3Mapping), //[1602h.03h], Название=RPDO3-3 Mapping, ТекстПУ=RPM33, EngText=RPDO3-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO3_4Mapping), //[1602h.04h], Название=RPDO3-4 Mapping, ТекстПУ=RPM34, EngText=RPDO3-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO4_1Mapping), //[1603h.01h], Название=RPDO4-1 Mapping, ТекстПУ=RPM41, EngText=RPDO4-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO4_2Mapping), //[1603h.02h], Название=RPDO4-2 Mapping, ТекстПУ=RPM42, EngText=RPDO4-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO4_3Mapping), //[1603h.03h], Название=RPDO4-3 Mapping, ТекстПУ=RPM43, EngText=RPDO4-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO4_4Mapping), //[1603h.04h], Название=RPDO4-4 Mapping, ТекстПУ=RPM44, EngText=RPDO4-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO5_1Mapping), //[1604h.01h], Название=RPDO5-1 Mapping, ТекстПУ=RPM51, EngText=RPDO5-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO5_2Mapping), //[1604h.02h], Название=RPDO5-2 Mapping, ТекстПУ=RPM52, EngText=RPDO5-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO5_3Mapping), //[1604h.03h], Название=RPDO5-3 Mapping, ТекстПУ=RPM53, EngText=RPDO5-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO5_4Mapping), //[1604h.04h], Название=RPDO5-4 Mapping, ТекстПУ=RPM54, EngText=RPDO5-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO6_1Mapping), //[1605h.01h], Название=RPDO6-1 Mapping, ТекстПУ=RPM61, EngText=RPDO6-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO6_2Mapping), //[1605h.02h], Название=RPDO6-2 Mapping, ТекстПУ=RPM62, EngText=RPDO6-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO6_3Mapping), //[1605h.03h], Название=RPDO6-3 Mapping, ТекстПУ=RPM63, EngText=RPDO6-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO6_4Mapping), //[1605h.04h], Название=RPDO6-4 Mapping, ТекстПУ=RPM64, EngText=RPDO6-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO7_1Mapping), //[1606h.01h], Название=RPDO7-1 Mapping, ТекстПУ=RPM71, EngText=RPDO7-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO7_2Mapping), //[1606h.02h], Название=RPDO7-2 Mapping, ТекстПУ=RPM72, EngText=RPDO7-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO7_3Mapping), //[1606h.03h], Название=RPDO7-3 Mapping, ТекстПУ=RPM73, EngText=RPDO7-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO7_4Mapping), //[1606h.04h], Название=RPDO7-4 Mapping, ТекстПУ=RPM74, EngText=RPDO7-4 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO8_1Mapping), //[1607h.01h], Название=RPDO8-1 Mapping, ТекстПУ=RPM81, EngText=RPDO8-1 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO8_2Mapping), //[1607h.02h], Название=RPDO8-2 Mapping, ТекстПУ=RPM82, EngText=RPDO8-2 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO8_3Mapping), //[1607h.03h], Название=RPDO8-3 Mapping, ТекстПУ=RPM83, EngText=RPDO8-3 Mapping, группа=CAN
(long)(&co2_vars.co_RPDO8_4Mapping), //[1607h.04h], Название=RPDO8-4 Mapping, ТекстПУ=RPM84, EngText=RPDO8-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO1COBID), //[1800h.01h], Название=COB-ID for TPDO1, ТекстПУ=ITPDO1, EngText=COB-ID for TPDO1, группа=CAN
(long)(&co2_vars.co_transType), //[1800h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO1ITime), //[1800h.03h], Название=Inhibit Time 1, ТекстПУ=ITime1, EngText=Inhibit Time 1, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1800h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO1EventTimer), //[1800h.05h], Название=Event Timer 1, ТекстПУ=EvTmr1, EngText=Event Timer 1, группа=CAN
(long)(&co2_vars.co_TPDO2COBID), //[1801h.01h], Название=COB-ID for TPDO2, ТекстПУ=ITPDO2, EngText=COB-ID for TPDO2, группа=CAN
(long)(&co2_vars.co_transType), //[1801h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO2ITime), //[1801h.03h], Название=Inhibit Time 2, ТекстПУ=ITime2, EngText=Inhibit Time 2, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1801h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO2EventTimer), //[1801h.05h], Название=Event Timer 2, ТекстПУ=EvTmr2, EngText=Event Timer 2, группа=CAN
(long)(&co2_vars.co_TPDO3COBID), //[1802h.01h], Название=COB-ID for TPDO3, ТекстПУ=ITPDO3, EngText=COB-ID for TPDO3, группа=CAN
(long)(&co2_vars.co_transType), //[1802h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO3ITime), //[1802h.03h], Название=Inhibit Time 3, ТекстПУ=ITime3, EngText=Inhibit Time 3, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1802h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO3EventTimer), //[1802h.05h], Название=Event Timer 3, ТекстПУ=EvTmr3, EngText=Event Timer 3, группа=CAN
(long)(&co2_vars.co_TPDO4COBID), //[1803h.01h], Название=COB-ID for TPDO4, ТекстПУ=ITPDO4, EngText=COB-ID for TPDO4, группа=CAN
(long)(&co2_vars.co_transType), //[1803h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO4ITime), //[1803h.03h], Название=Inhibit Time 4, ТекстПУ=ITime4, EngText=Inhibit Time 4, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1803h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO4EventTimer), //[1803h.05h], Название=Event Timer 4, ТекстПУ=EvTmr4, EngText=Event Timer 4, группа=CAN
(long)(&co2_vars.co_TPDO5COBID), //[1804h.01h], Название=COB-ID for TPDO5, ТекстПУ=ITPDO5, EngText=COB-ID for TPDO5, группа=CAN
(long)(&co2_vars.co_transType), //[1804h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO5ITime), //[1804h.03h], Название=Inhibit Time 5, ТекстПУ=ITime5, EngText=Inhibit Time 5, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1804h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO5EventTimer), //[1804h.05h], Название=Event Timer 5, ТекстПУ=EvTmr5, EngText=Event Timer 5, группа=CAN
(long)(&co2_vars.co_TPDO6COBID), //[1805h.01h], Название=COB-ID for TPDO6, ТекстПУ=ITPDO6, EngText=COB-ID for TPDO6, группа=CAN
(long)(&co2_vars.co_transType), //[1805h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO6ITime), //[1805h.03h], Название=Inhibit Time 6, ТекстПУ=ITime6, EngText=Inhibit Time 6, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1805h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO6EventTimer), //[1805h.05h], Название=Event Timer 6, ТекстПУ=EvTmr6, EngText=Event Timer 6, группа=CAN
(long)(&co2_vars.co_TPDO7COBID), //[1806h.01h], Название=COB-ID for TPDO7, ТекстПУ=ITPDO7, EngText=COB-ID for TPDO7, группа=CAN
(long)(&co2_vars.co_transType), //[1806h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO7ITime), //[1806h.03h], Название=Inhibit Time 7, ТекстПУ=ITime7, EngText=Inhibit Time 7, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1806h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO7EventTimer), //[1806h.05h], Название=Event Timer 7, ТекстПУ=EvTmr7, EngText=Event Timer 7, группа=CAN
(long)(&co2_vars.co_TPDO8COBID), //[1807h.01h], Название=COB-ID for TPDO8, ТекстПУ=ITPDO8, EngText=COB-ID for TPDO8, группа=CAN
(long)(&co2_vars.co_transType), //[1807h.02h], Название=Тип передачи, ТекстПУ=TransT, EngText=Transmission Type, группа=CAN
(long)(&co2_vars.co_TPDO8ITime), //[1807h.03h], Название=Inhibit Time 8, ТекстПУ=ITime8, EngText=Inhibit Time 8, группа=CAN
(long)(&co2_vars.co_compatEntry), //[1807h.04h], Название=Compatibility Entry, ТекстПУ=CompEn, EngText=Compatibility Entry, группа=CAN
(long)(&co2_vars.co_TPDO8EventTimer), //[1807h.05h], Название=Event Timer 8, ТекстПУ=EvTmr8, EngText=Event Timer 8, группа=CAN
(long)(&co2_vars.co_TPDO1_1Mapping), //[1A00h.01h], Название=TPDO1-1 Mapping, ТекстПУ=TPM11, EngText=TPDO1-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO1_2Mapping), //[1A00h.02h], Название=TPDO1-2 Mapping, ТекстПУ=TPM12, EngText=TPDO1-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO1_3Mapping), //[1A00h.03h], Название=TPDO1-3 Mapping, ТекстПУ=TPM13, EngText=TPDO1-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO1_4Mapping), //[1A00h.04h], Название=TPDO1-4 Mapping, ТекстПУ=TPM14, EngText=TPDO1-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO2_1Mapping), //[1A01h.01h], Название=TPDO2-1 Mapping, ТекстПУ=TPM21, EngText=TPDO2-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO2_2Mapping), //[1A01h.02h], Название=TPDO2-2 Mapping, ТекстПУ=TPM22, EngText=TPDO2-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO2_3Mapping), //[1A01h.03h], Название=TPDO2-3 Mapping, ТекстПУ=TPM23, EngText=TPDO2-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO2_4Mapping), //[1A01h.04h], Название=TPDO2-4 Mapping, ТекстПУ=TPM24, EngText=TPDO2-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO3_1Mapping), //[1A02h.01h], Название=TPDO3-1 Mapping, ТекстПУ=TPM31, EngText=TPDO3-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO3_2Mapping), //[1A02h.02h], Название=TPDO3-2 Mapping, ТекстПУ=TPM32, EngText=TPDO3-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO3_3Mapping), //[1A02h.03h], Название=TPDO3-3 Mapping, ТекстПУ=TPM33, EngText=TPDO3-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO3_4Mapping), //[1A02h.04h], Название=TPDO3-4 Mapping, ТекстПУ=TPM34, EngText=TPDO3-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO4_1Mapping), //[1A03h.01h], Название=TPDO4-1 Mapping, ТекстПУ=TPM41, EngText=TPDO4-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO4_2Mapping), //[1A03h.02h], Название=TPDO4-2 Mapping, ТекстПУ=TPM42, EngText=TPDO4-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO4_3Mapping), //[1A03h.03h], Название=TPDO4-3 Mapping, ТекстПУ=TPM43, EngText=TPDO4-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO4_4Mapping), //[1A03h.04h], Название=TPDO4-4 Mapping, ТекстПУ=TPM44, EngText=TPDO4-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO5_1Mapping), //[1A04h.01h], Название=TPDO5-1 Mapping, ТекстПУ=TPM51, EngText=TPDO5-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO5_2Mapping), //[1A04h.02h], Название=TPDO5-2 Mapping, ТекстПУ=TPM52, EngText=TPDO5-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO5_3Mapping), //[1A04h.03h], Название=TPDO5-3 Mapping, ТекстПУ=TPM53, EngText=TPDO5-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO5_4Mapping), //[1A04h.04h], Название=TPDO5-4 Mapping, ТекстПУ=TPM54, EngText=TPDO5-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO6_1Mapping), //[1A05h.01h], Название=TPDO6-1 Mapping, ТекстПУ=TPM61, EngText=TPDO6-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO6_2Mapping), //[1A05h.02h], Название=TPDO6-2 Mapping, ТекстПУ=TPM62, EngText=TPDO6-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO6_3Mapping), //[1A05h.03h], Название=TPDO6-3 Mapping, ТекстПУ=TPM63, EngText=TPDO6-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO6_4Mapping), //[1A05h.04h], Название=TPDO6-4 Mapping, ТекстПУ=TPM64, EngText=TPDO6-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO7_1Mapping), //[1A06h.01h], Название=TPDO7-1 Mapping, ТекстПУ=TPM71, EngText=TPDO7-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO7_2Mapping), //[1A06h.02h], Название=TPDO7-2 Mapping, ТекстПУ=TPM72, EngText=TPDO7-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO7_3Mapping), //[1A06h.03h], Название=TPDO7-3 Mapping, ТекстПУ=TPM73, EngText=TPDO7-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO7_4Mapping), //[1A06h.04h], Название=TPDO7-4 Mapping, ТекстПУ=TPM74, EngText=TPDO7-4 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO8_1Mapping), //[1A07h.01h], Название=TPDO8-1 Mapping, ТекстПУ=TPM81, EngText=TPDO8-1 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO8_2Mapping), //[1A07h.02h], Название=TPDO8-2 Mapping, ТекстПУ=TPM82, EngText=TPDO8-2 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO8_3Mapping), //[1A07h.03h], Название=TPDO8-3 Mapping, ТекстПУ=TPM83, EngText=TPDO8-3 Mapping, группа=CAN
(long)(&co2_vars.co_TPDO8_4Mapping), //[1A07h.04h], Название=TPDO8-4 Mapping, ТекстПУ=TPM84, EngText=TPDO8-4 Mapping, группа=CAN
(long)(&co2_vars.co_nodeID), //[2000h.00h], Название=CAN NODE-ID, ТекстПУ=NodeID, EngText=CAN NODE-ID, группа=CAN
(long)(&co2_vars.co_bitRate), //[2001h.00h], Название=CAN Bit Rate, ТекстПУ=CANBR, EngText=CAN Bit Rate, группа=CAN
(long)(&co2_vars.co_vendorID), //[2002h.01h], Название=Код производителя, ТекстПУ=VendID, EngText=Vendor ID, группа=CAN
(long)(&co2_vars.co_productCode), //[2002h.02h], Название=Код продукта, ТекстПУ=PrCode, EngText=Product Code, группа=CAN
(long)(&co2_vars.co_revisionNumber), //[2002h.03h], Название=Номер ревизии, ТекстПУ=RevNum, EngText=Revision Number, группа=CAN
(long)(&co2_vars.co_serialNumber), //[2002h.04h], Название=Серийный номер, ТекстПУ=SerNum, EngText=Serial Number, группа=CAN
(long)(&co2_vars.co_specialData1), //[2003h.01h], Название=Special Data 1, ТекстПУ=SpDat1, EngText=Special Data 1, группа=CAN
(long)(&co2_vars.co_specialData2), //[2003h.02h], Название=Special Data 2, ТекстПУ=SpDat2, EngText=Special Data 2, группа=CAN
(long)(&co2_vars.co_specialData3), //[2003h.03h], Название=Special Data 3, ТекстПУ=SpDat3, EngText=Special Data 3, группа=CAN
(long)(&co2_vars.co_specialData4), //[2003h.04h], Название=Special Data 4, ТекстПУ=SpDat4, EngText=Special Data 4, группа=CAN
(long)(&co2_vars.co_secretCode), //[2004h.00h], Название=Secret Code, ТекстПУ=Secret, EngText=Secret Code, группа=CAN
(long)(&co2_vars.co_protectBit), //[2005h.00h], Название=Protect Bit, ТекстПУ=ProtBt, EngText=Protect Bit, группа=CAN
(long)(&co2_odHash[0]), //[2007h.01h], Название=md5_hash_0, ТекстПУ=md5_hash_0, EngText=md5_hash_0, группа=CAN
(long)(&co2_odHash[1]), //[2007h.02h], Название=md5_hash_1, ТекстПУ=md5_hash_1, EngText=md5_hash_1, группа=CAN
(long)(&co2_odHash[2]), //[2007h.03h], Название=md5_hash_2, ТекстПУ=md5_hash_2, EngText=md5_hash_2, группа=CAN
(long)(&co2_odHash[3]), //[2007h.04h], Название=md5_hash_3, ТекстПУ=md5_hash_3, EngText=md5_hash_3, группа=CAN
(long)(&co2_vars.co_heartbeatFlag0), //[2010h.01h], Название=Heartbeat Flag 0-31, ТекстПУ=HFlag0, EngText=Heartbeat Flag 0-31, группа=CAN
(long)(&co2_vars.co_heartbeatFlag1), //[2010h.02h], Название=Heartbeat Flag 32-63, ТекстПУ=HFlag1, EngText=Heartbeat Flag 32-63, группа=CAN
(long)(&co2_vars.co_heartbeatFlag2), //[2010h.03h], Название=Heartbeat Flag 64-95, ТекстПУ=HFlag2, EngText=Heartbeat Flag 64-95, группа=CAN
(long)(&co2_vars.co_heartbeatFlag3), //[2010h.04h], Название=Heartbeat Flag 96-127, ТекстПУ=HFlag3, EngText=Heartbeat Flag 96-127, группа=CAN
(long)(&co2_vars.co_heartbeatMask0), //[2011h.01h], Название=Heartbeat Mask 0-31, ТекстПУ=HMask0, EngText=Heartbeat Mask 0-31, группа=CAN
(long)(&co2_vars.co_heartbeatMask1), //[2011h.02h], Название=Heartbeat Mask 32-63, ТекстПУ=HMask1, EngText=Heartbeat Mask 32-63, группа=CAN
(long)(&co2_vars.co_heartbeatMask2), //[2011h.03h], Название=Heartbeat Mask 64-95, ТекстПУ=HMask2, EngText=Heartbeat Mask 64-95, группа=CAN
(long)(&co2_vars.co_heartbeatMask3), //[2011h.04h], Название=Heartbeat Mask 96-127, ТекстПУ=HMask3, EngText=Heartbeat Mask 96-127, группа=CAN
(long)(&co2_vars.co_heartbeatAutoStart), //[2012h.00h], Название=Heartbeat Autostart, ТекстПУ=HBASta, EngText=Heartbeat Autostart, группа=CAN
(long)(&co2_vars.co_heartbeatAutoRecovery), //[2014h.00h], Название=Heartbeat Autorecovery, ТекстПУ=HBARec, EngText=Heartbeat Autorecovery, группа=CAN
(long)(&co2_vars.co_nodeState), //[2015h.00h], Название=Состояние драйвера CAN-Open, ТекстПУ=State, EngText=Состояние драйвера CAN-Open, группа=CAN
(long)(&co2_vars.co_emergencyErrorCode), //[2016h.00h], Название=Emergency Error Code, ТекстПУ=EmErCo, EngText=Emergency Error Code, группа=CAN
(long)(&co2_vars.co_deviceErrorState), //[2017h.00h], Название=Device Error State, ТекстПУ=DeErSt, EngText=Device Error State, группа=CAN
(long)(&co2_vars.co_ODCommand), //[2080h.01h], Название=Object Dictionary Command, ТекстПУ=ODComm, EngText=Object Dictionary Command, группа=CAN
(long)(&co2_vars.co_currentODIndex), //[2080h.02h], Название=Current OD Index, ТекстПУ=ODCInd, EngText=Current OD Index, группа=CAN
(long)(&co2_vars.co_currentODSubIndex), //[2080h.03h], Название=Current OD Sub-Index, ТекстПУ=ODCSub, EngText=Current OD Sub-Index, группа=CAN
(long)(&co2_vars.co_currentODEText), //[2080h.04h], Название=Current OD Element Text, ТекстПУ=ODCTxt, EngText=Current OD Element Text, группа=CAN
(long)(&co2_vars.co_currentODEFormat), //[2080h.05h], Название=Current OD Element Format, ТекстПУ=ODCFrm, EngText=Current OD Element Format, группа=CAN
(long)(&co2_vars.co_currentODEMin), //[2080h.06h], Название=Current OD Element Min, ТекстПУ=ODCMin, EngText=Current OD Element Min, группа=CAN
(long)(&co2_vars.co_currentODEMax), //[2080h.07h], Название=Current OD Element Max, ТекстПУ=ODCMax, EngText=Current OD Element Max, группа=CAN
(long)(&co2_vars.co_currentODEDefault), //[2080h.08h], Название=Current OD Element Default, ТекстПУ=ODCDef, EngText=Current OD Element Default, группа=CAN
(long)(&co2_vars.co_currentODEMinLow), //[2080h.09h], Название=Current OD Element MinLow, ТекстПУ=ODCMiL, EngText=Current OD Element MinLow, группа=CAN
(long)(&co2_vars.co_currentODEMaxLow), //[2080h.0Ah], Название=Current OD Element MaxLow, ТекстПУ=ODCMaL, EngText=Current OD Element MaxLow, группа=CAN
(long)(&co2_vars.co_currentODEDefaultLow), //[2080h.0Bh], Название=Current OD Element Default Low, ТекстПУ=ODCDeL, EngText=Current OD Element Default Low, группа=CAN
(long)(&co2_vars.co_currentODEAddrLow), //[2080h.0Ch], Название=Current OD Element Address, ТекстПУ=ODCAdr, EngText=Current OD Element Address, группа=CAN
(long)(&co2_vars.co_currentODEAddrLow), //[2080h.0Dh], Название=Current OD Element Address, ТекстПУ=ODCAdr, EngText=Current OD Element Address, группа=CAN
(long)(&co2_vars.co_currentODEType), //[2080h.0Eh], Название=Группа параметров, ТекстПУ=Группа, EngText=Parameter Group, группа=CAN
(long)(&co2_vars.co_odIndexSize), //[2081h.00h], Название=Количество индексов, ТекстПУ=КолИнд, EngText=Number of Indexes, группа=CAN
(long)(&co2_vars.co_defaultIndex1), //[2082h.01h], Название=Default Index 1, ТекстПУ=DfInd1, EngText=Default Index 1, группа=CAN
(long)(&co2_vars.co_defaultIndex2), //[2082h.02h], Название=Default Index 2, ТекстПУ=DfInd2, EngText=Default Index 2, группа=CAN
(long)(&co2_vars.co_maskElement01), //[2083h.01h], Название=Mask Element, ТекстПУ=MskEl0, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement01), //[2083h.02h], Название=Mask Element, ТекстПУ=MskEl1, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement23), //[2083h.03h], Название=Mask Element, ТекстПУ=MskEl2, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement23), //[2083h.04h], Название=Mask Element, ТекстПУ=MskEl3, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement45), //[2083h.05h], Название=Mask Element, ТекстПУ=MskEl4, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement45), //[2083h.06h], Название=Mask Element, ТекстПУ=MskEl5, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement67), //[2083h.07h], Название=Mask Element, ТекстПУ=MskEl6, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement67), //[2083h.08h], Название=Mask Element, ТекстПУ=MskEl7, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement89), //[2083h.09h], Название=Mask Element, ТекстПУ=MskEl8, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElement89), //[2083h.0Ah], Название=Mask Element, ТекстПУ=MskEl9, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementAB), //[2083h.0Bh], Название=Mask Element, ТекстПУ=MskElA, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementAB), //[2083h.0Ch], Название=Mask Element, ТекстПУ=MskElB, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementCD), //[2083h.0Dh], Название=Mask Element, ТекстПУ=MskElC, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementCD), //[2083h.0Eh], Название=Mask Element, ТекстПУ=MskElD, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementEF), //[2083h.0Fh], Название=Mask Element, ТекстПУ=MskElE, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_maskElementEF), //[2083h.10h], Название=Mask Element, ТекстПУ=MskElF, EngText=Mask Element, группа=CAN
(long)(&co2_vars.co_scaleNum0), //[2100h.01h], Название=Scale Number 0, ТекстПУ=SN0, EngText=Scale Number 0, группа=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.02h], Название=Scale Number 0 Format, ТекстПУ=S0Fmt, EngText=Scale Number 0 Format, группа=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum0Format), //[2100h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum1), //[2101h.01h], Название=Scale Number 1, ТекстПУ=SN1, EngText=Scale Number 1, группа=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.02h], Название=Scale Number 1 Format, ТекстПУ=S1Fmt, EngText=Scale Number 1 Format, группа=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum1Format), //[2101h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum2), //[2102h.01h], Название=Scale Number 2, ТекстПУ=SN2, EngText=Scale Number 2, группа=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.02h], Название=Scale Number 2 Format, ТекстПУ=S2Fmt, EngText=Scale Number 2 Format, группа=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum2Format), //[2102h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum3), //[2103h.01h], Название=Scale Number 3, ТекстПУ=SN3, EngText=Scale Number 3, группа=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.02h], Название=Scale Number 3 Format, ТекстПУ=S3Fmt, EngText=Scale Number 3 Format, группа=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum3Format), //[2103h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum4), //[2104h.01h], Название=Scale Number 4, ТекстПУ=SN4, EngText=Scale Number 4, группа=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.02h], Название=Scale Number 4 Format, ТекстПУ=S4Fmt, EngText=Scale Number 4 Format, группа=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum4Format), //[2104h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum5), //[2105h.01h], Название=Scale Number 5, ТекстПУ=SN5, EngText=Scale Number 5, группа=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.02h], Название=Scale Number 5 Format, ТекстПУ=S5Fmt, EngText=Scale Number 5 Format, группа=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum5Format), //[2105h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum6), //[2106h.01h], Название=Scale Number 6, ТекстПУ=SN6, EngText=Scale Number 6, группа=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.02h], Название=Scale Number 6 Format, ТекстПУ=S6Fmt, EngText=Scale Number 6 Format, группа=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum6Format), //[2106h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum7), //[2107h.01h], Название=Scale Number 7, ТекстПУ=SN7, EngText=Scale Number 7, группа=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.02h], Название=Scale Number 7 Format, ТекстПУ=S7Fmt, EngText=Scale Number 7 Format, группа=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum7Format), //[2107h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum8), //[2108h.01h], Название=Scale Number 8, ТекстПУ=SN8, EngText=Scale Number 8, группа=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.02h], Название=Scale Number 8 Format, ТекстПУ=S8Fmt, EngText=Scale Number 8 Format, группа=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum8Format), //[2108h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum9), //[2109h.01h], Название=Scale Number 9, ТекстПУ=SN9, EngText=Scale Number 9, группа=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.02h], Название=Scale Number 9 Format, ТекстПУ=S9Fmt, EngText=Scale Number 9 Format, группа=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum9Format), //[2109h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumA), //[210Ah.01h], Название=Scale Number A, ТекстПУ=SNA, EngText=Scale Number A, группа=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.02h], Название=Scale Number A Format, ТекстПУ=SAFmt, EngText=Scale Number A Format, группа=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumAFormat), //[210Ah.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumB), //[210Bh.01h], Название=Scale Number B, ТекстПУ=SNB, EngText=Scale Number B, группа=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.02h], Название=Scale Number B Format, ТекстПУ=SBFmt, EngText=Scale Number B Format, группа=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumBFormat), //[210Bh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumC), //[210Ch.01h], Название=Scale Number C, ТекстПУ=SNC, EngText=Scale Number C, группа=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.02h], Название=Scale Number C Format, ТекстПУ=SCFmt, EngText=Scale Number C Format, группа=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumCFormat), //[210Ch.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumD), //[210Dh.01h], Название=Scale Number D, ТекстПУ=SND, EngText=Scale Number D, группа=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.02h], Название=Scale Number D Format, ТекстПУ=SDFmt, EngText=Scale Number D Format, группа=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumDFormat), //[210Dh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumE), //[210Eh.01h], Название=Scale Number E, ТекстПУ=SNE, EngText=Scale Number E, группа=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.02h], Название=Scale Number E Format, ТекстПУ=SEFmt, EngText=Scale Number E Format, группа=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumEFormat), //[210Eh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNumF), //[210Fh.01h], Название=Scale Number F, ТекстПУ=SNF, EngText=Scale Number F, группа=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.02h], Название=Scale Number F Format, ТекстПУ=SFFmt, EngText=Scale Number F Format, группа=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNumFFormat), //[210Fh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum10), //[2110h.01h], Название=Scale Number 10, ТекстПУ=SN10, EngText=Scale Number 10, группа=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.02h], Название=Scale Number 10 Format, ТекстПУ=S10Fmt, EngText=Scale Number 10 Format, группа=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum10Format), //[2110h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum11), //[2111h.01h], Название=Scale Number 11, ТекстПУ=SN11, EngText=Scale Number 11, группа=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.02h], Название=Scale Number 11 Format, ТекстПУ=S11Fmt, EngText=Scale Number 11 Format, группа=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum11Format), //[2111h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum12), //[2112h.01h], Название=Scale Number 12, ТекстПУ=SN12, EngText=Scale Number 12, группа=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.02h], Название=Scale Number 12 Format, ТекстПУ=S12Fmt, EngText=Scale Number 12 Format, группа=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum12Format), //[2112h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum13), //[2113h.01h], Название=Scale Number 13, ТекстПУ=SN13, EngText=Scale Number 13, группа=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.02h], Название=Scale Number 13 Format, ТекстПУ=S13Fmt, EngText=Scale Number 13 Format, группа=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum13Format), //[2113h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum14), //[2114h.01h], Название=Scale Number 14, ТекстПУ=SN14, EngText=Scale Number 14, группа=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.02h], Название=Scale Number 14 Format, ТекстПУ=S14Fmt, EngText=Scale Number 14 Format, группа=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum14Format), //[2114h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum15), //[2115h.01h], Название=Scale Number 15, ТекстПУ=SN15, EngText=Scale Number 15, группа=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.02h], Название=Scale Number 15Format, ТекстПУ=S15Fmt, EngText=Scale Number 15Format, группа=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum15Format), //[2115h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum16), //[2116h.01h], Название=Scale Number 16, ТекстПУ=SN16, EngText=Scale Number 16, группа=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.02h], Название=Scale Number 16Format, ТекстПУ=S16Fmt, EngText=Scale Number 16Format, группа=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum16Format), //[2116h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum17), //[2117h.01h], Название=Scale Number 17, ТекстПУ=SN17, EngText=Scale Number 17, группа=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.02h], Название=Scale Number 17Format, ТекстПУ=S17Fmt, EngText=Scale Number 17Format, группа=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum17Format), //[2117h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum18), //[2118h.01h], Название=Scale Number 18, ТекстПУ=SN18, EngText=Scale Number 18, группа=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.02h], Название=Scale Number 18Format, ТекстПУ=S18Fmt, EngText=Scale Number 18Format, группа=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum18Format), //[2118h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum19), //[2119h.01h], Название=Scale Number 19, ТекстПУ=SN19, EngText=Scale Number 19, группа=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.02h], Название=Scale Number 19Format, ТекстПУ=S19Fmt, EngText=Scale Number 19Format, группа=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum19Format), //[2119h.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum1A), //[211Ah.01h], Название=Scale Number 1A, ТекстПУ=SN1A, EngText=Scale Number 1A, группа=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.02h], Название=Scale Number 1AFormat, ТекстПУ=S1AFmt, EngText=Scale Number 1AFormat, группа=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum1AFormat), //[211Ah.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum1B), //[211Bh.01h], Название=Scale Number 1B, ТекстПУ=SN1B, EngText=Scale Number 1B, группа=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.02h], Название=Scale Number 1BFormat, ТекстПУ=S1BFmt, EngText=Scale Number 1BFormat, группа=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum1BFormat), //[211Bh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum1C), //[211Ch.01h], Название=Scale Number 1C, ТекстПУ=SN1C, EngText=Scale Number 1C, группа=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.02h], Название=Scale Number 1C Format, ТекстПУ=S1CFmt, EngText=Scale Number 1C Format, группа=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum1CFormat), //[211Ch.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&co2_vars.co_scaleNum1D), //[211Dh.01h], Название=Scale Number 1D, ТекстПУ=SN1D, EngText=Scale Number 1D, группа=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.02h], Название=Scale Number 1D Format, ТекстПУ=S1DFmt, EngText=Scale Number 1D Format, группа=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.03h], Название=Scale Number Format Q, ТекстПУ=Q-type, EngText=Scale Number Format Q, группа=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.04h], Название=Scale Number Format NumOfFloat, ТекстПУ=NFloat, EngText=Scale Number Format NumOfFloat, группа=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.05h], Название=Scale Number Format Prefix, ТекстПУ=Prefix, EngText=Scale Number Format Prefix, группа=CAN
(long)(&co2_vars.co_scaleNum1DFormat), //[211Dh.06h], Название=Scale Number Format Units, ТекстПУ=33, EngText=Scale Number Format Units, группа=CAN
(long)(&cmd_logic.local_cmd.all), //[2502h.01h], Название=cmd_pow_on, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.02h], Название=cmd_pow_off, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.03h], Название=cmd_trip_reset, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.04h], Название=cmd_pulses_on, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.05h], Название=cmd_pulses_off, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.06h], Название=cmd_more, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.07h], Название=cmd_less, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.08h], Название=cmd_set_cmd_source_LOCAL, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.09h], Название=cmd_set_cmd_source_REMOTE, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Ah], Название=cmd_set_refs_source_LOCAL, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Bh], Название=cmd_set_refs_source_REMOTE, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Ch], Название=cmd_set_dio_logic_mode_manual, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Dh], Название=cmd_set_dio_logic_mode_auto, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Eh], Название=cmd_set_dio_logic_mode_test, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.0Fh], Название=cmd_set_ctrl_profile1, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.10h], Название=cmd_set_ctrl_profile2, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_cmd.all), //[2502h.11h], Название=cmd_set_ctrl_profile3, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.status.cmd_source), //[2502h.12h], Название=cmd_logic_all, ТекстПУ=cmd_logic_all, EngText=cmd_logic_all, группа=Уставки и команды
(long)(&cmd_logic.status.refs_source), //[2502h.13h], Название=refs_source, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.status.profile), //[2502h.14h], Название=cmd_logic.status.profile, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.status.dio_logic_mode), //[2502h.15h], Название=dio_logic_mode, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&drv_interface.req_data), //[2506h.01h], Название=Таймаут потери связи, ТекстПУ=OfflineCounterMax, EngText=OfflineCounterMax, группа=ВНЕ ГРУПП
(long)(&drv_interface.ans_data), //[2506h.02h], Название=Счетчик потери связи, ТекстПУ=OfflineCounter, EngText=OfflineCounter, группа=ВНЕ ГРУПП
(long)(&drv_interface.data_Low), //[2506h.03h], Название=data_Low, ТекстПУ=data_Low, EngText=data_Low, группа=ВНЕ ГРУПП
(long)(&drv_interface.data_High), //[2506h.04h], Название=data_High, ТекстПУ=data_High, EngText=data_High, группа=ВНЕ ГРУПП
(long)(&RTCclock.packed_time), //[250Fh.00h], Название=Часы реального времени, ТекстПУ=RTC, EngText=Real time clock, группа=Наблюдаемые
(long)(&apl.protect_Code), //[2532h.01h], Название=Код аварии ARM, ТекстПУ=Код аварии ARM, EngText=, группа=Наблюдаемые
(long)(&apl.alarm_Code), //[2532h.02h], Название=Расширение кода аварии, ТекстПУ=Авр+, EngText=Extension of fault ID, группа=Наблюдаемые
(long)(&disp_group_number), //[2534h.01h], Название=Номер груп для пульта управления, ТекстПУ=№ гр ПУ, EngText=, группа=CAN
(long)(&VendorToken), //[2600h.01h], Название=VendorToken, ТекстПУ=VendorToken, EngText=VendorToken, группа=ВНЕ ГРУПП
(long)(&co2_vars.co_blockTransferCommand), //[2700h.00h], Название=Block Transfer Interpreter, ТекстПУ=BT Interpreter, EngText=BT Interpreter, группа=Слово управления
(long)(&swu_vars), //[2701h.01h], Название=cmd, ТекстПУ=cmd, EngText=cmd, группа=Слово управления
(long)(&swu_vars), //[2701h.02h], Название=status, ТекстПУ=status, EngText=status, группа=Слово управления
(long)(&swu_vars), //[2701h.03h], Название=quest1, ТекстПУ=quest1, EngText=quest1, группа=Слово управления
(long)(&swu_vars), //[2701h.04h], Название=quest2, ТекстПУ=quest2, EngText=quest2, группа=Слово управления
(long)(&swu_vars), //[2701h.05h], Название=quest3, ТекстПУ=quest3, EngText=quest3, группа=Слово управления
(long)(&swu_vars), //[2701h.06h], Название=quest4, ТекстПУ=quest4, EngText=quest4, группа=Слово управления
(long)(&swu_vars), //[2701h.07h], Название=ans1, ТекстПУ=ans1, EngText=ans1, группа=Слово управления
(long)(&swu_vars), //[2701h.08h], Название=ans2, ТекстПУ=ans2, EngText=ans2, группа=Слово управления
(long)(&swu_vars), //[2701h.09h], Название=ans3, ТекстПУ=ans3, EngText=ans3, группа=Слово управления
(long)(&swu_vars), //[2701h.0Ah], Название=ans4, ТекстПУ=ans4, EngText=ans4, группа=Слово управления
(long)(&swu_vars), //[2701h.0Bh], Название=addr, ТекстПУ=addr, EngText=addr, группа=Слово управления
(long)(&swu_vars), //[2701h.0Ch], Название=CPU_ID, ТекстПУ=CPU_ID, EngText=CPU_ID, группа=Слово управления
(long)(&swu_vars), //[2701h.0Dh], Название=sector_mask, ТекстПУ=sector_mask, EngText=sector_mask, группа=Слово управления
(long)(&swu_vars), //[2701h.0Eh], Название=version, ТекстПУ=version, EngText=version, группа=Слово управления
(long)(&swu_vars), //[2701h.0Fh], Название=CRC, ТекстПУ=CRC, EngText=CRC, группа=Слово управления
(long)(&inv.status), //[3000h.00h], Название=inv_status, ТекстПУ=, EngText=, группа=ВНЕ ГРУПП
(long)(&msCounter), //[3100h.01h], Название=Счётчик прерываний 1 кГц, ТекстПУ=Сч.прерыв.1 кГц, EngText=, группа=Для отладки
(long)(&FastCounter), //[3100h.02h], Название=Счётчик прерываний 10 кГц, ТекстПУ=Сч.прерыв.10 кГц, EngText=, группа=Для отладки
(long)(&LoopCounter), //[3100h.03h], Название=BackgroundCounter, ТекстПУ=BackgroundCounter, EngText=, группа=Для отладки
(long)(&TIsr10), //[3100h.04h], Название=T_10кГц, ТекстПУ=T_10кГц, EngText=T_10кГц, группа=Для отладки
(long)(&TIsr1), //[3100h.05h], Название=T_1кГц, ТекстПУ=T_1кГц, EngText=T_1кГц, группа=Для отладки
(long)(&rmp.T), //[5000h.01h], Название=T до номинала, ТекстПУ=rmpT, EngText=T разгона до номинала, группа=ЗИ
(long)(&rmp.input), //[5000h.02h], Название=Вход ЗИ, ТекстПУ=ВходЗИ, EngText=Ramp input, группа=ЗИ
(long)(&rmp.output), //[5000h.03h], Название=Выход ЗИ, ТекстПУ=ВыходЗИ, EngText=Ramp output, группа=ЗИ
(long)(&mppt.Dinit), //[5101h.01h], Название=Dinit, ТекстПУ=Dinit, EngText=Dinit, группа=MPPT
(long)(&mppt.Dmax), //[5101h.02h], Название=Dmax, ТекстПУ=Dmax, EngText=Dmax, группа=MPPT
(long)(&mppt.Dmin), //[5101h.03h], Название=Dmin, ТекстПУ=Dmin, EngText=Dmin, группа=MPPT
(long)(&mppt.deltaD), //[5101h.04h], Название=deltaD, ТекстПУ=deltaD, EngText=deltaD, группа=MPPT
(long)(&mppt.ena), //[5101h.05h], Название=ena, ТекстПУ=ena, EngText=ena, группа=MPPT
(long)(&mppt.V), //[5101h.06h], Название=V, ТекстПУ=V, EngText=V, группа=MPPT
(long)(&mppt.I), //[5101h.07h], Название=I, ТекстПУ=I, EngText=I, группа=MPPT
(long)(&mppt.D), //[5101h.08h], Название=D, ТекстПУ=D, EngText=D, группа=MPPT
(long)(&mppt.P), //[5101h.09h], Название=P, ТекстПУ=P, EngText=P, группа=MPPT
(long)(&mppt.delayvar), //[5101h.0Ah], Название=delay, ТекстПУ=, EngText=, группа=MPPT
(long)(&mppt.deltaV), //[5101h.0Bh], Название=deltaV, ТекстПУ=, EngText=, группа=MPPT
(long)(&mppt.Vmax), //[5101h.0Ch], Название=Vmax, ТекстПУ=, EngText=, группа=MPPT
(long)(&mppt.Vmin), //[5101h.0Dh], Название=Vmin, ТекстПУ=, EngText=, группа=MPPT
(long)(&pid_iq.pid_ref_reg3), //[5102h.01h], Название=Задание, ТекстПУ=Зад-ие, EngText=Задание, группа=Рег. тока Iq
(long)(&pid_iq.pid_fdb_reg3), //[5102h.02h], Название=Обратная связь, ТекстПУ=Обр.Св, EngText=Обратная связь, группа=Рег. тока Iq
(long)(&pid_iq.Kp_reg3), //[5102h.03h], Название=Пропорц. коэфф. Kp, ТекстПУ=Kp, EngText=Пропорциональный коэффициент Kp, группа=Рег. тока Iq
(long)(&pid_iq.pid_out_max), //[5102h.04h], Название=Максимум выхода, ТекстПУ=Max, EngText=Максимум выхода, группа=Рег. тока Iq
(long)(&pid_iq.pid_out_min), //[5102h.05h], Название=Минимум выхода, ТекстПУ=Min, EngText=Минимум выхода, группа=Рег. тока Iq
(long)(&pid_iq.Ki_reg3), //[5102h.06h], Название=Интегральный коэфф. Ki, ТекстПУ=Ki, EngText=Интегральный коэффициент Ki, группа=Рег. тока Iq
(long)(&pid_iq.Kd_reg3), //[5102h.07h], Название=Дифф. коэфф. Kd, ТекстПУ=Kd, EngText=Дифференциальный коэффициент Kd, группа=Рег. тока Iq
(long)(&pid_iq.Kc_reg3), //[5102h.08h], Название=Интегр.корректир.коэффициент, ТекстПУ=Kc, EngText=Integral correction gain, группа=Рег. тока Iq
(long)(&pid_iq.e_reg3), //[5102h.09h], Название=Ошибка рассогласования сигналов, ТекстПУ=Ошибка, EngText=, группа=Рег. тока Iq
(long)(&pid_iq.pid_out_reg3), //[5102h.0Ah], Название=Выход регулятора, ТекстПУ=Выход, EngText=Controller Output, группа=Рег. тока Iq
(long)(&pid_iq.up_reg3), //[5102h.0Bh], Название=Вых.Пропорц., ТекстПУ=Вых.Пропорц., EngText=Ud, группа=Рег. тока Iq
(long)(&pid_iq.ui_reg3), //[5102h.0Ch], Название=Вых.Интегр., ТекстПУ=Вых.Интегр., EngText=Integral Output, группа=Рег. тока Iq
(long)(&pid_iq.ud_reg3), //[5102h.0Dh], Название=Вых.Диффер., ТекстПУ=Вых.Диффер., EngText=Ud, группа=Рег. тока Iq
(long)(&pid_id.pid_ref_reg3), //[5103h.01h], Название=Задание, ТекстПУ=Зад-е, EngText=Reference, группа=Рег. тока Id
(long)(&pid_id.pid_fdb_reg3), //[5103h.02h], Название=Обратная связь, ТекстПУ=Обр.Св, EngText=Feedback, группа=Рег. тока Id
(long)(&pid_id.Kp_reg3), //[5103h.03h], Название=Пропорц. коэфф. Kp, ТекстПУ=Kp, EngText=Kp, группа=Рег. тока Id
(long)(&pid_id.pid_out_max), //[5103h.04h], Название=Максимум выхода, ТекстПУ=Max, EngText=Maximum Output Limits, группа=Рег. тока Id
(long)(&pid_id.pid_out_min), //[5103h.05h], Название=Минимум выхода, ТекстПУ=Min, EngText=Minimum Output Limits, группа=Рег. тока Id
(long)(&pid_id.Ki_reg3), //[5103h.06h], Название=Интегральный коэфф. Ki, ТекстПУ=Ki, EngText=Ki, группа=Рег. тока Id
(long)(&pid_id.Kd_reg3), //[5103h.07h], Название=Дифф. коэфф. Kd, ТекстПУ=Kd, EngText=Kd, группа=Рег. тока Id
(long)(&pid_id.Kc_reg3), //[5103h.08h], Название=Интегр.корректир.коэффициент, ТекстПУ=Kc, EngText=Integral correction gain, группа=Рег. тока Id
(long)(&pid_id.e_reg3), //[5103h.09h], Название=Ошибка рассогласования сигналов, ТекстПУ=Ошибка, EngText=, группа=Рег. тока Id
(long)(&pid_id.pid_out_reg3), //[5103h.0Ah], Название=Выход регулятора, ТекстПУ=Выход, EngText=Controller output, группа=Рег. тока Id
(long)(&pid_id.up_reg3), //[5103h.0Bh], Название=Вых.Пропорц., ТекстПУ=Вых.Пропорц., EngText=Ud, группа=Рег. тока Id
(long)(&pid_id.ui_reg3), //[5103h.0Ch], Название=Вых.Интегр., ТекстПУ=Вых.Интегр., EngText=Integral Output, группа=Рег. тока Id
(long)(&pid_id.ud_reg3), //[5103h.0Dh], Название=Вых.Диффер., ТекстПУ=Вых.Диффер., EngText=Ud, группа=Рег. тока Id
(long)(&pid_Udc.pid_ref_reg3), //[5104h.01h], Название=Задание, ТекстПУ=Зад-е, EngText=Reference, группа=Регулятор Udc1
(long)(&pid_Udc.pid_fdb_reg3), //[5104h.02h], Название=Обратная связь, ТекстПУ=Обр.Св, EngText=Feedback, группа=Регулятор Udc1
(long)(&pid_Udc.Kp_reg3), //[5104h.03h], Название=Пропорц. коэфф. Kp, ТекстПУ=Kp, EngText=Kp, группа=Регулятор Udc1
(long)(&pid_Udc.Ki_reg3), //[5104h.04h], Название=Интегральный коэфф. Ki, ТекстПУ=Ki, EngText=Ki, группа=Регулятор Udc1
(long)(&pid_Udc.pid_out_max), //[5104h.05h], Название=Максимум выхода, ТекстПУ=Max, EngText=Maximum Output Limits, группа=Регулятор Udc1
(long)(&pid_Udc.pid_out_min), //[5104h.06h], Название=Минимум выхода, ТекстПУ=Min, EngText=Minimum Output Limits, группа=Регулятор Udc1
(long)(&pid_Udc.pid_out_reg3), //[5104h.07h], Название=Выход регулятора, ТекстПУ=Выход, EngText=Controller output, группа=Регулятор Udc1
(long)(&pid_Udc.up_reg3), //[5104h.08h], Название=Вых.Пропорц., ТекстПУ=Вых.Пропорц., EngText=Ud, группа=Регулятор Udc1
(long)(&pid_Udc.ui_reg3), //[5104h.09h], Название=Вых.Интегр., ТекстПУ=Вых.Интегр., EngText=Integral Output, группа=Регулятор Udc1
(long)(&pid_Udc.Kd_reg3), //[5104h.0Ah], Название=Дифф. коэфф. Kd, ТекстПУ=Kd, EngText=Kd, группа=Регулятор Udc1
(long)(&pwm.UalphaRef), //[5105h.01h], Название=UaЗад, ТекстПУ=UaЗад, EngText=UaЗад, группа=ШИМ
(long)(&pwm.UbetaRef), //[5105h.02h], Название=UbЗад, ТекстПУ=UbЗад, EngText=UbЗад, группа=ШИМ
(long)(&pwm.U_lim), //[5105h.03h], Название=U_огр, ТекстПУ=U_огр, EngText=U_огр, группа=ШИМ
(long)(&pwm.gammaA), //[5105h.04h], Название=GammaA, ТекстПУ=GmA, EngText=GammaA, группа=ШИМ
(long)(&pwm.gammaB), //[5105h.05h], Название=GammaB, ТекстПУ=GmB, EngText=GammaB, группа=ШИМ
(long)(&pwm.gammaC), //[5105h.06h], Название=GammaC, ТекстПУ=GmC, EngText=GammaC, группа=ШИМ
(long)(&pwm.k_pwm), //[5105h.07h], Название=TPWM, ТекстПУ=TPWM, EngText=TPWM, группа=ШИМ
(long)(&pwm.DeadBand), //[5105h.08h], Название=Мертвое время (мкс), ТекстПУ=Мерт. время, EngText=DeadBand, группа=ШИМ
(long)(&pwm.MinGammaLimit), //[5105h.09h], Название=Ограничение мин. скважн., ТекстПУ=GamLim, EngText=GamLim, группа=ШИМ
(long)(&pwm.U_ref_fan_pwm), //[5105h.0Ah], Название=U_ref_fan_pwm, ТекстПУ=, EngText=, группа=ШИМ
(long)(&pwm.I_ref_pwm), //[5105h.0Bh], Название=I_ref_pwm, ТекстПУ=, EngText=, группа=ШИМ
(long)(&pwm.PWM_type), //[5105h.0Ch], Название=Тип ШИМ, ТекстПУ=ТипШИМ, EngText=PWMType, группа=ШИМ
(long)(&pwm.UdCompEnable), //[5105h.0Dh], Название=ULimitation, ТекстПУ=ULimitation, EngText=ULimitation, группа=ШИМ
(long)(&pwm.Frequency), //[5105h.0Eh], Название=Частота ШИМ, ТекстПУ=Fшим, EngText=PWM frequency, группа=ШИМ
(long)(&pwm.sector), //[5105h.0Fh], Название=Сектор, ТекстПУ=Сектор, EngText=Sector, группа=ШИМ
(long)(&pwm.U_mag), //[5105h.10h], Название=U_ампл, ТекстПУ=U_ампл, EngText=U_ампл, группа=ШИМ
(long)(&pwm.PDP_Fault), //[5105h.11h], Название=Флаги аварий, ТекстПУ=F_bits, EngText=F_bits, группа=ШИМ
(long)(&pwm.PDP_Fault), //[5105h.12h], Название=Флаги аварий, ТекстПУ=F_bits, EngText=F_bits, группа=ШИМ
(long)(&pwm.PDP_Fault), //[5105h.13h], Название=Флаги аварий, ТекстПУ=F_bits, EngText=F_bits, группа=ШИМ
(long)(&dcs_ctrl.state), //[510Bh.01h], Название=sm_state, ТекстПУ=smstat, EngText=sm_state, группа=Наладка
(long)(&inv.status), //[510Bh.02h], Название=inv_status, ТекстПУ=, EngText=, группа=Наладка
(long)(&dcs_ctrl.test_param1), //[510Bh.03h], Название=test_param1, ТекстПУ=, EngText=, группа=Наладка
(long)(&dcs_ctrl.test_param2), //[510Bh.04h], Название=test_param2, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.attempts_counter), //[510Bh.05h], Название=attemps_counter, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.sub_state), //[510Bh.06h], Название=sub_state, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.counter), //[510Bh.07h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.sub_counter), //[510Bh.08h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.go_day_mode_timeout_s), //[510Bh.09h], Название=go_day_mode_timeout_s, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.go_night_mode_timeout_s), //[510Bh.0Ah], Название=go_night_mode_timeout_s, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.P_low_time_s), //[510Bh.0Bh], Название=P_low_time_s, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.P_low_timeshift_s), //[510Bh.0Ch], Название=P_low_timeshift, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.P_low_attempts_max), //[510Bh.0Dh], Название=P_low_attemps_max, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.P_night), //[510Bh.0Eh], Название=P_night, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.Udc_day), //[510Bh.0Fh], Название=Udc_day, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.Udc_night), //[510Bh.10h], Название=Udc_night, ТекстПУ=, EngText=, группа=Наладка
(long)(&dcs_refs.Id_ref), //[510Bh.11h], Название=dcs_refs.Id_ref, ТекстПУ=dcs_refs.Id_ref, EngText=dcs_refs.Id_ref, группа=Наладка
(long)(&dcs_refs.Iq_ref), //[510Bh.12h], Название=dcs_refs.Iq_ref, ТекстПУ=dcs_refs.Iq_ref, EngText=dcs_refs.Iq_ref, группа=Наладка
(long)(&HAL.DIO.DI_1), //[510Bh.13h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&HAL.DIO.DI_4), //[510Bh.14h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[0].o_word), //[510Bh.15h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[1].o_word), //[510Bh.16h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[2].o_word), //[510Bh.17h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[0].i_word), //[510Bh.18h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[1].i_word), //[510Bh.19h], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[2].i_word), //[510Bh.1Ah], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&can_mini.can_io[0].a_inp), //[510Bh.1Bh], Название=internal_use_only, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.Udc_level_go_on), //[510Bh.1Ch], Название=Udc_level_go_on, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.Udc_min_lim_power), //[510Bh.1Dh], Название=Udc_min_lim_power, ТекстПУ=, EngText=, группа=Наладка
(long)(&inv.params.Udc_max_lim_power), //[510Bh.1Eh], Название=Udc_max_lim_power, ТекстПУ=, EngText=, группа=Наладка
(long)(&dcs_prot.Imax), //[510Eh.01h], Название=Imax, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.Udc_max), //[510Eh.02h], Название=Udc1_max, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.Udc_min), //[510Eh.03h], Название=Udc1_min, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.U1_max), //[510Eh.04h], Название=U1max, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.U1_min), //[510Eh.05h], Название=U1min, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.Idc_max), //[510Eh.06h], Название=Idc1_max, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.bit_fault1), //[510Eh.07h], Название=dio_prot_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.bit_alarm1), //[510Eh.08h], Название=bit_alarm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.bit_alarm1), //[510Eh.09h], Название=bit_alarm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.bit_fault1), //[510Eh.0Ah], Название=dcs_prot_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.bit_fault1), //[510Eh.0Bh], Название=dcs_prot_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.masked_bit_fault1), //[510Eh.0Ch], Название=dcs_prot_masked_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.masked_bit_fault1), //[510Eh.0Dh], Название=dcs_prot_masked_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.mask_fault_pwm1), //[510Eh.0Eh], Название=dcs_prot_mask_fault_pwm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.mask_fault_pwm1), //[510Eh.0Fh], Название=dcs_prot_mask_fault_pwm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.mask_fault_off), //[510Eh.10h], Название=dcs_prot_mask_fault_off, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.mask_fault_off), //[510Eh.11h], Название=dcs_prot_mask_fault_off, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.bit_fault1), //[510Eh.12h], Название=dio_prot_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.bit_fault1), //[510Eh.13h], Название=dio_prot_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.masked_bit_fault1), //[510Eh.14h], Название=dio_prot_masked_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.masked_bit_fault1), //[510Eh.15h], Название=dio_prot_masked_bit_fault1, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.mask_fault_pwm1), //[510Eh.16h], Название=dio_prot_mask_fault_pwm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.mask_fault_pwm1), //[510Eh.17h], Название=dio_prot_mask_fault_pwm, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.mask_fault_off), //[510Eh.18h], Название=dio_prot_mask_fault_off, ТекстПУ=, EngText=, группа=Защиты
(long)(&dio_protect.mask_fault_off), //[510Eh.19h], Название=dio_prot_mask_fault_off, ТекстПУ=, EngText=, группа=Защиты
(long)(&dcs_prot.T_max), //[510Eh.1Ah], Название=Уставка Тmax, ТекстПУ=Tmax, EngText=Tmax, группа=Защиты
(long)(&apl_protect.AR1.ena), //[510Fh.01h], Название=apl_protect.AR1.ena, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.masked_word[0]), //[510Fh.02h], Название=apl_protect.masked_word0, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.masked_word[1]), //[510Fh.03h], Название=apl_protect.masked_word1, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.masked_off_word[0]), //[510Fh.04h], Название=apl_protect.masked_off_word0, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.masked_off_word[1]), //[510Fh.05h], Название=apl_protect.masked_off_word1, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.mask_apv_word[0]), //[510Fh.06h], Название=apl_protect.mask_apv_word0, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.mask_apv_word[0]), //[510Fh.07h], Название=apl_protect.mask_apv_word0, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.mask_apv_word[1]), //[510Fh.08h], Название=apl_protect.mask_apv_word1, ТекстПУ=, EngText=, группа=Защиты
(long)(&apl_protect.mask_apv_word[1]), //[510Fh.09h], Название=apl_protect.mask_apv_word1, ТекстПУ=, EngText=, группа=Защиты
(long)(&pll.Ua), //[5111h.01h], Название=pll_Ua, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.Ub), //[5111h.02h], Название=pll_Ub, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.Uc), //[5111h.03h], Название=pll_Uc, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.Um1), //[5111h.04h], Название=pll_Um1, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.Um2), //[5111h.05h], Название=pll_Um2, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.wt_e), //[5111h.06h], Название=pll_wt_e, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.fs), //[5111h.07h], Название=pll.fs, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&pll.alpha), //[5111h.08h], Название=pll.alpha, ТекстПУ=, EngText=, группа=Синхронизация с сетью
(long)(&cmd_logic.remote_refs.P_ref), //[5112h.01h], Название=remote.P_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_refs.P_ref), //[5112h.02h], Название=local.P_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.refs.P_ref), //[5112h.03h], Название=refs.P_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.remote_refs.P_dcdc_ref), //[5112h.04h], Название=remote.P_dcdc_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.local_refs.P_dcdc_ref), //[5112h.05h], Название=local.P_dcdc_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&cmd_logic.refs.P_dcdc_ref), //[5112h.06h], Название=refs.P_dcdc_ref, ТекстПУ=, EngText=, группа=Уставки и команды
(long)(&dcs_ctrl.cmd_set_mode), //[5112h.07h], Название=Регистр ошибок, ТекстПУ=ErrReg, EngText=Error Register, группа=Уставки и команды
(long)(&inv_params.I_nom), //[5113h.01h], Название=Номинальный ток, ТекстПУ=, EngText=Номинальный ток, группа=Базов. парам
(long)(&inv_params.U_nom), //[5113h.02h], Название=Номинальное напряжение фазн., ТекстПУ=Uф_ном, EngText=Номинальное напряжение фазн., группа=Базов. парам
(long)(&inv_params.Udc_nom), //[5113h.03h], Название=Номинальное напряжение ЗПТ, ТекстПУ=UdcНом, EngText=Номинальное напряжение ЗПТ, группа=Базов. парам
(long)(&inv_params.Rs), //[5113h.04h], Название=Rs, ТекстПУ=Rs, EngText=Rs, группа=Базов. парам
(long)(&inv_params.Ls), //[5113h.05h], Название=Ls, ТекстПУ=Ls, EngText=Ls, группа=Базов. парам
(long)(&inv_params.freq_nom), //[5113h.06h], Название=Номинальная частота, ТекстПУ=Ном.част., EngText=Rated frequency, группа=Базов. парам
(long)(&sw.HardwareType), //[5114h.01h], Название=Тип аппаратной части, ТекстПУ=HardwareType, EngText=HardwareType, группа=Настройки СУ
(long)(&sw.AutoOffset), //[5114h.02h], Название=АЦП авто смещ., ТекстПУ=АЦПсмещ, EngText=AutoOffset, группа=Настройки СУ
(long)(&sw.Reboot), //[5114h.03h], Название=Перезагрузка, ТекстПУ=Перезагрузка, EngText=Reboot, группа=Настройки СУ
(long)(&sim.dcs_sim_ena), //[5115h.01h], Название=dcs_sim_ena, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.dio_sim_ena), //[5115h.02h], Название=dio_sim_ena, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.freq), //[5115h.03h], Название=freq, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.angle), //[5115h.04h], Название=angle, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Um1_tr), //[5115h.05h], Название=Um1_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Udc_ref), //[5115h.06h], Название=sim.Udc_ref, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.I_diesel), //[5115h.07h], Название=I_diesel, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Idc_ref), //[5115h.08h], Название=sim.Idc_ref, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ua_tr), //[5115h.09h], Название=Ua_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ub_tr), //[5115h.0Ah], Название=Ub_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Uc_tr), //[5115h.0Bh], Название=Uc_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Um1_f), //[5115h.0Ch], Название=Um1_f, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ua_f), //[5115h.0Dh], Название=Ua_f, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ub_f), //[5115h.0Eh], Название=Ub_f, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Uc_f), //[5115h.0Fh], Название=Uc_f, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ia_tr), //[5115h.10h], Название=Ia_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ib_tr), //[5115h.11h], Название=Ib_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ic_tr), //[5115h.12h], Название=Ic_tr, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ia_inv), //[5115h.13h], Название=Ia_inv, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ib_inv), //[5115h.14h], Название=Ib_inv, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.Ic_inv), //[5115h.15h], Название=Ic_inv, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.event), //[5115h.16h], Название=sim.event, ТекстПУ=, EngText=, группа=Симулятор
(long)(&sim.event_timeout), //[5115h.17h], Название=sim.event_timeout, ТекстПУ=, EngText=, группа=Симулятор
(long)(&adc.sUbc_inv.value), //[5116h.01h], Название=Ubc_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_inv.value), //[5116h.02h], Название=Uac_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_inv.value), //[5116h.03h], Название=Unc_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUbc_inv._100to1V_gain), //[5116h.04h], Название=Ubc_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_inv._100to1V_gain), //[5116h.05h], Название=Uac_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_inv._100to1V_gain), //[5116h.06h], Название=Unc_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUbc_inv.offset), //[5116h.07h], Название=Ubc_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_inv.offset), //[5116h.08h], Название=Uac_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_inv.offset), //[5116h.09h], Название=Unc_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&delimeter_sign), //[5116h.0Ah], Название=__________________________, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUbc_tr.value), //[5116h.0Bh], Название=Ubc_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_tr.value), //[5116h.0Ch], Название=Uac_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_tr.value), //[5116h.0Dh], Название=Unc_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUbc_tr._100to1V_gain), //[5116h.0Eh], Название=Ubc_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_tr._100to1V_gain), //[5116h.0Fh], Название=Uac_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_tr._100to1V_gain), //[5116h.10h], Название=Unc_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUbc_tr.offset), //[5116h.11h], Название=Ubc_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUac_tr.offset), //[5116h.12h], Название=Uac_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUnc_tr.offset), //[5116h.13h], Название=Unc_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&delimeter_sign), //[5116h.14h], Название=__________________________, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ia_inv), //[5116h.15h], Название=Ia_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ib_inv), //[5116h.16h], Название=Ib_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ic_inv), //[5116h.17h], Название=Ic_inv, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIa_inv._100to1V_gain), //[5116h.18h], Название=Ia_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIb_inv._100to1V_gain), //[5116h.19h], Название=Ib_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIc_inv._100to1V_gain), //[5116h.1Ah], Название=Ic_inv_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIa_inv.offset), //[5116h.1Bh], Название=Ia_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIb_inv.offset), //[5116h.1Ch], Название=Ib_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIc_inv.offset), //[5116h.1Dh], Название=Ic_inv_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&delimeter_sign), //[5116h.1Eh], Название=__________________________, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ia_tr), //[5116h.1Fh], Название=Ia_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ib_tr), //[5116h.20h], Название=Ib_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Ic_tr), //[5116h.21h], Название=Ic_tr, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIa_tr._100to1V_gain), //[5116h.22h], Название=Ia_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIb_tr._100to1V_gain), //[5116h.23h], Название=Ib_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIc_tr._100to1V_gain), //[5116h.24h], Название=Ic_tr_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIa_tr.offset), //[5116h.25h], Название=Ia_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIb_tr.offset), //[5116h.26h], Название=Ib_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIc_tr.offset), //[5116h.27h], Название=Ic_tr_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&delimeter_sign), //[5116h.28h], Название=__________________________, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIdc._100to1V_gain), //[5116h.29h], Название=Idc_meas_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sIdc.offset), //[5116h.2Ah], Название=Idc_meas_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Idc), //[5116h.2Bh], Название=Idc_meas, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUdc._100to1V_gain), //[5116h.2Ch], Название=Udc_meas_gain, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.sUdc.offset), //[5116h.2Dh], Название=Udc_meas_offset, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.Udc), //[5116h.2Eh], Название=Udc_meas, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.I_REF_PWM_adc), //[5116h.2Fh], Название=I_REF_PWM_adc, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc._0p75V_REF_adc), //[5116h.30h], Название=_0p75V_REF_adc, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.Udc_adc_reg), //[5116h.31h], Название=Udc_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U1_BC_adc_reg), //[5116h.32h], Название=U1_BC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U1_AC_adc_reg), //[5116h.33h], Название=U1_AC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U1_NC_adc_reg), //[5116h.34h], Название=U1_NC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U2_BC_adc_reg), //[5116h.35h], Название=U2_BC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U2_AC_adc_reg), //[5116h.36h], Название=U2_AC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.U2_NC_adc_reg), //[5116h.37h], Название=U2_NC_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I2_C_adc_reg), //[5116h.38h], Название=I2_C_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I2_B_adc_reg), //[5116h.39h], Название=I2_B_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I2_A_adc_reg), //[5116h.3Ah], Название=I2_A_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I1_C_adc_reg), //[5116h.3Bh], Название=I1_C_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I1_B_adc_reg), //[5116h.3Ch], Название=I1_B_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.I1_A_adc_reg), //[5116h.3Dh], Название=I1_A_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.Idc_adc_reg), //[5116h.3Eh], Название=Idc_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs._0p75V_adc_reg), //[5116h.3Fh], Название=_0p75V_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&HAL.ADC.regs.IREF_PWM_adc_reg), //[5116h.40h], Название=I_REF_PWM_adc_reg, ТекстПУ=, EngText=, группа=АЦП
(long)(&adc.auto_offset_ena), //[5116h.41h], Название=АЦП авто смещ., ТекстПУ=АЦПсмещ, EngText=AutoOffset, группа=АЦП
(long)(&cur_par.Pdc), //[5138h.01h], Название=Pdc, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&cur_par.Pac), //[5138h.02h], Название=Pac, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ia_inv), //[5138h.03h], Название=Ia_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ib_inv), //[5138h.04h], Название=Ib_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ic_inv), //[5138h.05h], Название=Ic_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ia_tr), //[5138h.06h], Название=Ia_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ib_tr), //[5138h.07h], Название=Ib_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ic_tr), //[5138h.08h], Название=Ic_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Uab_inv), //[5138h.09h], Название=Uab_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ubc_inv), //[5138h.0Ah], Название=Ubc_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Uca_inv), //[5138h.0Bh], Название=Uca_inv_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Uab_tr), //[5138h.0Ch], Название=Uab_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Ubc_tr), //[5138h.0Dh], Название=Ubc_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.rms.Uca_tr), //[5138h.0Eh], Название=Uca_tr_rms, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Uab_inv), //[5138h.0Fh], Название=Uab_inv, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Ubc_inv), //[5138h.10h], Название=Ubc_inv, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Uca_inv), //[5138h.11h], Название=Uca_inv, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Uab_tr), //[5138h.12h], Название=Uab_tr, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Ubc_tr), //[5138h.13h], Название=Ubc_tr, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Uca_tr), //[5138h.14h], Название=Uca_tr, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&pll.Um1), //[5138h.15h], Название=Um1_tr, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&pll.Um2), //[5138h.16h], Название=Um2_tr, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&global_time.PowerOn_time_min), //[5138h.17h], Название=Время запитанного состояния, мин, ТекстПУ=Power On Time, EngText=Power On Time, группа=Наблюдаемые
(long)(&global_time.operational_time_min), //[5138h.18h], Название=Вреря работы привода, мин, ТекстПУ=Work Time, EngText=Work Time, группа=Наблюдаемые
(long)(&cur_par.Qac), //[5138h.19h], Название=Qac, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&cur_par.S), //[5138h.1Ah], Название=Sac, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&cur_par.cos_fi), //[5138h.1Bh], Название=cos(fi), ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Edc_day), //[5138h.1Ch], Название=Edc_day, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.Edc_total), //[5138h.1Dh], Название=Edc_total, ТекстПУ=, EngText=, группа=Наблюдаемые
(long)(&adc.sUbc_tr.calibration.gain), //[5139h.01h], Название=sUbc_tr.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sUbc_inv.calibration.gain), //[5139h.02h], Название=sUbc_inv.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIa_tr.calibration.gain), //[5139h.03h], Название=sIa_tr.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIb_tr.calibration.gain), //[5139h.04h], Название=sIb_tr.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIc_tr.calibration.gain), //[5139h.05h], Название=sIc_tr.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIa_inv.calibration.gain), //[5139h.06h], Название=sIa_inv.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIb_inv.calibration.gain), //[5139h.07h], Название=sIb_inv.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIc_inv.calibration.gain), //[5139h.08h], Название=sIc_inv.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sUdc.calibration.gain), //[5139h.09h], Название=sUdc.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sIdc.calibration.gain), //[5139h.0Ah], Название=sIdc.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&adc.sI_diesel.calibration.gain), //[5139h.0Bh], Название=sI_diesel.calibration.gain, ТекстПУ=, EngText=, группа=Калибровка измерений
(long)(&dlog.mode_reset), //[5150h.01h], Название=dlog.mode_reset, ТекстПУ=mode, EngText=dlog.mode_reset, группа=dlog
(long)(&dlog.control), //[5150h.02h], Название=dlog.control, ТекстПУ=dlcont, EngText=dlog.control, группа=dlog
(long)(&dlog.ind_subind1), //[5150h.03h], Название=dlog.ind_subind1, ТекстПУ=dlisi1, EngText=dlog.ind_subind1, группа=dlog
(long)(&dlog.ind_subind2), //[5150h.04h], Название=dlog.ind_subind2, ТекстПУ=dlisi2, EngText=dlog.ind_subind2, группа=dlog
(long)(&dlog.ind_subind3), //[5150h.05h], Название=dlog.ind_subind3, ТекстПУ=dlisi3, EngText=dlog.ind_subind3, группа=dlog
(long)(&dlog.ind_subind4), //[5150h.06h], Название=dlog.ind_subind4, ТекстПУ=dlisi4, EngText=dlog.ind_subind4, группа=dlog
(long)(&dlog.StartBits), //[5150h.07h], Название=StartBitL, ТекстПУ=StrtBL, EngText=StartBitL, группа=dlog
(long)(&dlog.StartBits), //[5150h.08h], Название=StartBitH, ТекстПУ=StrtBH, EngText=StartBitH, группа=dlog
(long)(&dlog.OneShotOperation), //[5150h.09h], Название=OneShotOperation, ТекстПУ=OneShotOp, EngText=OneShotOperation, группа=dlog
(long)(&dlog.trig_shift), //[5150h.0Ah], Название=Количество точек предыстории, ТекстПУ=N предыст., EngText=Prehistory Points Number, группа=dlog
(long)(&dlog.next_value_var), //[5151h.00h], Название=dlog.next_value_var, ТекстПУ=dlnval, EngText=dlog.next_value_var, группа=ВНЕ ГРУПП
(long)(&Debug1), //[5174h.01h], Название=DebugL1, ТекстПУ=DebugL1, EngText=DebugL1, группа=Для отладки
(long)(&Debug1), //[5174h.02h], Название=DebugL1, ТекстПУ=DebugL1, EngText=DebugL1, группа=Для отладки
(long)(&Debug2), //[5174h.03h], Название=DebugL2, ТекстПУ=DebugL2, EngText=DebugL2, группа=Для отладки
(long)(&Debug2), //[5174h.04h], Название=DebugL2, ТекстПУ=DebugL2, EngText=DebugL2, группа=Для отладки
(long)(&Debug3), //[5174h.05h], Название=DebugI3, ТекстПУ=DebugI3, EngText=DebugI3, группа=Для отладки
(long)(&Debug3), //[5174h.06h], Название=DebugI3, ТекстПУ=DebugI3, EngText=DebugI3, группа=Для отладки
(long)(&Debug4), //[5174h.07h], Название=DebugI4, ТекстПУ=DebugI4, EngText=DebugI4, группа=Для отладки
(long)(&Debug4), //[5174h.08h], Название=DebugI4, ТекстПУ=DebugI4, EngText=DebugI4, группа=Для отладки
(long)(&DebugW1), //[5174h.09h], Название=DebugW1, ТекстПУ=DebugW1, EngText=DebugW1, группа=Для отладки
(long)(&DebugW1), //[5174h.0Ah], Название=DebugW1, ТекстПУ=DebugW1, EngText=DebugW1, группа=Для отладки
(long)(&DebugW2), //[5174h.0Bh], Название=DebugW2, ТекстПУ=DebugW2, EngText=DebugW2, группа=Для отладки
(long)(&DebugW2), //[5174h.0Ch], Название=DebugW2, ТекстПУ=DebugW2, EngText=DebugW2, группа=Для отладки
(long)(&DebugW3), //[5174h.0Dh], Название=DebugW3, ТекстПУ=DebugW3, EngText=DebugW3, группа=Для отладки
(long)(&DebugW3), //[5174h.0Eh], Название=DebugW3, ТекстПУ=DebugW3, EngText=DebugW3, группа=Для отладки
(long)(&DebugW4), //[5174h.0Fh], Название=DebugW4, ТекстПУ=DebugW4, EngText=, группа=Для отладки
(long)(&DebugW4), //[5174h.10h], Название=DebugW4, ТекстПУ=DebugW4, EngText=, группа=Для отладки
(long)(&DebugF1), //[5174h.11h], Название=DebugF1, ТекстПУ=DebugF1, EngText=, группа=Для отладки
(long)(&DebugF2), //[5174h.12h], Название=DebugF2, ТекстПУ=DebugF2, EngText=, группа=Для отладки
(long)(&DebugF3), //[5174h.13h], Название=DebugF3, ТекстПУ=DebugF3, EngText=, группа=Для отладки
(long)(&DebugF4), //[5174h.14h], Название=DebugF4, ТекстПУ=DebugF4, EngText=, группа=Для отладки
(long)(&fan_actrl.Temp_max_fan), //[5175h.01h], Название=Уставка Тmax, ТекстПУ=Tmax, EngText=Tmax, группа=Система охлаждения
(long)(&fan_actrl.Temp_min_fan), //[5175h.02h], Название=Уставка Тmin, ТекстПУ=Tmin, EngText=Tmin, группа=Система охлаждения
(long)(&fan_actrl.V_out), //[5175h.03h], Название=Выход, ТекстПУ=U_out, EngText=U_out, группа=Система охлаждения
(long)(&fan_actrl.V_fdb), //[5175h.04h], Название=Обратный сигнал, ТекстПУ=U_fdb, EngText=U_fdb, группа=Система охлаждения
(long)(&fan_actrl.state), //[5175h.05h], Название=state, ТекстПУ=state, EngText=state, группа=Система охлаждения
(long)(&fan_actrl.T), //[5175h.06h], Название=Температура, ТекстПУ=t, EngText=temperature, группа=Система охлаждения
(long)(&fan_dctrl.T_max), //[5176h.01h], Название=Уставка Тmax, ТекстПУ=Tmax, EngText=Tmax, группа=Система охлаждения
(long)(&fan_dctrl.Temp_lo), //[5176h.02h], Название=Temp_lo, ТекстПУ=Temp_lo, EngText=Temp_lo, группа=Система охлаждения
(long)(&fan_dctrl.Temp_lo2hi), //[5176h.03h], Название=Temp_lo2hi, ТекстПУ=Temp_lo2hi, EngText=Temp_lo2hi, группа=Система охлаждения
(long)(&fan_dctrl.Temp_hi2lo), //[5176h.04h], Название=Temp_hi2lo, ТекстПУ=Temp_hi2lo, EngText=Temp_hi2lo, группа=Система охлаждения
(long)(&fan_dctrl.Temp_hi), //[5176h.05h], Название=Temp_hi, ТекстПУ=Temp_hi, EngText=Temp_hi, группа=Система охлаждения
(long)(&fan_dctrl.time_hi2lo_ms), //[5176h.06h], Название=time_hi2lo_ms, ТекстПУ=time_hi2lo_ms, EngText=time_hi2lo_ms, группа=Система охлаждения
(long)(&fan_dctrl.state), //[5176h.07h], Название=state, ТекстПУ=state, EngText=state, группа=Система охлаждения
(long)(&fan_spec.d_fdb), //[5176h.08h], Название=state, ТекстПУ=state, EngText=state, группа=Система охлаждения
(long)(&fan_dctrl.T), //[5176h.09h], Название=Температура, ТекстПУ=t, EngText=temperature, группа=Система охлаждения
(long)(&adc.T1), //[5177h.01h], Название=Датчик температуры №1, ТекстПУ=T1, EngText=T1, группа=Система охлаждения
(long)(&adc.T2), //[5177h.02h], Название=Датчик температуры №2, ТекстПУ=T2, EngText=T2, группа=Система охлаждения
(long)(&adc.T3), //[5177h.03h], Название=Датчик температуры №3, ТекстПУ=T3, EngText=T3, группа=Система охлаждения
(long)(&adc.T4), //[5177h.04h], Название=Датчик температуры №4, ТекстПУ=T4, EngText=T4, группа=Система охлаждения
(long)(&adc.T1_inv1), //[5177h.05h], Название=Температура IGBT#1, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&adc.T2_inv1), //[5177h.06h], Название=Температура IGBT#2, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&adc.T3_inv1), //[5177h.07h], Название=Температура IGBT#3, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&adc.T1_inv2), //[5177h.08h], Название=Температура IGBT#1, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&adc.T2_inv2), //[5177h.09h], Название=Температура IGBT#2, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&adc.T3_inv2), //[5177h.0Ah], Название=Температура IGBT#3, ТекстПУ=, EngText=, группа=Система охлаждения
(long)(&ModBus.Enabled), //[5A20h.01h], Название=Включен, ТекстПУ=Вкл, EngText=Enabled, группа=MODBUS
(long)(&ModBus.RSNodeID), //[5A20h.02h], Название=Номер в сети ModBus, ТекстПУ=, EngText=, группа=MODBUS
(long)(&ModBus.BaudRate), //[5A20h.03h], Название=, ТекстПУ=, EngText=, группа=MODBUS
(long)(&ModBus.OfflineCounterMax), //[5A20h.04h], Название=Таймаут потери связи, ТекстПУ=OfflineCounterMax, EngText=OfflineCounterMax, группа=MODBUS
(long)(&ModBus.AutoRestart), //[5A20h.05h], Название=Перезапуск при сбоях на линии, ТекстПУ=auto_res, EngText=auto_res, группа=MODBUS
(long)(&ModBus.OfflineCounter), //[5A20h.06h], Название=Счетчик потери связи, ТекстПУ=OfflineCounter, EngText=OfflineCounter, группа=MODBUS
(long)(&ModBus.isOnline), //[5A20h.07h], Название=Udc_meas_offset, ТекстПУ=, EngText=, группа=MODBUS
(long)(&ModBus.received_data), //[5A20h.08h], Название=Udc_meas, ТекстПУ=, EngText=, группа=MODBUS
(long)(&ModBus.MBInternals.TxState), //[5A20h.09h], Название=Состояние передачи посылки, ТекстПУ=TXState, EngText=TXState, группа=MODBUS
(long)(&ModBus.GPIOsValue), //[5A20h.0Ah], Название=dio_prot_mask_fault_off, ТекстПУ=, EngText=, группа=MODBUS
(long)(&ModBus.ReceivePacketCounter), //[5A20h.0Bh], Название=Пакетов принято, ТекстПУ=ReceivePacketCounte, EngText=ReceivePacketCounter, группа=MODBUS
(long)(&ModBus.ReceiveByteCounter), //[5A20h.0Ch], Название=Байт принято, ТекстПУ=ReceiveByteCounter, EngText=ReceiveByteCounter, группа=MODBUS
(long)(&aux_Q4.state), //[5A78h.01h], Название=state, ТекстПУ=, EngText=, группа=Q4
(long)(&aux_Q4.aux_on), //[5A78h.02h], Название=aux_on, ТекстПУ=, EngText=, группа=Q4
(long)(&aux_Q4.aux_off), //[5A78h.03h], Название=aux_off, ТекстПУ=, EngText=, группа=Q4
(long)(&aux_Q4.hold_on), //[5A78h.04h], Название=hold_on, ТекстПУ=, EngText=, группа=Q4
(long)(&aux_Q4.hold_off), //[5A78h.05h], Название=hold_off, ТекстПУ=, EngText=, группа=Q4
(long)(&aux_Q26.state), //[5A79h.01h], Название=state, ТекстПУ=, EngText=, группа=Q26
(long)(&aux_Q26.aux_on), //[5A79h.02h], Название=aux_on, ТекстПУ=, EngText=, группа=Q26
(long)(&aux_Q26.aux_off), //[5A79h.03h], Название=aux_off, ТекстПУ=, EngText=, группа=Q26
(long)(&aux_Q26.hold_on), //[5A79h.04h], Название=hold_on, ТекстПУ=, EngText=, группа=Q26
(long)(&aux_Q26.hold_off), //[5A79h.05h], Название=hold_off, ТекстПУ=, EngText=, группа=Q26
(long)(&aux_K7.state), //[5A7Ah.01h], Название=state, ТекстПУ=, EngText=, группа=K7
(long)(&aux_K7.aux_on), //[5A7Ah.02h], Название=aux_on, ТекстПУ=, EngText=, группа=K7
(long)(&aux_K7.aux_off), //[5A7Ah.03h], Название=aux_off, ТекстПУ=, EngText=, группа=K7
(long)(&aux_K7.hold_on), //[5A7Ah.04h], Название=hold_on, ТекстПУ=, EngText=, группа=K7
(long)(&aux_K7.hold_off), //[5A7Ah.05h], Название=hold_off, ТекстПУ=, EngText=, группа=K7
(long)(&dcdc.ena), //[5A7Bh.01h], Название=ena, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.status), //[5A7Bh.02h], Название=status, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.status_prev), //[5A7Bh.03h], Название=status_pre, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.Udc1), //[5A7Bh.04h], Название=Udc_meas, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.P_ref_kW_IQ8), //[5A7Bh.05h], Название=P_BMS_ref, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.Idc2_ref), //[5A7Bh.06h], Название=I_BMS_ref, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.regs.ctrl_word), //[5A7Bh.07h], Название=ctrl_word, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.E_charge_persent), //[5A7Bh.08h], Название=E_charge, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.U2_meas_V_I12Q4), //[5A7Bh.09h], Название=U2_meas, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.I2_meas_A_I12Q4), //[5A7Bh.0Ah], Название=I2_meas, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.P_meas_kW_IQ8), //[5A7Bh.0Bh], Название=P_meas, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.regs.status_word), //[5A7Bh.0Ch], Название=status_word, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.regs.link), //[5A7Bh.0Dh], Название=link, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.operating), //[5A7Bh.0Eh], Название=operating, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&aux_Q6.state), //[5A7Ch.01h], Название=state, ТекстПУ=, EngText=, группа=Q6
(long)(&aux_Q6.aux_on), //[5A7Ch.02h], Название=aux_on, ТекстПУ=, EngText=, группа=Q6
(long)(&aux_Q6.aux_off), //[5A7Ch.03h], Название=aux_off, ТекстПУ=, EngText=, группа=Q6
(long)(&aux_Q6.hold_on), //[5A7Ch.04h], Название=hold_on, ТекстПУ=, EngText=, группа=Q6
(long)(&aux_Q6.hold_off), //[5A7Ch.05h], Название=hold_off, ТекстПУ=, EngText=, группа=Q6
(long)(&aux_Q6.cmd_in), //[5A7Ch.06h], Название=cmd, ТекстПУ=cmd, EngText=cmd, группа=Q6
(long)(&dcdc.abc.time_H_charge), //[5A7Dh.01h], Название=time_H_charge, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.time_H_discharge), //[5A7Dh.02h], Название=time_H_discharge, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.charge_P), //[5A7Dh.03h], Название=charge_P, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.discharge_P), //[5A7Dh.04h], Название=discharge_P, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.P_ref), //[5A7Dh.05h], Название=internal_use_only, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.charge_counter), //[5A7Dh.06h], Название=charge_counter, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.discharge_counter), //[5A7Dh.07h], Название=discharge_counter, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.abc.ena), //[5A7Dh.08h], Название=ena, ТекстПУ=ena, EngText=ena, группа=DCDC_MASTER
(long)(&dcdc.charge_state), //[5A7Dh.09h], Название=state, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.U2_min), //[5A7Dh.0Ah], Название=U_min, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&dcdc.discharge_type), //[5A7Dh.0Bh], Название=discharge_type, ТекстПУ=, EngText=, группа=DCDC_MASTER
(long)(&adc.I_diesel), //[5A7Eh.01h], Название=I_diesel, ТекстПУ=, EngText=, группа=Дизель
(long)(&adc.P_diesel), //[5A7Eh.02h], Название=P_diesel, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.fuel_level), //[5A7Eh.03h], Название=diesel_fuel, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.ready), //[5A7Eh.04h], Название=diesel_ready, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.operating), //[5A7Eh.05h], Название=diesel_operating, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.cmd_in_on), //[5A7Eh.06h], Название=diesel_start, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.cmd_in_off), //[5A7Eh.07h], Название=diesel_stop, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.P_ref), //[5A7Eh.08h], Название=diesel_P_ref, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.ON), //[5A7Eh.09h], Название=diesel_ON, ТекстПУ=, EngText=, группа=Дизель
(long)(&diesel.ena), //[5A7Eh.0Ah], Название=ena, ТекстПУ=ena, EngText=ena, группа=Дизель
(long)(&diesel.state), //[5A7Eh.0Bh], Название=diesel_state, ТекстПУ=, EngText=, группа=Дизель
(long)(&sc_profile.profile), //[5A7Fh.01h], Название=sc_profile, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.status), //[5A7Fh.02h], Название=status, ТекстПУ=status, EngText=status, группа=Профиль
(long)(&sc_profile.profile1_state), //[5A7Fh.03h], Название=profile1_state, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.profile2_state), //[5A7Fh.04h], Название=profile2_state, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.profile3_state), //[5A7Fh.05h], Название=profile3_state, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.profile4_state), //[5A7Fh.06h], Название=profile4_state, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.in.cmd_local_set_profile), //[5A7Fh.07h], Название=cmd_local_set_profile, ТекстПУ=, EngText=, группа=Профиль
(long)(&sc_profile.in.cmd_remote_set_profile), //[5A7Fh.08h], Название=cmd_remote_set_profile, ТекстПУ=, EngText=, группа=Профиль
(long)(&dcs_ctrl.ctrl_mode_synced_P_gen), //[5A7Fh.09h], Название=dcs_ctrl.ctrl_mode_synced_P_gen, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Ah], Название=week, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Bh], Название=Пн, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Ch], Название=Вт, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Dh], Название=Ср, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Eh], Название=Чт, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.0Fh], Название=Пт, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.10h], Название=Сб, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_daily_cicle.week), //[5A7Fh.11h], Название=Вс, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_day_solar_mppt_charge_batt.set.dcdc_P_charge), //[5A80h.01h], Название=dcdc_P_charge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_day_solar_mppt_charge_batt.set.dcdc_I_charge), //[5A80h.02h], Название=dcdc_I_charge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.set.dcdc_P_discharge), //[5A81h.01h], Название=dcdc_P_discharge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.set.dcdc_I_discharge), //[5A81h.02h], Название=dcdc_I_discharge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.counter_diesel), //[5A81h.03h], Название=counter_diesel, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.set.diesel_P_ref), //[5A81h.04h], Название=diesel_P_ref, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.warming_time), //[5A81h.05h], Название=warming_time, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.counter_batt), //[5A81h.06h], Название=counter_batt, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.start_hour), //[5A81h.07h], Название=start_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.start_minute), //[5A81h.08h], Название=start_minute, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.autostart), //[5A81h.09h], Название=autostart, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.fade_hour), //[5A81h.0Ah], Название=fade_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.fade_minute), //[5A81h.0Bh], Название=fade_minute, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.without_batt), //[5A81h.0Ch], Название=without_batt, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.without_diesel), //[5A81h.0Dh], Название=without_diesel, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_evng_batt_diesel.batt_idle_time_min), //[5A81h.0Eh], Название=batt_idle_time_min, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.set.dcdc_P_charge), //[5A82h.01h], Название=dcdc_P_charge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.set.dcdc_I_charge), //[5A82h.02h], Название=dcdc_I_charge, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.start_hour), //[5A82h.03h], Название=start_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.start_minute), //[5A82h.04h], Название=start_minute, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.autostart), //[5A82h.05h], Название=autostart, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.night_to_day_hour), //[5A82h.06h], Название=night_to_day_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.night_to_day_minute), //[5A82h.07h], Название=night_to_day_minute, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_grid_night_batt_charge.jump_time_min), //[5A82h.08h], Название=jump_time_min, ТекстПУ=, EngText=, группа=Профиль
(long)(&vacuum.cmd_in_on), //[5A83h.01h], Название=cmd_in_on, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.cmd_in_off), //[5A83h.02h], Название=cmd_in_off, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.cmd_in_block), //[5A83h.03h], Название=cmd_in_block, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.cmd_out_on), //[5A83h.04h], Название=cmd_out_on, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.cmd_out_off), //[5A83h.05h], Название=cmd_out_off, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.cmd_out_block), //[5A83h.06h], Название=cmd_out_block, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.on), //[5A83h.07h], Название=on, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.off), //[5A83h.08h], Название=off, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.blocked), //[5A83h.09h], Название=blocked, ТекстПУ=, EngText=, группа=vacuum
(long)(&vacuum.state), //[5A83h.0Ah], Название=state, ТекстПУ=state, EngText=state, группа=vacuum
(long)(&sm_isla_batt_diesel.Udc2_high), //[5A84h.01h], Название=Udc2_high, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.Udc2_low), //[5A84h.02h], Название=Udc2_low, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.fade_hour), //[5A84h.03h], Название=fade_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.fade_minute), //[5A84h.04h], Название=fade_minute, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.ena), //[5A84h.05h], Название=ena, ТекстПУ=ena, EngText=ena, группа=Профиль
(long)(&sm_isla_batt_diesel.invs_off), //[5A84h.06h], Название=invs_off, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.autostart), //[5A84h.07h], Название=autostart, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.start_hour), //[5A84h.08h], Название=start_hour, ТекстПУ=, EngText=, группа=Профиль
(long)(&sm_isla_batt_diesel.start_minute), //[5A84h.09h], Название=start_minute, ТекстПУ=, EngText=, группа=Профиль
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
//Таблица групп

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
//Таблица CALLBACK-функций

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

