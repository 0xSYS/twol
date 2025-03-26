#include <fstream>
using namespace std;
ifstream in("date.in");


struct info{
    char name[10];
    char ip[10];
    char brd_ip[10];
    char mac_adr[10];
    char note[10];

};

info devices[100];

void ReadFromFile(const char* file){
    int nr=0;
    ifstream in(file);
    while(in>>devices[nr].name){
        in>>devices[nr].ip;
        in>>devices[nr].brd_ip;
        in>>devices[nr].mac_adr;
        nr++;
    }
}
void WriteToFile(const char* file){
    int nr=0;
    ofstream out(file);
    out<<"Name"<<" "<<"IP"<<" "<<"Broadcast IP"<<" "<<"Mac Address";
    while(out<<devices[nr].name<<" "){
        out<<devices[nr].ip<<" ";
        out<<devices[nr].brd_ip<<" ";
        out<<devices[nr].mac_adr<<" ";
        nr++;
    }
}
