@ECHO OFF
REM *************************************************************************
REM *                                                                       *
REM * System.....: RSC EZ-SNAP(R)                                           *
REM *                                                                       *
REM * Module.....: BURN.BAT                                                 *
REM *                                                                       *
REM * Description: Burn the Symbol environment into PDT3100 EEPROM.         *
REM *                                                                       *
REM * (c) 1997-1999 Redmer Software Company, Inc.  All rights reserved.     *
REM *                                                                       *
REM *************************************************************************
sendhex EZSNAP.hex 19200 2
