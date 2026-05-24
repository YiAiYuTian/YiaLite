#ifndef YIALITE_CORE_H
#define YIALITE_CORE_H

#include <cassert>

#ifdef _WIN32
    #if defined(YIALITE_SHARED)
        #ifdef YIALITE_EXPORTS
            #define YIALITE_API __declspec(dllexport)
        #else
            #define YIALITE_API __declspec(dllimport)
        #endif
    #else
        #define YIALITE_API
    #endif
#else
    #if defined(YIALITE_SHARED) && defined(YIALITE_EXPORTS)
        #define YIALITE_API __attribute__((visibility("default")))
    #else
        #define YIALITE_API
    #endif
#endif

#ifdef _DEBUG
    #define YIALITE_ASSERT(expression) assert(expression)
#else
    #define YIALITE_ASSERT(expression) ((void)0)
#endif

#endif