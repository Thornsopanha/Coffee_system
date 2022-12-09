#include<iostream>
#include<iomanip>
using namespace std;

#include"login.h"
#include"admin.h"

int main(){
    log=login();
    if(log==1){
        cout<<"admin";
        admin();
    }
    else if(log==2){
        cout<<"user";
    }
}


