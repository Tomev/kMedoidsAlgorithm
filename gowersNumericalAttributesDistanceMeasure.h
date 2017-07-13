#ifndef K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H

#include <unordered_map>

#include "numericalAttributeData.h"
#include "attributesDistanceMeasure.h"

class gowersNumericalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  public:
    gowersNumericalAttributesDistanceMeasure(unordered_map<string, attributeData*> *attributesData);

    double countAttributesDistance(string firstAttributeValue, string secondAttributeValue);

  protected:

    unordered_map<string, numericalAttributeData*> numericalAttributesData;
};


#endif //K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
