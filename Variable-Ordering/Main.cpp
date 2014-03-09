#include "Variable.h"
#include "HyperEdge.h"
#include "RandomGenerator.h"
#include <iostream>

int main( int argc, const char* argv[] )
{
	int nbVariables = 100; // some variables may be connected to 0 edges
	int nbEdges = 30;
	int avgVarPerEdge = 10;
	int sdVarPerEdge = 3; // some edges might be connected to 0 variables
	
	RandomGenerator generator = RandomGenerator(nbVariables,nbEdges,avgVarPerEdge,sdVarPerEdge);

	std::vector<Variable*> variables = generator.getVariables();
	std::vector<HyperEdge*> edges = generator.getEdges();
	std::cout << "Initial span = " << getSpan(edges) << std::endl;

	for(int i=0; i<20; i++) {
		std::cout << "current span = " <<iterate(variables,edges) << std::endl;
	}
}