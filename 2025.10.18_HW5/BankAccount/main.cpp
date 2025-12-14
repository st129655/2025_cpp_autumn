#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class BankAccount
{
private:
    std::string AccountOwner;
    std::string AccountNumber;
    double balance;
public:
    // Конструктор по умолчанию для тестов
    BankAccount() : AccountOwner(""), AccountNumber(""), balance(0.0) {};
    
    BankAccount(const std::string& AccountOwner, const std::string& AccountNumber, double sum) : 
        AccountOwner(AccountOwner), 
        AccountNumber(AccountNumber), 
        balance(sum) {};
    
    void deposit(double sum)
    {
        if (sum < 0)
        {
            std::cout << "Отрицательный депозит?" << std::endl;
            return;
        }
        this->balance += sum;
    }
    
    void withdraw(double sum)
    {
        if (sum > this->balance)
        {
            std::cout << "Недостаточно денег на счете" << std::endl;
            return;
        }
        else if (this->balance >= 0 && sum <= this->balance)
        {
            this->balance -= sum;
        }
    }
    
    void printInfo()
    {
        std::cout << "Account number: " << AccountNumber << std::endl;
        std::cout << "Account owner: " << AccountOwner << std::endl;
        std::cout << "Account balance: " << balance << std::endl;
        std::cout << std::endl;
    }
    
    double GetBalance() const 
    {
        return balance;
    }

    std::string GetAccountNumber() const 
    {
        return AccountNumber;
    }

    std::string GetAccountOwner() const 
    {
        return AccountOwner;
    }
};

class Bank
{
private:
    std::vector<std::shared_ptr<BankAccount>> accounts;
public:
    Bank() : accounts(std::vector<std::shared_ptr<BankAccount>>{}) {};
    
    void AddAccount(const std::shared_ptr<BankAccount> account)
    {
        accounts.push_back(account);
    }
    
    double GetTotalBalance()
    {
        double sum = 0;
        for (auto account : accounts)
        {
            sum += account->GetBalance();
        }
        return sum;
    }
    
    void PrintAllAccounts()
    {
        for (auto account : accounts)
        {
            account->printInfo();
        }
    }
    

    size_t GetAccountCount() const
    {
        return accounts.size();
    }
};


// 1. Конструктор с параметрами
TEST(BankAccountTest, ParameterizedConstructor)
{
    BankAccount account("John Doe", "1234567890", 1000.0);
    EXPECT_EQ(account.GetAccountOwner(), "John Doe");
    EXPECT_EQ(account.GetAccountNumber(), "1234567890");
    EXPECT_EQ(account.GetBalance(), 1000.0);
}

// 2. Внесение депозита
TEST(BankAccountTest, DepositPositive)
{
    BankAccount account("John Doe", "1234567890", 1000.0);
    account.deposit(500.0);
    EXPECT_EQ(account.GetBalance(), 1500.0);
}

