#ifndef _MENU_H_
#define _MENU_H_

#define ERROR 1; 
#define OK 0;

#define TITLE_BUFFER 256
#define MAX_BUFFER 1028

typedef struct _OPTION {
	char *pszTitle;
	void (*funcAction)();
} OPTION;

typedef struct _MENU {
	OPTION *pOptions;
	int iOptionCount;

} MENU;


int StartMenu(MENU* pMenu);
int DisplayOptions(MENU *pMenu);
int SelectAction(MENU *pMenu, char cSelection);
int DestroyMenu(MENU **pMenu);
int Exit(MENU* pMenu);


#endif /*ndef _MENU_H_ */
