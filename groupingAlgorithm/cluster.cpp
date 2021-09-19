#include <clocale>
#include <iostream>
#include <math.h>
#include <QDebug>
#include "cluster.h"

double cluster::_deactualizationParameter = 0.999;

cluster::cluster(){}

cluster::cluster(long index) : index(index) {}

cluster::cluster(std::shared_ptr<sample> object, bool isMedoid) : object(object)
{
  findRepresentative();
  if(!isMedoid) this->setWeight(1);
  if(isMedoid) timestamp = -1;
}

cluster::cluster(long index, std::shared_ptr<sample> object, bool isMedoid) : index(index),
  object(object)
{
  findRepresentative();
  if(!isMedoid) this->setWeight(1);
  if(isMedoid) timestamp = -1;
}

bool cluster::representsObject()
{
  //return subclusters.size() > 2;
  return object != nullptr;
}

std::string cluster::getClustersId()
{
  std::string id;

  if(this->representsObject()) id = "O"; // For "object"
  else id = "C"; // For "cluster"

  id +=  std::to_string(index);

  return id;
}

bool cluster::hasSubcluster(std::shared_ptr<cluster> c)
{
  for(std::shared_ptr<cluster> subcluster : subclusters)
  {
    if(c.get()->getClustersId() == subcluster.get()->getClustersId()) return true;
    if(subcluster.get()->hasSubcluster(c)) return true;
  }

  return false;
}

std::shared_ptr<sample> cluster::getObject()
{
  if(representsObject()) return object;
  //if(representsObject()) return object.get();
  else std::cout << "Cluster doesn't represent an object. Returning nullptr.\n";

  return nullptr;
}

void cluster::getObjects(std::vector<std::shared_ptr<sample>>* target)
{
  if(target == nullptr)
  {
    std::cout << "Target is a null pointer. Cannot return clusters objects.\n";
    return;
  }

  if(this->representsObject()) // Check if cluster is singular object
  {
    target->push_back(this->getObject());
  }
  else if(subclusters.size() > 0) // If it has subcluster get it's subclusters objects
  {
    for(std::shared_ptr<cluster> c : subclusters) c.get()->getObjects(target);
  }

}

void cluster::getSubclusters(std::vector<std::shared_ptr<cluster> > *target)
{
  target->clear();

  for(std::shared_ptr<cluster> c : subclusters)
    target->push_back(c);
}

void cluster::addSubcluster(std::shared_ptr<cluster> subcluster)
{
  subclusters.push_back(subcluster);
}

long cluster::size()
{
  if(subclusters.size() != 0) return subclusters.size();

  if(representsObject() && weight != 0) return 1;

  return 0;
}


/**
 * @brief cluster::dimension
 * @return Dimension of the cluster.
 */
long cluster::dimension()
{
  return representative->attributesValues.size();
}

void cluster::setWeight(double weight)
{
    this->weight = weight;
}

void cluster::setCWeight(double weight)
{
    _computationWeight = weight;
}

double cluster::getWeight()
{
  if(subclusters.size() == 0) return weight;

  double w = 0;

  for(std::shared_ptr<cluster> c : subclusters) w += c->getWeight();

  return w;
}

double cluster::getCWeight()
{
    return _computationWeight;
}

double cluster::getSquaredWeight()
{
  if(subclusters.size() == 0) return weight * weight;

  double w = 0;

  for(std::shared_ptr<cluster> c : subclusters) w += pow(c->getWeight(), 2);

  return w;
}

cluster* cluster::getMedoid()
{
  if(representsObject()) return this;

  //return this->medoid;
  return this->medoid.get();
}

void cluster::setMedoid(std::shared_ptr<cluster> newMedoid)
{
  medoid = newMedoid;
  //this->medoid = newMedoid;
}

std::shared_ptr<sample> cluster::getMean()
{
  if(mean.get() == nullptr) findMean();
  return mean;
}

void cluster::setMean(std::shared_ptr<sample> newMean)
{
  mean = newMean;
}

std::unordered_map<std::string, double> cluster::getVariation()
{
  if(subclusters.size() == 0) return variation;
  if(variation.size() == 0) findVariation();

  return variation;
}

void cluster::setVariantion(std::unordered_map<std::string, double> variantion)
{
  variation = variantion;
}

void cluster::setRepresentative(sample *newRepresentative)
{
  representative = newRepresentative;
}

void cluster::findRepresentative()
{
  if(representsObject()) representative = object.get();
}

sample *cluster::getRepresentative()
{
  findMean();
  return mean.get();
  //return representative;
}

void cluster::setTimestamp(double timestamp)
{
  this->timestamp = timestamp;
}

