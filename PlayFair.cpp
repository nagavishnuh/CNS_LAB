//PlayFair Cipher

#include <bits/stdc++.h>

using namespace std;

string encrypt(string plainText, char mat[5][5]){
    string temp = "";
    for(int i=0;i<plainText.length()-1;i++){
        temp+=plainText[i];
        if(plainText[i]==plainText[i+1]){
            temp += 'x';
        }
    }
    temp += plainText[plainText.length()-1];
    if(temp.length()%2==1){
        temp += 'x';
    }
    int x1,y1,x2,y2; // x-> row, y-> column
    string res = "";
    for(int i=0;i<temp.length();i+=2){
        char c=temp[i];
        char d = temp[i+1];
        for(int p=0;p<5;p++){
            for(int q=0;q<5;q++){
                if(mat[p][q]==c){
                    x1=p;
                    y1=q;
                }
                if(mat[p][q]==d){
                    x2=p;
                    y2=q;
                }
            }
        }
        if(x1==x2){
            res += mat[x1][(y1+1)%5];
            res += mat[x2][(y2+1)%5];
        }else if (y1==y2){
            res += mat[(x1+1)%5][y1];
            res += mat[(x2+1)%5][y2];
        }else{
            res += mat[x1][y2];
            res += mat[x2][y1];
        }
    }
    return res;
}

string decrypt(string cipherText, char mat[5][5]){
    int x1,y1,x2,y2; // x-> row, y-> column
    string res = "";
    for(int i=0;i<cipherText.length();i+=2){
        char c=cipherText[i];
        char d = cipherText[i+1];
        for(int p=0;p<5;p++){
            for(int q=0;q<5;q++){
                if(mat[p][q]==c){
                    x1=p;
                    y1=q;
                }
                if(mat[p][q]==d){
                    x2=p;
                    y2=q;
                }
            }
        }
        if(x1==x2){
            y1 = (y1==0)?5:y1;
            y2 = (y2==0)?5:y2;
            res += mat[x1][y1-1];
            res += mat[x2][y2-1];
        }else if (y1==y2){
            x1 = (x1==0)?5:x1;
            x2 = (x2==0)?5:x2;
            res += mat[x1-1][y1];
            res += mat[x2-1][y2];
        }else{
            res += mat[x1][y2];
            res += mat[x2][y1];
        }
    }
    return res;
}
//w = 4,2  o=0,1    v = 4,1   n=0,2 

int main(){
    string plainText,key;
    cout << "Enter plainText: ";
    cin >> plainText;
    cout << "Enter key: ";
    cin >> key;
    char mat[5][5];
    int i,j;
    int occurence[26] ={0};
    int k=0;
    for(i=0;i<5 && k<key.length();i++){
        for(j=0;j<5 && k<key.length();j++){
            if(occurence[key[k]-'a']==0){
                mat[i][j]=key[k];
                occurence[key[k]-'a']=1;
                k++;
            }
            else{
                j--;
            }
        }
    }
    k=0;
    i-=1;
    for(i;i<5 && k<26;i++){
        if(j==5){
            j=0;
        }
        for(j;j<5 && k<26;j++){
            if(k+'a'=='j'){
                j--;
                k++;
                continue;
            }
            if(occurence[k]==0){
                mat[i][j]=k+'a';
            }
            else{
                j--;
            }
            k++;
        }
    }
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    
    string cipherText = encrypt(plainText, mat);
    cout << cipherText<<endl;
    
    string decryptedText = decrypt(cipherText, mat);
    cout << decryptedText<<endl;
    return 0;
}