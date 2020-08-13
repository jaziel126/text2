#include<iostream>
#include<windows.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>//标准头文件，提供宏va_start、va_arg和va_end,
//用于存取变长参数表
using namespace std;

#define MAX_ARRAY_DIM 8//假设数组维度最长为8
#define OVERFLOW -2
#define OK 1
#define ERROR -1
typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType* base;//数组元素基地址
    int dim;//数组维度
    int* bounds;//存储数组维界（各维度大小）
    int* constants;//存储映像函数常数ci；便于求元素在数组中的位置
}Array;

//构建维度为dim的数组A；
Status InitArray(Array& A, int dim, ...) {
    //检查dim是否合法
    if (dim<1 || dim>MAX_ARRAY_DIM) return OVERFLOW;
    A.dim = dim;
    //读取变长参数表，存入bounds用于求出数组元素总数elemtotal来确定给数组分配空间大小
    int elemtotal = 1;
    va_list ap;
    va_start(ap, dim);
    A.bounds = (int*)malloc(dim * sizeof(int));
    for (int i = 0;i < dim;i++) {
        A.bounds[i] = va_arg(ap, int);
        elemtotal *= A.bounds[i];
    }
    va_end(ap);
    //分配数组空间
    A.base = (ElemType*)malloc(elemtotal * sizeof(ElemType));
    if (!A.base) return(OVERFLOW);
    //求映像函数常数ci，存入constants，便与后面求元素在数组中的相对地址；
    A.constants = (int*)malloc(dim * sizeof(int));
    A.constants[dim - 1] = 1;//Cn为L，L是每个元素大小；
    for (int i = dim - 2;i >= 0;i--) {
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
    }
    return OK;
}

//销毁数组A
Status DestoryArray(Array &A) {
    if (!A.base) return ERROR;
    free(A.base);
    A.base = NULL;
    if (!A.bounds) return ERROR;
    free(A.bounds);
    A.bounds = NULL;
    if (!A.constants) return ERROR;
    free(A.constants);
    A.constants = NULL;
    return OK;
}

//求元素e，就是va_list变长参数表指出的元素在数组中的位置
Status LocatArray(Array A, va_list ap, int &off) {
    off = 0;
    for (int i = 0;i < A.dim;i++) {
        int a = va_arg(ap, int);
        off += A.constants[i] * a;
    }
    return OK;
}

//存入数
Status AssignArray(Array& A, ElemType e, ...) {
    va_list ap;
    va_start(ap, e);
    int off;
    LocatArray(A, ap, off);
    *(A.base + off) = e;
    va_end(ap);
    return OK;
}

//取出数
Status ValueArray(ElemType& e, Array A, ...) {
    va_list ap;
    va_start(ap, A);
    int off;
    LocatArray(A, ap, off);
    e = *(A.base + off);
    va_end(ap);
    return OK;
}

int main() {
    int dim = 2;
    Array A;
    InitArray(A, dim, 3, 4);
    int e;
    cin >> e;
    AssignArray(A, e, 2, 2);
    int b;
    ValueArray(b,A, 2, 2);
    cout << b;
    int c;cin >> c;
    AssignArray(A, c, 2, 1);
    int d;
    ValueArray(d, A, 2, 1);
    cout << d;
    return OK;
}