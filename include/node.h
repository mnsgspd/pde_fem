#ifndef FEM_NODE_H
#define FEM_NODE_H

#include <Eigen/Dense>

namespace fem{
  class Node {
  private:


    
  public:
    Eigen::Vector2d coords_; // 2D coordinates using Eigen
    double value_;
    
    Node(){};
    
    //    Eigen::Vector2d getCoords() const { return coords; }
    //void setCoords(const Eigen::Vector2d& newCoords) { coords = newCoords; }

    void setCoordinate(const double* const coords){
      coords_(0)=coords[0];
      coords_(1)=coords[1];
    }
    
  };
} // namespace fem
#endif // FEM_NODE_H
