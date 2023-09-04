#include "fem_simulation.h"
#include "generator.h"
#include <memory>
#include <string>
//#include <iostream>
//#include <typeinfo>
namespace fem{
  void FEMSimulation::setup(const std::string& json_file){
    auto gen=std::make_unique<Generator>(json_file);
    mesh_ = gen->generateMesh();
    assembler_ = gen->generateAssembler();
    solver_ = gen->generateSolver();
    writer_ = gen->generateWriter();
    
    assembler_->initialize(mesh_.get(),solver_.get());
  }
  
  void FEMSimulation::run(){
    //    std::cout << typeid(*assembler_).name() << std::endl;
    assembler_->setMatVecSize();
    assembler_->assemble();
    writer_->exportVTK(*mesh_);
  }
}
