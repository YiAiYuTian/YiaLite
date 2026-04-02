#ifndef YIALITE_CORE_H
#define YIALITE_CORE_H

#include <cassert>

#ifdef _WIN32
    #ifdef YIALITE_STATIC
        #define YIALITE_API
    #else
        #ifdef YIALITE_EXPORTS
            #define YIALITE_API __declspec(dllexport)
        #else
            #define YIALITE_API __declspec(dllimport)
        #endif
    #endif
#endif

#ifdef _DEBUG
    #define YIALITE_ASSERT(expression) assert(expression)
#else
    #define YIALITE_ASSERT(expression) ((void)0)
#endif

#endif