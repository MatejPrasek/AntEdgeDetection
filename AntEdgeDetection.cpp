#include <iostream>
#include "CommandParser.h"
#include "ImageParser.h"
#include "AntColonySystem.h"
#include "Parameters.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Parsing m_parameters." << endl;
	Parameters parameters;
	
	Parse(argc, argv, parameters);
	cout << "Parameters parsed." << endl;

	cout << "Parsing image." << endl;
	ParseIntensity(parameters);
	cout << "Image parsed." << endl;

	cout << "Starting simulation." << endl;
	AntColonySystem acs (std::move(parameters));
	acs.Run();
	cout << "Simulation ended." << endl;

}
