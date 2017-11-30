#ifndef K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H

#include "../../attributesDistanceMeasure.h"

class smdCategoricalAttributesDistanceMeasure : public attributesDistanceMeasure
{
  public:
    double countAttributesDistance(std::string firstAttributeValue, std::string secondAttributeValue);
};


#endif //K_MEDOIDALGORITHM_SMCCATEGORICALATTRIBUTESDISTANCEMEASURE_H
