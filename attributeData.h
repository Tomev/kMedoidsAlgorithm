#ifndef K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_ATTRIBUTEDATA_H

#include "string"

using namespace std;

class attributeData
{
  public:

    string getName() { return name; }
    virtual string getType() = 0;

    void setName(string newName);

  protected:

    string name;

};


#endif //K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
