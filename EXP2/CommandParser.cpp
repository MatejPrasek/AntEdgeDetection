#include "CommandParser.h"

void Parse(int argc, char** argv, Parameters &parameters)
{
	cxxopts::Options options("ACO_edge_detection", "ACO for edge detection - bachelor thesis");
		
	options.add_options()
		("i,image", "Path to an image to be processed", cxxopts::value<std::string>()->default_value("./standard_test_images/256/lena_color.tif"))
		("a,alpha", "Pheromone coefficient", cxxopts::value<float>()->default_value("1"))
		("b,beta", "Heuristic coefficient", cxxopts::value<float>()->default_value("2"))
		("n,ants", "Number of ants", cxxopts::value<int>()->default_value("250"))
		("r,rho", "Pheromone evaporation coefficient (0, 1>", cxxopts::value<float>()->default_value("0.1"))
		("p,phi", "Pheromone decay coefficient (0, 1>", cxxopts::value<float>()->default_value("0.05"))
		("k,cons", "Number of construction steps", cxxopts::value<int>()->default_value("40"))
		("l,iter", "Number of iterations", cxxopts::value<int>()->default_value("10"))
		("q,q0", "Degree of exploration (0, 1>", cxxopts::value<float>()->default_value("0.4"))
		("t,tauini", "Initial value of pheromone matrix", cxxopts::value<float>()->default_value("0.01"))
		("m,mem", "Ant's memory (Number of positions of last visited pixels)", cxxopts::value<int>()->default_value("8"))
		("d,debug", "For debugging purposes", cxxopts::value<bool>()->default_value("false"))
		("random", "Assign ants starting positions randomly", cxxopts::value<bool>()->default_value("false"))
		("h,threshold", "Threshold for image rendering", cxxopts::value<int>()->default_value("0"))
		("s,skip", "First x iteration will not be count to the result", cxxopts::value<int>()->default_value("0"))
		;

	auto parsed = options.parse(argc, argv);

	parameters.imagePath = parsed["image"].as<std::string>();
	parameters.alpha = parsed["alpha"].as<float>();
	parameters.beta = parsed["beta"].as<float>();
	parameters.ants = parsed["ants"].as<int>();
	parameters.rho = parsed["rho"].as<float>();
	parameters.phi = parsed["phi"].as<float>();
	parameters.constructionSteps = parsed["cons"].as<int>();
	parameters.iterations = parsed["iter"].as<int>();
	parameters.q0 = parsed["q0"].as<float>();
	parameters.tauini = parsed["tauini"].as<float>();
	parameters.memory = parsed["mem"].as<int>();
	parameters.debug = parsed["debug"].as<bool>();
	parameters.random = parsed["random"].as<bool>();
	parameters.threshold = parsed["threshold"].as<int>();
	parameters.skip = parsed["skip"].as<int>();
}
