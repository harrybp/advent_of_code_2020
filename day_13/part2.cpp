#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

long long modInverse(long long a, long long m){
    a = a % m;
    for (long long x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return a;
}

int main(){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile("input.txt");

    // Dont care about first line
    getline(inputFile, inputText);
    getline(inputFile, inputText);
    std::stringstream ss(inputText);

    int index = 0;
    std::vector<int> m_v;
    std::vector<int> a_v;
    long long M = 1;

    // Loop through, storing m and a, multiply all ms into M
    while(std::getline(ss, tokenText, ',')){
        if(tokenText != "x"){
            int busTime = stoi(tokenText);
            m_v.push_back(busTime);
            a_v.push_back(-index);
            M *= busTime;
        }
        index++;
    }

    // Calculate bi  = M/m
    //           bip = inverse of bi mod m
    // Total up a * bi * bip
    long long total = 0;
    for(int i = 0; i < m_v.size(); i++){
        long long bi = M / m_v[i];
        long long bip = modInverse(bi, m_v[i]);
        total += a_v[i] * bi * bip;
    }

    // Answer is total % M
    // Adjust result to handle negatives
    long long result = (M + (total % M)) % M;
    printf("%lld\n", result);

    inputFile.close();
    return 1;
}
