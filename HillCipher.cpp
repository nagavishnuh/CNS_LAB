//Hill cipher

#include <bits/stdc++.h>

using namespace std;

int extendedGCD(int a, int b){
    int r1 = a;
    int r2 = b;
    int t,t1=0,t2=1;
    while(r2!=0){
        int q = r1/r2;
        int r = r1%r2;
        t = t1-q*t2;
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    }
    t1 %= 26;
    if(t1<0){
        t1 += 26;
    }
    if(r1==1){
        return t1;
    }else{
        cout << "\nMultiplicative Inverse doesn't exist.";
        exit(0);
    }
}

string decrypt(string cipherText, int size, int key[][3]){
    int det =0;
    if(size==2){
        det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    }else{
        det = key[0][0]*(key[1][1]*key[2][2]-key[1][2]*key[2][1]) - 
        key[0][1]*(key[1][0]*key[2][2]-key[1][2]*key[2][0]) + 
        key[0][2]*(key[1][0]*key[2][1]-key[1][1]*key[2][0]);
    }
    det %=26;
    if(det<0){
        det +=26;
    }
    
    int mulInv = extendedGCD(26,det);
    int keyInv[size][size];
    int minor[size][size],adj[size][size];
    if(size==2){
        adj[0][0]=key[1][1];
        adj[0][1] = -1*key[0][1];
        adj[1][0] = -1 * key[1][0];
        adj[1][1] = key[0][0];
    }else{
        minor[0][0] = key[1][1]*key[2][2]-key[1][2]*key[2][1];
        minor[0][1] = key[1][0]*key[2][2]-key[1][2]*key[2][0];
        minor[0][2] = key[1][0]*key[2][1]-key[1][1]*key[2][0];
        minor[1][0] = key[0][1]*key[2][2]-key[0][2]*key[2][1];
        minor[1][1] = key[0][0]*key[2][2]-key[0][2]*key[2][0];
        minor[1][2] = key[0][0]*key[2][1]-key[0][1]*key[2][0];
        minor[2][0] = key[0][1]*key[1][2]-key[0][2]*key[1][1];
        minor[2][1] = key[0][0]*key[1][2]-key[1][0]*key[0][2];
        minor[2][2] = key[0][0]*key[1][1]-key[0][1]*key[1][0];
        
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                int cofactor = ((i+j)%2==0)?1:-1;
                adj[j][i] = cofactor * minor[i][j];
            }
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            keyInv[i][j]=mulInv*adj[i][j];
            keyInv[i][j] %= 26;
            if(keyInv[i][j]<0){
                keyInv[i][j]+=26;
            }
        }
    }
    
    int row = cipherText.length()/size;
    int col = size;
    int cipherMatrix[row][col];
    int k=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col && k<cipherText.length();j++){
            cipherMatrix[i][j] = cipherText[k++]-'a';
        }
    }
    string decryptedText = "";
    int res[row][col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            res[i][j]=0;
            for(int k=0;k<col;k++){
                res[i][j] += cipherMatrix[i][k]*keyInv[k][j];
            }
            res[i][j] %= 26;
            decryptedText += res[i][j] + 'a';
        }
    }
    return decryptedText;
}


string encrypt(string plainText, int size, int key[][3]){
    int fillers;
    if(size==2){
        fillers = plainText.length()%size;
    }else{
        fillers = plainText.length()%size;
        if(fillers!=0){
            fillers = 3-fillers;
        }
    }
    while(fillers!=0){
        plainText += "x";
        fillers--;
    }
    cout << "PlainText: " << plainText;
    int row = plainText.length()/size;
    int col = size;
    int plainMatrix[row][col];
    int k=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col && k<plainText.length();j++){
            plainMatrix[i][j] = plainText[k++]-'a';
        }
    }
    
    int res[row][col];
    string cipherText ="";
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            res[i][j]=0;
            for(int k=0; k<col;k++){
                res[i][j] += plainMatrix[i][k] * key[k][j];
            }
            res[i][j] %= 26;
            cipherText += res[i][j]+'a';
        }
    }
    return cipherText;
}

int main(){
    string plainText;
    int key[3][3];
    int size;
    cout << "Enter plainText: ";
    cin >> plainText;
    cout << "Enter the size of key: ";
    cin >> size;
    cout << "Enter the elements: "<<endl;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cin >> key[i][j];
        }
    }
    string cipherText = encrypt(plainText,size,key);
    cout << "\nCipherText: "<<cipherText;
    
    string decryptedText = decrypt(cipherText, size, key);
    cout << "\nDecrypted Text: " << decryptedText;
    return 0;
}