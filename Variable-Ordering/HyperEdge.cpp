#include <algorithm>

#include "HyperEdge.h"

HyperEdge::HyperEdge()
  : centerOfGravity(0)
{

}

double HyperEdge::getSpan() const
{ 
	double minPosition =
 (*std::min_element(this->variables.begin(),this->variables.end(),compare))->position();
	
  double maxPosition =
  (*std::max_element(this->variables.begin(),this->variables.end(),compare))->position();
	
  return maxPosition - minPosition;
}
