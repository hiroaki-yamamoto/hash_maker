#include<iostream>
#include<string>
#include "const.hxx"
#include "order.hxx"
using namespace std;
void show_desc();
string invalid="The argument is invalid.";
int main(int argc,char *argv[]){
    if(argc<3){
        show_desc();
        return 0;
    }
    string arg1(argv[1]),arg2(argv[2]);
    if(arg1=="md5"){
        if(arg2=="order") print_order_md5();
        else if(arg2=="const") print_const_md5();
        else{
            cout<<invalid<<endl;
            return 1;
        }
    }else if(arg1=="rmd6"){
        if(arg2=="order") print_order_rmd6();
        else if(arg2=="const") print_const_rmd6();
        else{
            cout<<invalid<<endl;
            return 1;
        }
    }else{
        cout<<invalid<<endl;
    }
return 0;
}
void show_desc(){
    cout<<"Hash maker developper suite"<<endl<<
    "How to use:"<<endl<<"hdev [md5|rmd6] [order|const]"<<endl;
}
