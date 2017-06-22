//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_GOWERSDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_GOWERSDISTANCEMEASURE_H

#include "objectsDistanceMeasure.h"

class gowersDistanceMeasure : public objectsDistanceMeasure
{
  double countObjectsDistance(sample* s1, sample* s2);

};


#endif //K_MEDOIDALGORITHM_GOWERSDISTANCEMEASURE_H
