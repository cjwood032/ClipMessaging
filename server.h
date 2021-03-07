#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
//short socketCreate(void);
//int bindCreatedSocket (int hsocket);
void * receiveProgramme();
void * serverReceive();
//windows sleeps in ms so we need to sleep longer
#if defined(__WINDOWS__)||defined(_WIN32)||defined(__CYGWIN__)
    #define WINMULTIPLIER 1000
#else
    #define WINMULTIPLIER 1
#endif
#endif