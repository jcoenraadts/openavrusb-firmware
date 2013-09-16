C:\WinAVR-20100110\bin\avrdude.exe  -pusb162 -cavrisp2 -PCOM3 -F -u -Uflash:w:USB_demo.hex:a -Ulfuse:w:0xae:m -Uhfuse:w:0xdf:m -Uefuse:w:0xfc:m

@ECHO %ERRORLEVEL%

@if ERRORLEVEL 0 GOTO NEXT

pause

:NEXT
C:\WinAVR-20100110\bin\avrdude.exe -F -pusb162 -cavrisp2 -PCOM3 -Ulock:w:0xf0:m

@if ERRORLEVEL 0 GOTO EXIT
pause

:EXIT