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

int main(int argc, char **argv)
{

    std::cout
            << "¸.·´¯`·.¸¸.·´ OpenNURBS Demo Program `·.¸¸.·´¯`·.¸\n";

    // set up a few NURBS curves and make a surface, using object primitives

    int64_t index = 0; // right now points just have a single global int64_t index

    // set up vectors of doubles (to hold some starting coords)
    // an example set of 7 points we will use as control points
    vector<double> coords0 = {0.0, 0.0, 0.0};
    vector<double> coords1 = {0.0, 1.0, 0.5};
    vector<double> coords2 = {0.0, 2.0, 1.0};
    vector<double> coords3 = {1.0, 1.0, 1.5};
    vector<double> coords4 = {2.0, 0.0, 2.0};
    vector<double> coords5 = {1.0, 0.0, 2.5};
    vector<double> coords6 = {0.0, 0.0, 3.0};

    // we will instantiate shared_ptr for 7 point objects
    auto point0 = make_shared<gPoint<double>>(coords0, index++);
    auto point1 = make_shared<gPoint<double>>(coords1, index++);
    auto point2 = make_shared<gPoint<double>>(coords2, index++);
    auto point3 = make_shared<gPoint<double>>(coords3, index++);
    auto point4 = make_shared<gPoint<double>>(coords4, index++);
    auto point5 = make_shared<gPoint<double>>(coords5, index++);
    auto point6 = make_shared<gPoint<double>>(coords6, index++);

    vector<double> getCoords0;
    //cout << " dim : " << point1->getDim() << "\n";
    //point1->getCoords(getCoords0);
    //cout << " getCoords : " << getCoords0[0] << ", " << getCoords0[1] << ", " << getCoords0[2] << "\n";

    // we make a vector of the points we want for a gCurve object
    vector<shared_ptr<gPoint<double>>> CP0
            = {point0, point1, point2, point3, point4, point5, point6};

    // we make an example knot vector here
    // this is a 'uniform' knot vector, with length (m+1)=12
    vector<double> KV0 = {0, 0, 0, 0, 0, 0.333, 0.666, 1.0, 1.0, 1.0, 1.0, 1.0};

    // the degree of this curve is p=4, the order is (p+1)=5
    // there are (n+1) = 7 basis functions, for n=m-p-1=6
    // m = # knots - 1
    // n = # points -1
    // p = degree of the curve = # knots - # points - 1
    // order of the curve = p + 1 = # points that control curve placement at a time
    // using "The NURBS Book" variable names

    // we will instantiate a shared_ptr for a curve object
    auto curve0 = make_shared<gCurve<double>>(CP0, KV0);

    vector<shared_ptr<gPoint<double>>> myPoints;
    //curve0->getControlPoints(myPoints);

    auto myPoint = make_shared<gPoint<double>>(coords0, index++);
    cout << "dim : " << myPoint->getDim() << "\n";
    curve0->getPoint(myPoint, 0.5);
    for (int i = 0; i < 3; i++)
    {
        cout << myPoint->coord(i) << " ";
    }


    /*
    vector<shared_ptr<gPoint<double>>> curve0_points;
    if (curve0->getPoints(curve0_points, 100)) { // returns 101 points along the curve, w/ endpoints
        cout << " Curve 0 instantiated with 101 points.\n";
    } else {
        cout << " Curve 0 instantiation failed!\n";
    }

     */
    return 0;
}
