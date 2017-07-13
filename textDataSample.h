//
// Created by Tomev on 13.06.2017.
//

#ifndef MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H
#define MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H

#include <string>
#include <iostream>
#include <unordered_map>

#include "sample.h"

using namespace std;

class textDataSample : public sample
{
  public:
    unordered_map<string, string> attributesValues;
    void print();
};


#endif //MEDOIDSTORINGALGORITHM_TEXTDATASAMPLE_H
