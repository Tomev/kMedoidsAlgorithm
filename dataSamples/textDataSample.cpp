//
// Created by Tomev on 13.06.2017.
//

#include "textDataSample.h"

void textDataSample::print()
{
    std::cout << "Data: \n";

    for(auto kv : attributesValues ) cout << kv.first << ": " << kv.second << endl;
}
