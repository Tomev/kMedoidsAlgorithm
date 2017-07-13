#include "smcCategoricalAttributesDistanceMeasure.h"

double smcCategoricalAttributesDistanceMeasure::countCategoricalAttributesDistance
  (string firstAttributeValue, string secondAttributeValue)
{
  if (firstAttributeValue == secondAttributeValue) return 0;

  return 1;
}
