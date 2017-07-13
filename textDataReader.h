/*
  Created by Tomev on 29.05.2017.

  Class meant to read txt files (in this case .arff)
  from data stream repository:

  http://www.cse.fau.edu/~xqzhu/stream.html.

*/


#ifndef RESERVOIRALGORITHM_TEXTDATAREADER_H
#define RESERVOIRALGORITHM_TEXTDATAREADER_H

#include "dataReader.h"

#include <fstream>

class textDataReader : public dataReader
{
  public:

    textDataReader(std::ifstream *sourceFile);
    void getNextRawDatum(void *target);
    void gatherAttributesData(unordered_map<string, unordered_map<string, attributeData*>> *attributesData);
    bool hasMoreData();

  private:

    std::ifstream *sourceFile;
    vector<string> *attributesOrder;
};


#endif //RESERVOIRALGORITHM_TEXTDATAREADER_H
