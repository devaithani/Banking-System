# include<bits/stdc++.h>
using namespace std;

    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

class Authentication
{
    private:
        string id_ = "mayankaithani";
        string password_ = "Karwaan";
    
    public:
        bool authenticate(string id, string password)
        {
            if(id == id_ && password == password_)
                return 1;
            else 
                return 0;
        }
};

class CustomerRecords
{
    private:
        string depositorName_;
        string accountNumber_;
        string accountType_;
        float balance_;
        
    public:
    
        CustomerRecords(){}
        
        CustomerRecords(string depositorName, string accountNumber, string accountType, float balance)
        {
            this->depositorName_ = depositorName;
            this->accountNumber_ = accountNumber;
            this->accountType_ = accountType;
            this->balance_ = balance;
            
            writeToFile();
        }
        
        void writeToFile()
        {
            fstream fileOut;
            fileOut.open("Records.txt", ios::out | ios::app);
            fileOut<<accountNumber_<<",";
            fileOut<<depositorName_<<",";
            fileOut<<accountType_<<",";
            fileOut<<balance_<<"\n";
        }
        
        void setName(string depositorName)
        {
            depositorName_ = depositorName;
        }
        
        void setAccountNo(string accountNumber)
        {
            accountNumber_ = accountNumber;
        }
        
        void setAccountType(string accountType)
        {
            accountType_ = accountType;
        }
        
        void setBalance(float balance)
        {
            balance_ = balance;
        }
        
        string getName()
        {
            return depositorName_;
        }
        
        string getAccountNo()
        {
            return accountNumber_;
        }
        
        string getAccountType()
        {
            return accountType_;
        }
        
        float getBalance()
        {
            return balance_;
        }
        
};

void readFromFile(vector<CustomerRecords>& records)
{
    fstream fileInput;
    fileInput.open("Records.txt", ios::in);
    string line, word;
    
    while (!fileInput.eof())
    {
        CustomerRecords tempObject;
        fileInput>>line;
        stringstream s(line);
        
        getline(s, word, ',');
        tempObject.setAccountNo(word);
        getline(s, word, ',');
        tempObject.setName(word);
        getline(s, word, ',');
        tempObject.setAccountType(word);
        getline(s, word, ',');
        //float tempBalance = stof(word);
        tempObject.setBalance(0.00);
        
        records.push_back(tempObject);
    }
}

void displayFile(vector<CustomerRecords>& records)
{
    cout<<"\n*********** LIST OF CUSTOMERS ***********\n";
    for(int i=0;i<records.size(); i++)
    {
        cout<<"Customer "<<i+1<<" Account Number : "<<records[i].getAccountNo()<<endl;
        cout<<"Customer "<<i+1<<" Name : "<<records[i].getName()<<endl;
        cout<<"Customer "<<i+1<<" Account Type : "<<records[i].getAccountType()<<endl;
        cout<<"Customer "<<i+1<<" Account Balance : "<<records[i].getBalance()<<endl;
        cout<<"____________________________________________________________________\n";
    }
}

void deleteRecord(vector<CustomerRecords>& records, string toBeDeletedAN)
{
    remove("Records.txt");
    for(int i=0;i<records.size(); i++)
    {
        if(records[i].getAccountNo() != toBeDeletedAN)
        {
            records[i].writeToFile();
        }
    }
}

string  generateRandom(int len) {
    string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}

class Transaction
{
    private:
        string transactionID_ = generateRandom(6);
        string operation_;
        float amount_;
        float balance_;
        int dateOfTransaction_ = timePtr->tm_mday;
        int monthOfTransaction_ = timePtr->tm_mon;
        int yearOfTransaction_ = timePtr->tm_year;
        CustomerRecords customer_;
    
    public:
        Transaction(){}
        
        void credit()
        {
            cout<<"\nEnter Account Number : ";
            string temp;
            cin>>temp;
            customer_.setAccountNo(temp);
            string fileName = "TR" + customer_.getAccountNo() + ".txt";
            cout<<"\nEnter amount to be credited : ";
            cin>>amount_;
            balance_ += amount_;
            operation_ = "Credit";
            writeToFile(fileName);
        }
        
