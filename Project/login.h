
int login(){
    int choice;
    string pw;
    while(1){
        cout<<"1.Login As Admin\n2.Login As User\nYour Choice: "; cin>>choice;
        if(choice==1){
            cout<<"Enter Password: "; cin>>pw;
            if(pw=="admin123"){
                cout<<"Login as admin\n";
                return 1;
            }
            else{
                cout<<"Password Is Incorrect\n";
            }
        }
        else if(choice==2){
            cout<<"Enter Password: "; cin>>pw;
            if(pw=="user123"){
                cout<<"Login as user\n";
                return 2;
            }
            else{
                cout<<"Password Is Incorrect\n";
            }
        }
    }
}
