#ifndef K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H

#include "attributeData.h"

class categoricalAttributeData : public attributeData
{
  public:

    categoricalAttributeData(std::string name);

    std::string getType();
    std::string getName();

  protected:

    std::string name;

};


#endif //K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H
