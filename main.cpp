#include "test.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv, char **env){
	cout<<"start to test embeded perl"<<endl;
	void* perl=start_perl(argc,argv,env);
	test_perl();
	shutdown_perl(perl);
	cout<<"end of test"<<endl;
	return 0;
}
