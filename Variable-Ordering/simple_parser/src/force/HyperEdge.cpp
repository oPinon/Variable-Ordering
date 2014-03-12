#include <algorithm>
#include "HyperEdge.h"
#include "Variable.h"

HyperEdge::HyperEdge()
	: centerOfGravity(0)
{

}

double HyperEdge::getSpan() const
{ 
	if(variables.size()>0) {
		double minPosition =
			(*std::min_element(this->variables.begin(),this->variables.end(),compare))->position();

		double maxPosition =
			(*std::max_element(this->variables.begin(),this->variables.end(),compare))->position();

		return maxPosition - minPosition;
	} else return 0;
}
