#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account {
public:
    string name;
    int accountNumber;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount Number: " << accountNumber
             << "\nName: " << name
             << "\nBalance: $" << balance << "\n";
    }
};

void writeAccount() {
    Account acc;
    acc.createAccount();
    ofstream outFile("accounts.txt", ios::app);
    outFile << acc.accountNumber << "," << acc.name << "," << acc.balance << "\n";
    outFile.close();
    cout << "✅ Account created successfully!\n";
}

void displayAccounts() {
    ifstream inFile("accounts.txt");
    string line;
    cout << "\n--- All Accounts ---\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}

void depositWithdraw(bool isDeposit) {
    int accNo;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNo;

    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        int num;
        string name;
        double bal;
        size_t pos1 = line.find(",");
        size_t pos2 = line.rfind(",");
        num = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        bal = stod(line.substr(pos2 + 1));

        if (num == accNo) {
            found = true;
            cout << "Enter Amount: ";
            cin >> amount;
            if (!isDeposit && amount > bal) {
                cout << "❌ Insufficient Balance!\n";
            } else {
                if (isDeposit) bal += amount;
                else bal -= amount;
                cout << "✅ Transaction Successful! New Balance: $" << bal << "\n";
            }
        }

        tempFile << num << "," << name << "," << bal << "\n";
    }

    inFile.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "❌ Account not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Bank Account Management ---\n";
        cout << "1. Create Account\n2. Display All Accounts\n3. Deposit Money\n4. Withdraw Money\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: writeAccount(); break;
        case 2: displayAccounts(); break;
        case 3: depositWithdraw(true); break;
        case 4: depositWithdraw(false); break;
        case 5: cout << "Goodbye! 👋\n"; break;
        default: cout << "❌ Invalid Choice!\n"; break;
        }

    } while (choice != 5);
