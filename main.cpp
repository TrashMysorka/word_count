#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <map>
#include <cstring>
using namespace std;
map<string, int> words;
bool amount_comp(const std::string& first, const std::string& second){
    return words[first] >= words[second];
}
bool size_comp(const std::string& first, const std::string& second){
    return first < second;
}
void get_word(string row, list<string>& rows, map<string, int>& words, int& count){
    string word = "";

    for(int i = 0; i < row.size(); i++){
        if (isalnum(row[i])){
            word += row[i];
        }
        else{
            if(word != "") {
                rows.push_front(word);
                words[word] += 1;
                word = "";
                count++;
            }
            if ((row[i] == '\n') || row[i] == '\0') break;
            else continue;

        }
    }
}
int main(int argc, char** argv) {
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string str;
    list<string> rows;
    int count = 0;
    while(!input.eof()){
        getline(input, str);
        get_word(str, rows, words, count);
    }
    rows.sort(size_comp);
    rows.unique();
    rows.sort(amount_comp);
    for (auto const& i : rows){
        output << i <<"," << words[i] <<"," << (float(words[i]) / float(count))*100 << "%" <<"\n" ;
    }
    return 0;
}
