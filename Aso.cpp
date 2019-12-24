
#include "pch.h"


std::vector<Vertex> Environment::positions;
std::vector<Edge> Environment::edges;

int main()
{
	srand(time(0));
	std::cout << "Alpha: " << alpha << std::endl;
	std::cout << "Beta: " << beta << std::endl;
	std::cout << "Pheromone evaporation speed: " << pheromoneEvaporation << std::endl;

	Vertex vone(1);
	Vertex vtwo(2);
	Vertex vthree(3);
	Vertex vfour(4);
	Vertex vfive(5);

	Edge oneTwo(4);
	Edge oneThree(2);
	Edge twoThree(2);
	Edge threeFour(5);
	Edge threeFive(2);
	Edge fourFive(2);

	addConnection(vone, vtwo, oneTwo);
	addConnection(vone, vthree, oneThree);
	addConnection(vtwo, vthree, twoThree);
	addConnection(vthree, vfour, threeFour);
	addConnection(vthree, vfive, threeFive);
	addConnection(vfour, vfive, fourFive);

	Environment::positions.push_back(vone);
	Environment::positions.push_back(vtwo);
	Environment::positions.push_back(vthree);
	Environment::positions.push_back(vfour);
	Environment::positions.push_back(vfive);

	Environment::edges.push_back(oneTwo);
	Environment::edges.push_back(oneThree);
	Environment::edges.push_back(twoThree);
	Environment::edges.push_back(threeFour);
	Environment::edges.push_back(threeFive);
	Environment::edges.push_back(fourFive);

	Ant voyager(vone);
	for (int n = 0; n < 1000; ++n) {
		std::cout << voyager.position.VertexID << "->";
		while (voyager.position.VertexID != vfive.VertexID) {
			go(voyager, voyager.position);
			std::cout << voyager.position.VertexID << "->";
		}
		for (auto &i : Environment::edges)
			i.pheromoneLevels = (1 - pheromoneEvaporation)* i.pheromoneLevels;
		voyager.position = vone;
		std::cout << std::endl;
	}
}