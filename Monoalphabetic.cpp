//Mono-Alphabetic

#include <bits/stdc++.h>

using namespace std;


void permute(string text,int l,int r, vector <string>& keyspace){
    if(l==r){
        keyspace.push_back(text);
    }else{
        for(int i=0;i<text.length();i++){
            swap(text[l],text[i]);
            permute(text, l+1,r,keyspace);
            swap(text[l],text[i]);
        }
    }
}

string encrypt(string plainText,string key, string uniqueText){
    string res = "";
    int idx;
    for(int i=0;plainText[i]!='\0';i++){
        for(int j=0;uniqueText[j]!='\0';j++){
            if(uniqueText[j]==plainText[i]){
                idx = j;
            }
        }
        res += key[idx];
    }
    return res;
}

void showFrequency(string plainText, string cipherText){
    unordered_map <char,int> plainMap;
    unordered_map <char,int> cipherMap;
    
    for(int i=0;i<plainText.length();i++){
        plainMap[plainText[i]]++;
        cipherMap[cipherText[i]]++;
    }
    
    for(int i=0;i<plainText.length();i++){
        float res = ((float)plainMap[plainText[i]]/plainText.length());
        
        cout << res << "\t\t" << plainText[i] << "\t\t" << cipherText[i] << endl;
    }
}

int main(){
    string plainText;
    vector <string> keyspace;
    int i;
    int unique[26]={0};
    string uniqueText = "";
    cout << "MONOALPHABETIC CIPHER IMPLEMENTATION"<<endl;
    ifstream fin;
    fin.open("plainText.txt");
    getline(fin, plainText);
    cout<<"PlainText: "<<plainText<<endl;
    for(i=0;plainText[i]!='\0';i++){
        unique[plainText[i]-'a']=1;
    }
    
    for(i=0;i<26;i++){
        if(unique[i]){
            char ch ='a' + i;
            uniqueText += ch;
        }
    }
    
    permute(uniqueText,0,uniqueText.length()-1,keyspace);
    string key = keyspace[rand()%keyspace.size()];
    
    cout << "Unique: "<< uniqueText<<endl;
    cout << "Key: "<<key<<endl;
    
    string cipherText = encrypt(plainText,key,uniqueText);
    cout << "CipherText: "<< cipherText<<endl;
    ofstream outfile;
    outfile.open("cipherText.txt");
    outfile << cipherText << endl;
    cout <<"\nFrequency\tPlainText\tCipherText\n";
    showFrequency(plainText, cipherText);
    
    return 0;
}