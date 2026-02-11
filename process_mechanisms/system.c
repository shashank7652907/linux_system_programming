#include <stdlib.h>

int main()
{
	int return_value;

	return_value = system("ls -l /");
    //this will create a subshell and execute ls -l
    //And returns the output to main program 
	return return_value;
}

