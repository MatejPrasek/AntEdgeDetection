#pragma once
#include <D:/vcpkg-master/packages/cxxopts_x86-windows/include/cxxopts.hpp>
#include "Parameters.h"

class CommandParser
{
public:
	void Parse(int argc, char** argv, Parameters* parameters);
};

