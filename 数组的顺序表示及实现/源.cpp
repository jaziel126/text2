#include<iostream>
#include<windows.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>//��׼ͷ�ļ����ṩ��va_start��va_arg��va_end,
//���ڴ�ȡ�䳤������
using namespace std;

#define MAX_ARRAY_DIM 8//��������ά���Ϊ8
#define OVERFLOW -2
#define OK 1
#define ERROR -1
typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType* base;//����Ԫ�ػ���ַ
    int dim;//����ά��
    int* bounds;//�洢����ά�磨��ά�ȴ�С��
    int* constants;//�洢ӳ��������ci��������Ԫ���������е�λ��
}Array;

//����ά��Ϊdim������A��
Status InitArray(Array& A, int dim, ...) {
    //���dim�Ƿ�Ϸ�
    if (dim<1 || dim>MAX_ARRAY_DIM) return OVERFLOW;
    A.dim = dim;
    //��ȡ�䳤����������bounds�����������Ԫ������elemtotal��ȷ�����������ռ��С
    int elemtotal = 1;
    va_list ap;
    va_start(ap, dim);
    A.bounds = (int*)malloc(dim * sizeof(int));
    for (int i = 0;i < dim;i++) {
        A.bounds[i] = va_arg(ap, int);
        elemtotal *= A.bounds[i];
    }
    va_end(ap);
    //��������ռ�
    A.base = (ElemType*)malloc(elemtotal * sizeof(ElemType));
    if (!A.base) return(OVERFLOW);
    //��ӳ��������ci������constants�����������Ԫ���������е���Ե�ַ��
    A.constants = (int*)malloc(dim * sizeof(int));
    A.constants[dim - 1] = 1;//CnΪL��L��ÿ��Ԫ�ش�С��
    for (int i = dim - 2;i >= 0;i--) {
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
    }
    return OK;
}

//��������A
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

//��Ԫ��e������va_list�䳤������ָ����Ԫ���������е�λ��
Status LocatArray(Array A, va_list ap, int &off) {
    off = 0;
    for (int i = 0;i < A.dim;i++) {
        int a = va_arg(ap, int);
        off += A.constants[i] * a;
    }
    return OK;
}

//������
Status AssignArray(Array& A, ElemType e, ...) {
    va_list ap;
    va_start(ap, e);
    int off;
    LocatArray(A, ap, off);
    *(A.base + off) = e;
    va_end(ap);
    return OK;
}

//ȡ����
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