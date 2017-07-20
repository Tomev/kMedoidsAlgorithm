#ifndef K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H

#include <vector>

#include "groupingAlgorithm/sample.h"
#include "attributesDistanceMeasure.h"
#include "attributeData.h"

class objectsDistanceMeasure
{
  public:

    virtual double countObjectsDistance(sample* sample1, sample* sample2) = 0;

  protected:

    unordered_map<string, attributeData*>* attributesData;

    attributesDistanceMeasure* categoricalAttributesDistanceMeasure;
    attributesDistanceMeasure* numericalAttributesDistanceMeasure;

    vector<string> commonAttributes;

    virtual void findCommonAttributes(sample* s1, sample* s2) = 0;
};


#endif //K_MEDOIDALGORITHM_INTERCLUSTERDISTANCEMEASURE_H
