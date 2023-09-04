#ifndef FEM_OUTPUT_WRITER_H
#define FEM_OUTPUT_WRITER_H

#include "mesh.h"

#include <string>
#include <fstream>

namespace fem {
  class OutputWriter {
  private:
    
  public:
    OutputWriter() = default;
    virtual ~OutputWriter() = default;  // デストラクタをvirtualにしておくことで、正しく派生クラスのデストラクタも呼ばれるようにします。
    OutputWriter(const OutputWriter&) = delete;
    OutputWriter& operator=(const OutputWriter&) = delete;
    OutputWriter(OutputWriter&&) = delete;
    OutputWriter& operator=(OutputWriter&&) = delete;
    
    void exportVTK(const Mesh& mesh);
  };
} // namespace fem

#endif // FEM_OUTPUT_WRITER_H
