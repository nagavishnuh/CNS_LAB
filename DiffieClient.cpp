// Diffie-Hellman Client Program
#include <bits/stdc++.h>
#include <arpa/inet.h>

using namespace std;

int connectToServer(int port){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr = {AF_INET, htons(port),INADDR_ANY};
    
    while(connect(sock, (struct sockaddr *)&addr, sizeof(addr))<0);
    cout << "Connection established."<<endl;
    return sock;
}

long powModN(long a, long b, long n){
    long res = 1;
    for(long i=0;i<b;i++){
        res = (res*a)%n;
    }
    return res;
}

int main(){
    //const char ip[50];
    int port;
    //cout <<"Enter IP Address: ";cin >> ip;
    cout << "Enter the port number: ";cin >> port;
    int sock = connectToServer(port);
    
    long q,a;
    cout <<"Enter prime Number q(>4): ";cin >> q;
    cout << "Enter alpha a: ";cin>>a;
    
    long Xa,Ya,Kc;
    Xa = rand()%(q-2)+2;
    cout << "Client's Private Key Xa: "<<Xa << endl;
    
    Ya = powModN(a,Xa,q);
    cout << "Client's Public Key Ya: "<<Ya << endl;

    send(sock,&Ya,sizeof(Ya),0);
    
    long Yb;
    recv(sock,&Yb,sizeof(Yb),0);
    
    Kc = powModN(Yb,Xa,q);
    cout << "Client's Secret Key Kc: "<<Kc<<endl;
    
    long cipher;
    recv(sock,&cipher,sizeof(cipher),0);
    cout << "Received cipher : "<<cipher<<endl;
    
    long M = Kc^cipher;
    cout << "Decrypted Message: "<<M<<endl;
    
    return 0;
}
