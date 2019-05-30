// ReignTillSalvation.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"

int main()
{
	{
		Individual one{ std::make_unique<Strong>("Roger") };
		one.action();
		one.changeState();
		one.action();
	}

}
