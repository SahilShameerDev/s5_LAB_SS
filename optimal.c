#include<stdio.h>
#include<stdlib.h>


void main(){
    int f,n,out[20],pf=0,max,flag1,flag2,opt[20],i,j,k,exist,pos;

    n = 14;
    f=4;
    int in[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3};

    for(i=0;i<f;i++){
        out[i] = -1;
    }

    for(i=0;i<n;i++){
        flag1 = 1;
        flag2 = 1;

        for(j=0;j<f;j++){
            if(out[j] == in[i]){
                flag1 = 0;
                flag2 = 0;
                break;
            }
        }
        if(flag1 == 1){
            for(j=i;j<f;j++){
                if(i<f){

                    out[j] = in[i];
                    pf++;
                    flag2 = 0;
                    break;
                }
            }
        }
        if(flag2 == 1){
            for(j=0;j<f;j++){
                opt[j] = 0;
            }
            for(j=0;j<f;j++){
                for(k = i+1; k<n; k++){
                    if(out[j] == in[k]){
                        opt[j] = k-i;
                        break;
                    }
                }
            }
            exist = 0;

            for(j=0;j<f;j++){
                if(opt[j] == 0){
                    pos = j;
                    exist = 1;
                    break;
                }
            }

            if(exist==0){
                max = opt[0];
                pos = 0;
                for(j=0;j<f;j++){
                    if(max<opt[j]){
                        max = opt[j];
                        pos = j;
                    }
                }
            }

            out[pos] = in[i];
            pf++;
        }

        for(j=0;j<f;j++){
            printf("%d ", out[j]);
        }
        printf("page frame: %d \n", pf);
    }
}