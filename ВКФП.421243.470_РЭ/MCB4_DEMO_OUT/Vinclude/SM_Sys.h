/*!
     Copyright 2023 ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      SMSys.h
 \brief     ������-������� ��� ������� ��������� �������. (��. TSM_Sys)
 \author    ��� "��� ������". http://motorcontrol.ru

 \defgroup  SMSys ������-������� ��� ������� ��������� �������. (��. TSM_Sys)
 @{
*/

#ifndef SM_Sys_H
#define SM_Sys_H

#ifdef __cplusplus
extern "C"
{
#endif
  
  //! ������� � �������������
  #define SYS_INIT 		0
  //! ������� �������������������
  #define SYS_READY 		1


/*! \class TSM_Sys
      \brief ������-������� ��� ������� ��������� �������.

      ����� \a TSM_Sys, ���������� �� ��������� SSMSys, �������� �������,
      ������ ������� �������� ���������� ����� ����������� ���������. ��������,
      ������� �������� ������� ������� ������ �������� ������� �������� �������
      ��������� �������. ����� ����, � ������������� ������� ������ ������������� ����������
      �����������.
       */

//! ��. TSM_Sys
  struct SSM_Sys
  {
      Uint32 GIT_VersionShortHash;
      Uint32 GIT_CommitTimestamp;
      Uint32 GIT_UncommitedFiles;
      Uint16 SiliconRevision;
      Uint16 ConverterHardwareRevision;

    int state;//!< ���������
    int state_prev;//!< ��������� ����������
    int E;//!<���� ������� ���������
    int IntEna;
    void (*init)(struct SSM_Sys*);     /* Pointer to the init funcion           */
    void (*slow_calc)(struct SSM_Sys*);     /* Pointer to the calc funtion           */
    void (*fast_calc)(struct SSM_Sys*);     /* Pointer to the calc funtion           */
    void (*ms_calc)(struct SSM_Sys*);     /* Pointer to the calc funtion           */
  } ;

  typedef struct SSM_Sys TSM_Sys;
  
//!������������� �� ���������
#define SM_Sys_DEFAULTS {\
    .init = SM_Sys_Init,\
    .slow_calc = SM_Sys_Slow_Calc,\
    .fast_calc = SM_Sys_Fast_Calc,\
    .ms_calc = SM_Sys_ms_Calc,\
  }

  //! \memberof TSM_Sys
  void SM_Sys_Init(TSM_Sys*);
  //! \memberof TSM_Sys
  void SM_Sys_Slow_Calc(TSM_Sys*);
  //! \memberof TSM_Sys
  void SM_Sys_Fast_Calc(TSM_Sys*);
  //! \memberof TSM_Sys
  void SM_Sys_ms_Calc(TSM_Sys*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/




