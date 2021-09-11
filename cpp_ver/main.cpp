//
//  main.cpp
//  slscq
//
//  Created by Uahh on 2021/9/5.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <nlohmann/json.hpp>


using namespace std;
using json = nlohmann::json;

class Slscq
{
public:
    Slscq() = default;
    Slscq(string json_path)
    {
        ifstream istr(json_path);
        istr >> this->data;
    }
    
    json data;
    
    int get_random_num(unsigned long total);
    string get_title();
    string get_noun();
    string get_verb();
    string get_adverb(int type);
    string get_phrase();
    string get_sentence();
    string get_parallel_sentence();
    string get_beginning();
    string get_body();
    string get_ending();
    bool replace_xx(string &str, string them);
    bool replace_vn(string &str);
    bool replace_v(string &str);
    bool replace_n(string &str);
    bool replace_ss(string &str);
    bool replace_sp(string &str);
    bool replace_p(string &str);
    void replace_all(string &str, string them);
};

int Slscq::get_random_num(unsigned long total)
{
    srand((unsigned int)clock());
    int num = rand() % (total);
    return num;
}

string Slscq::get_title()
{
    unsigned long total = data["title"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["title"][random_num];
    return str;
}

string Slscq::get_noun()
{
    unsigned long total = data["noun"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["noun"][random_num];
    return str;
}

string Slscq::get_verb()
{
    unsigned long total = data["verb"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["verb"][random_num];
    return str;
}

string Slscq::get_adverb(int type)
{
    string str;
    if(type == 1)
    {
        unsigned long total = data["adverb_1"].size();
        unsigned long random_num = get_random_num(total);
        str = data["adverb_1"][random_num];
    }
    else if(type == 2)
    {
        unsigned long total = data["adverb_2"].size();
        unsigned long random_num = get_random_num(total);
        str = data["adverb_2"][random_num];
    }
    return str;
}

string Slscq::get_phrase()
{
    unsigned long total = data["phrase"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["phrase"][random_num];
    return str;
}

string Slscq::get_sentence()
{
    unsigned long total = data["sentence"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["sentence"][random_num];
    return str;
}

string Slscq::get_parallel_sentence()
{
    unsigned long total = data["parallel_sentence"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["parallel_sentence"][random_num];
    return str;
}

string Slscq::get_beginning()
{
    unsigned long total = data["beginning"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["beginning"][random_num];
    return str;
}

string Slscq::get_body()
{
    unsigned long total = data["body"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["body"][random_num];
    return str;
}

string Slscq::get_ending()
{
    unsigned long total = data["ending"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["ending"][random_num];
    return str;
}

bool Slscq::replace_xx(string &str, string them)
{
    unsigned long step = str.find("xx");
    if(step != str.npos)
    {
        str.replace(step, 2, them);
        return true;
    }
    return false;
}

bool Slscq::replace_vn(string &str)
{
    unsigned long step = str.find("vn");
    unsigned long random_num = get_random_num(4) + 1;
    string vn = "";
    for(int i = 0; i < random_num; i++)
    {
        vn += get_verb() + get_noun();
        if(i != random_num - 1)
            vn += "，";
    }

    if(step != str.npos)
    {
        str.replace(step, 2, vn);
        return true;
    }
    return false;
}

bool Slscq::replace_v(string &str)
{
    unsigned long step = str.find("v");
    string v = "";
    v += get_verb();
    if(step != str.npos)
    {
        str.replace(step, 1, v);
        return true;
    }
    return false;
}

bool Slscq::replace_n(string &str)
{
    unsigned long step = str.find("n");
    string n = "";
    n += get_noun();
    if(step != str.npos)
    {
        str.replace(step, 1, n);
        return true;
    }
    return false;
}

bool Slscq::replace_ss(string &str)
{
    unsigned long step = str.find("ss");
    string ss = "";
    ss += get_sentence();
    if(step != str.npos)
    {
        str.replace(step, 2, ss);
        return true;
    }
    return false;
}

bool Slscq::replace_sp(string &str)
{
    unsigned long step = str.find("sp");
    string sp = "";
    sp += get_parallel_sentence();
    if(step != str.npos)
    {
        str.replace(step, 2, sp);
        return true;
    }
    return false;
}

bool Slscq::replace_p(string &str)
{
    unsigned long step = str.find("p");
    string p = "";
    p += get_phrase();
    if(step != str.npos)
    {
        str.replace(step, 1, p);
        return true;
    }
    return false;
}

void Slscq::replace_all(string &str, string them)
{
    while(replace_vn(str)) {};
    while(replace_v(str)) {};
    while(replace_n(str)) {};
    while(replace_ss(str)) {};
    while(replace_sp(str)) {};
    while(replace_p(str)) {};
    while(replace_xx(str, them)) {};
    return;
}

static const string usage = "usage: ./slscq THEME NUM";
void error() {
    cout << usage << endl;
    exit(-1);
}

int main(int argc, const char * argv[])
{
    if (argc != 3) {
        error();
    }
    Slscq j("./data.json");
    string them = string(argv[1]);
    int essay_num = atoi(argv[2]);
    if (essay_num <= 0) error();
    int begin_num = essay_num * 0.15 * 4;
    int body_num = essay_num * 0.7 * 4;
    int end_num = begin_num;
    
    string title = "";
    title = j.get_title();
    j.replace_all(title, them);
    
    string begin = "        ";
    string body = "        ";
    string end = "        ";
    while(begin.size() < begin_num)
    {
        string temp = "";
        temp += j.get_beginning();
        j.replace_all(temp, them);
        begin += temp;
    }
    while(body.size() < body_num)
    {
        string temp = "";
        temp += j.get_body();
        j.replace_all(temp, them);
        body += temp;
    }
    while(end.size() < end_num)
    {
        string temp = "";
        temp += j.get_ending();
        j.replace_all(temp, them);
        end += temp;
    }
    cout << title << endl;
    cout << begin << endl;
    cout << body << endl;
    cout << end << endl;
    return 0;
}

