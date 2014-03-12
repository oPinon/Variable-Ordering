#include "Variable.h"
#include "HyperEdge.h"
#include <algorithm> // for sort()
#include <iostream>

Variable::Variable(double position)
	: position_(position)
{
}

double iterate(std::vector<Variable*>& variables, std::vector<HyperEdge*>& edges){

	for (std::vector<HyperEdge*>::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		HyperEdge& edge = **it;

		edge.centerOfGravity = 0;
		for (Variable* v : (*it)->variables)
		{
			edge.centerOfGravity += v->position();
		}
		edge.centerOfGravity /= edge.variables.size();
	}

	for(std::vector<Variable*>::iterator it = variables.begin(); it != variables.end(); ++it)
	{
		Variable& var = **it;
		var.position()=0;

		for(std::vector<HyperEdge*>::iterator it = var.edges().begin(); it != var.edges().end(); ++it)
		{
			HyperEdge& edge = **it;
			var.position() += edge.centerOfGravity;
		}
		var.position() /= var.edges().size();
	}

	std::sort(variables.begin(),variables.end(),compare);

	for(int i=0; i<variables.size(); i++) // set the variables' positions according to their order
	{
		(*variables[i]).position() = i;
	}
	return getSpan(edges);
};

double getSpan(const std::vector<HyperEdge*>& edges) {
	double span = 0;
	for(int i=0; i<edges.size(); i++)
	{
		HyperEdge& e = *(edges[i]);
		span += e.getSpan();
	}
	return span;
};

bool
	compare(const Variable* v1, const Variable* v2)
{
	return (*v1).position() < (*v2).position();
};
