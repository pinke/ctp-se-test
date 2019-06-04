@echo off
@chcp 936
@rem vc6
mkdir tmp
del tmp/*.*
set path=%PATH%;D:\pinke\soft\vc6\VC98\Bin\;lib
call "D:\pinke\soft\vc6\VC98\Bin\VCVARS32-2.BAT"

@rem vs2013
@rem set path=%PATH%;g:\installed\vs213\VC\bin\Bin\;lib
@rem call g:\installed\vs213\VC\bin\vcvars32.bat x86

set path=%PATH%;%~dp0api\trade\win\lib
cl  test.cpp order\*.cpp /EHsc  "%~dp0api\trade\win\lib\*_se.lib"
del *.obj
pause
test
pause
