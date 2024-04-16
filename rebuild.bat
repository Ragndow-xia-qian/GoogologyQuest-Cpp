@echo off

rem 设置路径前缀
SET dir="D:\Code\cpp\Qt5 Projects\Game_GoogologyQuest"

rem 如果存在就删掉 releases，以达到重新构建的目的
if exist %dir%\releases rd %dir%\releases /s /q

rem 创建新的 releases 和 log 文件夹
cd %dir%
mkdir releases
cd releases
mkdir log

rem 复制可执行文件
copy %dir%\bin\Release\GoogologyQuest.exe %dir%\releases /y

rem 复制 Resources 文件夹
xcopy %dir%\bin\Release\Resources %dir%\releases\Resources /s /e /i /y

rem 调用 windeployqt 构建
%QT_TOOLCHAIN%/bin/windeployqt %dir%\releases\GoogologyQuest.exe
