#include<iostream>
#include<vector>
#include<string>
using namespace std;

// transaction class
class Transaction{
public:
    string type;
    double amount;

    Transaction(string t, double a){
        type=t;
        amount=a;
    }
};

// account class
class Account{
private:
    long long accountNo;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo){
        accountNo=accNo;
        balance=0;
    }

    // getter functions
    int getAccountNo(){ return accountNo; }
    double getBalance(){ return balance; }

    void deposit(double amount){
        if(amount <= 0){
            cout<<"Invalid amount!"<<endl;
            return;
        }
        balance+=amount;
        history.push_back(Transaction("Deposit",amount));
        cout<<"Deposit successful! New balance: "<<balance<<endl;
    }

    void withdraw(double amount){
        if(amount <= 0){
            cout<<"Invalid amount!"<<endl;
            return;
        }
        if(amount<=balance){
            balance-=amount;
            history.push_back(Transaction("Withdraw",amount));
            cout<<"Withdrawal successful! New balance: "<<balance<<endl;
        }else{
            cout<<"Insufficient balance"<<endl;
        }
    }

    void transfer(Account &toAccount, double amount){
        if(amount <= 0){
            cout<<"Invalid amount!"<<endl;
            return;
        }
        if(amount<=balance){
            balance-=amount;
            toAccount.balance+=amount;

            history.push_back(Transaction("Transfer Sent",amount));
            toAccount.history.push_back(Transaction("Transfer Received",amount));
            cout<<"Transfer successful!"<<endl;
        }else{
            cout<<"Insufficient balance"<<endl;
        }
    }

    void showTransactions(){
        if(history.empty()){
            cout<<"No transactions yet."<<endl;
            return;
        }
        cout<<"Transaction History:"<<endl;
        for(int i=0;i<history.size();i++){
            cout<<history[i].type<<" : Rs."<<history[i].amount<<endl;
        }
    }
};

// customer class
class Customer{
private:
    string name;
    Account account;

public:
    Customer(string n, int accNo):account(accNo){
        name=n;
    }

    // getter functions
    string getName(){ return name; }
    Account& getAccount(){ return account; }

    void showAccountInfo(){
        cout<<"Customer Name  : "<<name<<endl;
        cout<<"Account Number : "<<account.getAccountNo()<<endl;
        cout<<"Balance        : Rs."<<account.getBalance()<<endl;
    }
};

// find customer by account number
int findCustomer(vector<Customer> &customers, int accNo){
    for(int i=0;i<customers.size();i++){
        if(customers[i].getAccount().getAccountNo()==accNo)
            return i;
    }
    return -1;
}

int main(){
    vector<Customer> customers;
    int choice;

    do{
        cout<<"\n--- Banking System Menu ---"<<endl;
        cout<<"1. Create Customer"<<endl;
        cout<<"2. Deposit"<<endl;
        cout<<"3. Withdraw"<<endl;
        cout<<"4. Fund Transfer"<<endl;
        cout<<"5. View Account Info"<<endl;
        cout<<"6. View Transactions"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1){
            string name;
            int accNo;

            cout<<"Enter customer name: ";
            cin>>ws;
            getline(cin,name);

            cout<<"Enter account number: ";
            cin>>accNo;

            // duplicate account number check
            int check=findCustomer(customers,accNo);
            if(check != -1){
                cout<<"Account number already exists!"<<endl;
            }else{
                customers.push_back(Customer(name,accNo));
                cout<<"Customer created successfully"<<endl;
            }
        }

        else if(choice==2){
            int accNo;
            double amount;

            cout<<"Enter account number: ";
            cin>>accNo;

            int index=findCustomer(customers,accNo);
            if(index!=-1){
                cout<<"Enter amount: ";
                cin>>amount;
                customers[index].getAccount().deposit(amount);
            }else{
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==3){
            int accNo;
            double amount;

            cout<<"Enter account number: ";
            cin>>accNo;

            int index=findCustomer(customers,accNo);
            if(index!=-1){
                cout<<"Enter amount: ";
                cin>>amount;
                customers[index].getAccount().withdraw(amount);
            }else{
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==4){
            int fromAcc,toAcc;
            double amount;

            cout<<"Enter sender account number: ";
            cin>>fromAcc;

            cout<<"Enter receiver account number: ";
            cin>>toAcc;

            cout<<"Enter amount: ";
            cin>>amount;

            int sender=findCustomer(customers,fromAcc);
            int receiver=findCustomer(customers,toAcc);

            if(sender!=-1 && receiver!=-1){
                customers[sender].getAccount().transfer(customers[receiver].getAccount(),amount);
            }else{
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==5){
            int accNo;
            cout<<"Enter account number: ";
            cin>>accNo;

            int index=findCustomer(customers,accNo);
            if(index!=-1){
                customers[index].showAccountInfo();
            }else{
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==6){
            int accNo;
            cout<<"Enter account number: ";
            cin>>accNo;

            int index=findCustomer(customers,accNo);
            if(index!=-1){
                customers[index].getAccount().showTransactions();
            }else{
                cout<<"Account not found"<<endl;
            }
        }

        else if(choice==7){
            cout<<"Thank you!"<<endl;
        }

        else{
            cout<<"Invalid choice"<<endl;
        }

    }while(choice!=7);

    return 0;
}
