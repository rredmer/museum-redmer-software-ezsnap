@ECHO OFF
REM *************************************************************************
REM *                                                                       *
REM * System.....: RSC EZ-SNAP(R)                                           *
REM *                                                                       *
REM * Module.....: BUILD.BAT                                                *
REM *                                                                       *
REM * Description: Build the EZ-SNAP executable using Microsoft NMAKE.      *
REM *                                                                       *
REM * (c) 1997-1999 Redmer Software Company.  All rights reserved.          *
REM *                                                                       *
REM *************************************************************************
nmake ezsnap.dos > build.txt
copy ezsnap.exe nvm
erase *.obj
erase *.map
edit build.txt
erase build.txt
