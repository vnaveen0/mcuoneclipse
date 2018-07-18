/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CS1.h
**     Project     : S32K144_FreeRTOS_PEx
**     Processor   : S32K144_100
**     Component   : CriticalSection
**     Version     : Component 01.013, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-06-30, 20:21, # CodeGen: 15
**     Abstract    :
**
**     Settings    :
**          Component name                                 : CS1
**          SDK                                            : MCUC1
**          Use Processor Expert Default                   : no
**          Use FreeRTOS                                   : no
**     Contents    :
**         CriticalVariable - void CS1_CriticalVariable(void);
**         EnterCritical    - void CS1_EnterCritical(void);
**         ExitCritical     - void CS1_ExitCritical(void);
**         Deinit           - void CS1_Deinit(void);
**         Init             - void CS1_Init(void);
**
** * Copyright (c) 2014-2018, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file CS1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup CS1_module CS1 module documentation
**  @{
*/         

#ifndef __CS1_H
#define __CS1_H

/* MODULE CS1. */
#include "MCUC1.h" /* SDK and API used */
#include "CS1config.h" /* configuration */


/* other includes needed */
#if CS1_CONFIG_USE_RTOS_CRITICAL_SECTION
  #include "FreeRTOS.h"
  #include "task.h"  /* FreeRTOS header file for taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros */
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* workaround macros for wrong EnterCritical()/ExitCritical() in the low level drivers. */
#define CS1_CriticalVariableDrv() \
  CS1_CriticalVariable()
#define CS1_EnterCriticalDrv() \
  CS1_EnterCritical()
#define CS1_ExitCriticalDrv() \
  CS1_ExitCritical()

#ifdef __HIWARE__
  #pragma MESSAGE DISABLE C3303 /* C3303 Implicit concatenation of strings */
#endif

#if CS1_CONFIG_USE_PEX_DEFAULT
  #define CS1_CriticalVariable() /* nothing needed */
#elif CS1_CONFIG_USE_RTOS_CRITICAL_SECTION
  #define CS1_CriticalVariable() /* nothing needed */
#elif CS1_CONFIG_USE_CUSTOM_CRITICAL_SECTION
  #define CS1_CriticalVariable() uint8_t cpuSR; /* variable to store current status */
#endif
/*
** ===================================================================
**     Method      :  CriticalVariable (component CriticalSection)
**
**     Description :
**         Defines a variable if necessary. This is a macro.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#if CS1_CONFIG_USE_PEX_DEFAULT
  #define CS1_EnterCritical()   EnterCritical()
#elif CS1_CONFIG_USE_RTOS_CRITICAL_SECTION
  #define CS1_EnterCritical()   taskENTER_CRITICAL_FROM_ISR() /* FreeRTOS critical section inside interrupt */
#elif CS1_CONFIG_USE_CUSTOM_CRITICAL_SECTION
  #define CS1_EnterCritical() \
    do {                                  \
      /*lint -save  -esym(529,cpuSR) Symbol 'cpuSR' not subsequently referenced. */\
      __asm (                             \
      "mrs   r0, PRIMASK     \n\t"        \
      "cpsid i               \n\t"        \
      "strb r0, %[output]   \n\t"         \
      : [output] "=m" (cpuSR) :: "r0");   \
      __asm ("" ::: "memory");            \
      /*lint -restore Symbol 'cpuSR' not subsequently referenced. */\
    } while(0)
#endif
/*
** ===================================================================
**     Method      :  EnterCritical (component CriticalSection)
**
**     Description :
**         Enters a critical section
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#if CS1_CONFIG_USE_PEX_DEFAULT
  #define CS1_ExitCritical()   ExitCritical()
#elif CS1_CONFIG_USE_RTOS_CRITICAL_SECTION
  #define CS1_ExitCritical()   taskEXIT_CRITICAL_FROM_ISR(0) /* FreeRTOS critical section inside interrupt */
#elif CS1_CONFIG_USE_CUSTOM_CRITICAL_SECTION
  #define CS1_ExitCritical() \
   do{                                  \
     __asm (                            \
     "ldrb r0, %[input]    \n\t"        \
     "msr PRIMASK,r0        \n\t"       \
     ::[input] "m" (cpuSR) : "r0");     \
   } while(0)
#endif
/*
** ===================================================================
**     Method      :  ExitCritical (component CriticalSection)
**
**     Description :
**         Exits a critical section
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CS1_Deinit(void);
/*
** ===================================================================
**     Method      :  Deinit (component CriticalSection)
**
**     Description :
**         Driver de-initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CS1_Init(void);
/*
** ===================================================================
**     Method      :  Init (component CriticalSection)
**
**     Description :
**         driver initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END CS1. */

#ifdef __cplusplus
}
#endif

#endif
/* ifndef __CS1_H */
/*!
** @}
*/
