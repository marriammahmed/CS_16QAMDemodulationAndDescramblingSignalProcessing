//
//  main.cpp
//  MOXZs
//
//  Created by Mariam Hatem on 16/11/2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>
using namespace std;


vector<int8_t> readBinaryFile(string filename){
    vector<int8_t> samples;
    
    ifstream file(filename, ios::binary);
    if(!file){
        cout<<"Kein file"<<endl;
        return samples;
    }
    
   int8_t temp;
   while(file.read((char*)&temp, sizeof(int8_t))){
        samples.push_back(temp);
    }
    
    file.close();
    
    return samples;
}

uint8_t demodulate(int8_t real, int8_t imag) {
    
    if (real == -3 && imag == -3) return 0;
    if (real == -3 && imag == -1) return 1;
    if (real == -3 && imag == 1) return 2;
    if (real == -3 && imag == 3) return 3;
    
    if (real == -1 && imag == -3) return 4;
    if (real == -1 && imag == -1) return 5;
    if (real == -1 && imag == 1) return 6;
    if (real == -1 && imag == 3) return 7;
    
    if (real == 1 && imag == -3) return 12;
    if (real == 1 && imag == -1) return 13;
    if (real == 1 && imag == 1) return 14;
    if (real == 1 && imag == 3) return 15;
    
    if (real == 3 && imag == -3) return 8;
    if (real == 3 && imag == -1) return 9;
    if (real == 3 && imag == 1) return 10;
    if (real == 3 && imag == 3) return 11;
    
    return 0;
}

vector<bool> descramble(vector<bool>scrambled_bits){
    int secret_code[13]={1,0,1,1,1,0,0,0,1,0,1,0,0};
    
    vector<bool> descrambled;
    
    for(int i=0;i< scrambled_bits.size();i++){
        bool current= scrambled_bits[i];
        bool secret= secret_code[i%13];
        
        bool result= current ^ secret;
        descrambled.push_back(result);
        
    }
    return descrambled;
}

string bitstoASCII(vector<bool> bits){
    string output="";
    for(int i=0;i<bits.size();i+=8){
        
        int8_t byte=0;
        for(int j=0;j<8;j++){
            byte=(byte<<1) | bits[i+j];
        }
        output+=(char)byte;
    }
    
    return output;
}

int main(int argc, const char * argv[]) {
    string filename= "/Users/marriamhatem/Downloads/applicant-test.bin";
    vector<int8_t> samples= readBinaryFile(filename);
    cout<<"loaded "<<samples.size()<< " samples"<<endl;
    
    vector<bool>demod_bits;
    for(int i=0;i<samples.size();i+=2){
       int8_t real= samples[i];
       int8_t img= samples[i+1];
       int8_t symbol= demodulate(real,img);
       bitset<4>bits(symbol);
    
        
        for(int j=3;j>=0;j--){
            demod_bits.push_back(bits[j]);
        }
    }
    cout << "First 10 demod bits: ";
    for(int i = 0; i < 10; i++) {
        cout << demod_bits[i];
    }
    cout << endl;
    vector<bool> descrambled= descramble(demod_bits);
    string output= bitstoASCII(descrambled);
    cout<<output<<endl;
    return 0;
}
