// Include Order Guidelines:
// 1. Corresponding header file for this source file.
// 2. Standard library headers.
// 3. Third-party library headers.
// 4. Other project-specific headers.
#include "output_writer.h"

#include <fstream>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkPolyData.h>
#include <vtkPointData.h> 
#include <vtkPolyDataWriter.h>
#include <vtkFloatArray.h>

namespace fem {
  void OutputWriter::exportVTK(const Mesh& mesh){
    
    // Create a new VTK points object
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (const auto& node : mesh.nodes_) {
      points->InsertNextPoint(node.coords_[0], node.coords_[1], 0.0); // Assuming 2D mesh
    }
    
    // Create a new VTK cell array
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    for (const auto& element : mesh.elements_) {
      if (element.points_.size() == 3) { // Triangle
	vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
	triangle->GetPointIds()->SetId(0, element.points_[0]);
	triangle->GetPointIds()->SetId(1, element.points_[1]);
	triangle->GetPointIds()->SetId(2, element.points_[2]);
	cells->InsertNextCell(triangle);
      } else if (element.points_.size() == 4) { // Quad
	vtkSmartPointer<vtkQuad> quad = vtkSmartPointer<vtkQuad>::New();
	quad->GetPointIds()->SetId(0, element.points_[0]);
	quad->GetPointIds()->SetId(1, element.points_[1]);
	quad->GetPointIds()->SetId(2, element.points_[2]);
	quad->GetPointIds()->SetId(3, element.points_[3]);
	cells->InsertNextCell(quad);
      }
    }
    
    // Setup the point data
    vtkSmartPointer<vtkFloatArray> solutionValues = vtkSmartPointer<vtkFloatArray>::New();
    solutionValues->SetName("solution");
    //    vtkSmartPointer<vtkFloatArray> velocities = vtkSmartPointer<vtkFloatArray>::New();
    //    velocities->SetName("velocity");
    //    velocities->SetNumberOfComponents(2);  // Since velocity is Vector2d
    
    for (const auto& node : mesh.nodes_) {
      solutionValues->InsertNextValue(node.value_);
      //      velocities->InsertTuple2(node.velocity_[0], node.velocity_[1]);
    }
    
    // Setup the cell data
    //    vtkSmartPointer<vtkFloatArray> stresses = vtkSmartPointer<vtkFloatArray>::New();
    //    stresses->SetName("stress");
    //stresses->SetNumberOfComponents(4);  // Tensor for 2D: 4 components
    
    //    for (const auto& element : mesh.elements_) {
    //      stresses->InsertTuple4(
    //			     element.stress_(0,0), element.stress_(0,1),
    //			     element.stress_(1,0), element.stress_(1,1)
    //			     );
    //    }
    
    // Attach data to a PolyData object
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetPolys(cells);
    polyData->GetPointData()->AddArray(solutionValues);
    //    polyData->GetPointData()->AddArray(velocities);
    //    polyData->GetCellData()->AddArray(stresses);
    
    // Write data to file
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName("output.vtk");
    writer->SetInputData(polyData);
    writer->SetFileTypeToBinary();
    writer->Write();
  }
  
} // namespace fem
