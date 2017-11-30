#include "averageLinkClusterDistanceMeasure.h"

#include <iostream>

averageLinkClusterDistanceMeasure::averageLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double averageLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  std::vector<std::shared_ptr<sample>> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters
  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  double result = countSumOfClustersObjectsDistances(&firstClusterObjects, &secondClusterObjects);
  result /= firstClusterObjects.size() * secondClusterObjects.size();

  return result;
}

double averageLinkClusterDistanceMeasure::countSumOfClustersObjectsDistances(
  std::vector<std::shared_ptr<sample>> *firstClusterObjects, std::vector<std::shared_ptr<sample>> *secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double sum = 0, distance;

  for(std::shared_ptr<sample> firstClusterObject : *firstClusterObjects)
  {
    for(std::shared_ptr<sample> secondClusterObject : *secondClusterObjects)
    {
      distance = objDistanceMeasure->countObjectsDistance(firstClusterObject.get(), secondClusterObject.get());

      if(distance > 1)
      {
        std::cout << "Distance > 1.";
        continue;
      }

      if(distance < 0)
      {
        std::cout << "Distance < 0";
        continue;
      }

      sum += distance;
    }
  }

  return sum;
}
