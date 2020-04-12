@echo off

cd %~dp0

set keyboard=jorne_ble
set keymap=default
set role=master

if "%1"=="slave" set role=slave

echo building %role%

set file=%keyboard%_%role%_%keymap%.hex

bash -c "cd ../../ && export NRFSDK15_ROOT=/mnt/c/SDK/nRF5_SDK_15.0.0_a53641a && make %keyboard%/%role%:%keymap%" || exit

cd ..\..\.build

%~dp0/uf2conv.py %file% -c -f 0xADA52840

copy /Y flash.uf2 %~dp0\precompiled\%role%.uf2

echo dfu| plink.exe -serial com9

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist e:\ goto :loop

timeout 1

copy flash.uf2 e:\

