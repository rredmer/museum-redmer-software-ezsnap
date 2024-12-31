mode COM1: BAUD=19 PARITY=N DATA=8 STOP=1
pause
dtron
pause
TFT3000 -S38 -p1 -X p %1
mode COM1: 
