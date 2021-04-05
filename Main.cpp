#include "Nodes.h"
#include "MinHeap.h"
#include "MaxHeap.h"
#include <iostream>
#include <random>

using std::cout;
using std::endl;

int main() {
	// Generate initial heaps for jobs and machines.
	MinHeap<MachineNode> machineHeap(3);
	machineHeap.add(MachineNode(1));
	machineHeap.add(MachineNode(3));
	machineHeap.add(MachineNode(2));

	MaxHeap<JobNode> jobHeap(7);
	jobHeap.add(JobNode(1, 2));
	jobHeap.add(JobNode(2, 14));
	jobHeap.add(JobNode(3, 4));
	jobHeap.add(JobNode(4, 16));
	jobHeap.add(JobNode(5, 6));
	jobHeap.add(JobNode(6, 5));
	jobHeap.add(JobNode(7, 3));

	// Assign jobs until there are none left
	while (!jobHeap.isEmpty()) {
		JobNode currJob = jobHeap.extractMax();
		MachineNode currMac = machineHeap.extractMin();
		cout << "Schedule job " << currJob.ID << " on machine "
			<< currMac.ID << " from " << currMac.availTime
			<< " to " << currMac.availTime + currJob.time << endl;
		currMac.availTime += currJob.time;
		machineHeap.add(currMac);
	}
	cout << endl;

	// New set for task 3

	srand(time(0));

	MinHeap<MachineNode> machines(5);
	machines.add(MachineNode(1));
	machines.add(MachineNode(2));
	machines.add(MachineNode(3));
	machines.add(MachineNode(4));
	machines.add(MachineNode(5));

	MaxHeap<JobNode> jobs(10);

	for (int i = 1; i <= 10; i++) {
		int num = rand()%20 + 1;
		cout << "Job " << i << " time: " << num << endl;
		jobs.add(JobNode(i, num));
	}

	while (!jobs.isEmpty()) {
		JobNode currJob = jobs.extractMax();
		MachineNode currMac = machines.extractMin();
		cout << "Schedule job " << currJob.ID << " on machine "
			<< currMac.ID << " from " << currMac.availTime
			<< " to " << currMac.availTime + currJob.time << endl;
		currMac.availTime += currJob.time;
		machines.add(currMac);
	}

	return 0;
}