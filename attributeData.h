#ifndef K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_ATTRIBUTEDATA_H

#include <string>

class attributeData
{
  public:

    std::string getName() { return name; }
    virtual std::string getType() = 0;

  protected:

    std::string name;

};


#endif //K_MEDOIDALGORITHM_ATTRIBUTEDATA_H
