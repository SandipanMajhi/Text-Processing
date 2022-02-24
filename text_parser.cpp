/**
 * Update Feb 24, 2022 : The program attempts to clean the vocabulary of unnnecessary non english 
 * alphabets from the vocabulary.
 * 
 * 
 */

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <list>

using namespace std;

#define alp 128

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
        if(!word_search(key)){
            for(auto c : key){
                int index = c - '\0';
                if(!cur -> children[index])
                    cur -> children[index] = new Node();
                cur->children[index] -> count++;
                cur = cur -> children[index];
            }
            cur -> isEnd = 1;
        }        
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

    void traverse_maxend(Node *cur){
        if(cur  -> isEnd){
            cout << this -> sg;
            for (auto c : this -> inlist)
                cout << (char) (c + '\0') ;
            cout << "\n";
        }

        int maxcount = 0, maxind = -1;
        Node *maxcur;

        for(int ind = 0 ; ind  < alp ; ind++){
            if(cur -> children[ind] && cur -> children[ind] -> count > maxcount){
                maxcount = cur -> children[ind] -> count;
                maxcur = cur -> children[ind];
                maxind = ind;
            }
        }
        if(maxind != -1){
            this -> inlist.push_back(maxind);
            traverse_maxend(maxcur);
            this -> inlist.pop_back();
        }

    }

    void best_suggest(string key){
        Node *cur = search(key);
        if(cur != nullptr){
            this -> sg = key;
            traverse_maxend(cur);
        }else
            cout << "No Suitable Match" << endl;
    }

    Node* delete_after_nonalphabets(Node *node){
        for(int i = 0; i<alp; i++){
            if(node -> children[i]){
                node -> children[i] = delete_after_nonalphabets(node -> children[i]);
            }
        }
        return nullptr;
    }

    void clean_vocab(Node *cur){
        for(int ind = 0; ind  < alp ; ind++){
            if(cur -> children[ind] ){
                if(ind >= 65 && ind <= 90 || ind >= 97 && ind <= 122){
                    clean_vocab(cur -> children[ind]);
                }else{
                    cur -> children[ind] = delete_after_nonalphabets(cur -> children[ind]);
                }
            }
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
    string word;
    // cout << "Type some string : " << endl;
    // cin >> word;

    // cout << "Probable auto completions : " << endl;
    // t.suggestion(word);

    // cout << "Best auto completion by frequency : " << endl;
    // t.best_suggest(word);

    cout << "The complete vocabulary before cleaning : " << endl;
    t.printTrie(t.root);

    cout << "The vocabulary after cleaning : " << endl;
    t.clean_vocab(t.root);
    t.printTrie(t.root); 

    return 0;
}