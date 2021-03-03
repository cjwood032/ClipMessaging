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
    void copyToClipboard(const char *str)
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
    void copyFromClipboard(char *head)
    {
        //This uses a temporary file to get the value of the clipboard.
        //Once a better solution is found it will be implemented.
        char c;
        int inputSize=0;
        int headerLength = 0;
        char *output = NULL;
        char buffer[100];
        FILE *fpoint = NULL;
        freopen("tempfile.txt","w+",stdout);
        const char issued_cmd[] ="pbpaste";
        char cmd[strlen(head)+strlen(issued_cmd)-1];
        headerLength = strlen(head);
        sprintf(cmd,issued_cmd);
        system(cmd);
        freopen("/dev/tty","w",stdout);
        fpoint=fopen("tempfile.txt","r");
        fseek(fpoint,0,SEEK_END);
        inputSize = ftell(fpoint);
         output = (char *)malloc((headerLength+inputSize)*sizeof(char));
        rewind(fpoint);
        fread(buffer,sizeof(char),inputSize,fpoint);
        strcpy(output,head);
        strcat(output,buffer);
        printf("\nthe final output\n%s\n",output);
        fclose(fpoint);
        free(output);
        remove("tempfile.txt");
    }
    void copyToClipboard(const char *str)
    {
        const char issued_cmd[] ="echo '%s' | pbcopy";
        char cmd[strlen(str)+strlen(issued_cmd)-1];
        sprintf(cmd,issued_cmd,str);
        system(cmd);
    }
    //we can't run this outside of MACOS
#endif 
int main()
{
    copyFromClipboard("Worked ");
    copyToClipboard("This is only a test,\ndo not adjust your television set");
    copyFromClipboard("Worked ");
    return 0;
}
