#include <cmath>
#include "gowersNumericalAttributesDistanceMeasure.h"

gowersNumericalAttributesDistanceMeasure::gowersNumericalAttributesDistanceMeasure(
  unordered_map<string, attributeData *> *attributesData)
{
  // Store only numerical attributes data
  for(auto nameData : *attributesData)
  {
    if(nameData.second->getType() == "numerical")
      numericalAttributesData[nameData.first] = static_cast<numericalAttributeData*>(nameData.second);
  }
}

double gowersNumericalAttributesDistanceMeasure::countNumericalAttributesDistance
  (double firstAttributeValue, double secondAttributeValue)
{
  // Check if minimal and maximal values for this attribute are equal. If so distance is 0.
  if(numericalAttributesData.at(currentAttributeName)->getMinMaxDifference() <= 1e-5) return 0;

  // Otherwise count and return Gowers distance
  double result = fabs(firstAttributeValue - secondAttributeValue);
  result /= numericalAttributesData.at(currentAttributeName)->getMinMaxDifference();

  return result;
}
