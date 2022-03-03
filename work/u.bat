@echo off
if [%1]==[] goto :show
@echo on
copy src\dev\%1 examples\gimmick\dev\%1 /y
copy src\dev\%1 examples\hobbit_v2\dev\%1 /y
copy src\dev\%1 examples\journey\dev\%1 /y
copy src\dev\%1 examples\ninjajar_v2\dev\%1 /y
@echo off
goto :end
:show
echo u.bat file_with_path_from_src_dev
echo don't use if you don't know what this is
:end 
