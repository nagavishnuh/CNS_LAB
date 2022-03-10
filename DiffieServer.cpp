// Diffie-Hellman Server Program
#include <bits/stdc++.h>
#include <arpa/inet.h>

using namespace std;

int createServer(int port){
    int sersock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr = {AF_INET, htons(port),INADDR_ANY};
    
    bind(sersock, (struct sockaddr *)&addr, sizeof(addr));
    cout << "Server ready. Waiting for client."<<endl;
    listen(sersock,5);
    int sock = accept(sersock,NULL,NULL);
    cout <<"Connection established."<<endl;
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
    int port;
    cout << "Enter the port number: ";cin >> port;
    int sock = createServer(port);
    
    long q,a;
    cout <<"Enter prime Number q(>4): ";cin >> q;
    cout << "Enter alpha a: ";cin>>a;
    
    long Xb,Yb,Ks;
    Xb = rand()%(q-2)+2;
    cout << "Server's Private Key Xa: "<<Xb << endl;
    
    Yb = powModN(a,Xb,q);
    cout << "Server's Public Key Ya: "<<Yb << endl;
    
    long Ya;
    recv(sock,&Ya,sizeof(Ya),0);
    
    send(sock,&Yb,sizeof(Yb),0);
    
    Ks = powModN(Ya,Xb,q);
    cout << "Server's Secret Key Kc: "<<Ks<<endl;
    
    long M;
    cout << "Enter message(number): ";cin>>M;
    
    long cipher = Ks^M;
    send(sock,&cipher,sizeof(cipher),0);
    cout <<"CipherText sent successfully."<<endl;
    
    return 0;
}
