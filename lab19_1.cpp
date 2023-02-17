#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream text(filename.c_str());
    string line;
    char a[50];
    int b, c, d;
    char format[] = "%[^:]: %d %d %d";
    while(getline(text, line)){
        sscanf(line.c_str(), format, a, &b, &c, &d);
        names.push_back(a);
        scores.push_back(b + c + d);
        grades.push_back(score2grade(b + c + d));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string temp;
    getline(cin, temp);
    int s = temp.size();
    int start = 0;
    int end = temp.find_first_of(" ");

    command = temp.substr(start, end - start);
    key = temp.substr(end+1, s-1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int s = names.size();
    bool found = false;
    for (int i = 0; i < s; i++){
        if(toUpperStr(names[i]) == key){
            found = true;
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
        }
        else if(i == s-1 && found == false){
            cout << "---------------------------------\n";
            cout << "Cannot found.\n";
            cout << "---------------------------------\n";
        }
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int s = names.size();
    cout << "---------------------------------\n";
    for (int i = 0; i < s; i++){
        string str(1, grades[i]);
        if(str == key){
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}