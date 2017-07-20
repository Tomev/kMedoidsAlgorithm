#ifndef MEDOIDSTORINGALGORITHM_SAMPLE_H
#define MEDOIDSTORINGALGORITHM_SAMPLE_H

#include <string>
#include <unordered_map>

using namespace std;

class sample
{
  public:
    unordered_map<string, string> attributesValues;
    virtual void print() = 0;
};


#endif //MEDOIDSTORINGALGORITHM_SAMPLE_H
