// Transposition Cipher

#include<bits/stdc++.h>
using namespace std;

string Encryption(string PlainText,string Key)
{
    int col = Key.length();
    int row = ceil((float)PlainText.length()/Key.length());
    char matrix[row][col];
    int i,j,k=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col && k<PlainText.length();j++)
        {
            matrix[i][j]=PlainText[k++];
        }
    }
    while(j<col)
    {
        matrix[i-1][j++]='z';
    }
    cout<<"\nTransposition Matrix:"<<endl;
    for(i=0;i<col;i++)
    {
        cout<<Key[i]<<"";
    }
    cout<<endl;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            cout<<matrix[i][j]<<"";
        }
        cout<<endl;
    }
    string temp=Key;
    string CipherText="";
    sort(temp.begin(),temp.end());
    for(int i=0;i<col;i++)
    {
        int idx = Key.find(temp[i]);
        for(int j=0;j<row;j++)
        {
           CipherText += matrix[j][idx];
        }
    }
    return CipherText;
}


string Decryption(string CipherText,string Key)
{
    
    int row = CipherText.length()/Key.length();
    int col = Key.length();
    char matrix[row][col];
    int idx;
    string temp=Key;
    int k=0;
    sort(temp.begin(),temp.end());
    for(int i=0;i<col;i++)
    {
        int idx = Key.find(temp[i]);
        for(int j=0;j<row;j++)
        {
           matrix[j][idx] = CipherText[k++]; 
        }
    }
    string DecryptedText="";
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            DecryptedText += matrix[i][j];
        }
    }

    return DecryptedText;
}



int main()
{
    string PlainText,Key;
    cout<<"Transposition Cipher\n";
    cout<<"Enter PlainText:";
    cin>>PlainText;
    cout<<"Enter Key:"<<endl;\
    cin>>Key;
    
    string CipherText = Encryption(PlainText,Key);
    cout<<"Encryption:"<<"\n"<<"PlainText:"<<PlainText<<endl;
    cout<<"CipherText:"<<CipherText<<endl;
    string DecryptedText = Decryption(CipherText,Key);
    cout<<"Decryption:"<<"\n"<<"CipherText:"<<CipherText<<endl;
    cout<<"Decryption:"<<DecryptedText<<endl;
    return 0;
}
    
    
