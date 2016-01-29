// EGrammar main

#include "EGrammar.h"

int main(int argc, char *argv[])
{
	// Pick up commandline input filename, if any
	if (argc > 1 && (!yylexopen(argv[1])))
	{
		cout << "Error: Cannot open input file " << argv[1] << endl;
		exit(1);
	}
	
	gram();
	
	
	return 0;
}
