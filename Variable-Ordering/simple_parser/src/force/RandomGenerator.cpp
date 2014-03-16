#include "RandomGenerator.h"
#include <time.h> // for seeding std::srand()

RandomGenerator::RandomGenerator(int nbVariables, int nbEdges, double avgVarPerEdge, double sdVarPerEdge, int seed)
{
	std::srand (time(NULL)+seed); // seeding

	for(int i=0; i<nbVariables; i++) {
		this->variables.push_back( new Variable(i) );
	}

	for(int i=0; i<nbEdges; i++) {
		double nbConnectedVariables = avgVarPerEdge + ((RAND_MAX-2*rand())*sdVarPerEdge)/RAND_MAX;
		HyperEdge& edge = *(new HyperEdge());

		std::vector<int> pool;
		for(int i=0;i<nbVariables;i++) { pool.push_back(i); }

		for(int i=0; i< nbConnectedVariables || pool.size()==0; i++) {
			int pickedVariable = rand()%pool.size();

			Variable& var = *variables[pool[pickedVariable]];
			
			edge.variables.push_back(&var);
			var.edges().push_back(&edge);

			pool.erase(pool.begin()+pickedVariable);
		}

		edges.push_back(&edge);
	}
}

std::vector<Variable*> RandomGenerator::getVariables() { return variables; }
std::vector<HyperEdge*> RandomGenerator::getEdges() { return edges; }
