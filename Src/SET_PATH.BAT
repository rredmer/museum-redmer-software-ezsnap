REM *************************************************************************
REM *                                                                       *
REM * System.....: RSC Symbol PDT3100 Application                           *
REM *                                                                       *
REM * Module.....: SET_PATH.BAT                                             *
REM *                                                                       *
REM * Description: Set the Windows Environment variables for compiler.      *
REM *                                                                       *
REM * (c) 1997-1999 Redmer Software Company.  All rights reserved.          *
REM *                                                                       *
REM *************************************************************************
ECHO OFF
CLS
ECHO "Setting Paths..."
SET PATH=S:\MDF250;S:\MVC200\BIN;S:\PDT3000;S:\PDT3000\MSGS;S:\PDT3000\FILES;%PATH%
SET INCLUDE=S:\PDT3000;S:\pdt3000\adl\include;S:\MVC200\INCLUDE
SET LIB=S:\PDT3000\LIB;S:\PDT3000\ADL\LIB;S:\MVC200\LIB
SET DPATH=S:\PDT3000\MSGS
SET EXE3000=S:\PDT3000
SET FILES3000=S:\PDT3000\FILES
SET CLIB=S:\MVC200\LIB
SET HELPFILES=S:\MVC200\HELP\*.HLP
SET 3000INC=S:\PDT3000\3000
SET 3000H=S:\PDT3000\3000
SET LIB3000=S:\PDT3000\LIB
ECHO ON
