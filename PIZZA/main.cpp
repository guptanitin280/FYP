#include<bits/stdc++.h>
#include "algorithms/BruteForce.h"
using namespace std;

int main() {
    string filePath = "test_data/a.txt";
    BruteForce bf(filePath);
    Output o = bf.solve();
    return 0;
}