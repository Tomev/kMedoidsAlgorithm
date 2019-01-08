#include <c++/clocale>
#include <c++/iostream>
#include <math.h>

#include "cluster.h"

cluster::cluster(){}

cluster::cluster(long index) : index(index) {}

cluster::cluster(std::shared_ptr<sample> object) : object(object)
{
  findRepresentative();
  this->setWeight(1);
}

cluster::cluster(long index, std::shared_ptr<sample> object) : index(index),
  object(object)
{
  findRepresentative();
  this->setWeight(1);
}

bool cluster::representsObject()
{
  return object != NULL;
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

  if(subclusters.size() > 0) // If it has subcluster get it's subclusters objects
  {
    for(std::shared_ptr<cluster> c : subclusters) c.get()->getObjects(target);
  }
  else if(this->representsObject()) // Check if cluster is singular object
  {
    target->push_back(this->getObject());
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

  if(representsObject()) return 1;

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

double cluster::getWeight()
{
  if(subclusters.size() == 0) return weight;

  double w = 0;

  for(std::shared_ptr<cluster> c : subclusters) w += c->getWeight();

  return w;
}

double cluster::getSquaredWeight()
{
  if(subclusters.size() == 0) return weight;

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

long cluster::setTimestamp(long timestamp)
{
  this->timestamp = timestamp;
  return this->timestamp;
}

long cluster::getTimestamp()
{
  return this->timestamp;
}

void cluster::initializePredictionParameters(double KDEValue)
{
  predictionParameters = std::vector<double>({KDEValue, 0});

  updateLastPrediction();
}

void cluster::updatePredictionParameters(double KDEValue)
{
  double upperValue, lowerValue;

  upperValue = predictionParameters[0] + predictionParameters[1];
  upperValue += (1.0 - _deactualizationParameter) * (KDEValue - _lastPrediction);

  lowerValue = predictionParameters[1];
  lowerValue += pow(1.0 - _deactualizationParameter, 2) * (KDEValue - _lastPrediction);

  if(fabs(lowerValue) > 10)
  {
    std::cout<< "=============================" << std::endl;
    std::cout << lowerValue << std::endl;
    std::cout << _deactualizationParameter << std::endl;
    std::cout<< "=============================" << std::endl;
  }

  predictionParameters = std::vector<double>({ upperValue, lowerValue });

  updateLastPrediction();
}

void cluster::updateLastPrediction()
{
  _lastPrediction = predictionParameters[0] + predictionParameters[1];
}

void cluster::updateDeactualizationParameter(double KDEValue)
{
  double eParameter = _lastPrediction - KDEValue;

  if(_doubleTildedZ < 1e-5)
  {
    _doubleTildedZ = fabs(eParameter);
    _tildedZ = 0.0;
    _deactualizationParameter = 1.0;
  }
  else
  {
    _doubleTildedZ = (1.0 - _uPredictionParameter) * fabs(eParameter) + _uPredictionParameter * _doubleTildedZ;
    _tildedZ = (1.0 - _uPredictionParameter) * eParameter + _uPredictionParameter * _tildedZ;
    _deactualizationParameter = 1.0 - fabs(_tildedZ / _doubleTildedZ);
  }

  _lastKDEValue = KDEValue;
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

  averageLastPrediction /= getWeight();

  return averageLastPrediction;
}

double cluster::getDeactualizationParameter()
{
  if(representsObject()) return _deactualizationParameter;

  double averageDeactualizationParameter = 0;

  for(auto c : subclusters)
    averageDeactualizationParameter += c->_deactualizationParameter * c->weight;

  averageDeactualizationParameter /= getWeight();

  return averageDeactualizationParameter;
}

double cluster::getLastKDEValue()
{
  if(representsObject()) return  _lastKDEValue;

  double averageLastKDEValue = 0;

  for(auto c : subclusters)
    averageLastKDEValue += c->_lastKDEValue * c->weight;

  averageLastKDEValue /= getWeight();

  return averageLastKDEValue;
}

std::vector<double> cluster::getPredictionParameters()
{
  if(representsObject()) return predictionParameters;

  double upperValue = 0;
  double lowerValue = 0;

  for(auto c : subclusters)
  {
    if(c->predictionParameters.size() == 0) continue;
    upperValue += c->predictionParameters[0] * c->weight;
    lowerValue += c->predictionParameters[1] * c->weight;
  }

  upperValue /= getWeight();
  lowerValue /= getWeight();

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

  double summaricWeight = getWeight();

  for(auto kv : numericAttributesData)
    mean->attributesValues[kv.first] = std::to_string(kv.second / summaricWeight);

  std::pair<std::string, double> symbolicAttributeValWeight;

  for(auto kv : symbolicAttributesData)
  {
    symbolicAttributeValWeight.second = 0.0f;

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

  double summaricWeight = getWeight();
  double summaricSquaredWeight = getSquaredWeight();

  double varCoefficient = summaricWeight;
  varCoefficient /= (pow(summaricWeight, 2) - summaricSquaredWeight);

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
