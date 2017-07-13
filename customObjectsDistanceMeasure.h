#ifndef K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H



#include "objectsDistanceMeasure.h"

class customObjectsDistanceMeasure : public objectsDistanceMeasure
{
  customObjectsDistanceMeasure(
    attributesDistanceMeasure *categoricalAttributesDistanceMeasure,
    attributesDistanceMeasure *numericalAttributesDistanceMeasure);

  double countObjectsDistance(sample* sample1, sample* sample2);

  protected:

    void findCommonAttributes(sample* sample1, sample* sample2);
};


#endif //K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H
