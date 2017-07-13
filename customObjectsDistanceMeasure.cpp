#include <algorithm>
#include "customObjectsDistanceMeasure.h"

customObjectsDistanceMeasure::customObjectsDistanceMeasure(
  attributesDistanceMeasure *categoricalAttributesDistanceMeasure,
  attributesDistanceMeasure *numericalAttributesDistanceMeasure,
  unordered_map<string, attributeData*> *attributesData)
{
  this->categoricalAttributesDistanceMeasure = categoricalAttributesDistanceMeasure;
  this->numericalAttributesDistanceMeasure = numericalAttributesDistanceMeasure;
  this->attributesData = attributesData;
}

double customObjectsDistanceMeasure::countObjectsDistance(sample *sample1, sample *sample2)
{
  findCommonAttributes(sample1, sample2);

  // If there are no common attributes return -1.
  if(commonAttributes.size() == 0) return -1.0;

  double result = 0.0;
  attributesDistanceMeasure* currentMeasure;

  for(string attributeName : commonAttributes)
  {
    if(attributesData->at(attributeName)->getType() == "numerical")
      currentMeasure = numericalAttributesDistanceMeasure;
    else
      currentMeasure = categoricalAttributesDistanceMeasure;

    currentMeasure->setCurrentAttributeName(attributeName);

    result += currentMeasure->countAttributesDistance(
      sample1->attributesValues.at(attributeName),
      sample2->attributesValues.at(attributeName)
    );
  }

  return result;
}

void customObjectsDistanceMeasure::findCommonAttributes(sample *sample1, sample *sample2)
{
  commonAttributes.clear();

  vector<string> firstSampleAttributes, secondSampleAttributes;

  for(auto nameValue : sample1->attributesValues) firstSampleAttributes.push_back(nameValue.first);
  for(auto nameValue : sample2->attributesValues) secondSampleAttributes.push_back(nameValue.first);

  for(string attributeName : firstSampleAttributes)
  {
    if(find(secondSampleAttributes.begin(), secondSampleAttributes.end(), attributeName) != firstSampleAttributes.end())
    {
      // If both contains given attribute
      commonAttributes.push_back(attributeName);
    }
  }
}
