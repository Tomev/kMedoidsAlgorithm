#ifndef K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H

#include <vector>
#include <unordered_map>

#include "groupingAlgorithm/sample.h"
#include "attributesDistanceMeasure.h"
#include "attributeData.h"

class objectsDistanceMeasure
{
  public:

    virtual double countObjectsDistance(sample* sample1, sample* sample2) = 0;

  protected:

    std::unordered_map<std::string, attributeData*>* attributesData;

    attributesDistanceMeasure* categoricalAttributesDistanceMeasure;
    attributesDistanceMeasure* numericalAttributesDistanceMeasure;

    std::vector<std::string> commonAttributes;

    virtual void findCommonAttributes(sample* s1, sample* s2) = 0;
};


#endif //K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
