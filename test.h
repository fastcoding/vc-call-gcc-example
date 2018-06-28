#ifndef TEST_H
#define TEST_H
#ifdef DLL
#define DLLAPI 
//__declspec(dllexport)
#else
#define DLLAPI 
//__declspec(dllimport)
#endif
#ifdef __cplusplus
extern "C" {
#endif
void DLLAPI *start_perl (int argc, char **argv, char **env);
void DLLAPI test_perl();
void DLLAPI shutdown_perl(void*perl);
#ifdef __cplusplus
}
#endif
#endif
