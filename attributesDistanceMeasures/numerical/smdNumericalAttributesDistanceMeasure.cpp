#include "smdNumericalAttributesDistanceMeasure.h"

double smdNumericalAttributesDistanceMeasure::countAttributesDistance(
  std::string firstAttributeValue, std::string secondAttributeValue)
{
  // Return 0 if they're identical.
  if(firstAttributeValue == secondAttributeValue) return 0;

  // Return 1 otherwise.
  return 1;
}
