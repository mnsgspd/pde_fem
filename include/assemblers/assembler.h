#ifndef FEM_ASSEMBLER_H
#define FEM_ASSEMBLER_H
#include "mesh.h"
#include "solvers/solver.h"

namespace fem {
  
  class Assembler {
  private:
    Mesh* mesh_ = nullptr;
    Solver* solver_ = nullptr;
  public:
    Assembler() = default;
    // Virtual destructor
    virtual ~Assembler() = default;
    
    // Pure virtual function
    // The '= 0' denotes a pure virtual function, indicating 
    // that this function has no implementation in this class 
    // and must be implemented by any concrete derived class.
    virtual void assemble() = 0;
    void setSize(int n);
    
    // Pure virtual functions for matrix and vector assembly
    //virtual void assembleMatrix(/* required parameters */) = 0;
    //virtual void assembleVector(/* required parameters */) = 0;
    
    // Other member functions or variables can be added
    void initialize(Mesh* mesh, Solver* solver) {
      mesh_ = mesh;
      solver_ = solver;      
    }
  };
}  // namespace fem
#endif  // FEM_ASSEMBLER_H
