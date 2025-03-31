#include <stdio.h>

#include "debug.h"
#include "menu.h"

void hello(){
	printf("Hello worldy\n");
	return;
}

void test(){
	printf("This is a test\n");
	return;
}

int main(void){
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
	/*bdebug("Option 2 title: %s. Testing function ...", pOptionTest->pszTitle);*/
	pOptionTest->funcAction();

	StartMenu(pMenuTest, "TestProgram");

	pOptionTest = NULL;
	pMenuTest = NULL;

	return OK;
}

