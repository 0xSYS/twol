#pragma once





#ifdef __linux__
  #define API_EXPORT __attribute__((visibility("default")))
  #define API_CONSTR __attribute__((constructor))
  #define API_DESTRUCT __attribute__((destructor))
#endif

#if defined(_WIN32) || defined(_WIN64)
  #define API_EXPORT __declspec(dllexport)
#endif
