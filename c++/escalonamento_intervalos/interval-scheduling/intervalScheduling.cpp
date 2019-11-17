#include<iostream>

using namespace std;


struct Job {
    int startTime;
    int finishTime;
    bool isDone;
};


/* MergeSort prototypes */

void mergeSort(Job* array, int start, int end);
void merge(Job* array, int start, int mid, int end);


/* main function */

int main() {
    int number;
    cin >> number;

    if(number < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    Job array[number];

    for(int i=0; i<number; i++) {
        cin >> array[i].startTime >> array[i].finishTime;
        array[i].isDone = false;
    }

    mergeSort(array, 0, number-1);  /* merge sort */

    int total = 1;
    Job compare = array[0];
    array[0].isDone = true;

    for(int i=1; i<number; i++) {
        if(array[i].startTime >= compare.finishTime) {
            total++;
            compare = array[i];
            array[i].isDone = true;
        }
    }

    cout << "\n\n" << total << endl;

    for(int i=0; i<number; i++) {
        if(array[i].isDone == true) {
            cout << array[i].startTime << " " << array[i].finishTime << endl;
        }
    }

    return 0;
}


/* MergeSort Definitions */

void mergeSort(Job* array, int start, int end) {
    if(start < end) {
        int mid = (start+end)/2;

        mergeSort(array, start, mid);
        mergeSort(array, mid+1, end);

        merge(array, start, mid, end);
    }

    return ;
}


void merge(Job* array, int start, int mid, int end) {
    int amount1 = mid - start + 1;
    int amount2 = end - mid;

    Job* tempArray1 = new Job[amount1];
    Job* tempArray2 = new Job[amount2];

    for(int i=0; i<amount1; i++) {
        tempArray1[i] = array[start+i];
    }

    for(int i=0; i<amount2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    int index1, index2, indexMerged;
    index1 = index2 = 0;
    indexMerged = start;

    /* sorting in ascending order of finishTime */
    while(index1<amount1 && index2<amount2) {
        if(tempArray1[index1].finishTime <= tempArray2[index2].finishTime) {
            array[indexMerged++] = tempArray1[index1++];
        }
        else {
            array[indexMerged++] = tempArray2[index2++];
        }
    }

    while(index1 < amount1) {
        array[indexMerged++] = tempArray1[index1++];
    }

    while(index2 < amount2) {
        array[indexMerged++] = tempArray2[index2++];
    }

    delete[] tempArray1;
    delete[] tempArray2;

    return ;
}

