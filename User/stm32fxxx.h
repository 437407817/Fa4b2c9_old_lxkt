/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.h 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    06-March-2015
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32Fxxx_H
#define __STM32Fxxx_H



#include <stdio.h>
#include <stdlib.h>

#include "stm32f4xx.h"

#define STR_PARAM(param) #param



#define EMBED_FIRE_INTERFACE 0

#if (EMBED_FIRE_INTERFACE==1)

#else

#endif


//#define STM32F10X
#define STM32F4XX





#endif /* __STM32Fxxx_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
