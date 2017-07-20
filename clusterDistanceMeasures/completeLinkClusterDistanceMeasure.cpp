#include "completeLinkClusterDistanceMeasure.h"

#include <iostream>

completeLinkClusterDistanceMeasure::completeLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double completeLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  vector<sample*> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters
  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  double result = findHighestDistance(&firstClusterObjects, &secondClusterObjects);

  return result;
}

double completeLinkClusterDistanceMeasure::findHighestDistance(
  vector<sample *> *firstClusterObjects, vector<sample *> *secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double maxDistance = 0, distance;

  for(sample* firstClusterObject : *firstClusterObjects)
  {
    for(sample* secondClusterObject : *secondClusterObjects)
    {
      distance = objDistanceMeasure->countObjectsDistance(firstClusterObject, secondClusterObject);

      if(distance > 1)
      {
        cout << "Distance > 1.";
        continue;
      }

      if(distance < 0) cout << "Distance < 0";

      if(distance > maxDistance) maxDistance = distance;
    }
  }

  return maxDistance;
}
