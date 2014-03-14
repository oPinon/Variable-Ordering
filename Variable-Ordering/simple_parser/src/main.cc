#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "parsers/parse.hh"
#include "force/Variable.h"
#include "force/HyperEdge.h"

int main(int argc, char** argv)
{
  using namespace pnmc::parsers;
  
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " bpn|prod|tina|xml file" << std::endl;
    return 1;
  }
  
  input_format format;
  if (strcmp(argv[1], "bpn") == 0)
  {
    format = input_format::bpn;
  }
  else if (strcmp(argv[1], "prod") == 0)
  {
    format = input_format::prod;
  }
  else if (strcmp(argv[1], "tina") == 0)
  {
    format = input_format::tina;
  }
  else if (strcmp(argv[1], "xml") == 0)
  {
    format = input_format::xml;
  }
  else
  {
    std::cerr << "Invalid format specification" << std::endl;
    return 2;
  }
  
  std::ifstream file(argv[2]);
  if (not file.is_open())
  {
    std::cerr << "Can't read file '" << argv[2] << "'" << std::endl;
    return 3;
  }

  const auto net_ptr = parse(format, file);

  std::unordered_map<std::string, Variable> variables_holder;
  std::vector<HyperEdge> edges_holder;

  unsigned int pos = 0; 
  for (const auto& place : net_ptr->places())
  {
    // >>>>>>>>> avec quelle valeur faut-il initialiser la position? <<<<<<<<<<<<<<<<
    variables_holder.emplace(place.id, Variable(pos++));
  }
  
  for (const auto& transition : net_ptr->transitions())
  {
    HyperEdge& edge = *edges_holder.insert(edges_holder.end(), HyperEdge());
    edge.variables.reserve(transition.post.size() + transition.pre.size());

    for (const auto& arc : transition.pre)
    {
      Variable& v = variables_holder.find(arc.first)->second;
      edge.variables.push_back(&v);
      v.edges().push_back(&edge);
    }

    for (const auto& arc : transition.post)
    {
      Variable& v = variables_holder.find(arc.first)->second;
      edge.variables.push_back(&v);
      v.edges().push_back(&edge);
    }
  }
  
  std::vector<Variable*> variables;
  variables.reserve(variables_holder.size());
  for (auto& v : variables_holder)
  {
    variables.push_back(&v.second);
  }

  std::vector<HyperEdge*> edges;
  edges.reserve(edges_holder.size());
  for (auto& e : edges_holder)
  {
    edges.push_back(&e);
  }

  /*--------------------------------------------------------------------------*/
  // Vous pouvez maintenant utiliser edges et variables
  
	std::ofstream myfile;
	myfile.open ("evolution.csv", std::ios_base::app);

		myfile << getSpan(edges) << ',';
		
		int counter = 0;
		int previousSpan;		
		for(unsigned int iteration=0; (counter<10)&&(iteration<1000); iteration++) {
			int currentSpan = iterate(variables,edges);
			myfile << currentSpan << ',';
			if(currentSpan==previousSpan) {counter++;}
			previousSpan = currentSpan;
		}
		myfile << std::endl;

	myfile.close();

	std::cout << "done" << std::endl;
	return 0;

  return 0;
}
