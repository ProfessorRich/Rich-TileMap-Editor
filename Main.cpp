#include "Editor.h"

int main(int argc, char* args[])
{
	Editor* mainEd = new Editor();

	mainEd->Initialise();

	while (mainEd->GetIsRunning()) {
		mainEd->Update();
		mainEd->Render();
	}

	return 0;

};