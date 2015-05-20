/*=============================================================================
#     FileName: main.cpp
#         Desc: simulation main function
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-06 18:46:30
#      History:
=============================================================================*/
#include "proceed/proceed.h"
#include "kvbf/kvbf.h"
#include "./sbf_sigcomm2006/sbf.h"
#include<string.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<map>
#include<time.h>
typedef unsigned char byte;
//size_t kvbf_block::cl_num=0;
size_t kvbf_cell::ly_num=0;
size_t kvbf_cell::by_num=0;
map<string,byte> mp;
map<int,int> vmp;
map<int,int>::iterator it;
int mxsize;
ifstream fi;
ofstream fo;
#define hash_default 4
#define cell_default 90720
#define layer_default 3

int hash_num_begin=hash_default;
int hash_num_end=hash_default;
int cell_num_begin=cell_default;
int cell_num_end=cell_default;
int layer_num_per_cell_begin=layer_default;
int layer_num_per_cell_end=layer_default;

int main(int argc,char *argv[]){
    if( argc < 3 ){
        fprintf(stdout,"no input file name or change type\n");
        return 0;
    }
    int p = atoi(argv[2]);
    if( p==0 ){
        printf("please choose hash_num(default %d) range[,]:\n",hash_default);
        scanf("%d%d",&hash_num_begin,&hash_num_end);
    }
    else if( p==1 ){
        printf("please choose cell_num(default %d) range[,]:\n",cell_default);
        scanf("%d%d",&cell_num_begin,&cell_num_end);
    }
    else if( p==2 ){
        printf("please choose layer_num(default %d) range[,]:\n",layer_default);
        scanf("%d%d",&layer_num_per_cell_begin,&layer_num_per_cell_end);
    }
    else {
        printf("no %d options\n",p);
        return 0;
    }
    proceed(argv[1]);
    fo.open("result.out");
    srand(time(NULL));
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_num_begin;j<=cell_num_end;j+=cell_default){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                mxsize=0;
                vmp.clear();
                printf("start simulation hash = %d cell = %d layer = %d \n",i,j,k);
                if(p==0) printf("hash_num = %d ",i);
                else if(p==1) printf("cell_num_per_hash = %d ",j);
                else printf("layer_num_per_cell = %d ",k);
                kvbf* KVBF;
                sbf* SBF;
                KVBF = new kvbf(i,j/k,k,1);
                SBF = new sbf(i,j);
                fi.open("data.in");
                mp.clear();
                string s;
                char ch[10];
                byte answer,real_answer,bytev,sbf_answer;
                int v;
                int allcnt = 0;
                int wrong_query = 0,sbf_wrong_query = 0;
                while( fi>>s ){
                    //if( allcnt % 10000 == 0 ) printf("proceed %d packet!\n",allcnt);
                    fi>>v;
                    bytev =(byte)v;
                    //cout<<s<<" "<<v<<endl;
                    //scanf("%s",ch);
                    vmp[bytev]++;
                    KVBF->get(s.c_str(),&answer);
                    SBF->get(s.c_str(),&sbf_answer);
                    real_answer=mp[s];

                    if( real_answer != answer ){
                        wrong_query++;
                    }
                    if( real_answer != sbf_answer ){
                        sbf_wrong_query++;
                    }

                    //if( answer!= 0 ){
                    //    KVBF->del( s.c_str(),&answer );
                    //}

                    if( v < 16 ){
                        mp[s]=bytev;
                        //KVBF->ins(s.c_str(),&bytev);
                        if(sbf_answer==0)SBF->ins(s.c_str(),&bytev);
                        else SBF->mdf(s.c_str(),&bytev);
                        KVBF->mdf(s.c_str(),&bytev);
                    }
                    else {
                        mp[s]=0;
                        KVBF->del( s.c_str(),&answer);
                        SBF->del( s.c_str(),&sbf_answer);
                    }
                    mxsize= max( mxsize , (int)mp.size() );
                    allcnt++;
                }
                printf("error rate = %lf sbf error rate = %lf \n",1.0*wrong_query/allcnt,1.0*sbf_wrong_query/allcnt);
                int variant = (p==0?i:( p==1?j:k ));
                fo<<variant<<" "<<1.0*wrong_query/allcnt<<" "<<1.0*sbf_wrong_query/allcnt<<endl;
                fi.close();
                delete(KVBF);
                delete(SBF);
                for(it=vmp.begin();it!=vmp.end();it++){
                    printf("value -> %d  count = %d\n",it->first,it->second);
                }
                printf("max size = %d\n",mxsize);
            }
        }
    }
    fo.close();
    return 0;
}
