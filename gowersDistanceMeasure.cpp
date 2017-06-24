//
// Created by Tomev on 22.06.2017.
//

#include <c++/clocale>
#include <c++/iostream>

#include "gowersDistanceMeasure.h"

double gowersDistanceMeasure::countObjectsDistance(sample *s1, sample *s2)
{
  if(!canDistanceBeMeasured(s1, s2)) return -1;


}

bool gowersDistanceMeasure::canDistanceBeMeasured(sample *s1, sample *s2)
{
  if(s1 == NULL or s2 == NULL)
  {
    std::cout << "One of pointers is null. Cannot compute distance.\n";
    return false;
  }

  return true;
}
