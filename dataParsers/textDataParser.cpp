//
// Created by Tomev on 29.05.2017.
//

#include "textDataParser.h"
#include "../numericalAttributeData.h"

#include <sstream>

textDataParser::textDataParser(unordered_map<string, attributeData*> *attributesData) :
attributesData(attributesData)
{
  this->buffer = new std::string();
}

void textDataParser::parseData(void *target)
{
  std::string *line = static_cast<std::string*>(this->buffer);
  textDataSample *sampleHolder = static_cast<textDataSample*>(target);

  std::istringstream ss(*line);
  std::string value;

  sampleHolder->attributesValues.clear();

  int attributeIndex = 0;

  while(getline(ss, value, ',')) sampleHolder->attributesValues[attributesOrder->at(attributeIndex++)] = value;

  updateAttributesData(sampleHolder);
}

void textDataParser::updateAttributesData(textDataSample *newSample)
{
  for(auto kv : newSample->attributesValues)
  {
    // For now only consider numerical data
    if(attributesData->at(kv.first)->getType() == "numerical")
    {
      numericalAttributeData *numAttribute = static_cast<numericalAttributeData*>(attributesData->at(kv.first));
      double value = stod(kv.second);

      numAttribute->setMaximalValue(value);
      numAttribute->setMinimalValue(value);

      numAttribute->attributeOccured();
    }
  }
}

int textDataParser::addDatumToContainer(std::vector<sample*> *container)
{
  container->push_back(new textDataSample());

  return container->size()-1;
}

void textDataParser::writeDatumOnPosition(std::vector<sample*> *container, int position)
{
  parseData(container->at(position));
}

void textDataParser::setAttributesOrder(vector<string> *attributesOrder)
{
  this->attributesOrder = attributesOrder;
}


