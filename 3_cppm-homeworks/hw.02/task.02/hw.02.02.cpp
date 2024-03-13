#include <iostream>

struct BankAccount
{
    int account = 0;
    std::string name = "Default";
    float balance = 0;
};

void fillAccount(BankAccount& ba)
{
    std::cout << "Введите номер счета: ";
    std::cin >> ba.account;
    std::cout << "Введите имя владельца:: ";
    std::cin >> ba.name;
    std::cout << "Введите баланс: ";
    std::cin >> ba.balance;
}

void changeBalance(BankAccount& ba)
{
    std::cout << "Введите новый баланс: ";
    std::cin >> ba.balance;
}

void showAccount(const BankAccount& ba)
{
    std::cout << "Ваш счет: " << ba.name << ", " << ba.account << ", " << ba.balance << std::endl;
}

int main()
{
    BankAccount user;

    fillAccount(user);
    changeBalance(user);
    showAccount(user);

    return 0;
}