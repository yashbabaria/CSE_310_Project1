//
//  encode.cpp
//  Project_One
//  CSE 310: #84794
//  Created by Yash Babaria on 9/4/19.
//  Copyright © 2019 Yash Babaria. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
string* cyclicShift(string);
void insertion(string*,int);
void mergeSort(string*,int,int);
void merge(string*,int,int,int);

int main(int argc,const char* argv[]) {
    // We now take the input from the user get sorting alg the user wants
    string sort = argv[1];
    // the function takes in no parameters because the file will be inputed by the user
    string flag;
    // the while loop will go through each line of the file until the end of the line
    while(getline(cin,flag)){
        while(flag.length() == 0){
            // If there is a whitespace in the program this loop will skip a line until
            // there is no whitespace
            cout << 0 << "\n" << endl;
            getline(cin,flag);
        }
        // This initializes a string* list.
        string* list = new string[flag.length()];
        // the list will call the cyclicShift method and consist of cyclic shifts of the line.
        list = cyclicShift(flag);
        string insert = "insertion";
        string merge = "merge";
        if(sort == insert){
            insertion(list, flag.length());
        }else if(sort == merge){
            mergeSort(list,0,flag.length()-1);
        }
        // Now for this loop we are trying to find the index of the word in the list
        // Once we find the index, we print it.
        int count;
        for(int i = 0; list[i] != ""; i++){
            if(list[i] == flag){
                count = i;
                break;
            }
        }
        cout << count << endl;
        // This for loop will output which the program is requiring
        for(int i = 0; i < flag.length(); i++){
            int count = 0;
            count++;
            int dec = 1;
            while(dec != 0 && (i+1) < flag.length()){
                if(list[i][flag.length()-1] == list[i+1][flag.length()-1]){
                    i++;
                    count++;
                }else{
                    dec = 0;
                }
            }
            cout << count << " " << list[i][flag.length()-1] << " ";
        }
        cout << endl;
    }
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

// The cyclicShift function shifts a word to left and adds it to a string*
// The method will get the line of the file, do the shifting, and add it to a list
string* cyclicShift(string word){
    // We make this string* to add the shifts of each letter of the word
    string* temp = new string[word.length()];
    string newWord = word;
    for(int i = 0; i < word.length(); i++){
        char letter = newWord[0];
        for(int j = 0; j < word.length()-1; j++){
            newWord[j] = newWord[j+1];
        }
        newWord[word.length()-1] = letter;
        temp[i] = newWord;
    }
    return temp;
}
