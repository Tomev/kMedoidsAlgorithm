#include "centroidLinkClusterDistanceMeasure.h"

centroidLinkClusterDistanceMeasure::centroidLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure)
{
  this->objDistanceMeasure = objDistanceMeasure;
}

double centroidLinkClusterDistanceMeasure::countClustersDistance(cluster *cluster1, cluster *cluster2)
{
  return objDistanceMeasure->countObjectsDistance(cluster1->getRepresentative(), cluster2->getRepresentative());
}


