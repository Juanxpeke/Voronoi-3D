#include "PathManager.h"
#include "OFFConstructor.h"

int main()
{
    V3D::OFFConstructor off;

    off.initFace();
    off.addVertex(0.0, 0.0, 0.0);
    off.addVertex(1.0, 0.0, 0.0);
    off.addVertex(0.0, 1.0, 0.0);
    off.endFace();

    off.initFace();
    off.addVertex(0.0, 0.0, 0.0);
    off.addVertex(0.0, 1.0, 0.0);
    off.addVertex(0.0, 1.0, 1.0);
    off.addVertex(0.0, 0.0, 1.0);
    off.endFace();

    const std::string outputPath = V3D::filePath("assets/output/BasicOFF.off");

    off.write(outputPath);

    return 0;
}