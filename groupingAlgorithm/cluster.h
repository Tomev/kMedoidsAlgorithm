#ifndef K_MEDOIDALGORITHM_CLUSTER_H
#define K_MEDOIDALGORITHM_CLUSTER_H

#include <vector>
#include <string>
#include <memory>

#include "sample.h"

class cluster
{
  public:

    cluster();
    cluster(long index);
    cluster(std::shared_ptr<sample> object, bool isMedoid = false);
    cluster(long index, std::shared_ptr<sample> object, bool isMedoid = false);

    bool representsObject();
    std::string getClustersId();

    std::shared_ptr<sample> getObject();
    void getObjects(std::vector<std::shared_ptr<sample>> *target);
    void getSubclusters(std::vector<std::shared_ptr<cluster>> *target);

    void addSubcluster(std::shared_ptr<cluster> subcluster);

    bool hasSubcluster(std::shared_ptr<cluster> c);

    long size();
    long dimension();
    double timestamp = 0;

    void setWeight(double weight);
    void setCWeight(double weight);
    double getWeight();
    double getCWeight();
    double getSquaredWeight();

    cluster *getMedoid();
    void setMedoid(std::shared_ptr<cluster> newMedoid);

    std::shared_ptr<sample> getMean();
    void setMean(std::shared_ptr<sample> newMean);

    std::unordered_map<std::string, double> getVariation();
    void setVariantion(std::unordered_map<std::string, double> variantion);

    void setRepresentative(sample *newRepresentative);
    void findRepresentative();
    sample* getRepresentative();

    void setTimestamp(double timestamp);
    double getTimestamp();

    void countVariation();

    // Prediction
    std::vector<double> predictionParameters;
    double _deactualizationParameter = 0.99; // w_a -- w, since first article
    int _predictionsSteps = 1;
    int _j = 0;
    std::vector<std::vector<double>> _matrixDj = {};
    std::vector<double>_djVector = {};

    double _uPredictionParameter = 0.95;
    double _lastPrediction = 0;
    double _currentKDEValue = 0;
    double _currentDerivativeValue = 0;

    // Prediction rewritten
    void updatePrediction();

    double getLastPrediction();
    double getDeactualizationParameter();
    std::vector<double> getPredictionParameters();
    std::vector<double> getDjVector();
    std::vector<std::vector<double>> getDjMatrix();
    int getPrognosisJ();

  protected:

    long index;
    double weight = 0; // p_i from 6 spraw e-mail
    double _computationWeight = 0; // w_i from 6 spraw e-mail

    std::shared_ptr<sample> object;
    sample* representative;
    std::shared_ptr<sample> mean;
    std::shared_ptr<cluster> medoid;

    std::unordered_map<std::string, double> variation;

    std::vector<std::shared_ptr<cluster>> subclusters;

    void findMean();
      void findMeanFromSubclusters();

    void findVariation();

    // Prediction
    void updateFinitePrediction();
    void updateInfinitePrediction();
    void updateFinitePredictionMatrices();
    void updateFinitePredictionParameters();
    void updateInfinitePredictionMatrices();
    void updateInfinitePredictionParameters();
    void updateLastPrediction();

};

typedef std::shared_ptr<cluster> clusterPtr;


#endif //K_MEDOIDALGORITHM_CLUSTER_H
