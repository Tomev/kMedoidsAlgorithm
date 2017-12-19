#include <iostream>
#include <algorithm>
#include <set>

#include "kMedoidsAlgorithm.h"

kMedoidsAlgorithm::kMedoidsAlgorithm(int numberOfMedoids, std::shared_ptr<clustersDistanceMeasure> clusDistanceMeasure,
                                     int medoidsFindingStrategy) :
  numberOfMedoids(numberOfMedoids), medoidsFindingStrategy(medoidsFindingStrategy)
{
  this->clusDistanceMeasure = clusDistanceMeasure;
}

bool kMedoidsAlgorithm::canGroupingBePerformed(std::vector<std::shared_ptr<sample>>* objects)
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

void kMedoidsAlgorithm::groupObjects(std::vector<std::shared_ptr<sample>> *objects,
                                     std::vector<std::shared_ptr<cluster> > *target)
{
  if(!canGroupingBePerformed(objects)) return;

  clusterObjects(objects);

  performGrouping(target);
}

void kMedoidsAlgorithm::groupClusters(std::vector<std::shared_ptr<cluster> > *clusters, std::vector<std::shared_ptr<cluster> > *target)
{
  this->clusters.clear();

  for(std::shared_ptr<cluster> c : *clusters) this->clusters.push_back(c);

  performGrouping(target);
}

int kMedoidsAlgorithm::performGrouping(std::vector<std::shared_ptr<cluster> > *target)
{
  double summaricWeight = 0.0;

  for(std::shared_ptr<cluster> c : this->clusters)
    summaricWeight += c.get()->getWeight();

  std::cout << "Sum weight: " << summaricWeight << std::endl;

  gatherSimilarityData();

  std::cout << "Similarity data gathered.\n";

  switch(medoidsFindingStrategy)
  {
    case RANDOM:
      selectRandomMedoids();
    break;
    case RANDOM_ACCORDING_TO_DISTANCE:
      selectRandomMedoidsAccordingToDistance();
    break;
    case OPTIMAL:
    default:
      findOptimalMedoids();
  }

  createClustersFromMedoids(target);

  std::cout << "Setting medoids.\n";

  for(std::shared_ptr<cluster> c : *target)
    setMedoidInWeightedCluster(c);

  std::cout << "Grouping finished.\nClusters:" << std::endl;

  for(unsigned int i = 0; i < target->size(); ++i)
  {
    std::cout << i << ". cluster's size: " << target->at(i).get()->size()
              << std::endl;
  }

  return target->size();
}

void kMedoidsAlgorithm::clusterObjects(std::vector<std::shared_ptr<sample>> *objects)
{
  clusters.clear();

  for(unsigned long clusterNumber = 0; clusterNumber < objects->size(); ++clusterNumber)
  {
    clusters.push_back(std::make_shared<cluster>(cluster(clusterNumber+1,
                                                         objects->at(clusterNumber))));
  }
}

int kMedoidsAlgorithm::gatherSimilarityData()
{
  similarityData.clear();

  for(unsigned int i = 0; i < clusters.size(); ++i)
  {
    for (unsigned int j = i + 1; j < clusters.size(); ++j)
    {
      std::string name =  clusters[i].get()->getClustersId() + "-" +
                          clusters[j].get()->getClustersId();

      similarityData[name] = clusDistanceMeasure->countClustersDistance(clusters[i].get(),
                                                                        clusters[j].get());;
    }
  }

  return similarityData.size();
}

void kMedoidsAlgorithm::findOptimalMedoids()
{
  //selectRandomMedoids();
  selectRandomMedoidsAccordingToDistance();

  double lowestCost = countCost(&medoids);

  std::vector<std::shared_ptr<cluster>> potentialBestMedoids;

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
  medoids.clear();

  std::set<int> medoidsIndexes;

  // Randomize medoid indexes until required number is achieved.
  while(medoidsIndexes.size() != numberOfMedoids) medoidsIndexes.insert(rand() % clusters.size());

  for(int medoidsIndex : medoidsIndexes)
    medoids.push_back(clusters.at(medoidsIndex));
}

