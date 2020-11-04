// CSC220 Assignment 1
// 09/20/2020
// Kristina Ilyovska

#include <stdio.h>
#include <stdlib.h>

void mergesort(int* arr, int length);
void mergesort_internal(int * arr, int* aux, int length);
void merge(int* arr, int* aux, int length);
int common(int* a, int*b, int m, int n);

void mergesort(int* arr, int length) { //wrapper, allocates memory only once
	int* aux = (int*) malloc(sizeof(int) * length);
	mergesort_internal(arr, aux, length);
	free(aux);
}

void mergesort_internal(int * arr, int* aux, int length) {
	if (length < 2) {
		return;
	}
	mergesort_internal(arr, aux, length/2);
	mergesort_internal(arr + (length/2), aux, length - (length/2));
	merge(arr, aux, length);
}


void merge(int* arr, int* aux, int length) { 
	int begin = 0;
	int mid = length/2;
	int i = 0;
    int firstHalfB = begin;
    int secondHalfB = mid;
    while (firstHalfB < mid && secondHalfB < length) { //in bounds of both arrays
        if (arr[firstHalfB] < arr[secondHalfB]) {
            aux[i] = arr[firstHalfB];
            ++firstHalfB;
        } else {
            aux[i] = arr[secondHalfB];
            ++secondHalfB;
        }
        ++i;
    }
    if (secondHalfB == length) { //first array half is longer
        for (int j = firstHalfB; j < mid; ++j) {
            aux[i] = arr[j];
            ++i;
        }
    } else { //second array half is longer
        for (int j = secondHalfB; j < length; ++j) {
            aux[i] = arr[j];
            ++i;
        }
    }
    for (int k = 0; k < length; ++k) { // copy sorted values to original array
        arr[k] = aux[k];
    }
}

int common(int* a, int*b, int m, int n){
	int count = 0;
	mergesort(a, m); //sort a
	mergesort(b, n); //sort b
	int i = 0, j = 0;
	while (i < m - 1 && j < n - 1) { // -1 accounts for not going out of bounds
        if (a[i] == b[j]) {
            ++count;
            if (a[i] == a[i + 1]) {
            	while (a[i] == a[i + 1]) { //skip all duplicates in a
					++i;
				}
            }
            if (b[j] == b[j + 1]) {
            	while (b[j] == b[j + 1]) { //skip all duplicates in b
					++j;
				}
            } 
            ++i;
            ++j;
        } else if (a[i] < b[j]) {
        	++i;
        } else{
        	++j;
        }        
    }
	return count;
}