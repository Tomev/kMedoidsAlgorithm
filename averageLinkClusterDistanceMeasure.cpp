#include "averageLinkClusterDistanceMeasure.h"

#include <iostream>

averageLinkClusterDistanceMeasure::averageLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double averageLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  vector<sample*> firstClusterObjects, secondClusterObjects;

  // Get samples from clusters
  cluster1->getObjects(&firstClusterObjects);
  cluster2->getObjects(&secondClusterObjects);

  double result = countSumOfClustersObjectsDistances(&firstClusterObjects, &secondClusterObjects);
  result /= firstClusterObjects.size() * secondClusterObjects.size();

  return result;
}

double averageLinkClusterDistanceMeasure::countSumOfClustersObjectsDistances(
  vector<sample *> *firstClusterObjects, vector<sample *> *secondClusterObjects)
{
  // Ensure that distance is normalized to [0,1]
  double sum = 0, distance;

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

      if(distance < 0)
      {
        cout << "Distance < 0";
        continue;
      }

      sum += distance;
    }
  }

  return sum;
}
