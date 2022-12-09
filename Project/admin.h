#include<fstream>

const int SIZE = 15;

struct node{
    string id;
    string name;
    float price;
//    char size_;
    node *next;
    node *previous;
};

struct List{
    int n;
    node *head;
    node *tail;
};

List *emptyList(){
    List *l;
    l = new List();

    l->n=0;
    l->tail=NULL;
    l->head=NULL;

    return l;
}

List *ht[SIZE];

int hashFunction(string IdValue){
    int key=0;
    for(int i = 0; i<IdValue.length(); i++){
        key = key + IdValue[i];
    }
    return key%SIZE;
}

void initializeList(){
    for(int i = 0; i<SIZE; i++){
        ht[i]=emptyList();
    }
}

void addEnd(List *l, string ID,string nameData, float priceData){
    node *e;
    e= new node();
    e->name = nameData;
    e->id=ID;
    e->price = priceData;
//    e->size_ = Size;
    e->next = NULL;
    e->previous = l->head;
    if(l->n==0){
        l->tail=e;
        l->head=e;
    }
    else{
        l->tail->next=e;
        l->tail=e;
    }
    l->n++;
}

void addDatatoHash(string ID, string nameData, float priceData){
    int index;
    index = hashFunction(ID);
    addEnd(ht[index], ID, nameData, priceData);
}

void Display(){
    node *tmp;
    cout<<endl<<setw(15)<<left<<"ID"<<setw(20)<<left<<"Name"<<setw(15)<<"Price"<<endl;
    for(int i = 0; i<SIZE; i++){
        tmp = ht[i]->head;
        while(tmp!=NULL){
            cout<<setw(15)<<left<<tmp->id<<setw(20)<<tmp->name<<"$"<<setw(15)<<tmp->price<<endl;
            tmp=tmp->next;
        }
    }
}

 int Remove(string ID){
    node *tmp, *e;
    int index;
    index = hashFunction(ID);
    e = ht[index]->head;
    if(e!=NULL && e->id==ID){
        ht[index]->head=e->next;
        delete e;
        ht[index]->n--;
        return 1;
    }
    while(e!=NULL && e->id!=ID){
        tmp = e;
        e = e->next;
    }
    if(e==NULL){
        return 0;
    }
    tmp->next = e->next;
    delete e;
    ht[index]--;
    return 1;
}

void Search(string ID){
    node *tmp;
    int index;
    index = hashFunction(ID);
    tmp = ht[index]->head;
    cout<<endl;
    while(tmp!=NULL){
        if(tmp->id==ID){
            cout<<endl<<setw(15)<<left<<"ID"<<setw(20)<<left<<"Name"<<setw(15)<<"Price"<<endl;
            cout<<setw(15)<<left<<tmp->id<<setw(20)<<tmp->name<<"$"<<setw(15)<<tmp->price<<endl;
            return;
        }
        tmp = tmp->next;
    }
    cout<<"ID "<<ID<<" Not Found\n";
}


void update(List *L, string ID, string newID, string Name, float Price){
    node *t;
    t = L->head;
    while(t!=NULL){
        if(t->id==ID){
            Remove(ID);
            addDatatoHash(newID, Name, Price);
            return;
        }
        t=t->next;
    }
}

int Check(string ID){
    node *t;
    int index;
    index = hashFunction(ID);
    t=ht[index]->head;
    if(ht[index]->n==0){
        return 0;
    }
    else{
        while(t!=NULL){
            if(ID==t->id){
                return 1;
            }
            t=t->next;
        }
        return 0;
    }
}

void read(){

    fstream file;
    file.open("myFile.txt", ios::in);

    string ID, Name;
    float Price;
    if(!file){
        return;
    }
    else{
        while(!file.eof()){
            file>>ID>>Name>>Price;
            addDatatoHash(ID,Name,Price);
        }
        Remove(ID);
    }
    file.close();
}


void autoSave(List *L){
    fstream file;
    node *t;
    file.open("myFile.txt", ios::out);
    for(int i = 0; i<SIZE; i++){
        t = ht[i]->head;
        while(t!=NULL){
            file<<t->id<<" "<<t->name<<" "<<t->price<<endl;
            t = t->next;
        }

    }
    file.close();
}

void admin(){
    List *L;
    initializeList();
    string Name, ID;
    char Size;
    float Price;
    int choice, c, option;
    read();
    while(1){
        cout<<"\nWelcome Coffee Shop System"<<endl;
        cout<<"0.Exit\n1.Add\n2.Display\n3.Search by ID\n4.Update\n5.Delete\nYour Choice: ";
        cin>>choice;
        if(choice==0){
            cout<<"Exit";
            break;
        }
        else if(choice==1){
            cout<<"\nInput ID: "; cin>>ID;
            c=Check(ID);
            if(c==1){
                cout<<"ID already taken!!\n";
            }
            else if(c==0){
                cout<<"Input Name: "; cin>>Name;
                cout<<"Input Price: "; cin>>Price;
//                cout<<"Size\n1. Small\n2. Medium\n3. Large\nYour Choice: "; cin>>option;
//                if(option==1){
//                    Size = 'S';
//                }
//                else if(option==2){
//                    Size = 'M';
//                }
//                else if(option==3){
//                    Size = 'L';
//                }
                addDatatoHash(ID,Name,Price);
            }
        }
        else if(choice==2){
            Display();
        }
        else if(choice==3){
            cout<<"\nInput ID: "; cin>>ID;
            Search(ID);
        }
        else if(choice==5){
            int r;
            cout<<"\nInput ID: "; cin>>ID;
            r=Remove(ID);
            if(r==1){
                cout<<"Successfully removed an item\n";
            }
            else{
                cout<<"Remove unsuccessfully, item not found\n";
            }
        }
        else if(choice==4){
            string newID;
            cout<<"\nInput ID: "; cin>>ID;
            c=Check(ID);
            if(c==1){
                cout<<"\nUpdate ID: "; cin>>newID;
                c=Check(newID);
                    if(c==0){
                        int index;
                        index = hashFunction(ID);
                        cout<<"Update Name: "; cin>>Name;
                        cout<<"Update Price: "; cin>>Price;
                            update(ht[index],ID,newID,Name,Price);
                        cout<<"Update Completed\n";
                    }
                    else if(c==1){
                        cout<<"ID already taken!!\n";
                    }
            }
            else{
                cout<<"Update fail, ID not found\n";
            }
        }
        autoSave(L);
    }
}
