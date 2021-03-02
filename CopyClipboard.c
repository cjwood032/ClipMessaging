#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <winuser.h>
//Copy this I guess?
/*
here is a
multiline example
to test
*/
int main()
{
    char output[20]="did not work ";

    OpenClipboard(0);
    HGLOBAL hglb;
    hglb =GetClipboardData(CF_TEXT);
    if(hglb!=NULL)
    {
        //printf("the copied data\n%s\n",(char*)hglb);
        strcat(output,(char*)hglb);
    }
    else
    {
        printf("The clipboard was empty\n");
    }
    printf("the final output\n%s\n",output);
    CloseClipboard();
    return 0;
}
