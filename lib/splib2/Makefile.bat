@echo off
call setenv.bat
if [%1]==[install] goto install

cd cwrapper
copy ..\SPconfig.def .
gencompile "zcc +zx -vn -make-lib -I.." sp_c.lst
del SPconfig.def
cd ..

z80asm -I. -d -ns -nm -Mo -DFORzx -xsplib2_mk2 @sp.lst

:install
echo Copying
copy splib2_mk2.lib %Z88DK_PATH%\lib\clibs
copy spritepack.h %Z88DK_PATH%\include\

echo done!
pause
