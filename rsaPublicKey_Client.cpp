// RSA publicKey Client Program
#include <bits/stdc++.h>
#include <arpa/inet.h>

using namespace std;

int p,q,n,d,e,phi;
int PUc[2],PRc[2];
int PUs[2];
int sock;

void connectToServer(int port,char* ip){
    sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr = {AF_INET, htons(port), inet_addr(ip)};
    
    while(connect(sock, (struct sockaddr *)&addr, sizeof(addr))<0);
    cout <<"Connection Established...!"<<endl;
}
int gcd(int a, int b){
    return (b==0)?a:gcd(b,a%b);
}

void genKeys(){
    cout << "Enter prime numbers p and q(>100): ";
    cin >> p>> q;
    n = p*q;
    phi = (p-1)*(q-1);
    do{
        e = rand()%(phi-2)+2;
    }while(gcd(e,phi)!=1);
    
    for(int i=1;i<phi;i++){
        if((i*e)%phi==1){
            d = i;
            break;
        }
    }
    
    PUc[0]=e; PUc[1]=n;
    PRc[0]=d; PRc[1]=n;
    cout << "Client Private Key: {"<<PRc[0]<<","<<PRc[1]<<"}"<<endl;
    cout << "Client Public Key: {"<<PUc[0]<<","<<PUc[1]<<"}"<<endl;
}

int powModN(int a, int b, int n){
    int res = 1;
    for(int i=0;i<b;i++){
        res =(res*a)%n;
    }
    return res;
}

int encrypt(int text, int PU[2]){
    return powModN(text, PU[0], PU[1]);
}

int decrypt(int text, int PR[2]){
    return powModN(text, PR[0], PR[1]);
}

void shareKeys(){
    recv(sock,&PUs,sizeof(PUs),0);
    send(sock,&PUc,sizeof(PUc),0);
    cout << "Client's Public Key sent to server..!"<< endl;
    cout << "Server's Public Key: {"<<PUs[0]<<","<<PUs[1]<<"}"<<endl;
}

int main(){
    int port;
    char ip[50];
    cout << "Enter port: ";cin >> port; 
    cout<<"Enter Server's IP address : ";cin>>ip;
    connectToServer(port,ip);
    genKeys();
    shareKeys();
    
    int ID;
    cout << "Enter ID(<100): ";
    cin >> ID;
    
    int N1 = rand()%100;
    int msg = N1*100+ID;
    int encN1ID = encrypt(msg,PUs);
    send(sock,&encN1ID,sizeof(encN1ID),0);
    
    int encN2N1;
    recv(sock,&encN2N1,sizeof(encN2N1),0);
    int decMsg = decrypt(encN2N1, PRc);
    int N2s = decMsg/100;
    int N1s = decMsg%100;
    cout << "\nServer's Nonce N2 = " << N2s<<endl;
    cout << "\nClient's Nonce received from Server N1s = "<< N1s << endl;
    
    if(N1!=N1s){
        cout << "Nonce doesn't match";exit(-1);
    }else{
        cout << "Server Authenticated.!!" << endl;
    }
    
    int encN2 = encrypt(N2s,PUs);
    send(sock, &encN2, sizeof(encN2),0);
    
    int K;
    cout << "Enter Key: ";cin >> K;
    int encK = encrypt(encrypt(K,PRc),PUs);
    send(sock,&encK,sizeof(encK),0);
    cout << "Session Key sent to Server."<<endl;
    return 0;
}
