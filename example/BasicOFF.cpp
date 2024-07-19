#include "PathManager.h"
#include "OFFConstructor.h"

int main()
{
    V3D::OFFConstructor off;

    off.init_face();
    off.add_vertex(0.0, 0.0, 0.0);
    off.add_vertex(1.0, 0.0, 0.0);
    off.add_vertex(0.0, 1.0, 0.0);
    off.end_face();

    off.init_face();
    off.add_vertex(0.0, 0.0, 0.0);
    off.add_vertex(0.0, 1.0, 0.0);
    off.add_vertex(0.0, 1.0, 1.0);
    off.add_vertex(0.0, 0.0, 1.0);
    off.end_face();

    const std::string outputPath = V3D::filePath("assets/output/BasicOFF.off");

    off.write(outputPath);

    return 0;
}