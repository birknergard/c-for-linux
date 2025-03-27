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

	bdebug("Option 1 title: %s", (*pMenuTest->pOptions[0]).pszTitle);

	DestroyMenu(pMenuTest);

	return OK;
}

