#include<iostream>
#include<vector>
#include<string>
using namespace std;

string Permutation(vector<int> array, string inp){
    string out = "";
    for(int i=0;i<array.size();i++)
        out += inp[array[i]-1];
    return out;
}

class S_DES
{
public:
    string K1,K2,cipher;

    void initialize(string key)
    {
        if(key.size()!=10)
	{
            cout<<"\nInValid Key-Length "<<key<<" "<<key.size();
            exit(1);
        }
	Keys_Generation(key);
    }
	
    void Keys_Generation(string key)
    {
        vector<int> P10{3,5,2,7,4,10,1,9,8,6};
        string P10_output = Permutation(P10,key);
        string P10_left = P10_output.substr(0,5);
        string P10_right = P10_output.substr(5,5);
        string pl1 = LShift(P10_left,1);
        string pr1 = LShift(P10_right,1);
        string plpr = pl1+pr1;
        vector<int> P8{6,3,7,4,8,5,10,9};
        K1 = Permutation(P8,plpr);
        cout<<"K1: "<<K1<<endl;
	string pl2=LShift(pl1,2);
	string pr2=LShift(pr1,2);
        plpr = pl2+pr2;
        K2 = Permutation(P8,plpr);
        cout<<"K2: "<<K2<<endl;
        cout<<"\n";
    }

    string LShift(string input,int n)
    {
        string output = input;
        char firstbit;
	    while(n--){
            firstbit = output[0];
            output = output.substr(1,output.size()-1);
            output += firstbit;
        }
        return output;
    }
    
    void Encryption(string text)
    {
	string IPOut=IP(text);
        string LIP = IPOut.substr(0,4);
        string RIP = IPOut.substr(4,4);
        cout<<"IP : "<<IPOut<<endl;
        cout<<"\n";
        cout<<"----- Fk1 -----"<<endl;
        string F1Out=Function_F(LIP,RIP,1);
        cout<<"\n";
        string sw=SW(F1Out);
        cout<<"SW : "<<sw<<endl;
        string L1 = sw.substr(0,4), R1 = sw.substr(4,4);
        cout<<"\n----- Fk2 -----"<<endl;
	    F1Out=Function_F(L1,R1,2);
        cout<<"\n";
        string InvIPOut=InvIP(F1Out);
	    cipher=InvIPOut;
        cout<<"\n******** Encrypted Cipher-text : "<<InvIPOut<<" ********"<<endl;
        cout<<"\n";
	}

	string IP(string text)
	{
        vector<int> IP_array{2,6,3,1,4,8,5,7};
        string ip_out = Permutation(IP_array,text);
	
	return ip_out;
    }

    string InvIP(string input)
    {
        vector<int> InvIPArray{4,1,3,5,7,2,8,6};
        string inv_ip_out = Permutation(InvIPArray,input);

	return inv_ip_out;
    }
    
	string Function_F(string linput,string rinput,int key)
	{
        vector<int> E_P={4,1,2,3,2,3,4,1};
        string E_POutput = Permutation(E_P,rinput);
        cout<<"E/P : "<<E_POutput<<endl;
        string EXOR_Output;
        if(key == 1)
            EXOR_Output = EX_OR(E_POutput,K1);
        else
            EXOR_Output = EX_OR(E_POutput,K2);
        string LEXOR = EXOR_Output.substr(0,4),REXOR = EXOR_Output.substr(4,4);
        cout<<"E/P xor Key : "<<LEXOR+REXOR<<endl;
        string SBOX0_Output=SBOX0(LEXOR);
        string SBOX1_Output=SBOX1(REXOR);
        string SBOX_Output = SBOX0_Output+SBOX1_Output;
        cout<<"SBox : "<<SBOX_Output<<endl;
        vector<int> P4={2,4,3,1}; 
        string P4_Output = Permutation(P4,SBOX_Output);
        cout<<"P4 : "<<P4_Output<<endl;
        string fk_Output = EX_OR(P4_Output,linput);
        cout<<"Fk : "<<fk_Output<<endl;
        string f1_out = fk_Output + rinput;
 	
	return f1_out;
	}
	
	string SW(string a)
	{
	    return a.substr(4,4)+a.substr(0,4);
	}
	
	string EX_OR(string a,string b)
	{
        string output = "";
        for(int i=0;i<a.size();i++)
        {
            if(a[i] == b[i])
                output += "0";
            else
                output += "1";
        }
        return output;
	}
	
    string SBOX0(string l)
	{
        int S0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
        string bits[]={"00","01","10","11"};
	    string lrow = l.substr(0,1)+l.substr(3,1),lcol = l.substr(1,1)+l.substr(2,1);
	    string SO;
        int i,lr,lc,b;
        for(i=0;i<4;i++)
        {
            if(lrow == bits[i])
                lr=i;
            if(lcol == bits[i])
                lc=i;
        }
        b=S0[lr][lc];
        return bits[b];
	}
	
    string SBOX1(string l)
	{

        int S1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,2},{2,1,0,3}};

        string bits[]={"00","01","10","11"};
	    string lrow = l.substr(0,1)+l.substr(3,1),lcol = l.substr(1,1)+l.substr(2,1);
	    string SO;
        int i,lr,lc,b;
        for(i=0;i<4;i++){
            if(lrow == bits[i])
                lr=i;
            if(lcol == bits[i])
                lc=i;
        }
        b=S1[lr][lc];
        return bits[b];
	}

	void Decryption()
	{
	    cout<<"Decryption starts...\n";
		string ip_dout=IP(cipher);
		cout<<"IP : "<<ip_dout<<endl;
		string l=ip_dout.substr(0,4),r=ip_dout.substr(4,4);
		cout<<"\n----- Fk2 -----"<<endl;
		string fk2_out=Function_F(l,r,2);
		string sw_out=SW(fk2_out);
		cout<<"\nSW : "<<sw_out<<endl;
		string l1=sw_out.substr(0,4),r1=sw_out.substr(4,4);
		cout<<"\n----- Fk1 -----"<<endl;
		string fk1_out=Function_F(l1,r1,1);
		string plain_text=InvIP(fk1_out);
		cout<<"\nIP-inv : "<<plain_text<<endl;
		cout<<"\n******** Decrypted Text : "<<plain_text<<" ********"<<endl;
	}
};

int main()
{
    string key,text;
    S_DES S;
    cout<<"\nEnter 10-bits key : ";
    cin>>key;
    cout<<"Enter 8-bits plain text : ";
    cin>>text;
    cout<<"\n";
    S.initialize(key);
    S.Encryption(text);
    S.Decryption();
    return 0;
}
