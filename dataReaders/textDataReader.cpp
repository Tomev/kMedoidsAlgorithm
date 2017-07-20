//
// Created by Tomev on 29.05.2017.
//

#include <c++/iostream>
#include <sstream>

#include "textDataReader.h"
#include "../numericalAttributeData.h"
#include "../categoricalAttributeData.h"

textDataReader::textDataReader(std::ifstream *sourceFile) : sourceFile(sourceFile) {}

void textDataReader::getNextRawDatum(void *target)
{
  // If file is opened
  if(sourceFile->is_open())
  {
    if(hasMoreData())
    {
      std::string *line = static_cast<std::string *>(target);
      std::getline(*sourceFile, *line);
    }
  }
  else
  {
    // If not then return error
    std::cout << "Couldn't read file.\n";
  }
}

void textDataReader::gatherAttributesData(unordered_map<string, attributeData*> *attributesData)
{
  // This only works for .arff files. Not tested for others.
  string line;

  attributesOrder = new vector<string>();

  if(attributesData != NULL)
  {
    // While line doesn't start with @attribute
    while (line.find("@attribute")) getNextRawDatum(&line);

    // While line starts with @attribute
    while (!line.find("@attribute")) {
      istringstream ss(line);

      string type;
      string name;

      // Find name and type of attribute

      getline(ss, name, ' ');
      getline(ss, name, ' ');
      getline(ss, type, ' ');

      // Append attribute to proper place
      if (type.find("numeric") == 0) (*attributesData)[name] = new numericalAttributeData(name);
      else (*attributesData)[name] = new categoricalAttributeData(name);

      attributesOrder->push_back(name);

      getNextRawDatum(&line);
    }
  }

  // If pointer was null, then only prepare for data reading.

  while(line.find("@data")) getNextRawDatum(&line);
}

bool textDataReader::hasMoreData()
{
  return !sourceFile->eof();
}

vector<string> *textDataReader::getAttributesOrder() {
  return this->attributesOrder;
}


