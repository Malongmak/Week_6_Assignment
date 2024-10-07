#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

// function to define a structure to hold patient information
typedef struct Patient {
    int id;                
    char name[50];        
    int severity;         
} Patient;

// function to define a structure for the max-heap
typedef struct MaxHeap {
    Patient* patients[MAX_PATIENTS]; 
    int size;                        
} MaxHeap;

// function prototypes
MaxHeap* createHeap();
void insert(MaxHeap* heap, Patient* patient);
Patient* extractMax(MaxHeap* heap);
void heapify(MaxHeap* heap, int index);
void updateSeverity(MaxHeap* heap, int id, int newSeverity);
void displayPatients(MaxHeap* heap);
Patient* createPatient(int id, const char* name, int severity);

int main() {
    MaxHeap* heap = createHeap();

    // function to add some patients to the system
    printf("Adding patients to the emergency room...\n");
    insert(heap, createPatient(1, "James", 5));
    insert(heap, createPatient(2, "John", 7));
    insert(heap, createPatient(3, "Daniela", 2));
    insert(heap, createPatient(4, "Maria", 10));
    insert(heap, createPatient(5, "Jacob", 6));

    // function to display the current queue of patients
    printf("\nCurrent patients waiting for treatment:\n");
    displayPatients(heap);

    // function to extract the patient with the highest severity for treatment
    printf("\nNext patient to be treated...\n");
    Patient* treatedPatient = extractMax(heap);
    if (treatedPatient) {
        printf("Treating patient: %s with severity %d\n", treatedPatient->name, treatedPatient->severity);
        free(treatedPatient); 
    }

    // function to update the severity of a patient
    printf("\nUpdating severity of patient ID 2 (John) to 8...\n");
    updateSeverity(heap, 2, 8);

    // function to display the updated queue of patients
    printf("\nUpdated patients waiting for treatment:\n");
    displayPatients(heap);

    // function to clean up remaining patients in the heap
    while (heap->size > 0) {
        free(extractMax(heap));
    }
    free(heap); 

    return 0;
}

// function to create a new max-heap
MaxHeap* createHeap() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->size = 0; 
    return heap;
}

// function to create a new patient
Patient* createPatient(int id, const char* name, int severity) {
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    patient->id = id;
    strncpy(patient->name, name, 50); 
    patient->severity = severity; 
    return patient;
}

// function to insert a patient into the max-heap
void insert(MaxHeap* heap, Patient* patient) {
    if (heap->size >= MAX_PATIENTS) {
        printf("Heap is full, cannot add more patients.\n");
        return;
    }
    heap->patients[heap->size] = patient;
    int index = heap->size;
    heap->size++; 

    // function to reheapify and maintain max-heap property
    while (index > 0) {
        int parentIndex = (index - 1) / 2; 
        if (heap->patients[index]->severity > heap->patients[parentIndex]->severity) {
            // function to swap if current patient's severity is greater than parent's
            Patient* temp = heap->patients[index];
            heap->patients[index] = heap->patients[parentIndex];
            heap->patients[parentIndex] = temp;
            index = parentIndex; 
        } else {
            break; 
        }
    }
}

// function to extract the patient with the highest severity from the max-heap
Patient* extractMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty, no patients to treat.\n");
        return NULL;
    }
    Patient* maxPatient = heap->patients[0]; 
    heap->patients[0] = heap->patients[heap->size - 1];
    heap->size--; 
    heapify(heap, 0); 
    return maxPatient; 
}

// function to maintain the max-heap property
void heapify(MaxHeap* heap, int index) {
    int largest = index; 
    int left = 2 * index + 1; 
    int right = 2 * index + 2; 

    // function to check if the left child is larger
    if (left < heap->size && heap->patients[left]->severity > heap->patients[largest]->severity) {
        largest = left;
    }
    // function to check if the right child is larger
    if (right < heap->size && heap->patients[right]->severity > heap->patients[largest]->severity) {
        largest = right;
    }
    // function to swap if largest is not the current index
    if (largest != index) {
        Patient* temp = heap->patients[index];
        heap->patients[index] = heap->patients[largest];
        heap->patients[largest] = temp;
        heapify(heap, largest); 
    }
}

// function to update severity
void updateSeverity(MaxHeap* heap, int id, int newSeverity) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->patients[i]->id == id) {
            heap->patients[i]->severity = newSeverity; 

            // Reheapify to maintain max-heap property
            heapify(heap, i); 
            return;
        }
    }
    printf("Patient with ID %d not found.\n", id); 
}

// function to display patients
void displayPatients(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("No patients currently waiting for treatment.\n");
        return;
    }
    for (int i = 0; i < heap->size; i++) {
        printf("ID: %d, Name: %s, Severity: %d\n",
               heap->patients[i]->id, heap->patients[i]->name, heap->patients[i]->severity);
    }
}