double cluster::getTimestamp()
{
  double ts = 0;

  if(subclusters.size() == 0)
    ts = timestamp;
  else if(subclusters.size() == 1){
    return subclusters[0]->getTimestamp();
  } else {
    for(auto c : subclusters){
        ts += c->getTimestamp() * c->getWeight();
    }
    ts /= getWeight();
  }

  return ts;
}

void cluster::updatePrediction()
{
    ++_j;
    //updateFinitePrediction();
    updateInfinitePrediction();
    updateLastPrediction();
}

void cluster::updateFinitePrediction()
{
  updateFinitePredictionMatrices();
  updateFinitePredictionParameters();
}

void cluster::updateInfinitePrediction()
{
  updateInfinitePredictionMatrices();
  updateInfinitePredictionParameters();
}


void cluster::updateFinitePredictionMatrices()
{
    int j = _j - 1;

    if(j == 0){ // Initialization
        _matrixDj = {{1, 0}, {0, 0}}; // Finite case
        _djVector = {_currentKDEValue, 0};
    } else { // Update
        double deactualizationCoefficient = pow(_deactualizationParameter, j);
        _matrixDj[0][0] += deactualizationCoefficient;
        _matrixDj[0][1] += -j * deactualizationCoefficient;
        _matrixDj[1][0] += -j * deactualizationCoefficient;
        _matrixDj[1][1] += j * j * deactualizationCoefficient;

        _djVector[1] = _deactualizationParameter * (_djVector[1] - _djVector[0]);
        _djVector[0] = _deactualizationParameter * _djVector[0] + _currentKDEValue;
    }
}

void cluster::updateFinitePredictionParameters()
{
  if(_j == 1){ // Initialization
    predictionParameters = {_currentKDEValue, 0};
  } else { // Update
    double denominator = _matrixDj[0][0] * _matrixDj[1][1] - _matrixDj[1][0] * _matrixDj[0][1];
    predictionParameters[0] = (_matrixDj[1][1] * _djVector[0] - _matrixDj[0][1] * _djVector[1]) / denominator;
    predictionParameters[1] = (_matrixDj[0][0] * _djVector[1] - _matrixDj[1][0] * _djVector[0]) / denominator;
  }
}

void cluster::updateLastPrediction()
{
  _lastPrediction = predictionParameters[0];
  _lastPrediction += predictionParameters[1] * _predictionsSteps;
}


double cluster::getLastPrediction()
{
  if(representsObject() || index == -1) return _lastPrediction;

  double averageLastPrediction = 0;

  for(auto c : subclusters)
    averageLastPrediction += c->_lastPrediction * c->weight;

  double w = getWeight();
  if(w > 0)
    averageLastPrediction /= w;

  return averageLastPrediction;
}

double cluster::getDeactualizationParameter()
{
  if(representsObject()) return _deactualizationParameter;

  double averageDeactualizationParameter = 0;

  for(auto c : subclusters)
    averageDeactualizationParameter += c->_deactualizationParameter * c->weight;

  double w = getWeight();
  if(w > 0)
    averageDeactualizationParameter /= w;

  return averageDeactualizationParameter;
}

std::vector<double> cluster::getPredictionParameters()
{
  if(subclusters.size() == 0) return predictionParameters;

  double upperValue = 0;
  double lowerValue = 0;

  for(auto c : subclusters)
  {
    if(c->predictionParameters.size() == 0) continue;
    upperValue += c->predictionParameters[0] * c->weight;
    lowerValue += c->predictionParameters[1] * c->weight;
  }

  double w = getWeight();
  if(w > 0){
    upperValue /= w;
    lowerValue /= w;
  }

  return std::vector<double>({upperValue, lowerValue});
}

std::vector<double> cluster::getDjVector()
{
    if(subclusters.size() == 0) return _djVector;

    double upperValue = 0;
    double lowerValue = 0;

    for(auto c : subclusters)
    {
      upperValue += c->_djVector[0] * c->weight;
      lowerValue += c->_djVector[1] * c->weight;
    }

    double w = getWeight();

    if(w > 0){
      upperValue /= w;
      lowerValue /= w;
    }

    return std::vector<double>({upperValue, lowerValue});
}

std::vector<std::vector<double> > cluster::getDjMatrix()
{
    if(subclusters.size() == 0){
        return _matrixDj;
    }

    std::vector<std::vector<double>> matrix = {{0, 0}, {0,0}};

    double clusterWeight = getWeight();

    for(auto c : subclusters){
      for(int i = 0; i < 2; ++i){
          for(int j = 0; j < 2; ++j){
              matrix[i][j] += c->_matrixDj[i][j] * c->getWeight() / clusterWeight;
          }
      }
    }

    return matrix;
}

