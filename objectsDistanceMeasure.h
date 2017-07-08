//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H


#include "sample.h"

#include <vector>

class objectsDistanceMeasure
{
  public:

    virtual double countObjectsDistance(sample* s1, sample* s2) = 0;

  protected:

    numericalAttributeDistanceMeasure* numDistanceMeasure;


};


#endif //K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
