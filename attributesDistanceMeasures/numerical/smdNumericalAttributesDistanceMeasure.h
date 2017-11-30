#ifndef K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H

#include "../../attributesDistanceMeasure.h"

class smdNumericalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  double countAttributesDistance(std::string firstAttributeValue, std::string secondAttributeValue);
};

#endif //K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H
