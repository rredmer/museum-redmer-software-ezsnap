@ECHO OFF
REM *************************************************************************
REM *                                                                       *
REM * System.....: RSC EZSNAP(R) PDT3100 Application                        *
REM *                                                                       *
REM * Module.....: BURN.BAT                                                 *
REM *                                                                       *
REM * Description: Burn the EZSNAP(R) environment into PDT3100 EEPROM.      *
REM *                                                                       *
REM * (c) 1996-1998 Redmer Software Company, Inc.  All rights reserved.     *
REM *                                                                       *
REM *************************************************************************
SENDHEX EZSNAP.HEX 19200 2
