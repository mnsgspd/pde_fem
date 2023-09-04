#ifndef FEM_POISSON_ASSEMBLER_H
#define FEM_POISSON_ASSEMBLER_H

#include "assemblers/assembler.h"

namespace fem {
  
  class PoissonAssembler : public Assembler {
  public:
    // In C++, the base class constructor is called before the derived class's constructor.
// Here, PoissonAssembler() : Assembler() means the Assembler's constructor is invoked
// first when creating a PoissonAssembler object, ensuring base initialization before derived.
    PoissonAssembler() : Assembler() {}
    ~PoissonAssembler() override = default;

    void assemble();
  };
}  // namespace fem

#endif  // FEM_POISSON_ASSEMBLER_H
