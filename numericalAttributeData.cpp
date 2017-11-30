#include "numericalAttributeData.h"

#include <iostream>
#include <cmath>

numericalAttributeData::numericalAttributeData(std::string name) : name(name) {}

std::string numericalAttributeData::getType()
{
  return "numerical";
}

double numericalAttributeData::getMaximalValue()
{
  if(hasAttributeOccurred()) return maximalValue;
  else
  {
    std::cout << "Attribute " + name + " has not yet occured.\n";
    return -1;
  }
}

double numericalAttributeData::getMinimalValue()
{
  if(hasAttributeOccurred()) return minimalValue;
  else
  {
    std::cout << "Attribute " + name + " has not yet occured.\n";
    return -1;
  }
}

double numericalAttributeData::getMinMaxDifference()
{
  if(hasAttributeOccurred()) return fabs(maximalValue - minimalValue);
  else return -1.0;
}

void numericalAttributeData::setMaximalValue(double newMaximalValue)
{
  if(!hasAttributeOccurred()) maximalValue = newMaximalValue;
  else if(maximalValue < newMaximalValue) maximalValue = newMaximalValue;
}

void numericalAttributeData::setMinimalValue(double newMinimalValue)
{
  if(!hasAttributeOccurred()) minimalValue = newMinimalValue;
  else if(minimalValue > newMinimalValue) minimalValue = newMinimalValue;
}

bool numericalAttributeData::hasAttributeOccurred()
{
  return occurred;
}

void numericalAttributeData::attributeOccured()
{
  this->occurred = true;
}


