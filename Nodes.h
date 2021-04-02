#pragma once

class JobNode {
	friend int main();
private:
	int ID, time;
public:
	JobNode() = default;
	JobNode(int id, int t) {
		ID = id;
		this->time = t;
	}
	operator int() {
		return time;
	}
};

class MachineNode {
	friend int main();
private:
	int ID, availTime;
public:
	MachineNode() = default;
	MachineNode(int id) {
		ID = id;
		availTime = 0;
	}
	operator int() {
		return availTime;
	}
};