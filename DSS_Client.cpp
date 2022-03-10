// DSS Client Program

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
    //const char ip[50];
    srand(time(NULL));
    int port;
    //ut << "Enter IP address: ";cin>>ip;
    cout << "Enter port: ";cin>>port;
    int sock = connectToServer(port);
    
    long p,q,h,g,X,Y;
    
    cout << "Enter P: ";cin>>p;
    cout << "Enter Q: ";cin >> q;
    
    do{
        h = rand()%(p-2)+2;
        g = powModN(h,(p-1)/q,p);
    }while(g<=1);
    
    X = rand()%(q-2)+2;
    
    Y = powModN(g,X,p);
    
    long K = rand()%(q-2)+2;
    
    long M;
    cout << "Enter message(number): ";cin>>M;
    long enc = H(M);
    
    cout << "P: "<<p<<endl;
    cout << "Q: "<<q<<endl;
    cout << "G: "<<g<<endl;
    cout << "X: "<<X<<endl;
    cout << "Y: "<<Y<<endl;
    cout << "K: "<<K<<endl;
    cout << "Encrypted Msg: "<<enc<<endl;
    long r = powModN(g,K,p)%q;
    long s = (extendedGCD(K,q)*(enc+X*r))%q;
    
    cout << "R: "<<r<<endl;
    cout << "S: "<<s<<endl;
    
    send(sock,&p,sizeof(p),0);
    send(sock,&q,sizeof(q),0);
    send(sock,&g,sizeof(g),0);
    send(sock,&Y,sizeof(Y),0);
    send(sock,&enc,sizeof(enc),0);
    send(sock,&r,sizeof(r),0);
    send(sock,&s,sizeof(s),0);
    
    cout << "All details sent...!"<<endl;
    return 0;
}
