#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <ctime>
#include <chrono>
#include <mutex>

using namespace std;



class Shop
{
public:
	int numbthreads;
	int numbbuyer;
	int Time;
	int avgbuy;
	int length;
	int numbtrue = 0;
	int numbfalse = 0;
	int numball = 0;
	int avglength = 0;
	double avgwait = 0;
	double avgbuy = 0;	
	double avgwork = 0;	
	double avgwaitbuyer = 0;	
	double avgbuyer = 0;	
	vector<thread> threads;
	int lengthqueue = 0;	
	vector<Customer> cus;
	mutex m;


	Shop(int numbthreads, int numbbuyer, int Time, int avgbuy, int length);
	void Start();
	void Work();
};

class Customer
{
public:
	std::chrono::system_clock::time_point t_start;
	int Time = 0;
	int timeQueue = 0;

	Customer();
	int TimeQueue();
};


