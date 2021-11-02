/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "stm32f4xx.h"

// ----------------------------------------------------------------------------
//
// STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
void SysTick_Handler(void)
{
    HAL_IncTick();
}



// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

//Funcion que parpadea cada 100ms el led Rojo
void parpadearLed(){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 , GPIO_PIN_SET);//Led rojo encendido
	HAL_Delay(100); //Delay 100ms
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 , GPIO_PIN_RESET); //Led rojo apagado
	HAL_Delay(100); //Delay 100ms
}
int
main(int argc, char* argv[])
{
	GPIO_InitTypeDef GPIOD_Params;

	__HAL_RCC_GPIOD_CLK_ENABLE(); //Activo reloj GIPOD  Leds

	__HAL_RCC_GPIOA_CLK_ENABLE(); //Activo reloj GIPOA  Pulsador

	GPIOD_Params.Pin = GPIO_PIN_14 | GPIO_PIN_15;
	GPIOD_Params.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOD_Params.Speed = GPIO_SPEED_LOW;
	GPIOD_Params.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIOD_Params);


	GPIOD_Params.Pin = GPIO_PIN_0;
	GPIOD_Params.Mode = GPIO_MODE_INPUT;
	GPIOD_Params.Speed = GPIO_SPEED_HIGH;
	GPIOD_Params.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIOD_Params);

	HAL_Init();
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	HAL_IncTick();
	HAL_GetTick();



  while (1){

	  parpadearLed();

	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)== ENABLE){
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 , GPIO_PIN_SET);
	  }else{
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 , GPIO_PIN_RESET);
	  }
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
