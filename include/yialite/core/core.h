#ifndef CORE_H
#define CORE_H

#ifdef _WIN32
    #ifdef YIALITE_EXPORTS
        #define YIALITE_API __declspec(dllexport)
    #else
        #define YIALITE_API __declspec(dllimport)
    #endif
#endif

#endif