#include <iostream>
#include <algorithm>
#include <set>

#include "kMedoidsAlgorithm.h"

kMedoidsAlgorithm::kMedoidsAlgorithm(int numberOfMedoids, clustersDistanceMeasure* clusDistanceMeasure) :
  numberOfMedoids(numberOfMedoids)
{
  this->clusDistanceMeasure = clusDistanceMeasure;
}

bool kMedoidsAlgorithm::canGroupingBePerformed(std::vector<sample*>* objects)
{
  if(objects->size() < numberOfMedoids)
  {
    std::cout << "Number of medoids is greater than objects number.\n";
    return false;
  }

  if(numberOfMedoids <= 0)
  {
    std::cout << "Number of medoids is lower or equal 0.\n";
    return false;
  }

  return true;
}

void kMedoidsAlgorithm::groupObjects(std::vector<sample*> *objects, std::vector<cluster>* target)
{
  if(!canGroupingBePerformed(objects)) return;

  clusterObjects(objects);

  gatherSimilarityData();

  findOptimalMedoids();
  createClustersFromMedoids(target);
}

void kMedoidsAlgorithm::clusterObjects(std::vector<sample*> *objects)
{
  for(int clusterNumber = 0; clusterNumber < objects->size(); ++clusterNumber)
    clusters.push_back(cluster(clusterNumber+1, objects->at(clusterNumber)));
}

int kMedoidsAlgorithm::gatherSimilarityData()
{
  similarityData.clear();

  for(int i = 0; i < clusters.size(); ++i)
  {
    for (int j = i + 1; j < clusters.size(); ++j)
    {
      string name = clusters[i].getClustersId() + "-" + clusters[j].getClustersId();
      similarityData[name] = clusDistanceMeasure->countClustersDistance(&clusters[i], &clusters[j]);
    }
  }

  return similarityData.size();
}

void kMedoidsAlgorithm::findOptimalMedoids()
{
  //selectRandomMedoids();
  selectRandomMedoidsAccordingToDistance();

  double lowestCost = countCost(&medoids);

  vector<cluster> potentialBestMedoids;

  double potentialLowestCost;

  while(true)
  {
    findPotentialBestMedoidConfiguration(&potentialBestMedoids, lowestCost);
    potentialLowestCost = countCost(&potentialBestMedoids);

    if(potentialLowestCost < lowestCost)
    {
      lowestCost = potentialLowestCost;
      medoids = potentialBestMedoids;
    }
    else break;
  }
}

void kMedoidsAlgorithm::selectRandomMedoids()
{
  std::set<int> medoidsIndexes;

  // Randomize medoid indexes until required number is achieved.
  while(medoidsIndexes.size() != numberOfMedoids) medoidsIndexes.insert(rand() % clusters.size());

  for(int medoidsIndex : medoidsIndexes)
  {
    cluster c = clusters.at(medoidsIndex);
    medoids.push_back(c);
  }
}

int kMedoidsAlgorithm::selectRandomMedoidsAccordingToDistance()
{
  // Create and fill vector of clusters indexes
  vector<int> nonMedoidsIndexes;

  for(int i = 0; i < clusters.size(); ++i)  nonMedoidsIndexes.push_back(i);

  // Select first medoid at random (uniformly) and add it to vector
  int nonMedoidPosition = rand() % nonMedoidsIndexes.size(),
      newMedoidIndex = nonMedoidsIndexes.at(nonMedoidPosition);

  addNewMedoidToVector(newMedoidIndex);

  nonMedoidsIndexes.erase(nonMedoidsIndexes.begin() + nonMedoidPosition);

  while(medoids.size() < numberOfMedoids)
    addNewMedoidAccordingToDistance(&nonMedoidsIndexes);

  return medoids.size();
}

int kMedoidsAlgorithm::addNewMedoidToVector(int medoidIndex)
{
  cluster newMedoid = clusters.at(medoidIndex);
  medoids.push_back(newMedoid);

  return medoids.size();
}

int kMedoidsAlgorithm::addNewMedoidAccordingToDistance(vector<int>* nonMedoidIndexes)
{
  vector<double> weights, probabilities;

  fillWeights(&weights, nonMedoidIndexes);
  fillProbabilitiesFromWeights(&weights, &probabilities);

  double r = ((double) rand() / (RAND_MAX));
  int newMedoidIndexPosition = 0;

  while(r > probabilities.at(newMedoidIndexPosition))
    ++newMedoidIndexPosition;

  addNewMedoidToVector(nonMedoidIndexes->at(newMedoidIndexPosition));
  nonMedoidIndexes->erase(nonMedoidIndexes->begin() + newMedoidIndexPosition);

  return 0;
}

int kMedoidsAlgorithm::fillWeights(vector<double> *weights, vector<int> *nonMedoidsIndexes)
{
  double weight;

  weights->clear();

  for(int nonMedoidIndex : *nonMedoidsIndexes)
  {
    weight = 0;

    for(cluster medoid : medoids)
      weight += this->clusDistanceMeasure->countClustersDistance(&medoid, &clusters.at(nonMedoidIndex));

    weight /= medoids.size();
    weights->push_back(weight);
  }

  return weights->size();
}

