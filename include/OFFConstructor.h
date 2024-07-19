#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace V3D
{
    class OFFConstructor
    {
    public:
        OFFConstructor() {}

        void init_face() {
            current_face.clear();
        }

        void add_vertex(double x, double y, double z) {
            vertices.push_back({x, y, z});
            current_face.push_back(vertices.size() - 1);
        }

        void end_face() {
            if (!current_face.empty()) {
                faces.push_back(current_face);
            }
        }

        void write(const std::string& path) {
            std::ofstream out(path);
            if (!out.is_open()) {
                std::cerr << "Failed to open file: " << path << std::endl;
                return;
            }

            out << "OFF\n";
            out << vertices.size() << " " << faces.size() << " 0\n";

            for (const auto& vertex : vertices) {
                out << vertex[0] << " " << vertex[1] << " " << vertex[2] << "\n";
            }

            for (const auto& face : faces) {
                out << face.size();
                for (const auto& index : face) {
                    out << " " << index;
                }
                out << "\n";
            }

            out.close();
        }

    private:
        std::vector<std::vector<double>> vertices;
        std::vector<std::vector<int>> faces;
        std::vector<int> current_face;
    };
}


