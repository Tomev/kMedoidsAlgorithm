#include <iostream>
#include "singleLinkClusterDistanceMeasure.h"

singleLinkClusterDistanceMeasure::singleLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double singleLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  vector<sample*> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters

  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  double result = findLowestDistance(&firstClusterObjects, &secondClusterObjects);

  return result;
}

double singleLinkClusterDistanceMeasure::findLowestDistance(
  vector<sample *>* firstClusterObjects, vector<sample *>* secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double minDistance = 1, distance;

  for(sample* firstClusterObject : *firstClusterObjects)
  {
    for(sample* secondClusterObject : *secondClusterObjects)
    {
      distance = objDistanceMeasure->countObjectsDistance(firstClusterObject, secondClusterObject);

      if(distance > 1) cout << "Distance > 1.";

      if(distance < 0)
      {
        cout << "Distance < 0";
        continue;
      }

      if(distance < minDistance) minDistance = distance;
    }
  }

  return minDistance;
}


