@echo off
REM %1 first param
echo ==========command
echo ping
echo ==========
REM 변수 지역화
setlocal

:message
REM 메시지를 화면에 출력한 후 사용자 입력을 %in%에 저장
REM /p 옵션: varible=message message를 화면에 출력하고 
REM 사용자 입력을 %in%에 저장
set /p in=What would you wanna see:__


if [%in%]==[] goto message
type %in%.txt
echo. 

REM REM %in%가 N면 변수 지역화를 해제하고 end로 점프
REM REM /i 옵션: 대소문자 무시
REM if /i [%in%]==[N] endlocal & goto end

REM REM 입력이 Y 또는 y면 install로 점프
REM if /i [%in%]==[Y] goto install
REM goto end

REM :install
REM REM 사용자 입력이 Y 또는 y인 경우 실행되는 명령어 집합
REM echo 당신은 %in%를 선택했습니다.


endlocal
:end