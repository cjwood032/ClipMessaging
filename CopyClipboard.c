#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN64)||defined(_WIN32)
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
#endif //we can't run this outside of windows...
#if defined(__APPLE__)
int copyToClipboard(const char *str);
int main()
{
    copyToClipboard("Let us see if this works!");
    return 0;
}
int copyToClipboard(const char *str)
{
    const char issued_cmd[] ="echo '%s' | pbcopy";
    char cmd[strlen(str)+strlen(issued_cmd)-1];
    sprintf(cmd,issued_cmd,str);
    return system(cmd);
}
#endif //we can't run this outside of MACOS