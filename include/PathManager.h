#pragma once

#include <string>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

namespace V3D
{
  std::string filePath(std::string relativePath)
  {
    return CGAL::data_file_path(relativePath);
  }
}
