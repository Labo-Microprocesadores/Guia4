/*
 * button.h
 *
 *  Created on: Sep 20, 2020
 *      Author: Carlos
 */

#ifndef BUTTON_H_
#define BUTTON_H_
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define BUTTON_NUM 1
#define TIME_BASE 3

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



	//agregar enum con tipos de boton para configure

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void buttonsInit(void);

bool wasPressed(pin_t button);

bool wasReleased(pin_t button);

bool configureButton(pin_t button, int type);


#endif /* BUTTON_H_ */