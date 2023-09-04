#ifndef FEM_FEM_SIMULATION_H
#define FEM_FEM_SIMULATION_H

#include "mesh.h"
#include "assemblers/assembler.h"
#include "solvers/solver.h"
#include "output_writer.h"
#include <memory>

namespace fem{
  class FEMSimulation {
  private:
    std::unique_ptr<Mesh> mesh_;
    std::unique_ptr<Assembler> assembler_;
    std::unique_ptr<Solver> solver_;
    std::unique_ptr<OutputWriter> writer_;
  public:
    FEMSimulation(){};
    void setup(const std::string& json_file);
    void run();
  };
}

#endif // FEM_FEM_SIMULATION_H
