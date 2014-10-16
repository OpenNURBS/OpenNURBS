/*
 * File:   gCurve.hpp
 *   a NURBS curve object in 3D real-space, with a global index
 *
 * Author: Ryan Molecke, Ph.D.
 *
 * Created on September 6, 2014, 6:50 AM
 * GNU puble license.txt file (Gnu Public License version 2.0)
 * MUST accompany this or any derivative software
 *
 * geometric model curve header file
*/

#include <vector>
#include <cstdint>
#include <memory>
#include <gPoint.hpp>

using namespace std;

template <typename T>
class gCurve {
private:
  // each curve owns a unique pointer to a vector of shared_ptrs to control points
  unique_ptr<vector<shared_ptr<gPoint<T>>>> controlPoints; // NURBS curve control points
  // each curve owns a unique pointer to vectors of knot and weight values (doubles or floats probably)
  unique_ptr<vector<T>> knotVector; // NURBS curve knot vector (must be sequentially non-decreasing)
  unique_ptr<vector<T>> knotWeights; // NURBS curve knot point weights (default is all weights = 1)

public:
  gCurve(vector<shared_ptr<gPoint<T>>> &controlPoints, vector<T> &knotVector);
  gCurve(vector<shared_ptr<gPoint<T>>> &controlPoints, vector<T> &knotVector, vector<T> &knotWeights);
  // the instantiators expect unique_ptrs to vectors,
  // they take control of the address pointer and memory, using a move operation with no copying

  // control point accessors (deep copy for the get operation)
  int getControlPoints(vector<shared_ptr<gPoint<T>>> &copyCP);
  int setControlPoints(vector<shared_ptr<gPoint<T>>> &newCP);

  // knot vector accessors
  int getKnotVector(vector<T> &copyKnotVector );
  int setKnotVector(vector<T> &newKnotVector);

  // knot weight accessors
  int getKnotWeights(vector<T> &copyknotWeights);
  int setKnotWeights(vector<T> &newKnotWeights);

  ~gCurve()=delete;
};

// for templated classes, the function defs need to stay in .h or .hpp included files...

template <typename T>
gCurve<T>::gCurve(vector<shared_ptr<gPoint<T>>> &controlPoints, vector<T> &knotVector) {

};

template <typename T>
gCurve<T>::gCurve(vector<shared_ptr<gPoint<T>>> &controlPoints, vector<T> &knotVector, vector<T> &knotWeights) {

};
// the instantiators expect unique_ptrs to vectors,
// they take control of the address pointer and memory, using a move operation with no copying

// control point accessors (deep copy for the get operation)

template <typename T>
int gCurve<T>::getControlPoints(vector<shared_ptr<gPoint<T>>> &copyCP) {

}

template <typename T>
int gCurve<T>::setControlPoints(vector<shared_ptr<gPoint<T>>> &newCP) {

}

// knot vector accessors

template <typename T>
int gCurve<T>::getKnotVector(vector<T> &copyKnotVector) {

}

template <typename T>
int gCurve<T>::setKnotVector(vector<T> &newKnotVector) {

}

// knot weight accessors

template <typename T>
int gCurve<T>::getKnotWeights(vector<T> &copyknotWeights) {

}

template <typename T>
int gCurve<T>::setKnotWeights(vector<T> &newKnotWeights) {

}

