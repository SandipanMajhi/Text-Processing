/**
 * @file text_parser.cpp
 * @author your name (you@domain.com)
 * @brief 
 * Text Parsing and Suggestion model
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <list>

using namespace std;

#define alp 256

class Node{
    public:
    int count;
    int isEnd;
    Node *children[alp];

    Node(){
        this -> count = 0;
        this -> isEnd = 0;
        for(int i = 0; i< alp; i++){
            this -> children[i] = nullptr;
        }
    }
};

class Trie{
    public:
    Node *root;
    list<int> inlist;
    string sg;

    Trie(){
        this -> root = new Node();
    }

    void insert(string key){
        Node *cur = this -> root;

        for(auto c : key){
            int index = c - '\0';
            if(!cur -> children[index])
                cur -> children[index] = new Node();
            cur->children[index] -> count++;
            cur = cur -> children[index];
        }

        cur -> isEnd = 1;
    }

    int word_search(string key){
        Node *cur = this -> root;

        for(auto c : key){
            int index = c - '\0';
            if(!cur -> children[index])
                return 0;
            cur = cur -> children[index];
        }

        return cur -> isEnd;
    }


    Node* search(string key){
        Node *cur = this -> root;

        for(auto c: key){
            int index = c - '\0';
            if(!cur -> children[index])
                return nullptr;
            cur = cur -> children[index];
        }

        return cur;
    }

    void printTrie(Node *node){
        if(node -> isEnd){
            for(auto c : this -> inlist)
                cout << (char) (c + '\0');
            cout << "\n";
        }

        for(int ind = 0; ind < alp; ind++){
            if(node -> children[ind]){
                this -> inlist.push_back(ind);
                printTrie(node -> children[ind]);
                this -> inlist.pop_back();
            }
        }
    }

    void traverse_till_end(Node *cur){
        if(cur -> isEnd){
            cout << this -> sg;
            for(auto c : this -> inlist)
                cout << (char)(c + '\0');
            cout << "\n";
        }

        for(int index = 0; index < alp; index++){
            if(cur -> children[index]){
                this -> inlist.push_back(index);
                traverse_till_end(cur -> children[index]);
                this -> inlist.pop_back();
            }
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


list<string> split(string s, string delim){
    int pos;
    list<string> l;

    while((pos = s.find(delim)) != string :: npos){
        l.push_back(s.substr(0,pos));
        s.erase(0, pos + delim.length());
    }

    l.push_back(s);
    return l;
}

using namespace std;

int main(){
    string s;
    ifstream myfile("story.txt");
    list<string> l;
    Trie t;

    while(getline(myfile, s)){
        l = split(s," ");
        for(auto c : l)
            t.insert(c);
    }

    t.printTrie(t.root);

    string word;

    

    return 0;
}