        void debit()
        {
            cout<<"\nEnter Account Number : ";
            string temp;
            cin>>temp;
            customer_.setAccountNo(temp);
            string fileName = "TR" + customer_.getAccountNo() + ".txt";
            cout<<"\nEnter amount (in the multiples of 100) to be debited : ";
            cin>>amount_;
            balance_ -= amount_;
            operation_ = "Debit";
            writeToFile(fileName);
        }
        
        void writeToFile(string fileName)
        {
            fstream fileOut;
            fileOut.open(fileName, ios::out | ios::app);
            fileOut<<transactionID_<<",";
            fileOut<<customer_.getAccountNo()<<",";
            fileOut<<operation_<<",";
            fileOut<<amount_<<",";
            fileOut<<balance_<<",";
            fileOut<<dateOfTransaction_<<",";
            fileOut<<monthOfTransaction_<<",";
            fileOut<<yearOfTransaction_<<"\n";
        }
        
        void readFromFile(string fileName)
        {
            fstream fileInput;
            fileInput.open(fileName, ios::in);
            string line, word;
            
            while (!fileInput.eof())
            {
                fileInput>>line;
                stringstream s(line);
                
                getline(s, word, ',');
                transactionID_ = word;
                getline(s, word, ',');
                customer_.setAccountNo(word);
                getline(s, word, ',');
                operation_ = word;
                getline(s, word, ',');
                amount_ = stof(word);
                getline(s, word, ',');
                balance_ = stof(word);
                getline(s, word, ',');
                dateOfTransaction_ = stoi(word);
                getline(s, word, ',');
                monthOfTransaction_ = stoi(word);
                getline(s, word, ',');
                yearOfTransaction_ = stoi(word);
                
                displayTransactions();
            }
        }
        
        string getTransactionID()
        {
            return transactionID_;
        }
        
        void displayTransactions()
        {
            cout<<"\nTransaction ID : "<<transactionID_;
            cout<<"\nAccount Number : "<<customer_.getAccountNo();
            cout<<"\nCredited/Debited : "<<operation_;
            cout<<"\nAmount : "<<amount_;
            cout<<"\nBalance after Operation : "<<balance_;
            cout<<"\nDate : "<<dateOfTransaction_<<"/"<<monthOfTransaction_<<"/"<<yearOfTransaction_<<endl;
            cout<<"____________________________________________________________________\n";
        }
        
        float calculateInterest()
        {
            int pd = timePtr->tm_mday;
            int pm = timePtr->tm_mon;
            int py = timePtr->tm_year;
            
            int bd = dateOfTransaction_;
            int bm = monthOfTransaction_;
            int by = yearOfTransaction_;
            
            int d, m, y;
            int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            y = py - by;
            if (pm < bm)
            {
                y--;
                m = 12 - (bm - pm);       
            }
            else
            {
                m = pm - bm;
            }
            if (pd < bd)
            {
                m--;
                d = md[pm - 1] - (bd - pd);
            }
            else
            {
                d = pd - bd;
            }
            
            if(m>0)
            {
                return balance_*(3.5)*m*(12*y);
            }
            else 
                return 0;
        }
};

void addToCustomerRecord()
{
    string name, accountNumber, accountType;
    cout<< "\n******* Add a new Customer ******* \n";
    cout<<"\nEnter New Customer's Name : ";
    cin>>name;
    cout<<"Enter Account Number : ";
    cin>>accountNumber;
    cout<<"Enter Account Type (Savings or Current) : ";
    cin>>accountType;
    CustomerRecords newCustomer(name, accountNumber, accountType, 0.00);
}

