#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;


int globaccountnum=100;




class bank{
    int account_no;
    char name[20];
    int password;
    char address[30];
    double balance;
    bank *next;
public:
    void assignaccno(){
       account_no=globaccountnum++;
    }
    void create_acc();
    void display_acc();
    void deposit();
    void withdraw();
    void modify();
    void check_pass();
    void generate_report();

    void set_next(bank* ptr){
        next=ptr;
    }
    int get_accno(){
        return account_no;
    }
    int get_pass(){
        return password;
    }
    bank* get_next(){
        return next;
    }
};




void bank::create_acc(){
    cin.ignore();
    assignaccno();
    cout<<"Enter the Account Holder Name\n";

    cin.getline(name,20);
    cout<<"Enter the Account Holder address\n";

    cin.getline(address,30);
    cout<<"Enter a four digit numeric password:\n";
    cin>>password;
    cout<<"Enter amount for initial deposition(0 if no amount to be deposited\n";
    cin>>balance;
    system("CLS");

    cout<<"Your account Details:\n";
    display_acc();
    generate_report();
    cin.get();

}

void bank::generate_report(){
    char acno[10];
    sprintf(acno,"%d",account_no);
    strcat(acno,".txt");
    FILE *fp=fopen(acno,"w");

    fprintf(fp,"DO NOT SHARE!\nAccount no: %d\nPassword %d\nName: %s",account_no,password,name);
    fclose(fp);
}

void bank::deposit()
{
    int Amount;
    cout << "Enter How much money you want to deposit: ";
    cin >> Amount;

    balance += Amount;
    cout << "Available Balance: "<< balance;
}

void bank::display_acc()
{
    cout<<"Account no: "<<account_no<<endl
        <<"Name: " << name << endl
        << "Address: " << address << endl
        << "Balance: " << balance << endl
        << endl;
        cin.get();
}

void bank::withdraw()
{
    float amount;


    cout << "Enter How much money "
         << "you want to withdraw: "
         << amount << endl;

    balance -= amount;
    cout << "Available balance: "
         << balance;
}

void bank::modify()
{
    cin.ignore();
    cout<<"Enter the name u want to change to";

    gets(name);
    cout<<"ENter the new adress";

    gets(address);
    generate_report();
    display_acc();

    cin.get();
}






bank* insertnewaccount(bank* start){

    if(start==NULL){
        start=(bank*)malloc(sizeof(bank));
        start->set_next(NULL);
        start->create_acc();
        return start;
    }

    bank *ptr=start,*temp=start;
    while(ptr!=NULL){
        temp=ptr;
        ptr=ptr->get_next();
    }
    ptr=(bank*)malloc(sizeof(bank));
    ptr->set_next(NULL);
    ptr->create_acc();
    temp->set_next(ptr);
    return start;
}


bank* isaccount(bank* start,int tempacc,int temppass){
    bank*ptr=start;
    while(ptr!=NULL){
        if(ptr->get_accno()==tempacc&&ptr->get_pass()==temppass){
            return ptr;
        }
        ptr=ptr->get_next();
    }
    return NULL;
}


void login(bank* start){
    int tempaccnum,temppass;
    bank* ptr;
    cout<<"Enter your acc_num";
    cin>>tempaccnum;
    cout<<"Enter your password";
    cin>>temppass;
    cin.ignore();
    if(ptr=isaccount(start,tempaccnum,temppass)){
        system("CLS");
        cout<<"LOG IN SUCCESS!\n";
        int m=0;
        while(m<4){
            cout<<"Enter 1 to Deposit\nEnter 2 to Withdraw\nEnter 3 to Modify account details\nEnter 4 to logout ";
            cin>>m;
            system("CLS");
            switch(m){
                case 1:
                    ptr->deposit();
                    break;
                case 2:
                    ptr->withdraw();
                    break;
                case 3:
                    ptr->modify();
                    break;
            }
            cin.ignore();
            cin.get();
            system("CLS");
        }

        return;
    }
    cout<<"Account no or password is incorrect";
    cin.get();
}


/*
void display(bank* start){
    bank *ptr=start;
    while(ptr!=NULL){
        ptr->display_acc();
        ptr=ptr->get_next();
    }
}
*/


int main()
{
    bank* start=NULL;

    int m=0;
    while(m<3){
        system("CLS");
        std::cout << R"(
         _._._                       _._._
        _|   |_                     _|   |_
        | ... |_._._._._._._._._._._| ... |
        | ||| |  o OMCAB BANK o  | ||| |
        | """ |  """    """    """  | """ |
   ())  |[-|-]| [-|-]  [-|-]  [-|-] |[-|-]|  ())
  (())) |     |---------------------|     | (()))
 (())())| """ |  """    """    """  | """ |(())())
 (()))()|[-|-]|  :::   .-"-.   :::  |[-|-]|(()))()
 ()))(()|     | |~|~|  |_|_|  |~|~| |     |()))(()
    ||  |_____|_|_|_|__|_|_|__|_|_|_|_____|  ||
 ~ ~^^ @@@@@@@@@@@@@@/=======\@@@@@@@@@@@@@@ ^^~ ~
      ^~^~                                ~^~^
)" << '\n';



        cout<<"_______________________________________\n||:Welcome to OMCAB Bank:            ||\n";
        cout<<"|| Enter 1 to Create new account     ||\n|| Enter 2 to Login into an account  ||\n|| Enter 3 to exit                   ||\n_______________________________________";
        cin>>m;
        system("CLS");
        switch(m){
            case 1:
                start=insertnewaccount(start);
                break;
            case 2:
                login(start);
                break;


        }
    }

}
