
#include <iostream>

using namespace std;

int val = 0;

int foo()
{
	return val++;
}

int main()
{
	cout<<foo();
	cout<<endl<<val;
}
