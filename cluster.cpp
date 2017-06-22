//
// Created by Tomev on 22.06.2017.
//

#include <c++/clocale>
#include "cluster.h"

cluster::cluster(int index) : index(index)
{
  this->object = NULL;
}

cluster::cluster(int index, sample *object) : index(index), object(object)
{

}

bool cluster::representsObject()
{
  return object != NULL;
}

long cluster::getClustersIndex() {
  return index;
}
