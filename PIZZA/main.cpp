#include<bits/stdc++.h>
#include "algorithms/BruteForce.h"
using namespace std;

int main() {
    string filePath = "test_data/a.txt";
    BruteForce bf(filePath);
    Output o = bf.solve();
    for(auto &c:o.features){
        cout<<c<<" ";
    }
    cout<<endl;
    return 0;
}