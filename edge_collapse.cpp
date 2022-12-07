#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h>
#include <chrono>
#include <fstream>
#include <iostream>
typedef CGAL::Simple_cartesian<double>               Kernel;
typedef Kernel::Point_3                              Point_3;
typedef CGAL::Surface_mesh<Point_3>                  Surface_mesh;
namespace SMS = CGAL::Surface_mesh_simplification;
int main(int argc, char** argv)
{
    Surface_mesh mesh;
    const std::string filename = ("../meshes/floormeshHighRes.off");
    std::ifstream is(filename);
    if (!is || !(is >> mesh))
    {
        std::cerr << "Invalid mesh: " << filename << std::endl;
        return EXIT_FAILURE;
    }
    //Trying to make use of edge_is_constrained to ignore the points not given in the vector, but can't figure out yet.
    //std::vector<Point_3> points;
    //auto edge_is_constrained_map = get(CGAL::Surface_mesh::edge_is_constrained, surface_mesh);
    //for (auto point : points)
    //{
    //    for (auto edge : out_edges(point, surface_mesh))
    //    {
    //        edge_is_constrained_map[edge] = true;
    //    }
    //}
    double stop_ratio = 0.1;
    SMS::Count_ratio_stop_predicate<Surface_mesh> stop(stop_ratio);
    int r = SMS::edge_collapse(mesh, stop);
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::cout << "\Done\n" << r << " edges removed.\n" << mesh.number_of_edges() << " current edges.\n";
    CGAL::IO::write_polygon_mesh("output.off", mesh, CGAL::parameters::stream_precision(17));
    return EXIT_SUCCESS;
}