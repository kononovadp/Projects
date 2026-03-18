#pragma once
#ifdef _WIN32
  #ifdef BUILD_DLL
    #define DLL_EXPORT extern "C" __declspec(dllexport)
  #else
    #define DLL_EXPORT extern "C" __declspec(dllimport)
  #endif
#else
  #define DLL_EXPORT extern "C"
#endif

