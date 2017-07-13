#ifndef K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_ATTRIBUTEDATA_H

#include "string"

using namespace std;

class attributeData
{
  public:

    virtual string getName() { return name; }
    virtual string getType() = 0;

  protected:

    string name;

};


#endif //K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
