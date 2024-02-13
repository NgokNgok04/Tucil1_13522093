#include <vector>
#include "util.h"
using namespace std;

vector<vector<string>> copyMatrix(vector<vector<string>> matrix){
    vector<vector<string>> newMatrix(6, vector<string>(6));
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}

vector<string> copyList(vector<string> list){
    vector<string> newList(vector<string>(6));
    for (int i = 0; i < list.size(); i++){
        newList[i] = list[i];
    }

    return newList;
}

void printMatrix(vector<vector<string>> matrix){
    for (int i = 0; i < matrix.size(); i++){
        vector<string> row = matrix[i];
        for (int j = 0; j < row.size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printList(vector<string> list){
    for (int i = 0; i < list.size() ; i++){
        cout << list[i] << " ";
    }
    cout << endl;
}

