#include "task.h"
#include <cmath>

Customer::Customer()
{
	t_start = std::chrono::system_clock::now();
}

int Customer::TimeQueue()
{
	std::chrono::duration<double> duration = std::chrono::system_clock::now() - t_start;
	return duration.count();
}

double fact(int k)
{
	if (k <= 0) return 1;

	else 
		return k * fact(k - 1); 
}

Shop::Shop(int numbthreads, int numbbuyer, int Time, int avgbuy, int length)
{
	this->numbthreads = numbthreads;
	this->numbbuyer = numbbuyer;
	this->Time = Time;
	this->avgbuy = avgbuy;
	this->length = length;
	for (int i = 0; i < numbthreads; ++i)
	{
		threads.push_back(thread(&Shop::Work, this));
		threads.at(i).detach();
	}
}

void Shop::Start()
{
	srand(time(0));
	while (numball < numbbuyer)
	{
		int r = rand() % 100;
		avgbuyer += r;
		this_thread::sleep_for(std::chrono::milliseconds(r));	
		m.lock();
		if (lengthqueue > length)
		{
			++numbfalse;
		}
		else
		{
			cus.push_back(Customer());
			++lengthqueue;
		}
		++numball;
		m.unlock();
	}
	while (numbfalse + numbtrue < numbbuyer)
	{
		this_thread::sleep_for(std::chrono::milliseconds(10));	
	}


	avgwait /= static_cast<double>(numbtrue);
	avgtimebuy /= static_cast<double>(numbtrue);
	avgwaitbuyer /= static_cast<double>(numbthreads);
	avgwork /= static_cast<double>(numbthreads);
	cout << "Обслуженные покупатели: " << numbtrue << endl;
	cout << "Необслуженные покупатели: " << numbfalse << endl;
	cout << "Среднее время нахождения в очереди: " << avgwait << endl;
	cout << "Среднее время на кассе: " << avgtimebuy << endl;
	cout << "Среднее время работы кассы: " << avgwork << endl;
	cout << "Среднее время простоя кассы: " << avgwaitbuyer << endl;


	double l = 100. / avgbuyer;	
	double nu = 100. / avgtimebuy;
	double ro = l / nu;
	double P0 = 1.;
	for (int i = 1; i <= numbthreads; ++i)
	{
		P0 += pow(ro,i) / fact(i);
	}
	for (int i = numbthreads + 1; i < numbthreads + length; ++i)
	{
		P0 += pow(ro, i) / (fact(numbthreads) * pow(numbthreads, i - numbthreads));
	}
	P0 = 1. / P0;
	double Prej = pow(ro, numbthreads + length) * P0 / (pow(numbthreads, length) * fact(numbthreads));
	cout << "Вероятность отказа теоретическая: " << Prej << endl;
	cout << "Вероятность отказа фактическая: " << static_cast<double>(numbfalse) / static_cast<double>(numbbuyer) << endl;
	double Q = 1. - Prej;
	cout << "Относительная пропускная способность теоретическая: " << Q << endl;
	cout << "Относительная пропускная способность фактическая: " << static_cast<double>(numbtrue) / static_cast<double>(numbbuyer) << endl;
	double A = l * Q;
	cout << "Абсолютная пропускная способность теоретическая: " << A << endl;
	cout << "Абсолютная пропускная способность фактическая: " << static_cast<double>(numbtrue) * avgbuyer / static_cast<double>(numbbuyer) << endl;
}

void Shop::Work()
{
	srand(time(0));
	while (numbfalse + numbtrue < numbbuyer)
	{
		m.lock();
		if (lengthqueue > 0)
		{
			--lengthqueue;
			avgwait += cus.front().TimeQueue();
			m.unlock();
		}
		else
		{
			avgwaitbuyer += 5;
			m.unlock();
			this_thread::sleep_for(std::chrono::milliseconds(5));	
			continue;
		}
		int numbbuy = rand() % avgbuy + avgbuy;
		for (int i = 0; i < numbbuy; ++i)
		{
			this_thread::sleep_for(std::chrono::milliseconds(Time));
		}
		m.lock();
		avgwork += numbbuy * Time;
		avgtimebuy += numbbuy * Time;
		cout << numbtrue + numbfalse + 1 << endl;
		++numbtrue;
		m.unlock();
	}
}




