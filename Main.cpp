#include "Nodes.h"
#include "MinHeap.h"
#include "MaxHeap.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	// Generate initial heaps for jobs and machines.
	MinHeap<MachineNode> machineHeap(3);
	machineHeap.add(MachineNode(1));
	machineHeap.add(MachineNode(2));
	machineHeap.add(MachineNode(3));

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

	return 0;
}