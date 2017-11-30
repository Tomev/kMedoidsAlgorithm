#include "completeLinkClusterDistanceMeasure.h"

#include <iostream>

completeLinkClusterDistanceMeasure::completeLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double completeLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  std::vector<std::shared_ptr<sample>> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters
  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  //std::cout << "Cluster distance measure: Got objects.\n";

  double result = findHighestDistance(&firstClusterObjects, &secondClusterObjects);

  return result;
}

double completeLinkClusterDistanceMeasure::findHighestDistance(
  std::vector<std::shared_ptr<sample>> *firstClusterObjects, std::vector<std::shared_ptr<sample>> *secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double maxDistance = 0, distance;

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

      if(distance < 0) std::cout << "Distance < 0";

      if(distance > maxDistance) maxDistance = distance;
    }
  }

  return maxDistance;
}
