#ifndef SPEC_H_
#define SPEC_H_		1

#if defined DLL_IMPORTS
#define DECLSPEC __declspec(dllimport)
#elif defined DLL_EXPORTS
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC
#endif

#endif
