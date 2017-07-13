#ifndef K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H

#include <unordered_map>

#include "numericalAttributeData.h"
#include "numericalAttributesDistanceMeasure.h"

class gowersNumericalAttributesDistanceMeasure : numericalAttributesDistanceMeasure
{
    gowersNumericalAttributesDistanceMeasure(unordered_map<string, attributeData*> *attributesData);

    double countNumericalAttributesDistance(double firstAttributeValue, double secondAttributeValue);

  private:

    unordered_map<string, numericalAttributeData*> numericalAttributesData;
};


#endif //K_MEDOIDALGORITHM_GOWERSNUMERICALATTRIBUTESDISTANCEMEASURE_H
