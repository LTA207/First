#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class bankAccount
{
private:
    string accname;
    string accnumber;
    double balance = 0;

public:
    bankAccount(){};
    bankAccount(string name, string num)
    {
        this->accname = name;
        this->accnumber = num;
    }
    string getaccnumber();
    string getaccname();
    double getbalance();
    void deposit(double);
    bool withdraw(double);
};

string bankAccount::getaccnumber()
{
    return this->accnumber;
}

string bankAccount::getaccname()
{
    return this->accname;
}

double bankAccount::getbalance()
{
    return this->balance;
}

void bankAccount::deposit(double money)
{
    this->balance += money;
}

bool bankAccount::withdraw(double money)
{
    if (money <= balance)
    {
        this->balance -= money;
        return true;
    }
    else
        return false;
}

class Bank
{
private:
    vector<bankAccount> list;

public:
    int search(string);
    int gettotal();
    bankAccount getitem(string);
    bool addaccount(string, string);
    bool depositMoney(string, double);
    bool withdrawMoney(string, double);
    bool removeAccount(string);
};

int Bank::search(string num)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (num == list[i].getaccnumber())
            return i;
    }
    return -1;
}

int Bank::gettotal()
{
    return list.size();
}

bankAccount Bank::getitem(string num)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (num == list[i].getaccnumber())
        {
            return list[i];
        }
    }
    throw runtime_error("Không tìm thấy tài khoản");
}

bool Bank::addaccount(string name, string num)
{
    bankAccount a(name, num);
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].getaccnumber() == a.getaccnumber())
            return false;
    }
    list.push_back(a);
    return true;
}

bool Bank::depositMoney(string num, double money)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].getaccnumber() == num)
        {
            list[i].deposit(money);
            return true;
        }
    }
    return false;
}

bool Bank::withdrawMoney(string num, double money)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].getaccnumber() == num)
        {
            if (list[i].withdraw(money))
                return true;
        }
    }
    return false;
}

bool Bank::removeAccount(string num)
{
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].getaccnumber() == num)
        {
            list.erase(list.begin() + i);
            return true;
        }
    }
    return false;
}

void printMenu()
{
    cout << "====== MENU ======" << endl;
    cout << "1. Thêm tài khoản" << endl;
    cout << "2. Nạp tiền vào tài khoản" << endl;
    cout << "3. Rút tiền từ tài khoản" << endl;
    cout << "4. Lấy thông tin tài khoản" << endl;
    cout << "5. Xóa tài khoản" << endl;
    cout << "6. Tổng số tài khoản" << endl;
    cout << "0. Thoát" << endl;
    cout << "==================" << endl;
    cout << "Nhập lựa chọn của bạn: ";
}

int main()
{
    Bank bank;

    while (true)
    {
        printMenu();

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Nhập tên tài khoản: ";
            string name;
            cin.ignore();
            getline(cin, name);

            cout << "Nhập số tài khoản: ";
            string accNum;
            cin >> accNum;

            bool success = bank.addaccount(name, accNum);
            if (success)
                cout << "Thêm tài khoản thành công!" << endl;
            else
                cout << "Số tài khoản đã tồn tại!" << endl;

            break;
        }
        case 2:
        {
            cout << "Nhập số tài khoản: ";
            string accNum;
            cin >> accNum;

            cout << "Nhập số tiền nạp: ";
            double amount;
            cin >> amount;

            bool success = bank.depositMoney(accNum, amount);
            if (success)
                cout << "Nạp tiền thành công!" << endl;
            else
                cout << "Số tài khoản không tồn tại!" << endl;

            break;
        }
        case 3:
        {
            cout << "Nhập số tài khoản: ";
            string accNum;
            cin >> accNum;

            cout << "Nhập số tiền rút: ";
            double amount;
            cin >> amount;

            bool success = bank.withdrawMoney(accNum, amount);
            if (success)
                cout << "Rút tiền thành công!" << endl;
            else
                cout << "Số tài khoản không tồn tại hoặc số dư không đủ!" << endl;

            break;
        }
        case 4:
        {
            cout << "Nhập số tài khoản: ";
            string accNum;
            cin >> accNum;

            try
            {
                bankAccount account = bank.getitem(accNum);
                cout << "Thông tin tài khoản:" << endl;
                cout << "Tên tài khoản: " << account.getaccname() << endl;
                cout << "Số dư: " << account.getbalance() << endl;
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }

            break;
        }
        case 5:
        {
            cout << "Nhập số tài khoản: ";
            string accNum;
            cin >> accNum;

            bool success = bank.removeAccount(accNum);
            if (success)
                cout << "Xóa tài khoản thành công!" << endl;
            else
                cout << "Số tài khoản không tồn tại!" << endl;

            break;
        }
        case 6:
        {
            int total = bank.gettotal();
            cout << "Tổng số tài khoản: " << total << endl;

            break;
        }
        case 0:
            return 0;
        default:
            cout << "Lựa chọn không hợp lệ!" << endl;
            break;
        }
    }

    return 0;
}
