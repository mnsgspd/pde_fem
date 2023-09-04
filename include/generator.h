#ifndef FEM_GENERATOR_H
#define FEM_GENERATOR_H

#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "mesh.h"
#include "assemblers/assembler.h"
#include "solvers/solver.h"
#include "output_writer.h"

namespace fem{
  class Generator {
  private:
    std::string json_file_;
    nlohmann::json json_data_;
  public:
    explicit Generator(const std::string& json_file);
    
    std::unique_ptr<Mesh> generateMesh();
    std::unique_ptr<Assembler> generateAssembler();
    std::unique_ptr<Solver> generateSolver();
    std::unique_ptr<OutputWriter> generateWriter();
    
    
    void exportToVTK(const Mesh& mesh, const int iteration) const;
    // The 'const' keyword after the method's parentheses ensures that
    // the method does not modify any member variables of the class.
    // Such methods are considered "read-only" for the object's state.
    
    // Mesh& represents a reference to a Mesh object.
    // Mesh* denotes a pointer to a Mesh object.
    // std::unique_ptr<Mesh>& is a reference to a unique_ptr that internally holds a pointer to a Mesh.
    // Using *mesh_ gives access to the actual Mesh object held by the unique_ptr. When calling exportToVTK with *mesh_,
    // we're passing a reference to the actual Mesh object to the function.
    
    
  };
} // namespace fem

#endif // FEM_IO_H
