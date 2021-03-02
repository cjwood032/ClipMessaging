#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <winuser.h>
//Copy this I guess?
int main()
{
    char output[20]="did not work";

    OpenClipboard(0);
    HGLOBAL hglb;
    hglb =GetClipboardData(CF_TEXT);
    if(hglb!=NULL)
    {
        strcpy(output,(char*)hglb);
    }
    else
    {
        printf("The clipboard was empty\n");
    }
    printf("%s",output);
    CloseClipboard();
    return 0;
}