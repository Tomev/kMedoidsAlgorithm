#include "smdCategoricalAttributesDistanceMeasure.h"

double smdCategoricalAttributesDistanceMeasure::countAttributesDistance
  (string firstAttributeValue, string secondAttributeValue)
{
  if (firstAttributeValue == secondAttributeValue) return 0;

  return 1;
}
