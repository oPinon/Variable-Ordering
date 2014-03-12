#include <algorithm>

#include "HyperEdge.h"

HyperEdge::HyperEdge(void) // <= pas besoin du void
  : centerOfGravity(0) // <= bien
{
  // centerOfGravity = 0; <= pas bien, on utilise la liste d'initilisation dans un constructeur
}

double HyperEdge::getSpan()
{
  // C'est dangereux de faire *std::min_element directement. En effet, si cet algo
  // ne trouve rien (dans ce cas, cela veut dire que variables est vide),
  // alors il renvoie variables.end(). Et déréférencer variables.end() fait planter le programme
  // (si vous avez de la chance)
  // En bref, pour certains algorithmes, il faut s'assurer que le conteneur n'est pas vide.
  // Bon, a priori,on sait que variables ne peut pas être vide!

  
	double minPosition =
 (*std::min_element(this->variables.begin(),this->variables.end(),Variable::compare))->position();
	
  double maxPosition =
  (*std::max_element(this->variables.begin(),this->variables.end(),Variable::compare))->position();
	
  return maxPosition - minPosition;
}