int main()
{
    cout<<"\n:::::::::::::::WELCOME TO THE BANKING SYSTEM :::::::::::::::::::\n";
    cout<<"\n                       COSMOS BANK                              \n";
    
    Authentication employee;
    string id, password;
    cout<<"\n\n\nEnter login id : ";
    cin>>id;
    cout<<"Enter Password : ";
    cin>>password;
    if(!employee.authenticate(id, password))
    {
        cout<<"\n OOPS  !!!!   Invalid credentials \n:-( Terminating program!!!!!!! :-( ";
        return 0;
    }
    START:
    int option;
    
    cout<<"\nChoose option number \n";
    cout<<"\n1. Add a new Customer";
    cout<<"\n2. Display Records file (i.e details of all the customers) ";
    cout<<"\n3. Delete any customer information ";
    cout<<"\n4. Credit money to any Customer's Account";
    cout<<"\n5. Debit money from any Customer's Account";
    cout<<"\n6. Display last entry to Records file";
    cout<<"\n7. Check if an account exists";
    cout<<"\n8. Display Customer name using Account Number";
    cout<<"\n9. Display Customer balance using Account Number";
    cout<<"\n10. Get transaction ID and Details using Account Number";
    cout<<"\n11. Display Customer Information using Account Number";
    cout<<"\n12. Check Interest if earned any\n\nOption : ";
    
    cin>>option;
    switch(option)
    {
        case 1:
        {
            addToCustomerRecord();
            cout<<"\n>>>>>>> New Customer added <<<<<<\n";
            break;
        }
        case 2:
        {
            vector<CustomerRecords> customer;
            readFromFile(customer);
            displayFile(customer);
            cout<<"\n>>>>>>> Information Displayed <<<<<<\n";
            break;
        }
        case 3:
        {
            vector<CustomerRecords> customer;
            readFromFile(customer);
            string accountNumber;
            cout<<"\nEnter account number : ";
            cin>>accountNumber;
            deleteRecord(customer, accountNumber);
            cout<<"\n>>>>>>> Record Deleted <<<<<<\n";
            break;
        }
        case 4:
        {
            Transaction trans;
            trans.credit();
            cout<<"\n>>>>>>> Amount credited <<<<<<\n";
            break;
        }
        case 5:
        {
            Transaction trans;
            trans.debit();
            cout<<"\n>>>>>>> Amount debited <<<<<<\n";
            break;
        }
        case 6:
        {
            cout<<"Last Record Details :- \n";
            vector<CustomerRecords> customer;
            readFromFile(customer);
            cout<<"Customer "<<" Account Number : "<<customer[customer.size()-1].getAccountNo()<<endl;
            cout<<"Customer "<<" Name : "<<customer[customer.size()-1].getName()<<endl;
            cout<<"Customer "<<" Account Type : "<<customer[customer.size()-1].getAccountType()<<endl;
            cout<<"Customer "<<" Account Balance : "<<customer[customer.size()-1].getBalance()<<endl;
            cout<<"____________________________________________________________________\n";
            cout<<"\n>>>>>>> Information Displayed <<<<<<\n";
            break;
        }
        case 7:
        {
            cout<<"\nEnter account number to check : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            int flag =0;
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    flag = 1;
            }
            if(flag ==0)
                cout<<"\n\n #####   No Account found  ####\n";
            else
                cout<<"\n\n #####   Account found  ####\n";
            break;
        }
        case 8:
        {
            cout<<"\nEnter Account number to extract the name : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    cout<<"\nAccount Holder Name : "<<customer[i].getName()<<endl;
            }
            cout<<"\n>>>>>>> Name Displayed <<<<<<\n";
            break;
        }
        case 9:
        {
            cout<<"\nEnter Account number to extract the balance : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    cout<<"\nAccount Holder Balance : Rs."<<customer[i].getBalance()<<endl;
            }
            cout<<"\n>>>>>>> Balance Displayed <<<<<<\n";
            break;
        }
        case 10:
        {
            cout<<"\nEnter Account number to see the transaction details : ";
            string accountNumber;
            cin>>accountNumber;
            string fileName = "TR" + accountNumber + ".txt";
            Transaction trans;
            trans.readFromFile(fileName);
            cout<<"\n>>>>>>> Transaction file displayed <<<<<<\n";
            break;
        }
        case 11:
        {
            cout<<"\nEnter Account number whose information to be displayed : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                {
                    cout<<"Customer "<<" Account Number : "<<customer[i].getAccountNo()<<endl;
                    cout<<"Customer "<<" Name : "<<customer[i].getName()<<endl;
                    cout<<"Customer "<<" Account Type : "<<customer[i].getAccountType()<<endl;
                    cout<<"Customer "<<" Account Balance : "<<customer[i].getBalance()<<endl;
                    cout<<"____________________________________________________________________\n";
                }
            }
            break;
        }
        case 12:
        {
            cout<<"\nEnter Account number to check if interest earned : ";
            string accountNumber;
            cin>>accountNumber;
            string fileName = "TR" + accountNumber + ".txt";
            Transaction trans;
            trans.readFromFile(fileName);
            cout<<"\nTotal Interest : "<<trans.calculateInterest();
            break;
        }
        default:
        {
            cout<<"\nInvalid option";
        }
    }
    
    
    return 0;
}