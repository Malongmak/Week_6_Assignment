#ifndef PATIENT_HEAP_H
#define PATIENT_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

// Structure to hold patient information
typedef struct Patient {
    int id;                
    char name[50];        
    int severity;         
} Patient;

// Structure for the max-heap
typedef struct MaxHeap {
    Patient* patients[MAX_PATIENTS]; 
    int size;                        
} MaxHeap;

// Function prototypes
MaxHeap* createHeap();
void insert(MaxHeap* heap, Patient* patient);
Patient* extractMax(MaxHeap* heap);
void heapify(MaxHeap* heap, int index);
void updateSeverity(MaxHeap* heap, int id, int newSeverity);
void displayPatients(MaxHeap* heap);
Patient* createPatient(int id, const char* name, int severity);

#endif // PATIENT_HEAP_H
