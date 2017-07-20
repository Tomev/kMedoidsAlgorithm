#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm/distanceBasedGroupingAlgorithm.h"
#include "objectsDistanceMeasure.h"
#include "clustersDistanceMeasure.h"

class kMedoidsAlgorithm : public distanceBasedGroupingAlgorithm
{
  public:

    kMedoidsAlgorithm(int numberOfMedoids, clustersDistanceMeasure* clusDistanceMeasure);
    void groupObjects(vector<sample*>* objects, vector<cluster>* target);
    void generateClustering(vector<sample*>* objects, vector<cluster>* target);

    void setMedoids(vector<cluster>* medoids);
    void generateClusteringFromMedoids(vector<sample*>* objects, vector<cluster>* target);

protected:

  protected:

    int numberOfMedoids = 1;

    vector<cluster> clusters;
    vector<cluster> medoids;

    bool canGroupingBePerformed(std::vector<sample*>* objects);
    void clusterObjects(std::vector<sample*> *objects);
    void selectRandomMedoids();
    double countCost(vector<cluster> *potentialMedoids);
      bool isMedoid(cluster* c, vector<cluster> *medoids);
      int findClosestMedoidIndex(cluster *c, vector<cluster>* potentialMedoids);
    void findPotentialBestMedoidConfiguration(vector<cluster> *potentialBestMedoids, double minCost);
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