// 3. Внесение отрицательного депозита
TEST(BankAccountTest, DepositNegative)
{
    BankAccount account("John Doe", "1234567890", 1000.0);
    testing::internal::CaptureStdout();
    account.deposit(-100.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(account.GetBalance(), 1000.0);  // Баланс не должен измениться
    EXPECT_NE(output.find("Отрицательный депозит?"), std::string::npos);
}

// 4. Успешное снятие средств
TEST(BankAccountTest, WithdrawSuccess)
{
    BankAccount account("John Doe", "1234567890", 1000.0);
    account.withdraw(300.0);
    EXPECT_EQ(account.GetBalance(), 700.0);
}

// 5. Неудачное снятие средств (недостаточно средств)
TEST(BankAccountTest, WithdrawFailure)
{
    BankAccount account("John Doe", "1234567890", 1000.0);
    testing::internal::CaptureStdout();
    account.withdraw(1500.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(account.GetBalance(), 1000.0);  // Баланс не должен измениться
    EXPECT_NE(output.find("Недостаточно денег на счете"), std::string::npos);
}

// 6. Получение информации о счете
TEST(BankAccountTest, GetAccountInfo)
{
    BankAccount account("John Doe", "1234567890", 1500.0);
    EXPECT_EQ(account.GetAccountOwner(), "John Doe");
    EXPECT_EQ(account.GetAccountNumber(), "1234567890");
    EXPECT_EQ(account.GetBalance(), 1500.0);
}


// 1. Конструктор банка
TEST(BankTest, DefaultConstructor)
{
    Bank bank;
    EXPECT_EQ(bank.GetAccountCount(), 0);
}

// 2. Добавление счета в банк
TEST(BankTest, AddAccount)
{
    Bank bank;
    auto account = std::make_shared<BankAccount>("John Doe", "1234567890", 1000.0);
    bank.AddAccount(account);
    EXPECT_EQ(bank.GetAccountCount(), 1);
}

// 3. Расчет общего баланса
TEST(BankTest, GetTotalBalance)
{
    Bank bank;
    auto account1 = std::make_shared<BankAccount>("John Doe", "1", 1000.0);
    auto account2 = std::make_shared<BankAccount>("Jane Doe", "2", 2000.0);
    auto account3 = std::make_shared<BankAccount>("Bob Smith", "3", 3000.0);
    
    bank.AddAccount(account1);
    bank.AddAccount(account2);
    bank.AddAccount(account3);
    
    EXPECT_EQ(bank.GetTotalBalance(), 6000.0);
}

// 4. Изменение баланса счетов
TEST(BankTest, AccountBalanceChanges)
{
    Bank bank;
    auto account = std::make_shared<BankAccount>("John Doe", "1234567890", 1000.0);
    bank.AddAccount(account);
    
    EXPECT_EQ(bank.GetTotalBalance(), 1000.0);
    
    account->deposit(500.0);
    EXPECT_EQ(bank.GetTotalBalance(), 1500.0);
    
    account->withdraw(300.0);
    EXPECT_EQ(bank.GetTotalBalance(), 1200.0);
}

// 5. Печать информации о счетах
TEST(BankTest, PrintAllAccounts)
{
    Bank bank;
    auto account = std::make_shared<BankAccount>("John Doe", "1234567890", 1000.0);
    bank.AddAccount(account);
    
    testing::internal::CaptureStdout();
    bank.PrintAllAccounts();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Account number: 1234567890"), std::string::npos);
    EXPECT_NE(output.find("Account owner: John Doe"), std::string::npos);
    EXPECT_NE(output.find("Account balance: 1000"), std::string::npos);
}

int main(int argc, char** argv) {
    std::cout << "🚀 Запуск тестов BankAccount и Bank..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    if (result == 0) {
        std::cout << " Все тесты пройдены успешно!" << std::endl;
    } else {
        std::cout << " Есть непройденные тесты!" << std::endl;
    }
    
    // Демонстрация работы (как в оригинальном коде)
    std::cout << "\n=== Демонстрация работы ===" << std::endl;
    auto sigma = std::make_shared<BankAccount>("Leha Milchakov", "1", 1111);
    auto emo_boy = std::make_shared<BankAccount>("Egor Krid", "2", 2222);
    auto absolut = std::make_shared<BankAccount>("Elena Golovach", "3", 3333);

    Bank SVOIBank;
    SVOIBank.AddAccount(sigma);
    SVOIBank.AddAccount(emo_boy);
    SVOIBank.AddAccount(absolut);

    std::cout << "\nВсе счета в банке:" << std::endl;
    SVOIBank.PrintAllAccounts();

    sigma->deposit(1488);
    emo_boy->withdraw(228);
    absolut->deposit(1337);

    std::cout << "\nСчета после операций:" << std::endl;
    SVOIBank.PrintAllAccounts(); 
    
    double Total = SVOIBank.GetTotalBalance();
    std::cout << "Общий баланс банка: " << Total << std::endl;
    
    return result;
}