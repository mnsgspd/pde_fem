#include <iostream>
#include <vector>
#include <string>
#include "generator.h"
#include "mesh.h"
#include "fem_simulation.h"

int main(int argc, char** argv) {
  
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_problem.json>" << std::endl;
    return -1;
  }
  std::string json_file = argv[1];
  if (json_file.size() < 5 || json_file.substr(json_file.size() - 5) != ".json") {
    std::cerr << "Error: The provided input file must have a .json extension." << std::endl;
    return -1;
  }
  
  // Load input data
  //fem::GENERATOR gen(json_file);
  //  auto mesh = io.generateMesh(json_file);
  fem::FEMSimulation sim;

  sim.setup(json_file);
  sim.run();
  
  
  // Implement the solver for the Laplace equation.
  // (For simplicity, the actual solver details are omitted here.)
  
  // Compute the solution
  //    mesh.solveLaplace();
  
  // Write results
  //  std::string outputFile = "solution.json";
  //io.writeOutput(mesh, outputFile);
  
  //  std::cout << "Solution written to " << outputFile << std::endl;
  
  return 0;
}
