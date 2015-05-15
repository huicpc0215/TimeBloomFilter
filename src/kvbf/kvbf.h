/*=============================================================================
#     FileName: kvbf.h
#         Desc: kvbf.h
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-12 14:46:11
#      History:
=============================================================================*/
#ifndef DEBUG
#define DEBUG
#endif

#ifndef KVBF_H
#define KVBF_H
#include "kvbf_block.h"
class kvbf{
    public:
    // default construction
    kvbf(size_t hash_num,size_t cell_num_per_block,size_t  layer_num,size_t byte_num);

    // destory function
    ~kvbf();

    // get key's value in this block
    // parameters : char *, byte *
    // return : void
    void get(const char *key,byte* answer);

    // insert the key in this block
    // parameters : char *, byte *
    // return : void
    void ins(const char *key,byte* _Value);

    // delete the key in this block
    // parameters : char *, byte *
    // return : void
    void del(const char *key,byte* _Value);

    // number of block;
    size_t bk_num;

    private:
    //tmp_value
    byte *tmp_value;

    // data storage
    kvbf_block **block;

};
#endif
