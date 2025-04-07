#include <stdio.h>

#include "debug.h"
#include "doubl_list.h"
#include "menu.h"

int main(int iArgC, char **apszArgV){
	/* For testing menu 
	OPTION *pOptionTest = NULL;
	MENU *pMenuTest = NULL;

	pMenuTest = CreateMenu();

	AddOption(pMenuTest, "HelloWorld", &hello);

	pOptionTest = pMenuTest->pOptions[0];
	bdebug("Option 1 title: %s. Testing function ...", pOptionTest->pszTitle);
	pOptionTest->funcAction();

	pOptionTest = NULL;
	
	AddOption(pMenuTest, "This is a test of second option", &test);

	pOptionTest = pMenuTest->pOptions[1];
	pOptionTest->funcAction();

	StartMenu(pMenuTest, "TestProgram");

	pOptionTest = NULL;
	pMenuTest = NULL;
	*/

	/* For testing linked list */

	LIST list = *CreateList();

}

