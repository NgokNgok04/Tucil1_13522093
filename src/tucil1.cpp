#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "util.h"
#include <tuple>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
using namespace std;
int rows;
int cols;
int buffer_size;
int maxReward;
vector<string> optSequence;
vector<tuple<int,int>> optPointSequence;

vector<vector<string>> matrix;
vector<vector<string>> allSequences;
vector<vector<tuple<int,int>>> pointMatrix; 
vector<vector<string>> matchSequences;
vector<int> rewardSequences;

void algorithm (vector<vector<string>> matrix, int posRow, int posCol, bool isHorizontal, vector<string> sequence, vector<tuple<int,int>> pointList,int iterate) {
    if (!isHorizontal){
        for (int i = 0; i < rows; i++){
            if (matrix[i][posCol] != "XX"){
                sequence[iterate] = matrix[i][posCol];
                matrix[i][posCol] = "XX";
                pointList.push_back(make_tuple(i,posCol));              
                if (iterate < buffer_size - 1) {
                    algorithm(matrix,i,posCol,true,sequence, pointList, iterate + 1);
                    pointList.pop_back();
                    matrix[i][posCol] = sequence[iterate];
                } else if (iterate == buffer_size - 1) {
                    allSequences.push_back(sequence);
                    pointMatrix.push_back(pointList);
                    // printList(sequence);
                    pointList.pop_back();
                }
            }
        }    
    } else if (isHorizontal){
        for (int j = 0; j < cols; j++){
            if (matrix[posRow][j] != "XX"){
                sequence[iterate] = matrix[posRow][j];
                matrix[posRow][j] = "XX";
                pointList.push_back(make_tuple(posRow,j));
                if (iterate < buffer_size - 1) {
                    algorithm(matrix,posRow,j,false,sequence,pointList, iterate + 1);
                    pointList.pop_back();
                    matrix[posRow][j] = sequence[iterate];
                } else if (iterate == buffer_size - 1) {
                    allSequences.push_back(sequence);
                    pointMatrix.push_back(pointList);
                    // printList(sequence);
                    pointList.pop_back();
                }
            }
        }
    }
};

bool matchingSequence(vector<string> sequence, vector<string> matchSequences){
    for (int i = 0; i < sequence.size(); i++){
        int k = i;
        for (int j = 0; j < matchSequences.size();j++){
            if (sequence[k] != matchSequences[j]){
                break;
            } else {
                k++;
            }

            if (j == (matchSequences.size() - 1)){
                return true;
            }
        }
    }

    return false;
}
tuple<vector<string>,int,vector<tuple<int,int>>> maxSequence(){
    maxReward = 0;
    int max;
    for (int i = 0; i < allSequences.size(); i++){
        vector<string> row = allSequences[i];
        max = 0;
        for (int j = 0; j < matchSequences.size(); j++){
            if(matchingSequence(row,matchSequences[j])){
                max += rewardSequences[j];
                if (max == 156){
                    printList(matchSequences[j]);
                    break;
                }
            };
        }
        if (max > maxReward) {
            maxReward = max;
            optSequence = row;
            optPointSequence = pointMatrix[i];
        }
    }

    if (maxReward <= 0){
        optSequence.clear();
        optPointSequence.clear();
    }
    return make_tuple(optSequence,maxReward,optPointSequence);
}

