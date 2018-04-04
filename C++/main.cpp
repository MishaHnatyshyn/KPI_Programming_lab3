#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Country {
    string name;
    vector<int> score;
    int final;
};

vector<string> split(string, char);
vector<vector<int>> pointsFromOneCountry(vector<int> arr);
vector<Country*> countryListCreate(string, int*);
vector<Country*> pointsCalculate(vector<Country*>, int);
void write10Best(string,vector<Country*>);

int main() {
    int count;
    vector<Country*> participants = countryListCreate("../eurovision.csv", &count);
    vector<Country*> results = pointsCalculate(participants, count);
    write10Best("../results.csv",results);
    return 0;
}

vector<string> split(string str,char symb){
    vector<string> result;
    int start = 0 , length = 0;
    for (int i = 0; i <= str.length(); ++i) {
        if (str[i] == symb || i == str.length()){
            length = i - start;
            string temp = str.substr(start,length);
            start +=length + 1;
            result.push_back(temp);
        }
    }
    return result;
}

vector<vector<int>> pointsFromOneCountry(vector<int> arr){
    vector<vector<int>> stack;

    for (int k = 0; k < 20; ++k) {
        vector<int> temp;
        temp.push_back(k);
        temp.push_back(arr[k]);
        stack.push_back(temp);
    }

    for (int l = 0; l < 20; l++){
        int j = l;
        while (j > 0 && stack[j][1] > stack[j-1][1]){
            vector<int> temp = {stack[j-1][0],stack[j-1][1]};
            stack[j-1] = stack[j];
            stack[j] = temp;
            j--;
        }
    }
    return stack;
}

vector<Country*> countryListCreate(string path, int * count){
    string tempLine;
    ifstream file(path);
    vector<Country*> participants;
    getline(file,tempLine);
    *count = atoi(tempLine.c_str());

    for(int i = 0; i < *count;i++){
        getline(file, tempLine);
        Country * country = new Country;
        vector<string> arr = split(tempLine, ',');
        country->name =  arr[0];

        for (int j = 1; j <= *count; j++) {
            country->score.push_back (atoi(arr[j].c_str()) );
        }
        country->final = 0;
        participants.push_back(country);
    }
    file.close();
    return participants;
};

void write10Best(string path,vector<Country*> participants){
    ofstream resultFile(path, ios::app);
    for (int k = 0; k < 10; ++k) {
        resultFile << participants[k]->name <<','<< participants[k]->final << endl;
    }
    resultFile.close();
}

vector<Country*> pointsCalculate(vector<Country*> participants, int count){
    for (int i = 0; i < count; i++) {
        vector<int> tempArr;

        for (int j = 0; j < count; ++j) {
            tempArr.push_back(participants[j]->score[i]);
        }

        vector<vector<int>> stack = pointsFromOneCountry(tempArr);
        participants[stack[0][0]]->final += 12;
        participants[stack[1][0]]->final += 10;

        for (int m = 2; m < 10; m++) {
            participants[stack[m][0]]->final += 10 - m;
        }
    }

    for (int i = 0; i < 20; i++){
        int j = i;
        while (j > 0 && participants[j]->final > participants[j-1]->final){
            Country * temp = participants[j-1];
            participants[j-1] = participants[j];
            participants[j] = temp;
            j--;
        }
    }

    return participants;
};
