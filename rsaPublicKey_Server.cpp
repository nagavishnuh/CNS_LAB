//RSA publicKey Server Program
#include <bits/stdc++.h>
#include <arpa/inet.h>

using namespace std;

int p,q,n,d,e,phi;
int PUs[2],PRs[2];
int PUc[2];
int sock;

void createServer(int port){
    int sersock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    
    bind(sersock, (struct sockaddr *)&addr, sizeof(addr));
    cout << "Server Established"<<endl;
    
    listen(sersock,5);
    sock = accept(sersock,NULL,NULL);
    cout << "Client Connected"<<endl;
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
    
    PUs[0]=e; PUs[1]=n;
    PRs[0]=d; PRs[1]=n;
    cout << "Client Private Key: {"<<PRs[0]<<","<<PRs[1]<<"}"<<endl;
    cout << "Client Public Key: {"<<PUs[0]<<","<<PUs[1]<<"}"<<endl;
}

void shareKeys(){
    send(sock,&PUs,sizeof(PUs),0);
    recv(sock,&PUc,sizeof(PUc),0);
    cout << "Client's Public Key sent to server..!"<< endl;
    cout << "Server's Public Key: {"<<PUc[0]<<","<<PUc[1]<<"}"<<endl;
}

int powModN(int a, int b, int n){
    int res = 1;
    for(int i=0;i<b;i++){
        res =(res*a)%n;
    }
    return res;
}

int decrypt(int text, int PR[2]){
    return powModN(text, PR[0], PR[1]);
}

int encrypt(int text, int PU[2]){
    return powModN(text, PU[0], PU[1]);
}

int main(){
    int port;
    cout << "Enter port: ";cin >> port; 
    createServer(port);
    genKeys();
    shareKeys();
    
    int encN1ID;
    recv(sock,&encN1ID,sizeof(encN1ID),0);
    cout << "Client's N1||ID: " << encN1ID << endl;
    int decMsg = decrypt(encN1ID,PRs);
    int N1 = decMsg/100;
    int ID = decMsg%100;
    cout << "Client's Nonce N1 = "<<N1<<endl;
    cout << "Client's ID = "<<ID<<endl;
    
    int N2 = rand()%100;
    int msg = N2*100+N1;
    int encN2N1 = encrypt(msg,PUc);
    send(sock,&encN2N1,sizeof(encN2N1),0);
    
    int encN2;
    recv(sock,&encN2,sizeof(encN2),0);
    int N2c = decrypt(encN2,PRs);
    cout << "Server's Nonce received from client N2c = "<<N2c<<endl;
    if(N2!=N2c){
        cout << "Nonce doesn't match";exit(-1);
    }else{
        cout << "Client Authenticated.!!" << endl;
    }
    
    int encK;
    recv(sock,&encK,sizeof(encK),0);
    int K = decrypt(decrypt(encK,PRs),PUc);
    cout << "Key received from Client : "<< K << endl;
    return 0;
}