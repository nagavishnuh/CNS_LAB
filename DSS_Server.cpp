// DSS server Program

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

long extendedGCD(long a, long b){
    long r,r1,r2,q,t1,t2,t;
    r1 = b;
    r2 = a;
    t1 = 0;
    t2 = 1;
    long N = b;
    while(r2!=0){
        q = r1/r2;
        r = r1%r2;
        t = (t1-t2*q);
        
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    }
    t1 %= b;
    if(t1<0){
    	t1 += b;
    }
    if(r1 == 1){
        return t1;
    }else{
        cout << "Multiplicative Inverse doesn't exist.";
        exit(0);
    }
}

long powModN(long a, long b, long n){
    long res = 1;
    for(long i=0;i<b;i++){
        res = (res*a)%n;
    }
    return res;
}

long H(long M){
    return M^1234;
}

int main(){
    srand(time(NULL));
    int port;
    cout << "Enter the port number: ";cin >> port;
    int sock = createServer(port);
    
    long p,q,g,Y,enc,r,s;
    
    recv(sock,&p,sizeof(p),0);
    recv(sock,&q,sizeof(q),0);
    recv(sock,&g,sizeof(g),0);
    recv(sock,&Y,sizeof(Y),0);
    recv(sock,&enc,sizeof(enc),0);
    recv(sock,&r,sizeof(r),0);
    recv(sock,&s,sizeof(s),0);
    
    long M = H(enc);
    cout << "Decrypted Message: "<<M<<endl;
    
    long w = extendedGCD(s,q)%q;
    long u1 = (enc*w)%q;
    long u2 = (r*w)%q;
    long v = ((powModN(g,u1,p)*powModN(Y,u2,p))%p)%q;
    
    cout << "w: "<<w<<endl;
    cout << "u1: "<<u1<<endl;
    cout << "u2: "<<u2<<endl;
    cout << "v: "<<v<<endl;
    
    if(v==r){
        cout <<"Digital Signature verified."<<endl;
    }else{
        cout << "Digital Signature doesn't match." << endl;
    }
    return 0;
}


