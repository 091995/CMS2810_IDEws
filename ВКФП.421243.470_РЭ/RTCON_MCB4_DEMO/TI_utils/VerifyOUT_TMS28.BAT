@echo off

echo ---------------------------------------------------------------------------------
echo Path to .bat: %~dp0
echo 1 = %~1 
echo 2 = %~2 

set PathToBAT=%~dp0
set PathToApp=%~1
set ParamsToApp=%~2

@rem ������� ����� ������ ���������� � ����
"%PathToApp%" %ParamsToApp% 2> "%PathToBAT%VerifyResult.tmp"  

echo ---------------------------------------------------------------------------------

@rem pause
