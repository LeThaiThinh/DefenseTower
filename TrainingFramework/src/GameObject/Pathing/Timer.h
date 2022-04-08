#pragma once
#include <chrono>
#include "utilities.h" 
#include "map"
#include "Singleton.h"
struct Operation
{
public:
	Operation(std::string name) {
		this->m_name = name;
		m_countPerCircle = 0;
		m_durationPerCircle = 0;
		m_countPerGame = 0;
		m_durationPerGame = 0;
	}
	~Operation(){}
	void StartOp() {
		begin = std::chrono::steady_clock::now();
	}
	void EndOp() {
		end = std::chrono::steady_clock::now();
		float time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		if (time < 100000000) {
			m_durationPerCircle += time;
			m_durationPerGame += time;
			m_countPerCircle++;
			m_countPerGame++;
		}
	}
	void EndOpPerCircle() {
		if (m_durationPerCircle > 0) {
			std::cout << m_countPerCircle << " query " << m_name << " in " << m_durationPerCircle << std::endl;
		}
		m_durationPerCircle = 0;
		m_countPerCircle = 0;
	}
	void EndOpPerGame() {
		std::cout << m_countPerGame << " query " << m_name << " in " << m_durationPerGame << "-> average: " << m_durationPerGame/ m_countPerGame << std::endl;
		m_durationPerGame = 0;
		m_countPerGame = 0;
	}

private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	int m_countPerCircle;
	float m_durationPerCircle;
	int m_countPerGame;
	float m_durationPerGame;
	std::string m_name;
};

class Timer: public CSingleton<Timer>
{
public:
	Timer(){}
	~Timer(){}
	void AddTimeOperation(std::string name) {
		auto it = operationList.find(name);
		if (it != operationList.end())
		{
			operationList.find(name)->second->StartOp();
		}
		else {
			std::shared_ptr<Operation>  op;
			op = std::make_shared<Operation>(name);
			operationList.insert(std::pair<std::string, std::shared_ptr<Operation>>(name, op));
		}
	}
	void EndOperation(std::string name) {
		auto it = operationList.find(name);
		if (it != operationList.end())
		{
			operationList.find(name)->second->EndOp();
		}
		else {
			std::shared_ptr<Operation>  op;
			op = std::make_shared<Operation>(name);
			operationList.insert(std::pair<std::string, std::shared_ptr<Operation>>(name, op));
		}
	}
	void EndAddTimeOperationPerCircle(std::string name) {
		auto it = operationList.find(name);
		if (it != operationList.end())
		{
			operationList.find(name)->second->EndOpPerCircle();
		}
		else {
			std::shared_ptr<Operation>  op;
			op = std::make_shared<Operation>(name);
			operationList.insert(std::pair<std::string, std::shared_ptr<Operation>>(name, op));
		}
	}
	void EndAddTimeOperationPerGame(std::string name) {
		auto it = operationList.find(name);
		if (it != operationList.end())
		{
			operationList.find(name)->second->EndOpPerGame();
		}
		else {
			std::shared_ptr<Operation>  op;
			op = std::make_shared<Operation>(name);
			operationList.insert(std::pair<std::string, std::shared_ptr<Operation>>(name, op));
		}
	}
	
	std::map<std::string, std::shared_ptr<Operation>> operationList;
};
