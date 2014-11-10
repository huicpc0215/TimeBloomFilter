/*=============================================================================
#     FileName: TimeBloomFilter.h
#         Desc: description for Time Bloom Filter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-11-07 09:37:15
#      History:
=============================================================================*/


#ifndef TimeBloomFilter_headers_TimeBloomFilter_H_
#define TimeBloomFilter_headers_TimeBloomFilter_H_
#include"BloomFilterCell.h"
#include<vector>
using namespace std;

class TimeBloomFilter{
    private:
    // Cellnumber BloomfilterCell also
    // type: BloomfilterCell
    vector<BloomFilterCell> B;
    vector<int> B_second;

    // cellnumber
    // type: int
    int CellNumber;

    // hash number
    // type : int
    int hashnumber;

    // k's hash that shows the k distinct number for any Integer
    // parameters: int x ( that to be hashed ) , int k ( hash number )
    // return : hashed position vector
    vector<int> get_hash(int x);

    public:
    // insert a integer and set the k position to zero
    // parameters: int x ( that want to insert into the TimeBloomFilter)
    // return : void
    void insert(int x);

    //construction function
    TimeBloomFilter();

    //construction with Cellnumber's bloomfiltercell
    TimeBloomFilter(int _cellnumber);

    //constuction with Cellnumber and hash number
    TimeBloomFilter(int _cellnumber,int _hashnumber);
    // query a integer how long the number has hashed into.
    // parameters: int x( that want to query if the element has hashed into the TimeBloomFilter)
    // return : 0-INF how long the number has hashed into
    int query(int x);

    // increase every cell by one unit
    // parameters: NULL
    // return : void
    void increase();
};
#endif