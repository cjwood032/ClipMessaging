#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__WINDOWS__)||defined(_WIN32)||defined(__CYGWIN__)
    #include <Windows.h>
    #include <winuser.h>
    //Copy this I guess?
    /*
    here is a
    multiline example
    to test
    */
    void copyFromClipboard(char *head)
    {
        char *output=NULL;
        int length=0;
        
        OpenClipboard(0);
        HGLOBAL hglb;
        hglb =GetClipboardData(CF_TEXT);
        if(hglb!=NULL)
        {
            length=strlen((char*)hglb)+strlen(head);
            output = (char *)malloc(length * sizeof(char));
            strcpy(output,head);
            strcat(output,(char*)hglb);
        }
        else
        {
            printf("The clipboard was empty\n");
        }
        printf("the final output\n%s\n",output);
        CloseClipboard();
        free(output);
    }
    int copyToClipboard(const char *str)
    {
        const size_t len = strlen(str) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), str, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }
//we can't run this outside of windows...
#elif defined(__APPLE__)

    int copyToClipboard(const char *str)
    {
        const char issued_cmd[] ="echo '%s' | pbcopy";
        char cmd[strlen(str)+strlen(issued_cmd)-1];
        sprintf(cmd,issued_cmd,str);
        return system(cmd);
    }
#endif //we can't run this outside of MACOS
int main()
{
    copyFromClipboard("Worked ");
    copyToClipboard("This is only a test,\ndo not adjust your television set");
    copyFromClipboard("Worked ");
    return 0;
}
