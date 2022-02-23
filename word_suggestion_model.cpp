/**
 * @file word_suggestion_model.cpp
 * @author your name (you@domain.com)
 * @brief Probabilistic word suggestion model
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <list>
#include <fstream>

using namespace std;

class Node{
    public:
    int count;
    int isEnd;
    Node *children[26];

    Node(){
        this -> count = 0;
        this -> isEnd = 0;
        for(int i = 0; i<26; i++){
            children[i] = NULL;
        }
    }
};

class Trie{

    public:
    int alp;
    Node *root;
    list<int> inlist;
    string sg;

    Trie(){
        this -> root = new Node();
        this -> alp = 26;
    }

    void insert(string key){
        Node *cur = this -> root;
        for(auto c : key){
            int index = c - 'a';
            if(!cur -> children[index])
                cur -> children[index] = new Node();
            cur -> children[index] -> count++; 
            cur = cur -> children[index];
        }
        cur -> isEnd = 1;
    }

    int word_search(string key){
        Node *cur = this -> root;
        for(auto c  : key){
            int index = c - 'a';
            if(!cur -> children[index])
                return 0;
            cur = cur -> children[index];
        }
        return cur -> isEnd;
    }

    Node* search(string key){
        Node *cur = this -> root;
        for(auto c  : key){
            int index = c - 'a';
            if(!cur -> children[index])
                return nullptr;
            cur = cur -> children[index];
        }
        return cur;
    }

    void printTrie(Node *node){
        if(node -> isEnd){
            for(auto c : this -> inlist)
                cout << (char)(c + 'a');
            cout << "\n";
        }
        for(int index = 0; index < this -> alp; index ++){
            if(node -> children[index]){
                this -> inlist.push_back(index);
                printTrie(node -> children[index]);
                this -> inlist.pop_back();
            }
        }
    }

    void traverse_till_end(Node *cur){
        if(cur -> isEnd){
            cout << this -> sg;
            for(auto c : this -> inlist)
                cout << (char)(c + 'a');
            cout << "\n";
        }
        for(int index  = 0; index < this -> alp; index++){
            if(cur -> children[index]){
                this ->inlist.push_back(index);
                traverse_till_end(cur -> children[index]);
                this -> inlist.pop_back();
            }
        }
    }

    void traverse_till_maxend(Node *cur){
        if(cur -> isEnd){
            cout << this -> sg;
            for(auto c : this -> inlist)
                cout << (char)(c + 'a');
            cout << "\n";
        }

        int maxcount = 0, maxind = -1;
        Node *maxcur;

        for(int ind = 0 ; ind  < this -> alp ; ind++){
            if(cur -> children[ind] && cur -> children[ind] -> count > maxcount){
                maxcount = cur -> children[ind] -> count;
                maxcur = cur -> children[ind];
                maxind = ind;
            }
        }
        if(maxind != -1){
            this -> inlist.push_back(maxind);
            traverse_till_maxend(maxcur);
            this -> inlist.pop_back();
        }
        
    }
    
    void best_suggest(string key){
        Node *cur = search(key);
        if(cur != nullptr){
            this -> sg = key;
            traverse_till_maxend(cur);
        }else{
            cout << "Not a match" << endl;
        }
    }

    void suggestion(string key){
        Node *cur = search(key);
        if(cur != nullptr){
            this -> sg = key;
            traverse_till_end(cur);
        }else{
            cout << "Not a match" << endl;
        }
    }
};

list<string> split(string s , string delim){
    size_t pos;
    list<string> splitlist;

    while((pos = s.find(delim)) != string:: npos){
        splitlist.push_back(s.substr(0, pos));
        s.erase(0, pos + delim.length());
    }
    splitlist.push_back(s);
    return splitlist;
}


int main(){
    Trie t;
    string s = "my name is sandipan blahh bloo blupper sansi sand sunflower blah boo bash lab ban";
    list<string> l = split(s," "); 

    for(auto word : l){
        t.insert(word);
    }
    string word;
    cin >> word;

    cout << "Autocompleted suggestions : " << endl;
    t.suggestion(word);

    cout << "The best suggestions :" << endl;
    t.best_suggest(word);

    return 0;
}