#include "smdCategoricalAttributesDistanceMeasure.h"

double smdCategoricalAttributesDistanceMeasure::countAttributesDistance
  (std::string firstAttributeValue, std::string secondAttributeValue)
{
  if (firstAttributeValue == secondAttributeValue) return 0;

  return 1;
}
