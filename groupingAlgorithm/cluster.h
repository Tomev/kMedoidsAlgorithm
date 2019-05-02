#ifndef K_MEDOIDALGORITHM_CLUSTER_H
#define K_MEDOIDALGORITHM_CLUSTER_H

#include <c++/vector>
#include <string>
#include <memory>

#include "sample.h"

class cluster
{
  public:

    cluster();
    cluster(long index);
    cluster(std::shared_ptr<sample> object);
    cluster(long index, std::shared_ptr<sample> object);

    bool representsObject();
    std::string getClustersId();

    std::shared_ptr<sample> getObject();
    void getObjects(std::vector<std::shared_ptr<sample>> *target);
    void getSubclusters(std::vector<std::shared_ptr<cluster>> *target);

    void addSubcluster(std::shared_ptr<cluster> subcluster);

    bool hasSubcluster(std::shared_ptr<cluster> c);

    long size();
    long dimension();

    void setWeight(double weight);
    double getWeight();
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

    long setTimestamp(long timestamp);
    long getTimestamp();

    void countVariation();

    long positiveTemporalDerivativeTimesInARow = 0;

    // Prediction
    std::vector<double> predictionParameters;
    double _deactualizationParameter = 0.995;
    int _predictionsSteps = 1;
    int _j = 0;
    std::vector<std::vector<double>> _matrixDj = {};
    std::vector<double>_djVector = {};
    bool _shouldUpdateDeactualizationParameter = false;
    double _tildedZ = 0;
    double _doubleTildedZ = 0;
    double _uPredictionParameter = 0.95;
    double _lastPrediction = 0;
    double _lastKDEValue = 0;
    double _currentKDEValue = 0;
    double _KDEDerivativeValue = 0;

    void initializePredictionParameters(double KDEValue);
    void updatePredictionParameters(double KDEValue);
    void updateDjMatrix();
    void updatedjVector(double KDEValue);
    void updateLastPrediction();
    void updateDeactualizationParameter(double KDEValue);

    double getTildedZ();
    double getDoubleTildedZ();
    double getLastPrediction();
    double getDeactualizationParameter();
    double getLastKDEValue();
    std::vector<double> getPredictionParameters();

    std::string rowToSave = "";

  protected:

    long index;
    double weight = 1;
    long timestamp = 0;

    std::shared_ptr<sample> object;
    sample* representative;
    std::shared_ptr<sample> mean;
    std::shared_ptr<cluster> medoid;

    std::unordered_map<std::string, double> variation;

    std::vector<std::shared_ptr<cluster>> subclusters;

    void findMean();
      void findMeanFromSubclusters();

    void findVariation();

};


#endif //K_MEDOIDALGORITHM_CLUSTER_H
