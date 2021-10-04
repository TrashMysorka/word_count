#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <map>
using namespace std;
map<string, int> words;
bool amount_comp(const std::string& first, const std::string& second){
    return words[first] >= words[second];
}
bool size_comp(const std::string& first, const std::string& second){
    return first < second;
}
void get_word(string row, list<string>& rows, int& count){
    string word;

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
void sort_list(list<string>& rows){
    rows.sort(size_comp);
    rows.unique();
    rows.sort(amount_comp);
}
void print_words( list<string>& rows, int& count,ofstream& output){
    for (auto const& i : rows){
        output << i <<"," << words[i] <<"," << (float(words[i]) / float(count))*100 << "%" <<"\n" ;
    }
}
int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string str;
    list<string> rows;
    int count = 0;
    while(!input.eof()){
        getline(input, str);
        get_word(str, rows, count);
    }
    sort_list(rows);

    print_words(rows, count, output);
    return 0;
}
