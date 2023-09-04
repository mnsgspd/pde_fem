#ifndef FEM_ELEMENT_H
#define FEM_ELEMENT_H

#include <vector>
#include "node.h"

namespace fem{
  class Element {

  private:
    
  public:
    Eigen::VectorXi points_; // vector storing the node numbers of the element
    // Constructors
    Element() {};
    
    void setPoints(const std::vector<int> & element_nodes){
      points_.resize((int)element_nodes.size());
      for(int i=0; i<(int)element_nodes.size();i++){
	points_(i)=element_nodes[i];
      }
    };
    // Accessors
    //std::vector<Node> getNodes() const { return nodes; }
    //void setNodes(const std::vector<Node>& newNodes) { nodes = newNodes; }
    

  };
}
#endif // FEM_ELEMENT_H
