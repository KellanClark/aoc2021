
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <algorithm>

struct Location {
	std::size_t id;
	std::string name;
	bool revisitable;
	std::vector<int> connections;
};
std::vector<Location> locations;
int startNode, endNode;

class Path {
public:
	Path() {
		nodes.resize(0);
		hasVistited.resize(locations.size());
		visitedTwice = false;
	}

	std::vector<int> nodes;
	std::vector<bool> hasVistited;
	bool visitedTwice;
};
int completedPaths;

void branch(Path path, int node) {
	if (locations[node].revisitable || !path.hasVistited[node]) {
		path.nodes.push_back(node);
		path.hasVistited[node] = true;
		
		if (node == endNode) {
			++completedPaths;
			return;
		}

		for (int i : locations[node].connections) {
			branch(path, i);
		}
	}
}

void branch2(Path path, int node) {
	if (locations[node].revisitable || !path.hasVistited[node] || (!path.visitedTwice && (node != startNode))) {
		if (!locations[node].revisitable && path.hasVistited[node])
			path.visitedTwice = true;
		path.nodes.push_back(node);
		path.hasVistited[node] = true;
		
		if (node == endNode) {
			++completedPaths;
			return;
		}

		for (int i : locations[node].connections) {
			branch2(path, i);
		}
	}
}

int main() {
	std::fstream inFile("../day12/input", std::ios_base::in);

	std::string line;
	std::string start, end;
	while (inFile >> line) {
		std::stringstream ss(line);
		std::getline(ss, start, '-');
		std::getline(ss, end, '\n');

		auto startHash = start[0] + (start[1] << 8);
		auto endHash = end[0] + (end[1] << 8);

		auto startIndex = std::find_if(locations.begin(), locations.end(), [&](auto i) {
			return i.id == startHash;
		}) - locations.begin();
		if (startIndex == (locations.end() - locations.begin())) { // Create new entry
			Location tmpLocation;
			tmpLocation.id = startHash;
			tmpLocation.name = start;
			tmpLocation.revisitable = std::isupper(start[0]);
			
			if (startHash == ('s' + ('t' << 8)))
				startNode = startIndex;
			if (startHash == ('e' + ('n' << 8)))
				endNode = startIndex;

			locations.push_back(tmpLocation);
		}
		
		auto endIndex = std::find_if(locations.begin(), locations.end(), [&](auto i) {
			return i.id == endHash;
		}) - locations.begin();
		if (endIndex == (locations.end() - locations.begin())) { // Create new entry
			Location tmpLocation;
			tmpLocation.id = endHash;
			tmpLocation.name = end;
			tmpLocation.revisitable = std::isupper(end[0]);
			
			if (endHash == ('s' + ('t' << 8)))
				startNode = endIndex;
			if (endHash == ('e' + ('n' << 8)))
				endNode = endIndex;
			
			locations.push_back(tmpLocation);
		}

		locations[startIndex].connections.push_back(endIndex);
		locations[endIndex].connections.push_back(startIndex);
	}

	// Part 1
	Path startPath;
	branch(startPath, startNode);
	printf("Part 1: %d\n", completedPaths);
	
	// Part 2
	completedPaths = 0;
	branch2(startPath, startNode);
	printf("Part 2: %d\n", completedPaths);

	return 0;
}