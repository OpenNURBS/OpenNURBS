/*
 *    OpenNURBS Demo File
 *
 *    Shows how to:
 *      - instantiate NURBS objects as object primitives
 *      - extrude / filet / offset / deform / combine NURBS objects
 *      - NURB curve / surface shortest distance (collision) calculation
 *      - load and save as .nrb_geom geometry model files
 *      - load, export meshes
 *      - advanced mesh operations
 *         - 3D space-filling meshes
 *         - boundary layering based on offset surfaces
 *         - binary mesh format
 *         - distributed mesh formats
 */

#include <memory>
#include <iostream>
#include "../geom_defs/gCurve.hpp"

int main(int argc, char **argv) {

    std::cout
            << "¸.·´¯`·.¸¸.·´ OpenNURBS Demo Program `·.¸¸.·´¯`·.¸\n";

    // set up a few NURBS curves and make a surface

    int64_t index=0;

    // set up vectors of doubles (to hold some starting coords)
    vector<double> coords0={ 0.0, 0.0, 0.0 };

    // Model objects such as points, curves, surfaces, regions
    // should usually be declared as shared_ptr at the main run level

    // demonstration of instantiating a point object
    auto point0=make_shared<gPoint<double>>( coords0, index++ );

    // demonstation of instantiating a curve object


    return 0;
}
