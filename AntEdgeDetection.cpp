#include <iostream>
#include <chrono>
#include <filesystem>
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

	string resultsPath = parameters.resultsPath;
	std::filesystem::create_directories(resultsPath);
	
	auto begin = chrono::steady_clock::now();
	cout << "Starting simulation." << endl;
	AntColonySystem acs (std::move(parameters));
	acs.Run();
	auto end = chrono::steady_clock::now();

	ofstream performance;
	performance.open(resultsPath + "performance.txt");
	performance << "Simulation lasted " << chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() / 1000.0 << " seconds";
	performance.close();
	
	cout << "Simulation ended." << endl;

}
