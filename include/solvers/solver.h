#ifndef FEM_SOLVER_H
#define FEM_SOLVER_H

// Necessary includes or forward declarations can be added here.
// e.g., #include "matrix.h"

namespace fem {
  
  // Base class for Solver
  class Solver {
  private:
    Eigen::SparseMatrix<double> global_matrix_;
    Eigen::VectorXd rhs_vector_;
    
  public:
    virtual ~Solver() = default;
    
    virtual void solve () = 0;

    void setSize(int n){
    };
    
    // Setter and getter functions for the matrix and vector can be added
    // e.g., virtual void setMatrix(const MatrixType& matrix) = 0;
    
  protected:
    // Protected constructor (to restrict instantiation)
    Solver() = default;
    
    // Other protected member functions or variables can be added
    
  };
  
} // namespace fem

#endif // FEM_SOLVER_H
