#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm/distanceBasedGroupingAlgorithm.h"
#include "objectsDistanceMeasure.h"
#include "clustersDistanceMeasure.h"

enum medoidsFindingStrategy
{
  OPTIMAL = 0,
  RANDOM = 1,
  RANDOM_ACCORDING_TO_DISTANCE = 2
};

class kMedoidsAlgorithm : public distanceBasedGroupingAlgorithm
{
  public:

    kMedoidsAlgorithm(int numberOfMedoids, clustersDistanceMeasure* clusDistanceMeasure, int medoidsFindingStrategy);

    void groupObjects(vector<sample*>* objects, vector<cluster>* target);

    void setMedoids(vector<cluster>* newMedoids);
    vector<cluster> getMedoids(vector<sample*>* objects);

    void generateClusteringFromMedoids(vector<sample*>* objects, vector<cluster>* target);

  protected:

    int numberOfMedoids = 1,
        medoidsFindingStrategy = OPTIMAL;

    vector<cluster> clusters;
    vector<cluster> medoids;

    unordered_map<string, double> similarityData;

    bool canGroupingBePerformed(std::vector<sample*>* objects);
    void clusterObjects(std::vector<sample*> *objects);
    int gatherSimilarityData();
    void findOptimalMedoids();
      void selectRandomMedoids();
      int selectRandomMedoidsAccordingToDistance();
        int addNewMedoidToVector(int medoidIndex);
        int addNewMedoidAccordingToDistance(vector<int>* nonMedoidIndexes);
          int fillWeights(vector<double> *weights, vector<int> *nonMedoidsIndexes);
          int fillProbabilitiesFromWeights(vector<double> *weights, vector<double> *probabilities);
      double countCost(vector<cluster> *potentialMedoids);
        bool isMedoid(cluster* c, vector<cluster> *medoids);
        int findClosestMedoidIndex(cluster *c, vector<cluster>* potentialMedoids);
        double getClustersSimilarity(cluster *c1, cluster *c2);
      void findPotentialBestMedoidConfiguration(vector<cluster> *potentialBestMedoids, double minCost);
    void createClustersFromMedoids(vector<cluster>* target);
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
