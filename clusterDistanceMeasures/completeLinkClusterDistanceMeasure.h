#ifndef K_MEDOIDALGORITHM_COMPLETELINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_COMPLETELINKCLUSTERDISTANCEMEASURE_H

#include "../clustersDistanceMeasure.h"

class completeLinkClusterDistanceMeasure: public clustersDistanceMeasure
{
public:

  completeLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

  double countClustersDistance(cluster *cluster1, cluster *cluster2);

protected:

  double findHighestDistance(vector<sample*> *firstClusterObjects, vector<sample*> *secondClusterObjects);

};


#endif //K_MEDOIDALGORITHM_COMPLETELINKCLUSTERDISTANCEMEASURE_H
