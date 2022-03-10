#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

int createServer(int port){
	int sersock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
	
	bind(sersock,(struct sockaddr*)&addr,sizeof(addr));
	cout<<"server online, waiting for client";
	
	listen(sersock,5);
	int sock = accept(sersock,NULL,NULL);
	cout<<"client connected"<<endl;
	
	return sock;
}

int toInt(char c){
    return c-'a';
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

int main(){
    int port;
    cout << "Enter port: ";cin >> port; 
    int sock = createServer(port);
    int PU[2];
    recv(sock,&PU,sizeof(PU),0);
    cout << "Public Key received PU = {"<<PU[0]<<","<<PU[1]<<"}"<<endl;
    
    string msg;
    cout << "Enter message: ";cin>>msg;
    if(msg.length()%2){
        msg+="z";
    }
    for(int i=0;i<msg.length();i+=2){
        int msg1 = toInt(msg[i])*100 + toInt(msg[i+1]);
        int encMsg = encrypt(msg1,PU);
        cout << "PlainText Block: "<< msg1 << endl;
        cout << "Encrypted Block: "<< encMsg <<endl << endl;
        send(sock,&encMsg,sizeof(encMsg),0);
    }
    int stop = -1;
    send(sock,&stop,sizeof(stop),0);
    cout << "Successful...!!!"<<endl;
    return 0;
}
