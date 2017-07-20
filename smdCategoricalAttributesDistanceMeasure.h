#ifndef K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H

#include "attributesDistanceMeasure.h"

class smdCategoricalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  double countAttributesDistance(string firstAttributeValue, string secondAttributeValue);
};


#endif //K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H
