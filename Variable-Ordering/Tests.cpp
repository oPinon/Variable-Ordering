#include "Variable.h"
#include "HyperEdge.h"
#include "RandomGenerator.h"
#include <iostream>
#include <fstream> // for writing into a file
#include "Tests.h"

int spanEvolutionTest()
{
	int nbVariables = 1000; // some variables may be connected to 0 edges
	int nbEdges = 300;
	int avgVarPerEdge = 100;
	int sdVarPerEdge = 30; // some edges might be connected to 0 variables

	std::ofstream myfile;
	myfile.open ("evolution.csv");

	for(int sample=0; sample<30; sample++) {

		RandomGenerator generator = RandomGenerator(nbVariables,nbEdges,avgVarPerEdge,sdVarPerEdge, sample);

		std::vector<Variable*> variables = generator.getVariables();
		std::vector<HyperEdge*> edges = generator.getEdges();

		myfile << getSpan(edges) << ',';
		for(int iteration = 0; iteration<50; iteration++) {
			myfile << iterate(variables,edges) << ',';
		}
		myfile << std::endl;
		std::cout << "sample " << sample << " done"<< std::endl;
	}
	myfile.close();

	std::cout << "done" << std::endl;
	return 0;
}