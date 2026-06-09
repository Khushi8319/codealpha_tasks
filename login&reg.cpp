#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// check if username already exists
bool isUserExists(string username){
    ifstream file("users.txt");
    string u,p;
    while(file>>u>>p){
        if(u==username){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// registration function
void registerUser(){
    string username,password;

    cout<<"Enter username: ";
    cin>>username;

    // validation
    if(username.length()<3){
        cout<<"Error: Username must be at least 3 characters\n";
        return;
    }

    cout<<"Enter password: ";
    cin>>password;

    if(password.length()<6){
        cout<<"Error: Password must be at least 6 characters\n";
        return;
    }

    if(isUserExists(username)){
        cout<<"Error: Username already exists\n";
        return;
    }

    ofstream file("users.txt",ios::app);
    file<<username<<" "<<password<<endl;
    file.close();

    cout<<"Registration successful\n";
}

// login function
void loginUser(){
    string username,password,u,p;

    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter password: ";
    cin>>password;

    ifstream file("users.txt");
    bool found=false;

    while(file>>u>>p){
        if(u==username && p==password){
            found=true;
            break;
        }
    }
    file.close();

    if(found)
        cout<<"Login successful! Welcome, "<<username<<"\n";
    else
        cout<<"Invalid username or password\n";
}

int main(){
    int choice;

    do{
        cout<<"\n1. Register\n2. Login\n3. Exit\nEnter choice: ";
        cin>>choice;

        if(choice==1)
            registerUser();
        else if(choice==2)
            loginUser();
        else if(choice==3)
            cout<<"Exit\n";
        else
            cout<<"Invalid choice\n";

    }while(choice!=3);

    return 0;
}
