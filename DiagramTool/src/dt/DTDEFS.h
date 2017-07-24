#pragma once
#define DT_EXTERN_C extern "C"
#ifndef __cplusplus
#define DT_EXTERN_C 
#endif
#define DT_DLL_EXPORT(RET_TYPE) DT_EXTERN_C __declspec(dllexport) RET_TYPE __stdcall