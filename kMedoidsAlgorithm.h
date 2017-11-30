#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm/distanceBasedGroupingAlgorithm.h"
#include "objectsDistanceMeasure.h"
#include "clustersDistanceMeasure.h"

#include "unordered_map"

enum medoidsFindingStrategy
{
  OPTIMAL = 0,
  RANDOM = 1,
  RANDOM_ACCORDING_TO_DISTANCE = 2
};

class kMedoidsAlgorithm : public distanceBasedGroupingAlgorithm
{
  public:

    kMedoidsAlgorithm(  int numberOfMedoids,
                        std::shared_ptr<clustersDistanceMeasure> clusDistanceMeasure,
                        int medoidsFindingStrategy);

    void groupObjects(std::vector<std::shared_ptr<sample>>* objects,
                      std::vector<std::shared_ptr<cluster>>* target);

    void groupClusters(std::vector<std::shared_ptr<cluster>>* clusters,
                       std::vector<std::shared_ptr<cluster>>* target);

    void setMedoids(std::vector<std::shared_ptr<cluster>>* newMedoids);

    std::vector<std::shared_ptr<cluster> > getMedoids(std::vector<std::shared_ptr<sample> > *objects);

    void generateClusteringFromMedoids(std::vector<std::shared_ptr<sample> > *objects,
                                       std::vector<std::shared_ptr<cluster>>* target);

  protected:

    unsigned int  numberOfMedoids = 1;
    int           medoidsFindingStrategy = OPTIMAL;

    std::vector<std::shared_ptr<cluster>> clusters;
    std::vector<std::shared_ptr<cluster>> medoids;

    std::unordered_map<std::string, double> similarityData;

    bool canGroupingBePerformed(std::vector<std::shared_ptr<sample> > *objects);
    void clusterObjects(std::vector<std::shared_ptr<sample>> *objects);
    int performGrouping(std::vector<std::shared_ptr<cluster>>* target);
      int gatherSimilarityData();
      void findOptimalMedoids();
        void selectRandomMedoids();
        int selectRandomMedoidsAccordingToDistance();
          int addNewMedoidToVector(int medoidIndex);
          int addNewMedoidAccordingToDistance(std::vector<int>* nonMedoidIndexes);
            int fillWeights(std::vector<double> *weights,
                            std::vector<int> *nonMedoidsIndexes);
            int fillProbabilitiesFromWeights(std::vector<double> *weights,
                                             std::vector<double> *probabilities);
        double countCost(std::vector<std::shared_ptr<cluster>> *potentialMedoids);
          bool isMedoid(cluster *c,
                        std::vector<std::shared_ptr<cluster>> *medoids);
          int findClosestMedoidIndex(cluster *c,
                                     std::vector<std::shared_ptr<cluster>>* potentialMedoids);
          double getClustersSimilarity(cluster *c1, cluster *c2);
        void findPotentialBestMedoidConfiguration(std::vector<std::shared_ptr<cluster>> *potentialBestMedoids,
                                                  double minCost);
      void createClustersFromMedoids(std::vector<std::shared_ptr<cluster>>* target);

      unsigned int setMedoidInWeightedCluster(std::shared_ptr<cluster> clus);
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
