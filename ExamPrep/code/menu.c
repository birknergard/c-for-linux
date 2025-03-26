#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "debug.h"
#include "menu.h"

OPTION *CreateOption(char *szTitle, void (*funcAction)()){
	OPTION *pNewOption = NULL;
	pNewOption = (OPTION *) malloc(sizeof(OPTION));
	if(pNewOption == NULL){
		berror("Malloc failed for newOption *.");
		return NULL;	
	}

	pNewOption->pszTitle = (char *) malloc(TITLE_BUFFER);
	if(pNewOption->pszTitle == NULL){
		berror("Malloc failed for newOptions->pszTitle.");
	}

	pNewOption->funcAction = funcAction;

	return pNewOption;
}

MENU *CreateMenu(int iOptionCount){
	MENU *pNewMenu = NULL;	

	pNewMenu = (MENU *) malloc(sizeof(MENU));
	if(pNewMenu == NULL){
		berror("Malloc fo pNewMenu failed.");
		return NULL;
	}

	pNewMenu->pOptions = (OPTION *) malloc(sizeof(OPTION) * iOptionCount);
	if(pNewMenu->pOptions == NULL){
		berror("Malloc to pNewMenu->pOptions failed");	
		return NULL;
	}

	pNewMenu->iOptionCount = iOptionCount;

	return pNewMenu;
}

int DestroyMenu(MENU **ppMenu){
	int i;
	OPTION *pCurrOption = NULL;
	for(i = 0; i < *ppMenu->iOptionCount; i++){
		pCurrOption = (*ppMenu)->pOptions[i];
		/*
		(*ppMenu)->pOptions[i]->funcAction = NULL;

		free(pCurrOption->pszTitle);
		(*ppMenu)->pOptions[i]->pszTitle = NULL;

		free(*ppMenu->pOptions[i]);
		*ppMenu->pOptions[i] = NULL;
		*/
	}

	free(*ppMenu);

	/* Removing dangling pointers */
	*ppMenu == NULL;

	return 0;
}

int StartMenu(MENU* pMenu){
	
}

int DisplayOptions(MENU *pMenu);
int SelectAction(MENU *pMenu, char cSelection);
int DestroyMenu(MENU **pMenu);
int Exit(MENU* pMenu);

void hello(){
	printf("Hello world\n");
	return;
}

int main(void){
	OPTION *pOptionTest = NULL;
	MENU *pMenuTest = NULL;

	pOptionTest = CreateOption("Hello", &hello);
	pMenuTest = CreateMenu(2);

	DestroyMenu(&pMenuTest);

	/*pOptionTest->funcAction();*/

	return OK;
}



