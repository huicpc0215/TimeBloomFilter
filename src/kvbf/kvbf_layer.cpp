/*=============================================================================
#     FileName: kvbf_layer.cpp
#         Desc: implemtation
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-11 16:30:49
#      History:
=============================================================================*/
#include<stdlib.h>
#include"kvbf_layer.h"
#include<string.h>

kvbf_layer::kvbf_layer(size_t b=1){
	Value = new byte;
	*Value = 0;
}

kvbf_layer::~kvbf_layer(){
    delete(Value);
}

byte* kvbf_layer::get(){
    return Value;
}

