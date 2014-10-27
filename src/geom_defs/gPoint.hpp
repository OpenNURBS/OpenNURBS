/*
 * File:   gPoint.hpp
 *   a point object in 3D real-space, with a global index
 *
 * Author: Ryan Molecke, Ph.D.
 *
 * Created on September 6, 2014, 6:50 AM
 * GNU puble license.txt file (Gnu Public License version 2.0)
 * MUST accompany this or any derivative software
 *
 * geometric model point header file
*/

#include <vector>
#include <cstdint>
#include <memory>
using namespace std;

template <typename T>
class gPoint {
private:
  unique_ptr<vector<T>> coords; // x, y, z coords (doubles or floats probably)
  int64_t gIndex;        // all points have a global index

public:
  gPoint(vector<T> &pointSet, int64_t ind);
  // on the SET operation, we just grab the unique_ptr<vector<T>>
  int setCoords(unique_ptr<vector<T>> &pointSet);
  int setIndex(int64_t ind) { return (gIndex = ind); };
  int64_t getIndex() { return gIndex; };
  // deep copy of the coords on the GET operation, not just move the unique_ptr
  void getCoords(vector<T> &pointSet); // get all the coords from a point
  int getDim() { return coords->size(); };
  T coord(int index) { return coords->at(index); }; // allows access to read ind. coords by index
  int64_t ind() { return gIndex; }; // allows access to read global index
};

// for templated classes, the function defs need to stay in .h or .hpp included files...

template <typename T>
gPoint<T>::gPoint(vector<T> &pointSet, int64_t ind) {
    coords = unique_ptr<vector<T>>(new vector<T>( pointSet.size() )); // deep copy coords on instantiation
    int i=0;
    try {
        for (auto it : pointSet) {
            coords->at(i)=it;
            i++;
        }
    } catch( const std::exception& e ) { // reference to the base of a polymorphic object
        std::cout << "  " << e.what() << " error.\n";
        // should have a log output versus screen output here
        cerr << " couldn't instantiate gPoint<T>::gPoint(vector<T>& coord, int64_t ind)\n";
    }
    gIndex=ind; // set the globalID of the point at instantiation
}

template <typename T>
int gPoint<T>::setCoords(unique_ptr<vector<T>> &pointSet) { // to set coords, pass in a unique_ptr<vector<T>>
    // copy a vector of doubles into coord
    coords = move(pointSet);
    return 1;
}

template <typename T>
void gPoint<T>::getCoords(vector<T> &pointSet) { // we deep copy on get, to save our local unique_ptr coords
    // get vector of doubles from coord
    pointSet.clear();
    pointSet.resize(coords->size());
    try {
        for (int i = 0; i < coords->size(); i++) {
            pointSet.at(i)=coords->at(i);
        }
    } catch( const std::exception& e ) { // reference to the base of a polymorphic object
        std::cout << "  " << e.what() << " error.\n";
        // should have a log output versus screen output here
        cerr << "  couldn't get coords in gPoint::getCoord()\n";
    }
}