int cluster::getPrognosisJ()
{
    if(subclusters.size() == 0) return _j;

    double j = 0;

    for(auto c : subclusters) j += c->_j * c->weight;

    j /= getWeight();

    return (int) j;
}

void cluster::findMean()
{
  if(this->representsObject()) mean = object;
  else findMeanFromSubclusters();
}

void cluster::findMeanFromSubclusters()
{
  double currentClusterWeight = 0;
  std::shared_ptr<sample> currentObject;

  std::unordered_map<std::string, double> numericAttributesData;
  std::unordered_map<std::string, std::unordered_map<std::string, double>> symbolicAttributesData;

  for(std::shared_ptr<cluster> sc : subclusters)
  {
    currentObject = sc->getObject();
    currentClusterWeight = sc->getWeight();

    // First initialize structures if they're not initialized
    if(numericAttributesData.size() + symbolicAttributesData.size() == 0)
    {
      for(auto kv : currentObject->attributesValues)
      {
        if((*(currentObject->attributesData))[kv.first]->getType() == "symbolic")
          symbolicAttributesData[kv.first][kv.second] = 0.0f;
        else
          numericAttributesData[kv.first] = 0.0f;
      }
    }

    // Being sure, that I now have data initialized to 0 I begin finding mean values
    for(auto kv : currentObject->attributesValues)
    {
      if((*(currentObject->attributesData))[kv.first]->getType() == "symbolic")
        symbolicAttributesData[kv.first][kv.second] =
            symbolicAttributesData[kv.first][kv.second] + currentClusterWeight;
      else
        numericAttributesData[kv.first] = numericAttributesData[kv.first] + currentClusterWeight * std::stod(kv.second);
    }
  }

  mean = std::shared_ptr<sample>(new sample());
  mean->attributesData = subclusters[0]->getObject()->attributesData;

  double w = getWeight();
  if(w > 0)
    for(auto kv : numericAttributesData)
      mean->attributesValues[kv.first] = std::to_string(kv.second / w);

  std::pair<std::string, double> symbolicAttributeValWeight;

  for(auto kv : symbolicAttributesData)
  {
    symbolicAttributeValWeight.second = 0;

    for(auto av : kv.second)
    {
      if(symbolicAttributeValWeight.second < av.second)
      {
        symbolicAttributeValWeight.second = av.second;
        symbolicAttributeValWeight.first = av.first;
      }
    }

    mean->attributesValues[kv.first] = symbolicAttributeValWeight.first;
  }

}

void cluster::findVariation()
{
  if(mean.get() == nullptr) findMean();

  variation.clear();

  double w = getWeight();
  double summaricSquaredWeight = getSquaredWeight();

  double varCoefficient = w;
  varCoefficient /= (pow(w, 2) - summaricSquaredWeight);

  double updatedVariationValue = 0;

  // Initialize variation
  for(auto kv : mean->attributesValues)
    variation[kv.first] = 0;

  for(std::shared_ptr<cluster> sc : subclusters)
  {
    for(auto kv : sc->getObject()->attributesValues)
    {
      if((*(mean->attributesData))[kv.first]->getType() == "numerical")
      {
        updatedVariationValue = std::stod(kv.second);
        updatedVariationValue -= std::stod(mean->attributesValues[kv.first]);
        updatedVariationValue = pow(updatedVariationValue, 2);
        updatedVariationValue *= sc->getWeight();
        updatedVariationValue += variation[kv.first];
        variation[kv.first] = updatedVariationValue;
      }
    }
  }

  for(auto kv : variation)
    kv.second *= varCoefficient;
}

void cluster::updateInfinitePredictionMatrices()
{
  int j = _j - 1;

  if(j == 0){ // Initialization
      _djVector = {_currentKDEValue, 0};
  } else { // Update
      _djVector[1] = _deactualizationParameter * (_djVector[1] - _djVector[0]);
      _djVector[0] = _deactualizationParameter * _djVector[0] + _currentKDEValue;
  }
}

void cluster::updateInfinitePredictionParameters()
{
  int j = _j - 1;

  if(j == 0){
      predictionParameters = {_currentKDEValue, 0};
  } else {
    double predictionDifference = _currentKDEValue - _lastPrediction;
    predictionParameters[0] += predictionParameters[1];
    predictionParameters[0] += (1 - pow(_deactualizationParameter, 2)) * predictionDifference;
    predictionParameters[1] += pow(1 - _deactualizationParameter, 2) * predictionDifference;
  }
}
