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
    char * copyFromClipboard()
    {
        int length=0;
        OpenClipboard(0);
        HGLOBAL hglb;
        hglb =GetClipboardData(CF_TEXT);
        if(hglb!=NULL)
        {
            CloseClipboard();
            return (char*)hglb;
        }
        else
        {
            printf("The clipboard was empty\n");
            CloseClipboard();
            return 0;
        }
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
    char * copyFromClipboard(char * output)
    {
        //This uses a temporary file to get the value of the clipboard.
        //Once a better solution is found it will be implemented.
        char c;
        int inputSize=0;
        FILE *fpoint = NULL;
        freopen("tempfile.txt","w+",stdout);
        const char issued_cmd[] ="pbpaste";
        char cmd[strlen(issued_cmd)-1];
        sprintf(cmd,issued_cmd);
        system(cmd);
        freopen("/dev/tty","w",stdout);
        fpoint=fopen("tempfile.txt","r");
        fseek(fpoint,0,SEEK_END);
        inputSize = ftell(fpoint);
        char buffer[inputSize];
        rewind(fpoint);
        fread(output,sizeof(char),inputSize,fpoint);
        fclose(fpoint);
        remove("tempfile.txt");
        //output = buffer;
        printf("%s\n",output);
        return output;
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
/*
int main()
{
    char * output;
    output = copyFromClipboard(output);
    printf("output from main \n%s\n",output);
    //copyToClipboard("This is only a test,\ndo not adjust your television set");
    //copyFromClipboard("Worked ");
    //free(output);
    return 0;
}
*/