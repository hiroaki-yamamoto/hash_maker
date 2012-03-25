#include<iostream>
#include<sstream>
#include<fstream>
#include<cctype>
#include<cstdlib>
#include "operator.h"
extern "C"{
    #include<sys/stat.h>
}

#include"types.h"
#include"rmd6.h"
#include"md5.h"

#define Generation 3
#define Revision 5

#define directory_message " is a directory. Skipped it"
#define correct_file	  " may be a correct file."
#define broken_file		  " may be a broken file."
#define open_failed		  "Failed to open a stream,"
#define hash_question	  "Is this a hash file?:"
#define invalid_format	  "The data is not formatted correctly.Skipped it."

using namespace std;
using namespace enc_hash;
template<class generator> void make_hash(generator gen,char *arg[],int acount);
void show_desc();
bool is_directory(const char *path);
int main(int argc,char* argv[]){
    if(argc<4){
        show_desc();
        return 0;
    }
    
    string arg1(argv[1]);
    if(arg1=="rmd6"){
        rmd6 gen;
        make_hash(gen,argv,argc);
    }else if(arg1=="md5"){
        md5 gen;
        make_hash(gen,argv,argc);
    }else{
        show_desc();
    }
return 0;
}

template<class generator> void make_hash(generator gen,char *arg[],int acount){
        string mode_str=arg[2];
    if(mode_str[0]!='-'){
    show_desc();
    return;
    }
    const char mode=mode_str[1];
    switch(mode){
        case 's':
            for(int count=3;count<acount;count++){
                cout<<gen.compute_hash(arg[count])<<" "<<arg[count]<<endl;
            }
            break;
        case 'f':
            for(int count=3;count<acount;count++){
                if(is_directory(arg[count])){
                    cout<<arg[count]<<directory_message<<endl;
                    continue;
                }
                ifstream in(arg[count],ios::binary);
                if(!in){
                    cout<<open_failed<<endl;
                    exit(1);
                }
                cout<<gen.compute_hash(in)<<" "<<arg[count]<<endl;
                in.close();
            }
            break;
        case 'c':
            for(int count=3;count<acount;count++){
                bool broken=false;
                if(is_directory(arg[count])){
                    cout<<arg[count]<<directory_message<<endl;
                    exit(1);
                }
                ifstream hash_file(arg[count]);
                if(!hash_file){
                    cout<<open_failed<<endl<<hash_question<<arg[count]<<endl;
                    exit(1);
                }
                string data;
                char buf[1];
                while(hash_file){
                    for(hash_file.rdbuf()->sgetn(buf,sizeof(buf));buf[0]!='\n';hash_file.rdbuf()->sgetn(buf,sizeof(buf))){
                        data+=buf[0];
                        if(!hash_file) break;
                    }
                    int found=data.find(" ",0);
                    if(data.empty()) break;
                    if(found<0){
                        cout<<invalid_format<<endl;
                        data.clear();
                        continue;
                    }
                    string hash_from_file=data.substr(0,found),file=data.substr(found+1,data.size());
                    stringstream strstream;
                    //Cutting blank spaces.
                    while(isspace(file[0])) file=file.substr(1,file.size());
                    if(is_directory(file.c_str())){
                        cout<<file<<directory_message<<endl;
                        data.clear();
                        continue;
                    }
                    ifstream filestream(file.data(),ios::binary);
                    if(!filestream){
                        cout<<open_failed<<endl;
                        exit(1);
                    }
                    strstream<<gen.compute_hash(filestream);
                    if(strstream.str()==hash_from_file) cout<<file<<correct_file<<endl;
                    else{
                        cout<<file<<broken_file<<endl;
                        broken=true;
                    }
                    data.clear();
                }
                hash_file.close();
                if(broken){exit(1);}
            }
            break;
        default:
            show_desc();
            break;
    }
}
bool is_directory(const char *path){
    struct stat result;
    if(stat(path,&result)!=0) return false;
    else return ((result.st_mode&S_IFMT)==S_IFDIR);
}
void show_desc(){
    stringstream sentence,hr;
    string usage="Usage:hash [mode] [-c|-s|-f] <string or files>";
    
    sentence<<"Hash maker:version:"<<"G."<<Generation<<" Rev."<<Revision<<endl<<endl<<usage;
    for(uint count=0;count<usage.size();count++) hr<<"=";
    sentence<<endl<<hr.str()<<endl;
    sentence<<"Modes:"<<endl;
    sentence<<"\trmd6\t:Make RIPEMD-160 hash."<<endl;
    sentence<<"\tmd5\t:Make MD5 hash."<<endl<<endl;
    sentence<<"-s <string>\t: Make hash-code from specified string."<<endl;
    sentence<<"-f <files>\t: Make hash-code from specified file."<<endl;
    sentence<<"-c <files>\t: Read hash files and check them."<<endl<<endl;
    sentence<<"Copyrights:"<<endl<<"This software is being developped by hyamamoto, and released with the latest GPL."<<endl;
    sentence<<"You can modify this software, but at least, you have to release the sourcecode when you redistribute."<<endl;

    cout<<sentence.str()<<endl;
}
