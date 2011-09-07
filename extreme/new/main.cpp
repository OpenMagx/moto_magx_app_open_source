
#include "RokrExtreme.h"

int main(int argc, char** argv)
{
	if(argc<3)
	{
		printf("Debug: invalid call\n");
		return 1;
	}
	
	RokrExtreme *gui = new RokrExtreme(argc, argv);
	gui->exec();
	delete gui;
	gui = NULL;
}

