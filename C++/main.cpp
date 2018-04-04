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
vector<Country*> countryListCreate(string, int*);

int main() {
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
