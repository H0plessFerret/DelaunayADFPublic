#include <meshloader3d.h>
#include <meshunloader3d.h>
#include <mathutilities.h>
#include <delaunayadf3d.h>
#include <exceptions.h>
#include <time.h>

int main()
{
    DelaunayADF3D mygen;
    MeshLoader3D loader;
    MeshUnloader3D unloader;
    std::string file_location;
    std::shared_ptr<UnstructuredGrid> grid_ptr(new UnstructuredGrid);

    time_t start, end;

    std::cout << "Please enter the full path to the file" << std::endl;
    //std::cin >> file_location;

    loader.load("../MyDiploma/mesh_files/presets/simple_cube.msh", *grid_ptr);

    time(&start);
    std::function<double(const BaseNode&)> lambda = [](const BaseNode&) { return 1. / 5.8; };

    mygen.initialize(grid_ptr, true, lambda);
    mygen.generate();

    time(&end);

    unloader.unload("../MyDiploma/mesh_files/core_tests_9.msh", *grid_ptr);


    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed
              << time_taken << std::setprecision(5) << " sec" << std::endl;

    return 0;
}
