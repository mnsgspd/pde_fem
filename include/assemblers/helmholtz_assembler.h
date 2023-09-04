#ifndef FEM_HELMHOLTZ_ASSEMBLER_H
#define FEM_HELMHOLTZ_ASSEMBLER_H

#include "assemblers/assembler.h"

namespace fem {
  class HelmholtzAssembler : public Assembler {
  public:
    HelmholtzAssembler() : Assembler() {}
    ~HelmholtzAssembler() override = default;
    
    void assemble();
  };
  
}  // namespace fem

#endif  // FEM_HELMHOLTZ_ASSEMBLER_H
