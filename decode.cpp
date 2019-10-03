//
//  decode.cpp
//  Project_One
//  CSE 310: #84794
//  Created by Yash Babaria on 9/4/19.
//  Copyright © 2019 Yash Babaria. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

// function headers for the program
void insertion(string*,int);
void mergeSort(string*,int,int);
void merge(string*,int,int,int);
int alreadyInNext(int*, int,int);

int main(int argc,const char* argv[]) {
    // We now take the input from the user get sorting alg the user wants
    string sort = argv[1];
    // We start making a string indexLine which is the index of where the actual word is located in the list
    string indexLine;
    // We use this while to go through each line until the end of the file
    while(getline(cin,indexLine)){
        // We now create string line which takes in the encoded line
        string line;
        getline(cin,line);
        // If the line is a blank space then we output the a new line
        if(line.length() == 0){
            cout << endl;
        }else{
            // now we create the index by converting indexLine into a int
            int index = atoi(indexLine.c_str());
            // creates a temp which copies the
            string temp = "";
            for(int i = 0; i < line.length();i++){
                temp += line[i];
            }
            // string* numInStrings is will take up only the cluster size of the variables
            string* numInStrings = new string[line.length()];
            int count = 0;
            for(int i = 0; i < line2.length(); i++){
                int f = atoi(temp.substr(i).c_str());
                if(f <= 9){
                    numInStrings[count] = temp.substr(i);
                    i+=3;
                }else if(f > 9){
                    numInStrings[count] = temp.substr(i);
                    i+=4;
                }
                count++;
            }
            // Since the nums are strings then we have to convert them into into ints
            //      then add them to the int* num;
            int* num = new int[count];
            // the clusterSize is the size of the correct line driven by the encoded line
            int clusterSize = 0;
            for(int i = 0; i < count; i++){
                int x = atoi(numInStrings[i].c_str());
                clusterSize += x;
                num[i] = x;
            }
            // string* letters gets the letters after the cluster numbers
            string* letters = new string[line.length()];
            int j = 0;
            for(int i = 0; i < count; i++){
                letters[i] = numInStrings[i][2];
            }
            // Now we create the last and sorted here so we can add the letters to each list
            // sortedList will be sorted after the loop
            string* last = new string[clusterSize];
            string* sortedLast = new string[clusterSize];
            int k = 0;
            for(int i = 0; !letters[i].empty(); i++){
                for(int j = 0; j < num[i]; j++){
                    last[k] = letters[i];
                    sortedLast[k] = letters[i];
                    k++;
                }
            }
            // Now from the sort variable, we try to do insertion sort or merge sort depending on the sort variable
            string insert = "insertion";
            string merge = "merge";
            if(sort == insert){
                insertion(sortedLast, clusterSize);
            }else if(sort == merge){
                mergeSort(sortedLast,0,clusterSize-1);
            }
            // sortedList will be sorted and compared to last elements
            // next is the index of where last was transformed into sortedList
            // I made all elements of next -1 because I check through each element
            //          and use the alreadyInNext function.
            int* next = new int[clusterSize];
            for(int i = 0; i < clusterSize; i++){
                next[i] = -1;
            }
            // To create next we have to compare sortedLast and last arrays
            for(int i = 0; i < clusterSize; i++){
                // Flag will be a boolean for the loop
                int flag = 1;
                // to get the next element, we try to find the the index of last of where sortedLast[i] is
                for(int j = 0; j < clusterSize && flag == 1; j++){
                    // if j is already in next, then we skip that last element and keep going through the list
                    int dec = alreadyInNext(next, j, clusterSize);
                    if(sortedLast[i] == last[j] &&  dec == 1){
                        next[i] = j;
                        flag = 0; // When we find the index we want to get out of this for loop and keep incrementing soredLast
                                  //       until the length of its size
                    }
                }
            }
            
            // Now we have to print out the line before the line was encoded
            // we create another int variable which is equal to the index
            int val = index;
            do{ // There is do while loop because we want to use index then we go through the list
                // First we get last element where index of next[val]
                cout << last[next[val]];
                // Then we change val from above and know we already used that number
                val = next[val];
            }while(val != index);     // We end on when val == index because we through all the numbers
            cout << endl;
            
        }
    }
}
// This function checks if the int* next has already have the index
//      this function returns an int which probably could be boolean
//      1 = the index is in next; 0 = the index is not in next
int alreadyInNext(int* list, int index, int size){
    for(int i = 0; list[i] >= 0 && i < size; i++){
        if(index == list[i]){
            return 1;
        }
    }
    return 0;
}

void mergeSort(string* list, int start, int end){
    // This starts by comparing start of the list to the end
    if(start < end){
        // We construct a mid to use for merge and mergeSort functions
        int mid = (start+end)/2;
        // We take each elements before list[mid]
        mergeSort(list, start, mid);
        // then we take the elements after list[mid+1]
        mergeSort(list,mid+1,end);
        // With all the elements we sort each element and transform the list
        merge(list,start,mid,end);
    }
}

void merge(string* list, int start, int mid, int end){
    // the variables are for each element
    int i = start;
    int j = mid + 1;
    int k = 0;      // k will be index which increment through the list
    // We create a string* temp to add the elements fromt the list
    string* temp = new string[end-start+1];
    // the while loop will compare each element and add them to the list in sorting order
    while(i <= mid && j <= end){
        // Here we compare the start which is 0 to the list[j] which j = mid+1
        // If list[i] is less then list[j], list[i] will be added to the temp
        if(list[i] <= list[j]){
            temp[k] = list[i];
            i++;        // then increment i until it greater than or equal to mid
        }else{ // else list[j] will be add to the list
            temp[k] = list[j];
            j++;     // then increment i until it greater than or equal to end
        }
        k++; // We then increment k for the index of temp
    }
    // If i is greater than mid then we have compare the list[j...end] and increment it to the list
    if(i > mid){
        while(j <= end){
            temp[k] = list[j];
            j++;
            k++;
        }
    }else{      // else j is greater than end then we compare the list[i..mid] and increment it to the list
        while(i <= mid){
            temp[k] = list[i];
            i++;
            k++;
        }
    }
    // Now we create the temp sorted list then we transform the list into a sorted array
    for(k = start; k <= end; k++){
        list[k] = temp[k-start];
    }
}

void insertion(string* list, int size){
    // this is where we use the insertion sort to sort the list alphabetically
    for(int i = 1; i < size; i++){
        string key = list[i];
        int j = i - 1;
        int num = 0;
        // since we are trying to compare the first letter of the word with on another,
        // we have to get the first letter from the index and compare it ot the key first letter
        while(j >= 0 && list[j][num] >= key[num]){
            // If the first letter is equal to the key first letter then we must go to the
            // next letter of the word which what is being implemented on the if statement
            if(list[j][num] == key[num]){
                num++;
            }else{
                list[j+1] = list[j];
                j = j - 1;
                num = 0;
            }
        }
        list[j+1]= key;
    }
}
