#pragma once

#ifdef Z_PLAT_WIN
    #ifdef Z_BUILD_DLL
        #define Z_API __declspec(dllexport)
    #else
        #define Z_API __declspec(dllimport)
    #endif
#else
    #error Zyliph Engine only supports windows for now 
#endif