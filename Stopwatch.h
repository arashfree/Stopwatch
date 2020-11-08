#pragma once
#include <chrono>
#include <iostream>
#include <vector>
class Stopwatch {
public:
	Stopwatch(std::string name, bool meanMode = 0) {
		_meanMode = meanMode;
		_name = name;
		_epochNum = -1;
	}
	void start() {
		_startTime = std::chrono::system_clock::now();
		_previousTime = _startTime;
		_lapNum = 0;
		_epochNum++;
	}
	void reset() {
		_startTime = std::chrono::system_clock::now();
		_previousTime = _startTime;
		_laps.clear();
		_lapNum = 0;
		_epochNum = 0;
	}
	void stop() {

	}

	void lap(std::string lap_name) {
		_nowTime = std::chrono::system_clock::now();
		float duration = std::chrono::duration_cast<std::chrono::microseconds>(_nowTime - _previousTime).count() / 1000.0;
		if (_epochNum == 0) {
			std::pair<std::string, float> lap(lap_name, duration);
			_laps.push_back(lap);
		}
		else if (!_meanMode){
			_laps[_lapNum].second = duration;
		}
		else {
			_laps[_lapNum].second = (_laps[_lapNum].second * _epochNum + duration) / ((float)_epochNum + 1.0);
		}
		_lapNum++;
		_previousTime = _nowTime;
	}
	void print() {
		std::cout << _name << ":\n";
		for (int i = 0;i < _laps.size();i++) {
			std::cout <<"\t"<< _laps[i].first<<":\t"<< _laps[i].second<< " ms\n";
		}
	}

private:
	bool _meanMode = 0;
	std::string _name;
	std::chrono::time_point<std::chrono::system_clock> _startTime;
	std::chrono::time_point<std::chrono::system_clock> _previousTime;
	std::chrono::time_point<std::chrono::system_clock> _nowTime;
	std::chrono::time_point<std::chrono::system_clock> _stopTime;

	std::vector<std::pair<std::string,float> > _laps;
	int _lapNum;
	int _epochNum;
};