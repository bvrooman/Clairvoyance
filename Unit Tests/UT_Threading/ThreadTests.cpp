#include <gtest\gtest.h>

#include "Threading\ClaireMutex.h"
#include "Threading\ClaireRecursiveMutex.h"
#include "Threading\ClaireThread.h"
#include "Threading\ClaireThreadGroup.h"
#include "Threading\ClaireScopedLock.h"
#include "Threading\ClaireThreadSpecificPtr.h"

#include <chrono>

using namespace Claire;
using namespace Claire::core;

class BankAccount
{
private:
	int	balance = 0;

public:
	void deposit(int amount)
	{
		balance += amount;
		std::cout << "Balance after deposit: " << std::dec << getBalance() << "\n";
	}

	void withdraw(int amount)
	{
		balance -= amount;
		std::cout << "Balance after withdraw: " << std::dec << getBalance() << "\n";
	}

	int getBalance(void)
	{

		return balance;
	}
};

Mutex accountMutex;

void depositIntoAccount(BankAccount* account)
{
	for (int i = 10; i > 0; i--)
	{
		ScopedLock<Mutex> l(accountMutex);
		int balance = account->getBalance();
		account->deposit(100);
		ASSERT_EQ(balance + 100, account->getBalance());
		this_thread::yield();
	}
}

void withdrawFromAccount(BankAccount* account)
{
	for (int i = 10; i > 0; i--)
	{
		ScopedLock<Mutex> l(accountMutex);
		int balance = account->getBalance();
		account->withdraw(100);
		ASSERT_EQ(balance - 100, account->getBalance());
		this_thread::yield();
	}
}

TEST(Threading, ThreadSynchronization)
{
	BankAccount* account = new BankAccount();
	Thread thread1(depositIntoAccount, account);
	Thread thread2(withdrawFromAccount, account);
	thread1.join();
	thread2.join();
}