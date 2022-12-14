#pragma once
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[]) 
{
 	if (argc == 3)
	{
		ifstream file{ argv[2] }; 
		if (file)
		{
			Scene sceneInfo(file);
			Engine engine(&sceneInfo);
			int exitcode{ 0 };
			if (engine.simulate())
			{
				//cout << "The image was created successfully!" << endl;
				//system("pause"); //without this, the CMD close without showing the message.
			}
			else
			{
				cout << "Error : there was an issue with the creation of the image." << endl;
				system("pause");
				exitcode = -3;
			}
			return exitcode;
		}
		else
		{
			cout << "Error : file cannot be found." << endl;
			system("pause");
			return -2;
		}
	}
	else
	{
		cout << "Error : not enough arguments." << endl;
		system("pause");
		return -1;
	}
}