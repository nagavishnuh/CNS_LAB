#include <bits/stdc++.h>
#include <arpa/inet.h>
using namespace std;

int conToServer(int port){
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
	
	if(connect(sersock,(struct sockaddr*)&addr,sizeof(addr))<0){
		cout<<"run server first";
		exit(0);
	}
	else{
		cout<<"connexted";
	}	
	return sock;
}

int gcd(int a, int b){
	return b==0?a:gcd(b,a%b);
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

char toChar(int n){
    return n+'a';
}


int main(){
	int port;
	cout<<"Enter port number:"<<endl;
	cin>>port;
	int sock = conToServer(port);
	
	int p,q;
	cout<<"enter two prime nos <100 for p and q"<<endl; cin>>p>>q;
	int n = p*q;
	int phi = (p-1)*(q-1);
	
	srand(time(NULL));
	
	int e,d;
	do{e = rand()%(phi-2)+2;}while(gcd(e,phi)!=1);
	
	for(d=1;d<phi;d++)
	{
		if((d*e)%phi == 1)
			break;
	}
	
	int PU[2] = {e,n};
	int PR[2] = {d,n};
	//print both
	
	send(sock,&PU,sizeof(PU),0);
	cout<<"sent pub key"<<endl;
	
	string msg="";
    while(true){
        int C;
        recv(sock,&C,sizeof(C),0);
        
        if(C==-1){
            break;
        }
        
        cout <<"CipherText Received: "<<C<<endl;
        
        int decMsg = decrypt(C,PR);
        cout <<"DecryptedText: "<<decMsg <<endl<< endl;
        msg += toChar(decMsg/100);
        msg += toChar(decMsg%100);
    }
    cout << "Decrypted Message: "<<msg<<endl;


return 0;
}
