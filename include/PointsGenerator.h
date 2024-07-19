#include "Definitions.h"
#include <CGAL/Random.h>

namespace V3D
{

  std::vector<Point> generatePointsInCube(double halfSide, size_t amount, Point origin = { 0, 0, 0 })
  {
    CGAL::Random random;

    std::vector<Point> points;

    for (int i = 0; i < amount; i++)
    {
      double randomX = random.get_double(origin.x() - halfSide, origin.x() + halfSide);
      double randomY = random.get_double(origin.y() - halfSide, origin.y() + halfSide);
      double randomZ = random.get_double(origin.z() - halfSide, origin.z() + halfSide);

      points.push_back(Point(randomX, randomY, randomZ));
    }

    return points;
  }

}