#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <stdarg.h>

#include "debug.h"
#include "menu.h"

OPTION *CreateOption(char szTitle[], void (*funcAction)()){
	OPTION *pNewOption = NULL;
	int iTitleLength = strlen(szTitle);

	pNewOption = (OPTION *) malloc(sizeof(OPTION));
	if(pNewOption == NULL){
		berror("Malloc failed for newOption *.");
		return NULL;	
	}

	pNewOption->pszTitle = (char *) malloc(TITLE_BUFFER);
	if(pNewOption->pszTitle == NULL){
		berror("Malloc failed for newOptions->pszTitle.");
	}
	if(iTitleLength >= TITLE_BUFFER){
		strncpy(pNewOption->pszTitle, szTitle, TITLE_BUFFER);
	} else {
		strncpy(pNewOption->pszTitle, szTitle, iTitleLength);
	}

	pNewOption->funcAction = funcAction;

	bdebug("Created new option *:\n Size: %d\n Title: %s\n funcPtr: %p\n",
	   	sizeof(*pNewOption), pNewOption->pszTitle, pNewOption->funcAction);

	return pNewOption;
}

MENU *CreateMenu(){
	MENU *pNewMenu = NULL;	

	pNewMenu = (MENU *) malloc(sizeof(MENU));
	if(pNewMenu == NULL){
		berror("Malloc to pNewMenu failed.");
		return NULL;
	}
	pNewMenu->pOptions = NULL;
	pNewMenu->iOptionCount = 0;

	return pNewMenu;
}

int AddOption(MENU *pMenu, char szTitle[], void (*funcAction)()){
	OPTION *pNewOption = NULL;
	OPTION **ppExtendedOptions = NULL;
	OPTION **ppNewOptionAddress = NULL;
	int *piOptionCount = NULL; 

	pNewOption = CreateOption(szTitle, funcAction);
	piOptionCount = &(pMenu->iOptionCount);

	/* If MENU is empty */
	if(piOptionCount == 0){
		pMenu->pOptions = (OPTION **)malloc(sizeof(OPTION *));
		memcpy(pMenu->pOptions, pNewOption, sizeof(OPTION*));
		(*piOptionCount)++;

	/* If menu contains previous elements */
	} else {
		/* Creating extended pointer */
		ppExtendedOptions = (OPTION **) malloc(sizeof(OPTION *) * ((*piOptionCount) + 1));

		/* Copying old data to new ptr */
		bdebug("Copying old data to new ptr\n");
		memcpy(ppExtendedOptions, pMenu->pOptions, sizeof(OPTION *) * (*piOptionCount));

		/* Incrementing pointer to start at open segment */
		ppNewOptionAddress = ppExtendedOptions + (sizeof(OPTION *) * (*piOptionCount));

		/* Inserting new data to new ptr */
		memcpy(ppNewOptionAddress, pNewOption, sizeof(OPTION *));

		/* Incrementing optioncount value */
		++piOptionCount;

		/* Deleting old data */
		free(pMenu->pOptions);

		/* Reassigning main ptr to new data */
		pMenu->pOptions = ppExtendedOptions;

		ppNewOptionAddress = NULL;
		ppExtendedOptions = NULL;
	}

	/* Handling dangling ptrs */
	piOptionCount = NULL;

	return OK;
}

int DestroyMenu(MENU *pMenu){
	int i;
	OPTION *pCurrOption = NULL;

	if(pMenu->iOptionCount > 0){
		for(i = 0; i < pMenu->iOptionCount; i++){
			pCurrOption = pMenu->pOptions[i]; 

			pCurrOption->funcAction = NULL;

			free(pCurrOption->pszTitle);
			pCurrOption->pszTitle = NULL;

			free(pCurrOption);

			pCurrOption = NULL;
		}
	}

	free(pMenu->pOptions);
	free(pMenu);

	/* Removing dangling pointers */
	pMenu = NULL;

	return 0;
}

/* TODO:
 */ 

int ExecuteAction(MENU pMenu, char cSelection);

int DisplayOptions(MENU pMenu){

}

int Exit(MENU *pMenu);

int StartMenu(MENU pMenu);
