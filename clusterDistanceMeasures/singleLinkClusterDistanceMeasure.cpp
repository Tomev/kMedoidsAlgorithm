#include <iostream>
#include "singleLinkClusterDistanceMeasure.h"

singleLinkClusterDistanceMeasure::singleLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double singleLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  std::vector<std::shared_ptr<sample>> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters

  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  double result = findLowestDistance(&firstClusterObjects, &secondClusterObjects);

  return result;
}

double singleLinkClusterDistanceMeasure::findLowestDistance(
  std::vector<std::shared_ptr<sample>>* firstClusterObjects, std::vector<std::shared_ptr<sample>>* secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double minDistance = 1, distance;

  for(std::shared_ptr<sample> firstClusterObject : *firstClusterObjects)
  {
    for(std::shared_ptr<sample> secondClusterObject : *secondClusterObjects)
    {
      distance = objDistanceMeasure->countObjectsDistance(firstClusterObject.get(),
                                                          secondClusterObject.get());

      if(distance > 1) std::cout << "Distance > 1.";

      if(distance < 0)
      {
        std::cout << "Distance < 0";
        continue;
      }

      if(distance < minDistance) minDistance = distance;
    }
  }

  return minDistance;
}


