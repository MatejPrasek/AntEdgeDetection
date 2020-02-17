#include <iostream>
#include "CommandParser.h"
#include "ImageParser.h"
#include "AntColonySystem.h"
#include "Parameters.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "Parsing parameters." << endl;
	auto parameters = new Parameters();

	auto cp = new CommandParser();
	cp->Parse(argc, argv, parameters);
	delete cp;
	cout << "Parameters parsed." << endl;

	cout << "Parsing image." << endl;
	auto ip = new ImageParser(parameters);
	ip->ParseIntensity();
	delete ip;
	cout << "Image parsed." << endl;

	cout << "Starting simulation." << endl;
	auto acs = new AntColonySystem(parameters);
	acs->Run();
	delete acs;
	cout << "Simulation ended." << endl;

	delete parameters;
}
