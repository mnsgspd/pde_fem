#ifndef FEM_CONJUGATE_GRADIENT_H
#define FEM_CONJUGATE_GRADIENT_H

#include "solvers/solver.h"
#include <vector>
#include <Eigen/Sparse>

namespace fem {
  
  class ConjugateGradient : public Solver {
  private:
    Eigen::SparseMatrix<double> global_matrix_;
    Eigen::VectorXd rhs_vector_;

  public:
    ConjugateGradient() : Solver(){};
    ~ConjugateGradient() override = default;
    
    void solve();
    
    // Functions to set the matrix A and vector b
    //    void setMatrix(const std::vector<std::vector<double>>& matrix);
    //    void setVector(const std::vector<double>& b);
    
    // Function to get the result vector x
    //    const std::vector<double>& getResult() const;
    
  };
  
} // namespace fem

#endif // FEM_CONJUGATE_GRADIENT_H
