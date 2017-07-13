#ifndef K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H

#include "attributeData.h"

class categoricalAttributeData : public attributeData
{
  public:

    categoricalAttributeData(string name);

    string getType();
    string getName();

  protected:

    string name;

};


#endif //K_MEDOIDALGORITHM_CATEGORICALATTRIBUTEDATA_H