int kMedoidsAlgorithm::selectRandomMedoidsAccordingToDistance()
{
  medoids.clear();

  // Create and fill vector of clusters indexes
  std::vector<int> nonMedoidsIndexes;

  for(unsigned int i = 0; i < clusters.size(); ++i)  nonMedoidsIndexes.push_back(i);

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
  medoids.push_back(clusters.at(medoidIndex));

  return medoids.size();
}

int kMedoidsAlgorithm::addNewMedoidAccordingToDistance(std::vector<int>* nonMedoidIndexes)
{
  std::vector<double> weights, probabilities;

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

int kMedoidsAlgorithm::fillWeights(std::vector<double> *weights, std::vector<int> *nonMedoidsIndexes)
{
  double weight;

  weights->clear();

  for(int nonMedoidIndex : *nonMedoidsIndexes)
  {
    weight = 0;

    for(std::shared_ptr<cluster> medoid : medoids)
      weight += this->clusDistanceMeasure->countClustersDistance(medoid.get(),
                                                                 clusters.at(nonMedoidIndex).get());

    weight /= medoids.size();
    weights->push_back(weight);
  }

  return weights->size();
}

int kMedoidsAlgorithm::fillProbabilitiesFromWeights(std::vector<double> *weights, std::vector<double> *probabilities)
{
  probabilities->clear();

  double weightsSum = 0;

  for(double weight : *weights) weightsSum += weight;

  probabilities->push_back(weights->at(0) / weightsSum);

  double probability;

  for(unsigned int i = 1; i < weights->size(); ++i)
  {
    probability = probabilities->at(i - 1);
    probability += weights->at(i) / weightsSum;
    probabilities->push_back(probability);
  }

  return probabilities->size();
}

double kMedoidsAlgorithm::countCost(std::vector<std::shared_ptr<cluster> > *potentialMedoids)
{
  double cost = 0;

  for(std::shared_ptr<cluster> c : clusters)
  {
    if(!isMedoid(c.get(), potentialMedoids))
    {
      int closestMedoidIndex = findClosestMedoidIndex(c.get(), potentialMedoids);
      cost += getClustersSimilarity(c.get(), potentialMedoids->at(closestMedoidIndex).get());
    }
  }

  return cost;
}

bool kMedoidsAlgorithm::isMedoid(cluster *c, std::vector<std::shared_ptr<cluster> > *medoids)
{
  for(std::shared_ptr<cluster> medoid : *medoids)
    if(c->getClustersId() == medoid.get()->getClustersId()) return true;

  return false;
}

int kMedoidsAlgorithm::findClosestMedoidIndex(cluster *c, std::vector<std::shared_ptr<cluster> > *potentialMedoids)
{
  int closestMedoidIndex = 0;
  double  minDistance = getClustersSimilarity(c, potentialMedoids->at(0).get()),
          distance;

  for(unsigned int medoidIndex = 1; medoidIndex < potentialMedoids->size(); ++medoidIndex)
  {
    distance = getClustersSimilarity(c, potentialMedoids->at(medoidIndex).get());

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
  std::string name =  c1->getMedoid()->getClustersId() + "-" +
                      c2->getMedoid()->getClustersId();

  auto similarityIterator = similarityData.find(name);

  if(similarityIterator == similarityData.end())
    name =  c2->getMedoid()->getClustersId() + "-" +
            c1->getMedoid()->getClustersId();

  similarityIterator = similarityData.find(name);

  if(similarityIterator == similarityData.end())
    return -1;

  return similarityData[name];
}

void kMedoidsAlgorithm::findPotentialBestMedoidConfiguration(std::vector<std::shared_ptr<cluster> > *potentialBestMedoids, double minCost)
{
  double minimalCost = minCost, potentialMinimalCost;
  std::vector<std::shared_ptr<cluster>> currentBestConfiguration = medoids;

  // For each medoid
  for(unsigned int medoidIndex = 0; medoidIndex < medoids.size(); ++medoidIndex)
  {
    std::cout << "Medoid index: " << medoidIndex << std::endl;

    // Exclude this medoid from medoids list
    *potentialBestMedoids = medoids;
    potentialBestMedoids->erase(potentialBestMedoids->begin()+medoidIndex);

    // Substitute missing medoid with each non-medoid cluster and count cost
    for(std::shared_ptr<cluster> c : clusters)
    {
      if (!isMedoid(c.get(), &medoids)) {
        potentialBestMedoids->push_back(c);
        potentialMinimalCost = countCost(potentialBestMedoids);

        if (potentialMinimalCost < minimalCost) {
          minimalCost = potentialMinimalCost;
          std::cout << minimalCost << std::endl;
          currentBestConfiguration.clear();
          currentBestConfiguration = *potentialBestMedoids;
        }

        potentialBestMedoids->pop_back();

      }
    }
  }

  *potentialBestMedoids = currentBestConfiguration;
}

void kMedoidsAlgorithm::createClustersFromMedoids(std::vector<std::shared_ptr<cluster> > *target)
{
  // Ensure that target vector is empty.
  target->clear();

  long index = 0;

  // Create outer clusters.
  for(std::shared_ptr<cluster> medoid : medoids)
  {
    target->push_back(std::make_shared<cluster>(cluster(++index, medoid.get()->getObject())));
    target->back().get()->setWeight(0);
    target->back().get()->addSubcluster(medoid);
    target->back().get()->setRepresentative(medoid.get()->getRepresentative());
    target->back().get()->setMedoid(target->back());
  }

  // Assign objects to outer clusters.
  int closestMedoidIndex;

  for(std::shared_ptr<cluster> c : clusters)
  {
    if(!isMedoid(c.get(), &medoids))
    {
      closestMedoidIndex = findClosestMedoidIndex(c->getMedoid(), &medoids);
      target->at(closestMedoidIndex).get()->addSubcluster(c);
    }
  }
}

unsigned int kMedoidsAlgorithm::setMedoidInWeightedCluster(std::shared_ptr<cluster> clus)
{
  std::vector<std::shared_ptr<cluster>> subclusters;
  clus.get()->getSubclusters(&subclusters);

  if(subclusters.size() == 0) return 0;

  // Initialize on first subcluster being medoid
  double minCost = 0, cost;
  std::shared_ptr<cluster> medoid = subclusters.at(0);
  unsigned int i;

  for(i = 1; i < subclusters.size(); ++i)
    minCost += clusDistanceMeasure->countClustersDistance(subclusters.at(0).get(),
                                                          subclusters.at(i).get())
               * subclusters.at(0).get()->getWeight() * subclusters.at(i).get()->getWeight();

  // Now for every other subcluster
  for(i = 1; i < subclusters.size(); ++i)
  {
    cost = 0;

    for(unsigned int j = 0; j < subclusters.size(); ++j)
    {
      if(j == i) continue;

      cost += clusDistanceMeasure->countClustersDistance(subclusters.at(j).get(),
                                                        subclusters.at(i).get())
              * subclusters.at(j).get()->getWeight() * subclusters.at(i).get()->getWeight();
    }

    if(cost < minCost)
    {
      minCost = cost;
      medoid = subclusters.at(i);
    }

  }

  clus.get()->setMedoid(medoid);

  return i;
}

void kMedoidsAlgorithm::setMedoids(std::vector<std::shared_ptr<cluster> > *newMedoids)
{
  if(newMedoids != nullptr)
  {
    if(newMedoids->size() == numberOfMedoids)
    {
      medoids = *newMedoids;
    }
  }
}

std::vector<std::shared_ptr<cluster>> kMedoidsAlgorithm::getMedoids(std::vector<std::shared_ptr<sample>>* objects)
{
  if(medoids.size() != numberOfMedoids)
  {
    clusterObjects(objects);
    findOptimalMedoids();
  }

  return medoids;
}

void kMedoidsAlgorithm::generateClusteringFromMedoids(std::vector<std::shared_ptr<sample>> *objects, std::vector<std::shared_ptr<cluster> > *target)
{
  if(!canGroupingBePerformed(objects)) return;

  clusterObjects(objects);

  if(medoids.size() != numberOfMedoids) findOptimalMedoids();

  createClustersFromMedoids(target);
}

