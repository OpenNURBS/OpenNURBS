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
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
class gCurve {
private:
  // each curve owns a unique pointer to a vector of shared_ptrs to control points
  unique_ptr<vector<shared_ptr<gPoint<T>>>> controlPoints; // NURBS curve control points
  // each curve owns a unique pointer to vectors of knot and weight values (doubles or floats probably)
  unique_ptr<vector<T>> knotVector;  // NURBS curve knot vector (must be sequentially non-decreasing)
  unique_ptr<vector<T>> knotWeights; // NURBS curve knot point weights (default is all weights = 1)
  int degree;                        // degree of curve is one less than order of curve

  int getKnotSpan(T);  // find the knot span index that a given parameter lies within

public:
  gCurve(vector<shared_ptr<gPoint<T>>> &cPoints, vector<T> &kVector);
  gCurve(vector<shared_ptr<gPoint<T>>> &cPoints, vector<T> &kVector, vector<T> &kWeights);
  // the instantiators expect unique_ptrs to vectors,
  // they take control of the address pointer and memory, using a move operation with no copying

  // to retrieve a points along the curve, given a number of curve divisions
  int getPoints(vector<shared_ptr<gPoint<T>>> &points, int divisions);

  // to retrieve a single point, given a NURBS curve parameter
  int getPoint(gPoint<T> &point, T u);

  // control point accessors (deep copy for the get operation)
  int getControlPoints(vector<shared_ptr<gPoint<T>>> &copyCP);
  int setControlPoints(vector<shared_ptr<gPoint<T>>> &newCP);

  // knot vector accessors
  int getKnotVector(vector<T> &copyKnotVector );
  int setKnotVector(vector<T> &newKnotVector);

  // knot weight accessors
  int getKnotWeights(vector<T> &copyknotWeights);
  int setKnotWeights(vector<T> &newKnotWeights);

  int basisFuns(T u, vector<T> &returnBasis);
  int basisFuns(T u, vector<T> &returnBasis, int knotSpan);

};

// for templated classes, the function defs need to stay in .h or .hpp included files...

template <typename T>
gCurve<T>::gCurve(vector<shared_ptr<gPoint<T>>> &cPoints, vector<T> &kVector) {
  unique_ptr<vector<shared_ptr<gPoint<T>>>> controlPoints(new vector<shared_ptr<gPoint<T>>>(cPoints.size()));
  int i = 0;
  for( auto it : cPoints){
    controlPoints->at(i) = it;
    i++;
  }
  i=0;
  unique_ptr<vector<T>> knotVector(new vector<T>(kVector.size()));
  for( auto it : kVector){
    knotVector->at(i) = it;
    i++;
  }
  // default case, all knot weights are 1, indicated by knotWeights being a null_ptr
  knotWeights = nullptr;
  degree = knotVector->size() - controlPoints->size() -1; // degree of curve is one less than order of curve
};

template <typename T>
gCurve<T>::gCurve(vector<shared_ptr<gPoint<T>>> &cPoints, vector<T> &kVector, vector<T> &kWeights) {
  unique_ptr<vector<shared_ptr<gPoint<T>>>> controlPoints(new vector<shared_ptr<gPoint<T>>>(cPoints.size()));
  int i = 0;
  for( auto it : cPoints){
    controlPoints->at(i) = it;
    i++;
  }
  i=0;
  unique_ptr<vector<T>> knotVector(new vector<T>(kVector.size()));
  for( auto it : kVector){
    knotVector->at(i) = it;
    i++;
  }
  i=0;
  unique_ptr<vector<T>> knotWeights(new vector<T>(kWeights.size()));
  for( auto it : kWeights){
    knotWeights->at(i) = it;
    i++;
  }
  degree = knotVector->size() - controlPoints->size() -1;
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

template <typename T>
int gCurve<T>::getKnotSpan(T u){ // alg A2.1 from p.68 of "The NURBS Book"
  int n = controlPoints->size()-1;
  int low, mid, hi;
  low = degree;
  hi = n+1;
  mid = floor((low+hi)/2);
  // first, special case returning n
  if(u == knotVector[hi]) return (n);
  // a binary search to find the knotspan index
  while(u < knotVector[mid] || u >= knotVector[mid+1]){
    if(u < knotVector[mid]) {
      hi = mid;
    } else {
      low = mid;
    }
    mid = floor((low+hi)/2);
  }
  return mid;
}

// sets values in a vector of (n+1) basis function values (floats or doubles usually)
// note: (n+1) is also the number of control points
// note: this is alg A2.2 from page 70 of "The NURBS Book"
template <typename T>
int gCurve<T>::basisFuns(T u, vector<T> &returnBasis, int knotSpan){
   int n = controlPoints->size()-1;
   try {
     int i = knotSpan;
     returnBasis->clear();
     returnBasis->resize(n+1);
     returnBasis[0]=1;
     unique_ptr<vector<T>> left(new vector<T>(n+1));
     unique_ptr<vector<T>> right(new vector<T>(n+1));
     for(int j=1; j<degree; j++){
       left[j] = u - knotVector[i+1-j];
       right[j] = knotVector[i+j] - u;
       T saved = 0.0;
       for (int r = 0; r<j; r++){
         T temp = returnBasis[r]/(right[r+1]-left[j-r]);
         returnBasis[r] = saved + right[r+1]*temp;
         saved = left[j-r]*temp;
       }
       returnBasis[j] = saved;
     }
     return 1;
   } catch (...) {
     return 0;
   }
}

template <typename T>
int basisFuns(T u, vector<T> &returnBasis){
  try {
    int i = getKnotSpan(u);
    return basisFuns(u, returnBasis, i);
  } catch (...) {
    return 0;
  }
}

// to retrieve a vector of points along a curve, given a number of curve divisions
// the returned vector includes both endpoints, so a vector of 101 length for 100 divisions
template <typename T>
int gCurve<T>::getPoints(vector<shared_ptr<gPoint<T>>> &points, int divisions){
  points->clear();
  points->resize(divisions);
  auto minmax = std::minmax_element(knotVector.begin(), knotVector.end());
  T stepSize = (knotVector[minmax.second()] - knotVector[minmax.first()])/divisions;
  int vecInd = 0;
  for(T i; i <= knotVector[minmax.second()]; i += stepSize){
    if(vecInd > points->size()){
      break;
    }
    auto shared_point = make_shared<gPoint<double>>;
    if(getPoint(shared_point,i)){
      points[vecInd] = shared_point; // copies a shared_ptr to a new point into the return vector
    } else {
      return 0;
    }
  }
  return 1;
}

// to retrieve a single point along a curve, given a NURBS curve parameter
template <typename T>
int gCurve<T>::getPoint(gPoint<T> &point, T u){
  try {
    int span = getKnotSpan(u);
    int myDim = point->getDim();
    unique_ptr<vector<T>> Basis(new vector<T>);
    basisFuns(u,Basis,span);
    unique_ptr<vector<T>> myCoords(new vector<T>(myDim));
    for(int dim=0; dim<myDim; dim++){ // initialize coords vector to zeroes
      myCoords[dim] = 0;
    }
    for(int i=0; i < degree; i++){
      for(int dim=0; dim<myDim; dim++){ // calculate point coords from basis functions
        myCoords[dim] += Basis[i]*controlPoints[span-degree+i]->coord(dim);
      }
    }
    point->setCoords(myCoords);
    return 1;
  } catch (...) {
    return 0;
  }
}
