#pragma once
#include <vector>
#include <algorithm> // for sort()

class HyperEdge;
double getSpan(const std::vector<HyperEdge*>& edges);

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

double iterate(std::vector<Variable*>& variables, std::vector<HyperEdge*>& edges);

bool compare(const Variable* v1, const Variable* v2);

void shuffle(std::vector<Variable*>& variables);
