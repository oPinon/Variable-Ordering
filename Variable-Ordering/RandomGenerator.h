#pragma once
#include "Variable.h"
#include "HyperEdge.h"
#include <vector>

class RandomGenerator
{
private:
	std::vector<Variable*> variables;
	std::vector<HyperEdge*> edges;
public:
	RandomGenerator(int nbVariables, int nbEdges, double avgVarPerEdge, double sdVarPerEdge);
	std::vector<Variable*> getVariables();
	std::vector<HyperEdge*> getEdges();
};

