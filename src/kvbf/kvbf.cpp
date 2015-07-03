/*=============================================================================
#     FileName: kvbf.cpp
#         Desc: kvbf.cpp
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-12 14:54:55
#      History:
=============================================================================*/
#include"kvbf.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>

//#define PARA


kvbf::kvbf(size_t hash_num=3,size_t cell_num=1024,size_t layer_num=2,size_t byte_num=1){
    bk_num = hash_num;
#ifdef PARA
    omp_set_num_threads(bk_num);
#endif
    //kvbf_block::cl_num = cell_num_per_block;
    int nowsize=cell_num/hash_num;
	int remain=cell_num;
    block = (kvbf_block **) malloc ( bk_num * sizeof( kvbf_block* ) );
    for(size_t i=0;i<bk_num;i++){
		block[i]=new kvbf_block( (int)i+1 ,(i==bk_num-1?remain:nowsize));
        remain-=nowsize;
    }
}
kvbf::~kvbf(){
    for(size_t i=0;i<bk_num;i++){
        delete(block[i]);
    }
    free(block);
}

void kvbf::get(const char *key,byte* answer){
	*answer=0xFF;
#ifdef PARA
#pragma omp parallel for
#endif
    for(size_t i=0;i<bk_num;i++){
        byte tmp=0;
        block[i]->get(key,&tmp);
        (*answer)&=tmp;
    }
}

void kvbf::ins(const char *key,byte* _Value){
#ifdef PARA
#pragma omp parallel for
#endif
    for(size_t i=0;i<bk_num;i++){
        byte tmp=0;
		tmp = *_Value;
        block[i]->ins(key,&tmp);
    }
}

void kvbf::del(const char *key,byte* _Value){
#ifdef PARA
#pragma omp parallel for
#endif
    for(size_t i=0;i<bk_num;i++){
        byte tmp=0;
		tmp = *_Value;
        block[i]->del(key,&tmp);
    }
}

void kvbf::mdf(const char *key,byte* newValue){
	printf("use modify function\n");
	printf("DO NOT USE modify function!\n");
}
