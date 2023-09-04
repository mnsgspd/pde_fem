#ifndef FEM_MESH_H
#define FEM_MESH_H

#include <vector>
#include "element.h"
#include "node.h"

namespace fem{
  class Mesh {
    
  private:
    
  public:
    // The following variables are declared as public to avoid verbose access mechanisms.
    // Care should be taken when directly accessing or modifying them.
    std::vector<Element> elements_;
    std::vector<Node> nodes_;
    int num_nodes_;
    int num_elements_;
    
    // Constructors
    Mesh() {}
    
    inline void print()const{};
    
    void setNumberOfNodes(const int num_nodes){
      num_nodes_=num_nodes;
      nodes_.resize(num_nodes_);
    }

    void setNodes(const int i, const double* const coords){
      nodes_[i].setCoordinate(coords);
    }
    
    void setNumberOfElements(int num_elements){
      num_elements_=num_elements;
      elements_.resize(num_elements_);
    }

    void setElements(const int i, const std::vector<int>& element_nodes){
      elements_[i].setPoints(element_nodes);
    }
    // Accessors
    //    std::vector<Node> getNodes() const { return nodes; }
    //void setNodes(const std::vector<Node>& newNodes) { nodes = newNodes; }
    //    std::vector<Element> getElements() const { return elements; }
    //void setElements(const std::vector<Element>& newElements) { elements = newElements; }
  };    
} // namespace fem
#endif // FEM_MESH_H
