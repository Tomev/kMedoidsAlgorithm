//
// Created by Tomev on 12.07.2017.
//

#include "categoricalAttributeData.h"

categoricalAttributeData::categoricalAttributeData(std::string name) : name(name) {}

std::string categoricalAttributeData::getType()
{
  return "categorical";
}

std::string categoricalAttributeData::getName()
{
  return attributeData::getName();
}