void readFile(string fileName){
    ifstream inputFile(fileName);

    if (inputFile.is_open()){
        string line;
        getline(inputFile,line);
        string line2;
        getline(inputFile,line2);
        istringstream iss(line2);
        int temp;
        if (iss >> temp) {
            buffer_size = stoi(line);
            rows = temp;
            iss >> cols;
            matrix.resize(rows,vector<string>(cols));
            for (int i = 0; i < rows; i++){
                getline(inputFile,line);
                istringstream iss(line);
                for (int j = 0; j < cols; j++){
                    iss >> matrix[i][j];
                }
            }

            getline(inputFile,line);
            int maximumSeq = stoi(line);
            rewardSequences.resize(maximumSeq);
            matchSequences.resize(0);

            for (int i = 0; i < maximumSeq; i++){
                getline(inputFile,line);
                // cout << line << endl;
                istringstream iss(line);

                string word;
                vector<string> listSequence;
                while(iss >> word){
                    listSequence.push_back(word);
                }
                matchSequences.push_back(listSequence);
                listSequence.clear();
                getline(inputFile,line);
                // cout << line << endl;
                rewardSequences[i] = stoi(line);
            }
        }
        // } else {
        //     int jumlahTokenUnik = stoi(line);
        //     vector<string> TokenUnik(jumlahTokenUnik); 
        //     cout << jumlahTokenUnik << endl;
        //     cout << line << endl;
        //     for (int i = 0; i < jumlahTokenUnik - 1; i++){
        //         iss >> TokenUnik[i];
        //         cout << TokenUnik[i] << "";
        //     };
        //     getline(inputFile,line);
        //     buffer_size = stoi(line);

        //     getline(inputFile,line);
        //     istringstream iss(line);
        //     iss >> rows >> cols;

        //     getline(inputFile,line);
        //     int maximumSeq = stoi(line);
        //     getline(inputFile,line);
        //     int maximumSeq1Row = stoi(line);
        //     rewardSequences.resize(maximumSeq);

        //     int random;
        //     srand(static_cast<unsigned int>(time(nullptr)));
        //     for (int i = 0; i <rows; i++){
        //         for (int j = 0; j <rows; j++){
        //             random = (rand() % (jumlahTokenUnik - 1));
        //             matrix[i][j] = TokenUnik[random];
        //         }
        //     }

        //     int random2;
        //     for (int i = 0; i < 0; i++){
        //         random2 = rand() % maximumSeq1Row + 2;
        //         for (int j = 0; j < random2; j++){
        //             random = (rand() % (jumlahTokenUnik - 1));
        //             matchSequences[i][j] = TokenUnik[random];
        //         }
        //     }
        //     for (int i = 0; i < maximumSeq; i++){
        //         random = (rand() % 100 + 1);
        //         rewardSequences[i] = random;
        //     }
            
        // }
    } else {
        cout << "Gagal membaca file" << endl;
    }


}
void writeFile(int duration){
    ofstream outputFile("output.txt");
    
    if (outputFile.is_open()){
        outputFile << maxReward << endl;

        for (int i = 0; i < buffer_size; i++){
            outputFile << optSequence[i] << " ";
        }
        outputFile << endl;

        for (int i = 0; i < buffer_size; i++){
            outputFile << get<1>(optPointSequence[i]) + 1 << ", " << get<0>(optPointSequence[i]) + 1<< endl;
        }

        outputFile << endl << endl;
        
        outputFile << duration << " ms";
        
        outputFile.close();

        cout << "File telah selesai, silahkan dicheck file output.txt" << endl;
    } else {
        cout << "Tidak bisa menulis file" << endl;
    }
}
int main() {
    bool isHorizontal = true;
    vector<tuple<int,int>> pointList = {};


    cout << "Masukkan Nama file: ";
    string fileName;
    cin >> fileName;
    readFile(fileName);
    vector<string> sequence(buffer_size);

    auto start_time = chrono::high_resolution_clock::now();

    algorithm(matrix,0,0,isHorizontal,sequence,pointList,0);
    tuple<vector<string>,int,vector<tuple<int,int>>> myTuple;
    myTuple = maxSequence();

    cout << "Optimal Sequence : "; printList(get<0>(myTuple)); cout << endl;
    cout << "Max Reward : " << get<1>(myTuple) << endl;
    cout << "Optimal Point Sequence : " << endl;

    vector<tuple<int,int>> Tuples = get<2>(myTuple);
    for (int i = 0; i < Tuples.size(); i++){
        cout << "(" << get<1>(Tuples[i]) + 1<< "," << get<0>(Tuples[i]) + 1<< ")" << endl;
    }

    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time-start_time);
    cout << "Runtime: " << duration.count() << " miliseconds" << endl; 

    cout << "Apakah ingin menyimpan solusi?(y/n) ";
    string answer;
    cin >> answer;

    if (answer == "y") {
        writeFile(duration.count());
    }
    return 0;
}
