REM echo "In batch file: %1"

REM LOOK FOR Q_OBJECT IN THE SOURCE FILE
for /f "usebackq" %%a in (`grep "Q_OBJECT" %1 ^| wc -l`) do @set ret=%%a

REM echo "Retval: %ret%"

REM IF THE SOURCE FILE CONTAINS Q_OBJECT, WE NEED TO RUN IT THROUGH MOC
if not %ret% == 0 echo %1 >> %2
