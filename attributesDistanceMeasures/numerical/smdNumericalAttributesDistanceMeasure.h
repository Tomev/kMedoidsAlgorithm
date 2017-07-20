#ifndef K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H

#include "../../attributesDistanceMeasure.h"

class smdNumericalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  double countAttributesDistance(string firstAttributeValue, string secondAttributeValue);
};

#endif //K_MEDOIDALGORITHM_SMDNUMERICALATTRIBUTESDISTANCEMEASURE_H
