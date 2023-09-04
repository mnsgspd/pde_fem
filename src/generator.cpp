#include "generator.h"
#include "assemblers/assembler.h"
#include "assemblers/poisson_assembler.h"
#include "assemblers/helmholtz_assembler.h"
#include "solvers/solver.h"
#include "solvers/conjugate_gradient.h"
#include "output_writer.h"
#include <fstream>

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>


namespace fem{

  Generator::Generator(const std::string& json_file) : json_file_(json_file) {
    std::ifstream input(json_file_);
    if (!input.is_open()) {
      throw std::runtime_error("Failed to open input file: " + json_file_);
    }
    input >> json_data_;
    input.close();
  }

  
  std::unique_ptr<Mesh> Generator::generateMesh(){
    std::string vtk_file = json_data_["vtk_file"];
    auto mesh = std::make_unique<Mesh>();
    
    // Use VTK to read the unstructured grid data
    vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
    reader->SetFileName(vtk_file.c_str());
    reader->Update();
    
    vtkUnstructuredGrid* grid = reader->GetOutput();
    int num_nodes = static_cast<int>(grid->GetNumberOfPoints());
    mesh->setNumberOfNodes(num_nodes);
    
    // Extract nodes from VTK
    for (int i = 0; i < num_nodes; i++) {
      double* coords = grid->GetPoint(i);
      mesh->setNodes(i, coords);
    }
    
    // Extract elements from VTK
    // This is just a sketch. Exact extraction depends on the cell type (triangles, quads, etc.)
    int num_elements = static_cast<int>(grid->GetNumberOfCells());
    mesh->setNumberOfElements(num_elements);
    
    for (int i = 0; i < num_elements; i++) {
      vtkCell* cell = grid->GetCell(i);
      int num_points=static_cast<int>(cell->GetNumberOfPoints());
      std::vector<int> element_nodes;
      for (int j = 0; j < num_points; j++) {
	element_nodes.push_back(static_cast<int>(cell->GetPointId(j)));
      }
      mesh->setElements(i, element_nodes);
    }    
    return mesh;
  } //std::unique_ptr<Mesh> Generator::generateMesh(){

  std::unique_ptr<Assembler> Generator::generateAssembler() {
    std::string governing_eq;
    if (json_data_.contains("governing_equation") && !json_data_["governing_equation"].is_null()) {
      governing_eq = json_data_["governing_equation"];
    } else {
      throw std::runtime_error("Error: 'governing_equation' key is missing or has a null value in the JSON data.");
    }
    std::replace(governing_eq.begin(), governing_eq.end(), ' ', '_');
    std::transform(governing_eq.begin(), governing_eq.end(), governing_eq.begin(), ::tolower);
    if (governing_eq == "poisson") {
      return std::make_unique<PoissonAssembler>();
    } else if (governing_eq == "helmholtz") {
      return std::make_unique<HelmholtzAssembler>();
    } else {
      throw std::runtime_error("Unknown governing equation: " + governing_eq);
    }
  }

  std::unique_ptr<Solver> Generator::generateSolver() {
    std::string solver_method;
    if (json_data_.contains("solver") && !json_data_["solver"].is_null()) {
      solver_method = json_data_["solver"];
    } else {
      throw std::runtime_error("Error: 'solver' key is missing or has a null value in the JSON data.");
    }
    std::replace(solver_method.begin(), solver_method.end(), ' ', '_');
    std::transform(solver_method.begin(), solver_method.end(), solver_method.begin(), ::tolower);
    if (solver_method == "conjugate_gradient"||solver_method == "cg") {
      return std::make_unique<ConjugateGradient>();
    } else {
      throw std::runtime_error("Unknown solver method: " + solver_method);
    }
  }


  std::unique_ptr<OutputWriter> Generator::generateWriter() {
    return std::make_unique<OutputWriter>();
  }

  void Generator::exportToVTK(const Mesh& mesh, const int iteration) const {
    mesh.print();
    std::string filename = "output_" + std::to_string(iteration) + ".vtk";
  }
} //namespace fem

  // ... rest of the file remains unchanged ...
