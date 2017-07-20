#include "smdNumericalAttributesDistanceMeasure.h"

double smdNumericalAttributesDistanceMeasure::countAttributesDistance(
  string firstAttributeValue, string secondAttributeValue)
{
  // Return 0 if they're identical.
  if(firstAttributeValue == secondAttributeValue) return 0;

  // Return 1 otherwise.
  return 1;
}
