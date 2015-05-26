// CS 14 Lab
// Lab Number 7
// Name: Robinson Vo-Ly
// SID: 861166275
// Date: 5/25/2015
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <ctime>
#include <time.h>
#include <unordered_set>
#include <set>

using namespace std::chrono;

std::vector<std::string> shuffle(std::vector<std::string>& v);
std::pair<double, double> hash_function(std::vector<std::string> v, int n); //std::pair<Insertion_Time,Query_Time>
std::pair<double, double> tree_function(std::vector<std::string> v, int n);

int main()
{
    /*Set up randomization*/

    srand(time(0));
    
    /*File streaming process */
    int n = 1;
    std::string file = "words.txt";
    std::vector<std::string> words;
    std::string input;
    std::fstream inFile;
    inFile.open(file.c_str());
    if(!inFile)
    {
        std::cout << "Error: File cannot be opened." << std::endl;
    }
    while(inFile.good())
    {
        inFile >> input;
        words.push_back(input);
    }
    
    inFile.close();
    inFile.open("data.txt");
    
    std::pair<double, double> avg_hash_times;
    std::pair<double, double> avg_tree_times;
    
    while (n <= 50000)
    {
        for(int i = 0; i < 10; ++i)
        {
            shuffle(words);

            std::pair<double, double> hash_times = hash_function(words, n);
            std::pair<double, double> tree_times = tree_function(words, n);
            
            avg_hash_times.first += hash_times.first;
            avg_hash_times.second += hash_times.second;
            
            avg_tree_times.first += tree_times.first;
            avg_tree_times.second += tree_times.second;
        }
        
        avg_hash_times.first /= 10;
        avg_hash_times.second /= 10;
        avg_tree_times.first /= 10;
        avg_tree_times.second /= 10;
        
        inFile << n << " "
        << avg_tree_times.first << " "
        << avg_hash_times.first << " "
        << avg_tree_times.second << " "
        << avg_hash_times.second << "\n";
        
        if(n + 5000 > 50000 && n != 50000)
        {
            n = 50000;
        }
        else
        {
            n += 5000;
        }
    }
}

std::vector<std::string> shuffle(std::vector<std::string>& v)
{
    int fswap;
    int sswap;
    
    for(int i = 0; i < 50000; ++i)
    {
        fswap = rand() % 49999;
        sswap = rand() % 49999;
        std::string temp;
        temp = v.at(fswap);
        v.at(fswap) = v.at(sswap);
        v.at(sswap) = temp;
    }
    
    return v;
}

std::pair<double, double> hash_function(std::vector<std::string> v, int n)
{
    high_resolution_clock::time_point start, end;
    std::pair<double,double> hash_time;
    std::unordered_set<std::string> u_set;
    
    /*Timing for insert */
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; ++i)
    {
        u_set.insert(v.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = duration_cast<duration<double>>(end - start);
    hash_time.first = elapsed_seconds.count() * 1000;
    
    /*Timing for find */
    start = std::chrono::high_resolution_clock::now();
    u_set.find(v.at(5));
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = duration_cast<duration<double>>(end - start);
    hash_time.second = elapsed_seconds.count() * 1000;
    
    return hash_time;
}

std::pair<double, double> tree_function(std::vector<std::string> v, int n)
{
    high_resolution_clock::time_point start, end;
    std::pair<double,double> tree_time;
    std::set<std::string> o_set;
    
    /*Timing for insert */
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < n; ++i)
    {
        o_set.insert(v.at(i));
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = duration_cast<duration<double>>(end - start);
    tree_time.first = elapsed_seconds.count() * 1000;
    
    /*Timing for find */
    start = std::chrono::high_resolution_clock::now();
    o_set.find(v.at(5));
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = duration_cast<duration<double>>(end - start);
    tree_time.second = elapsed_seconds.count() * 1000;
    
    return tree_time;
    
}