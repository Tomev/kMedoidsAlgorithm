#ifndef K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H

#include "objectsDistanceMeasure.h"

class customObjectsDistanceMeasure : public objectsDistanceMeasure
{
  public:

    customObjectsDistanceMeasure(
      attributesDistanceMeasure *categoricalAttributesDistanceMeasure,
      attributesDistanceMeasure *numericalAttributesDistanceMeasure,
      std::unordered_map<std::string, attributeData*> *attributesData);

    double countObjectsDistance(sample* sample1, sample* sample2);

  protected:

    void findCommonAttributes(sample* sample1, sample* sample2);
};


#endif //K_MEDOIDALGORITHM_CUSTOMOBJECTSDISTANCEMEASURE_H
