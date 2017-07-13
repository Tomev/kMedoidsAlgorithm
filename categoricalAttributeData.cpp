//
// Created by Tomev on 12.07.2017.
//

#include "categoricalAttributeData.h"

categoricalAttributeData::categoricalAttributeData(string name) : name(name) {}

string categoricalAttributeData::getType()
{
  return "categorical";
}

string categoricalAttributeData::getName()
{
  return attributeData::getName();
}
