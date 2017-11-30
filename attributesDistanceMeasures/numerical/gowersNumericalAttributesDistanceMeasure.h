#ifndef K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H

#include <unordered_map>

#include "../../numericalAttributeData.h"
#include "../../attributesDistanceMeasure.h"

class gowersNumericalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  public:
    gowersNumericalAttributesDistanceMeasure(std::unordered_map<std::string, attributeData*> *attributesData);

    double countAttributesDistance(std::string firstAttributeValue, std::string secondAttributeValue);

  protected:

    std::unordered_map<std::string, numericalAttributeData*> numericalAttributesData;
};


#endif //K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
