#include <fstream>
#include <iostream>
#include <sstream>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    // Open the CSV file
    ifstream file("../data.csv");
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }


    // Read each line of the file
    string line;
    while (getline(file, line)) {
        // Parse the line into fields
        vector<string> temp;
        string cur="";
        for(auto x: line){
            if(x==','){
                temp.push_back(cur);
                cur.clear();
            }else{
                cur+=x;
            }
        }
        temp.push_back(cur);
        cout<<setw(44)<<temp[1];
        cout<<'|';
        cout<<setw(5)<<temp[2];
        cout<<'|'<<temp[0]<<endl;

    }

    // Close the file
    file.close();

    return 0;
}
