#ifndef CORE_H
#define CORE_H

#ifdef _WIN32
    #ifdef LITE_EXPORTS
        #define LITE_API __declspec(dllexport)
    #else
        #define LITE_API __declspec(dllimport)
    #endif
#endif

#endif