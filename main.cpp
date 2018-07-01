#include "test.h"
#include <iostream>
using namespace std;
void call_from_perl(const char *msg)
{
	cout<<"test C func in vs called from perl:"<<msg<<endl;
}
int main(int argc, char **argv, char **env){
	cout<<"start to test embeded perl"<<endl;
	void* perl=start_perl(argc,argv,env);
	test_perl(call_from_perl);
	shutdown_perl(perl);
	cout<<"end of test"<<endl;
	return 0;
}
