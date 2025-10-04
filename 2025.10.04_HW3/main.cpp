#include<iostream>
#include<vector>
#include<string>

class BankAccount
{
private:
	std::string AccountOwner;
	std::string AccountNumber;
	double balance;
public:
	BankAccount(const std::string& AccountOwner, const std::string& AccountNumber,double sum) : 
		AccountOwner(AccountOwner), 
		AccountNumber(AccountNumber), 
		balance(sum) {};
	void deposit(double sum)
	{
		if (sum < 0)
		{
			std::cout << "Отрицательный депозит?"<<std::endl;
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
	std::vector <std::shared_ptr <BankAccount>> accounts;
public:
	Bank() :accounts(std::vector <std::shared_ptr <BankAccount >> {}) {};
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
};


int main(int argc, char** argv)
{
	auto sigma = std::make_shared <BankAccount>( "Leha Milchakov","1", 1111);
	auto emo_boy = std::make_shared <BankAccount>( "Egor Krid","2", 2222);
	auto absolut = std::make_shared <BankAccount>( "Elena Golovach","3", 3333);

	Bank SVOIBank;
	SVOIBank.AddAccount(sigma);
	SVOIBank.AddAccount(emo_boy);
	SVOIBank.AddAccount(absolut);

	SVOIBank.PrintAllAccounts();

	sigma->deposit(1488);
	emo_boy->withdraw(228);
	absolut->deposit(1337);

	SVOIBank.PrintAllAccounts(); 
	double Total = SVOIBank.GetTotalBalance();
	std::cout << Total << std::endl;
	return 0;
}
