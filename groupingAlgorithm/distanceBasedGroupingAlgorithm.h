#ifndef K_MEDOIDALGORITHM_DISTANCEBASEDGROUPINGALGORITHM_H
#define K_MEDOIDALGORITHM_DISTANCEBASEDGROUPINGALGORITHM_H

#include "groupingAlgorithm.h"
#include "../clustersDistanceMeasure.h"

class distanceBasedGroupingAlgorithm : public groupingAlgorithm
{
  protected:
    clustersDistanceMeasure* clusDistanceMeasure;
};

#endif //K_MEDOIDALGORITHM_DISTANCEBASEDGROUPINGALGORITHM_H
