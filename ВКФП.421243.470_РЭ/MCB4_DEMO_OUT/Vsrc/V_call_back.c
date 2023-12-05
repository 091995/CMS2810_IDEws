/*!
 \file      v_call_back.c
 \brief     ‘айл функций, вызываемых драйвером CANOpen

 ƒрайвер CANOpen умеет вызывать заданную пользователем функцию
 при обращению к заданному индексу. Ёта функция не должна быть привязана к какому-либо модулю.
 в этом файле собраны все такие функции

 \author	Drozdov Andrey V
 \version   v 1.1 27/02/2010
 */

/** \addtogroup v_call_back */
/*@{*/

#include "DSP28_Device.h"
#include "IQmathLib.h"
#include "main.h"

//!ќбращение к часам реального времени.

//!≈сли происходит запись, то устанавливается запрос на коррекцию часов.
void callback_RTC(unsigned int par) {

}

//!ќбращение к переменной next_value_var с данными цифрового осциллографа.

//!—уществует специальный интерфейс, позволяющий автоматизировать считывание оссциллографируемых переменных
//!модуля TDataLog. Ёта функция вызывается при обращении к переменной, через которую возможно считать записанные
//!осциллограммы. «апись в эту переменную устанавливает требуемый номер буфера (один и 4х) и номер извлекаемой точки.
//!ѕри чтении же в эту переменную выдвигатются сами отосциллограффированные данные.
#ifdef __cplusplus
#pragma CODE_SECTION("secureRamFuncs")
#else
#pragma CODE_SECTION(callback_dlog,"secureRamFuncs");
#endif
void callback_dlog(Uint16 par)
{
    // ≈сли произошла запись в переменную, то установим буфер на нужную точку.
    if (par == 1)
    {
        //  ¬ переменную next_value_var записываетс€ желаемое смещение, номер буфера, из которого хотим читать,
        // а также разреживание (делитель)
        int n_old = (int)((dlog.next_value_var >> 24) & 3);     // извлекаетс€ номер буфера ("старый" 4-канальный ёникон)
        int n_new = (int)((dlog.next_value_var >> 28) & 0xF);   // извлекаетс€ номер буфера ("новый" N-канальный ёникон)
        dlog.buff_num = n_new != 0 ? n_new : n_old;
        dlog.highPartOfValue = (int)((dlog.next_value_var >> 26) & 1); // отдавать старшую часть 32-битного значени€?
        dlog.Rcounter = (dlog.next_value_var >> 16) & 0xFF; // какую точку надо отдавать
        // ѕровер€ем хот€т ли использовать блочную передачу
        if ((dlog.next_value_var & 0xffff) == 1)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG1;
        }
        if ((dlog.next_value_var & 0xffff) == 2)
        {
            if (dlog.pco_vars->co_blockTransferCommand == CANBT_INTERFACE_FREE)
                dlog.pco_vars->co_blockTransferCommand = CANBT_INTERFACE_DATALOG2;
        }
    }

    //выдвигаем данные:
    int32 val32 = dlog.buff[(dlog.buff_num << 8) + ((dlog.Rcounter + dlog.first_point_written) & 0xFF)];
    int varSizeIs16 = (int)(dlog.objectInfo[dlog.buff_num].varSize == 16);
    dlog.next_value_var = (dlog.highPartOfValue != 0 ? val32 >> 16 : val32) & 0x0000FFFF;
    dlog.next_value_var |= ((Uint32)dlog.Rcounter) << 16;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 3)) << 24;
    dlog.next_value_var |= ((Uint32)dlog.highPartOfValue) << 26;
    dlog.next_value_var |= ((Uint32)varSizeIs16) << 27;
    dlog.next_value_var |= ((Uint32)(dlog.buff_num & 0xF)) << 28;

    if ((dlog.highPartOfValue != 0) || varSizeIs16)
    {
        // ѕри следующем запросе отдадим младшую часть следующей точки.
        dlog.Rcounter++;
        dlog.Rcounter &= 0xFF;
        dlog.highPartOfValue = 0;
    }
    else
    {
        // ѕри следующем запросе отдадим старшую часть этой же точки.
        dlog.highPartOfValue = 1;
    }
}



/*@}*/

