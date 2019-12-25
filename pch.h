
#ifndef PCH_H
#define PCH_H
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

const double alpha = 0.5;
const double beta = 0.5;
const double pheromoneEvaporation = 0.09;

class Edge {
public:
	double length;
	double pheromoneLevels;
	int point1ID;
	int point2ID;
	Edge() {}

	explicit Edge(const double& len) {
		length = len;
		pheromoneLevels = 1/len;
	}
};

class Vertex {
public:
    int VertexID;
	int pathAmount;

	Vertex() {}
	explicit Vertex(const int& id) {
		VertexID = id;
	}
};

class Environment {
public:
	static std::vector<Vertex> positions;
	static std::vector<Edge> edges;
};

class Ant {
public:
	Vertex position;
	Ant(const Vertex& pos) {
		position = pos;
	}
};

static void addConnection(Vertex& first, Vertex& second, Edge& addIt) {
	addIt.point1ID = first.VertexID;
	addIt.point2ID = second.VertexID;
	++first.pathAmount;
	++second.pathAmount;
}

static double fRand(const double& fMin, const double& fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

static bool confirmed(const double& P) {
	return P > fRand(0, 1);
}

static Vertex findById(const std::vector<Vertex>& vec, int& id) {
	for (auto& i : vec) {
		if (i.VertexID == id)
			return i;
	}
}

template <typename I>
I randomElement(I begin, I end)
{
	const unsigned long n = std::distance(begin, end);
	const unsigned long divisor = (RAND_MAX + 1) / n;

	unsigned long k;
	do { k = std::rand() / divisor; } while (k >= n);

	std::advance(begin, k);
	return begin;
}

static void go(Ant& voyager, Vertex& vert) {
	
	double sum = 0;
	for (size_t i = 0; i < Environment::edges.size(); ++i)
		if (Environment::edges[i].point1ID == vert.VertexID)
			sum += (pow(Environment::edges[i].pheromoneLevels, alpha) * pow(Environment::edges[i].length, -beta));

	while(true)
		for (size_t i = 0; i < Environment::edges.size(); ++i) {
			std::vector<Edge> zeroPaths;
			for (size_t j = 0; j < Environment::edges.size(); ++j) {
				if (Environment::edges[j].pheromoneLevels == 0 && Environment::edges[j].point1ID == vert.VertexID)
					zeroPaths.push_back(Environment::edges[j]);
			}
			for (size_t j = 0; j < Environment::edges.size(); ++j) {
			if (Environment::edges[j].point1ID == vert.VertexID)
				if (Environment::edges[j].pheromoneLevels > 0 &&
					confirmed((pow(Environment::edges[j].pheromoneLevels, alpha) * pow(Environment::edges[j].length, -beta)) / sum)) {
					
					Environment::edges[j].pheromoneLevels += 1 / Environment::edges[j].length;
					voyager.position = findById(Environment::positions, Environment::edges[j].point2ID);
					return;
				}
			}

			if (zeroPaths.size() != 0) {
				Edge toTake = *(randomElement(zeroPaths.begin(), zeroPaths.end()));

				for (auto& i : Environment::edges)
					if (i.point1ID == toTake.point1ID && i.point2ID == toTake.point2ID) {
						i.pheromoneLevels += 1 / i.length;
						break;
					}

				voyager.position = findById(Environment::positions, toTake.point2ID);
				return;
			}
			else
				continue;
		}
}

#endif //PCH_H