int kMedoidsAlgorithm::fillProbabilitiesFromWeights(vector<double> *weights, vector<double> *probabilities)
{
  probabilities->clear();

  double weightsSum = 0;

  for(double weight : *weights) weightsSum += weight;

  probabilities->push_back(weights->at(0) / weightsSum);

  double probability;

  for(int i = 1; i < weights->size(); ++i)
  {
    probability = probabilities->at(i - 1);
    probability += weights->at(i) / weightsSum;
    probabilities->push_back(probability);
  }

  return probabilities->size();
}

double kMedoidsAlgorithm::countCost(vector<cluster> *potentialMedoids)
{
  double cost = 0;

  for(cluster c : clusters)
  {
    if(!isMedoid(&c, potentialMedoids))
    {
      int closestMedoidIndex = findClosestMedoidIndex(&c, potentialMedoids);

      //cost += clusDistanceMeasure->countClustersDistance(&c, &(potentialMedoids->at(closestMedoidIndex)));
      cost += getClustersSimilarity(&c, &(potentialMedoids->at(closestMedoidIndex)));
    }
  }

  return cost;
}

bool kMedoidsAlgorithm::isMedoid(cluster *c, vector<cluster>* medoids)
{
  for(cluster medoid : *medoids)
    if(c->getClustersId() == medoid.getClustersId()) return true;

  return false;
}

int kMedoidsAlgorithm::findClosestMedoidIndex(cluster *c, vector<cluster>* potentialMedoids)
{
  int closestMedoidIndex = 0;
  double  //minDistance = clusDistanceMeasure->countClustersDistance(&(potentialMedoids->at(0)), c),
          minDistance = getClustersSimilarity(&(potentialMedoids->at(0)), c),
          distance;

  for(int medoidIndex = 1; medoidIndex < potentialMedoids->size(); ++medoidIndex)
  {
    //distance = clusDistanceMeasure->countClustersDistance(&(potentialMedoids->at(medoidIndex)), c);
    distance = getClustersSimilarity(&(potentialMedoids->at(medoidIndex)), c);

    if(distance < minDistance)
    {
      minDistance = distance;
      closestMedoidIndex = medoidIndex;
    }
  }

  return closestMedoidIndex;
}

double kMedoidsAlgorithm::getClustersSimilarity(cluster *c1, cluster *c2)
{
  string name = c1->getClustersId() + "-" + c2->getClustersId();

  auto similarityIterator = similarityData.find(name);

  if(similarityIterator == similarityData.end()) name = c2->getClustersId() + "-" + c1->getClustersId();

  return similarityData[name];
}

void kMedoidsAlgorithm::findPotentialBestMedoidConfiguration(vector<cluster> *potentialBestMedoids, double minCost)
{
  double minimalCost = minCost, potentialMinimalCost;
  vector<cluster> currentBestConfiguration = medoids;

  // For each medoid
  for(int medoidIndex = 0; medoidIndex < medoids.size(); ++medoidIndex)
  {
    cout << "Medoid index: " << medoidIndex << endl;

    // Exclude this medoid from medoids list
    *potentialBestMedoids = medoids;
    potentialBestMedoids->erase(potentialBestMedoids->begin()+medoidIndex);

    // Substitute missing medoid with each non-medoid cluster and count cost
    for(cluster c : clusters)
    {
      if (!isMedoid(&c, &medoids)) {
        potentialBestMedoids->push_back(c);
        potentialMinimalCost = countCost(potentialBestMedoids);

        if (potentialMinimalCost < minimalCost) {
          minimalCost = potentialMinimalCost;
          cout << minimalCost << endl;
          currentBestConfiguration.clear();
          currentBestConfiguration = *potentialBestMedoids;
        }

        potentialBestMedoids->pop_back();

      }
    }
  }

  *potentialBestMedoids = currentBestConfiguration;
}

void kMedoidsAlgorithm::createClustersFromMedoids(vector<cluster> *target)
{
  // Ensure that target vector is empty.
  target->clear();

  // Create outer clusters.
  for(int medoidIndex = 0; medoidIndex < medoids.size(); ++medoidIndex)
  {
    target->push_back(cluster(medoidIndex));
    target->back().addSubcluster(medoids.at(medoidIndex));
    target->back().setRepresentative(medoids.at(medoidIndex).getRepresentative());
  }

  // Assign objects to outer clusters.
  int closestMedoidIndex;

  for(cluster c : clusters)
  {
    if(!isMedoid(&c, &medoids))
    {
      closestMedoidIndex = findClosestMedoidIndex(&c, &medoids);
      target->at(closestMedoidIndex).addSubcluster(c);
    }
  }
}

void kMedoidsAlgorithm::setMedoids(vector<cluster> *newMedoids)
{
  if(newMedoids != nullptr)
  {
    if(newMedoids->size() == numberOfMedoids)
    {
      medoids = *newMedoids;
    }
  }
}

vector<cluster> kMedoidsAlgorithm::getMedoids(vector<sample*>* objects)
{
  if(medoids.size() != numberOfMedoids)
  {
    clusterObjects(objects);
    findOptimalMedoids();
  }

  return medoids;
}

void kMedoidsAlgorithm::generateClusteringFromMedoids(vector<sample *> *objects, vector<cluster> *target)
{
  if(!canGroupingBePerformed(objects)) return;

  clusterObjects(objects);

  if(medoids.size() != numberOfMedoids) findOptimalMedoids();

  createClustersFromMedoids(target);
}








