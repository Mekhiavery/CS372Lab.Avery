#include "Dictionary.hpp"
#include <map>
#include <random>
#include <string>
#include <cassert>
#include <iostream>
int main(){
    Dictionary<int,int> d;
    std::map<int,int> m;
    std::mt19937 g(70321);
    for(int iteration=0;iteration<12000;iteration++){
       int k=int(g()%350), v=int(g()%10000);
       switch(g()%4){
         case 0: d[k]=v; m[k]=v; break;
         case 1: d.insert(k,v); m.insert({k,v}); break;
         case 2: assert(d.erase(k)==(m.erase(k)>0)); break;
         case 3: {
           auto it=m.find(k);
           if(it==m.end()) {bool threw=false; try {d.at(k);} catch (const std::out_of_range&) {threw=true;} assert(threw);}
           else assert(d.at(k)==it->second);
         } break;
       }
       assert(d.size()==m.size());
       if(iteration%40==0){
         auto& keyList=d.keys();
         auto a=keyList.begin();
         for(const auto& [key,value]:m) { assert(a!=keyList.end()); assert(*a==key); ++a; assert(d.at(key)==value); }
       }
    }
    std::cout<<"Stress test passed with 12,000 random operations!\n";
}
