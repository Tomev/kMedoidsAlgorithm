#include "smcCategoricalAttributesDistanceMeasure.h"

double smcCategoricalAttributesDistanceMeasure::countAttributesDistance
  (string firstAttributeValue, string secondAttributeValue)
{
  if (firstAttributeValue == secondAttributeValue) return 0;

  return 1;
}
