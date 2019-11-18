#include <c++/clocale>
#include <c++/iostream>
#include <math.h>
#include <qDebug>

#include "cluster.h"

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
  return representative;
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

void cluster::initializePredictionParameters(double KDEValue)
{
  predictionParameters =  { KDEValue, 0 };
  _matrixDj = { { 1, 0 }, { 0, 0 } };
  _djVector = { KDEValue, 0 };

  if(_shouldUpdateDeactualizationParameter)
    updatePredictionParameters(KDEValue);

  updateLastPrediction();
}

void cluster::updatePredictionParameters(double KDEValue)
{
  ++_j;

  if(_shouldUpdateDeactualizationParameter)
    updateDeactualizationParameter(KDEValue);

  if(_j == 1)
    return;

  double upperValue = 0, lowerValue = 0, denominator = 0;

  // Finite case.
  updateDjMatrix();
  updatedjVector(KDEValue);

  denominator =
      _matrixDj[0][0] * _matrixDj[1][1] - _matrixDj[1][0] * _matrixDj[0][1];

  upperValue =
      _matrixDj[1][1] * _djVector[0] - _matrixDj[0][1] * _djVector[1];
  upperValue /= denominator;

  lowerValue =
      _matrixDj[0][0] * _djVector[1] - _matrixDj[1][0] * _djVector[0];
  lowerValue /= denominator;

  /*
  // Limit case.
  double predictionAndAcutalDifference =
      (KDEValue - _lastPrediction);

  upperValue = predictionParameters[0] + predictionParameters[1];
  upperValue += (1.0 - pow(_deactualizationParameter, 2))
      * predictionAndAcutalDifference;

  lowerValue = predictionParameters[1];
  lowerValue += pow(1.0 - _deactualizationParameter, 2)
      * predictionAndAcutalDifference;
  */

  predictionParameters = { upperValue, lowerValue };

  updateLastPrediction();
}

void cluster::updateDjMatrix()
{
  double leftValue = 0, rightValue = 0;
  std::vector<double> upperRow = {}, lowerRow = {};
  int j = _j - 1;

  double deactualizationCoefficient = pow(_deactualizationParameter, j);

  // First upper row.
  leftValue = _matrixDj[0][0] + deactualizationCoefficient;
  rightValue = _matrixDj[0][1] - j * deactualizationCoefficient;
  upperRow = {leftValue, rightValue};

  // Then lower row.
  leftValue = _matrixDj[1][0] - j * deactualizationCoefficient;
  rightValue = _matrixDj[1][1] + j * j * deactualizationCoefficient;
  lowerRow = {leftValue, rightValue};

  _matrixDj = {upperRow, lowerRow};
}

void cluster::updatedjVector(double KDEValue)
{
  double upperValue = 0.0, lowerValue = 0.0;
  upperValue = _deactualizationParameter * _djVector[0] + KDEValue;
  lowerValue = _deactualizationParameter * (_djVector[1] - _djVector[0]);
  _djVector = {upperValue, lowerValue};
}

void cluster::updateLastPrediction()
{
  _lastPrediction = predictionParameters[0];
  _lastPrediction += predictionParameters[1] * _predictionsSteps;
}

void cluster::updateDeactualizationParameter(double KDEValue)
{
  if(_j == 1)
  {
    _tildedZ = 1;
    _doubleTildedZ = 10;
    _deactualizationParameter = 0.9;
    rowToSave = std::to_string(KDEValue) + ",-,0,1,10,0.1,0.9\n";
    return;
  }

  double eParameter = _lastPrediction - KDEValue;

  //if(_j == 1) _doubleTildedZ = fabs(eParameter);

  //qDebug() << "y_s = " << _lastPrediction;
  //qDebug() << "y = " << KDEValue;

  _doubleTildedZ = (1.0 - _uPredictionParameter) * fabs(eParameter) +
      _uPredictionParameter * _doubleTildedZ;
  _tildedZ = (1.0 - _uPredictionParameter) * eParameter +
      _uPredictionParameter * _tildedZ;

  if(_doubleTildedZ < 1e-20)
  {
    //qDebug() << "dtilded z is low: " << _doubleTildedZ;
    _deactualizationParameter = 1.0;
    return;
  }

  //qDebug() << "e = " << eParameter;
  //qDebug() << "~~z = " << _doubleTildedZ;
  //qDebug() << "~z = " << _tildedZ;

  double zj = fabs(_tildedZ / _doubleTildedZ);
  //qDebug() << "z = " << zj;

  _deactualizationParameter = 1.0 - zj;

  rowToSave = std::to_string(KDEValue) + ",";
  rowToSave += std::to_string(_lastPrediction) + ",";
  rowToSave += std::to_string(eParameter) + ",";
  rowToSave += std::to_string(_tildedZ) + ",";
  rowToSave += std::to_string(_doubleTildedZ) + ",";
  rowToSave += std::to_string(zj) + ",";
  rowToSave += std::to_string(_deactualizationParameter) + "\n";
}

double cluster::getTildedZ()
{
  if(representsObject()) return _tildedZ;

  double averageTildedZ = 0;

  for(auto c : subclusters)
    averageTildedZ += c->_tildedZ * c->weight;

  averageTildedZ /= getWeight();

  return averageTildedZ;
}

double cluster::getDoubleTildedZ()
{
  if(representsObject()) return _doubleTildedZ;

  double averageDoubleTildedZ = 0;

  for(auto c : subclusters)
    averageDoubleTildedZ += c->_doubleTildedZ * c->weight;

  averageDoubleTildedZ /= getWeight();

  return averageDoubleTildedZ;
}

double cluster::getLastPrediction()
{
  if(representsObject()) return _lastPrediction;

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

double cluster::getLastKDEValue()
{
  if(representsObject()) return  _lastKDEValue;

  double averageLastKDEValue = 0;

  for(auto c : subclusters)
    averageLastKDEValue += c->_lastKDEValue * c->weight;

  double w = getWeight();
  if(w > 0)
    averageLastKDEValue /= w;

  return averageLastKDEValue;
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

void cluster::findMean()
{
  if(this->representsObject()) mean = object;
  else findMeanFromSubclusters();
}

void cluster::findMeanFromSubclusters()
{
  double currentClusterWeight = 0.0f;
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
