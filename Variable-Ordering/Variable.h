#pragma once
#include <vector>
#include "HyperEdge.h"

class HyperEdge;

class Variable
{
private:
	double position_;
	std::vector<HyperEdge*> connected_edges_;

public:
	Variable(double position);

	bool
		operator<(const Variable& other)
		const
	{
		return position_ < other.position_;
	}

	double
		position()
		const
	{
		return position_;
	}

	double&
		position()
	{
		return position_;
	}

	const std::vector<HyperEdge*>&
		edges()
		const
	{
		return connected_edges_;
	}

	std::vector<HyperEdge*>&
		edges()
	{
		return connected_edges_;
	}

};

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
		var.position /= var.edges().size();
	}

	std::sort(variables.begin(),variables.end(),[](Variable* lhs, Variable* rhs){return lhs->position < rhs->position;}); // sorts the variables according to their positions (could use compare() instead of a "lambda")

	for(int i=0; i<variables.size(); i++) // set the variables' positions according to their order
	{
		(*variables[i]).position() = i;
	}
	return getSpan(edges);
};

double getSpan(const std::vector<HyperEdge*>& edges) {
	double span = 0;
	for(HyperEdge* e0 : edges)
	{
		HyperEdge e = *e0;
		span += e.getSpan();
	}
	return span;
};

bool compare(Variable* v1, Variable* v2)
{ return v1->position() < v2->position(); }



