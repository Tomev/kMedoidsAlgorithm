#include <iostream>
#include <c++/ctime>
#include <unordered_map>

#include "dataReader.h"
#include "dataParser.h"
#include "textDataReader.h"
#include "textDataParser.h"
#include "groupingAlgorithm.h"
#include "kMedoidsAlgorithm.h"

// Tests
void checkAttributesData(unordered_map<string, unordered_map<string, attributeData*>> *attributesData);

using namespace std;

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");

  dataReader* dr = new textDataReader(&sourceFile);
  dataParser* dp = new textDataParser();

  unordered_map<string, unordered_map<string, attributeData*>> attributesData;
  attributesData["numerical"] = unordered_map<string, attributeData*>();
  attributesData["categorical"] = unordered_map<string, attributeData*>();

  dr->gatherAttributesData(&attributesData);
  dp->setAttributesOrder(dr->getAttributesOrder());

  string line;
  vector<sample*> samples;
  vector<cluster> clusters;


  for(int i = 0; i < 1000; ++i)
  {
    dr->getNextRawDatum(dp->buffer);
    dp->addDatumToContainer(&samples);
    dp->parseData(samples.back());
  }

  groupingAlgorithm* a = new kMedoidsAlgorithm(10);

  a->groupObjects(&samples, &clusters);

  //checkAttributesData(&attributesData);

  cout << "Clusters size: " <<  clusters.size() << endl;

  return 0;
}

void checkAttributesData(unordered_map<string, unordered_map<string, attributeData*>> *attributesData)
{
  cout << "Categorical attributes number: " << attributesData->at("categorical").size() << endl;
  cout << "Numerical attributes number: " << attributesData->at("numerical").size() << endl;

  // Gather keys

  vector<string> catKeys;
  catKeys.reserve(attributesData->at("categorical").size());
  vector<string> numKeys;
  numKeys.reserve(attributesData->at("numerical").size());

  for(auto kv : attributesData->at("categorical")) catKeys.push_back(kv.first);

  for(auto kv : attributesData->at("numerical")) numKeys.push_back(kv.first);

  cout << "Numerical attributes:\n";

  for(string attributeName : numKeys) cout << attributeName << endl;

  cout << "Categorical attributes:\n";

  for(string attributeName : catKeys) cout << attributeName << endl;


}