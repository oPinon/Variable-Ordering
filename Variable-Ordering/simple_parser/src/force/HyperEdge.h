#pragma once
#include "Variable.h"
#include <vector>

class Variable;

class HyperEdge
{
public:
	double centerOfGravity;
	std::vector<Variable*> variables;
	HyperEdge();
	double getSpan() const;
};

