#include <iostream>
#include <string>
#include <vector>

class Planet {
public:
    static std::string chars;
    static Planet arr[50653];

    void add_child(Planet* c);
    int count_orbits(int depth);
    static Planet* decode(std::string planet_code);
    std::vector<Planet*> m_children;
};
std::string Planet::chars;
Planet Planet::arr[];

Planet* Planet::decode(std::string planet_code) {
    int index = 0;
    for (int c = 0; c < planet_code.length(); c++) {
        index *= Planet::chars.length();
        index += Planet::chars.find(planet_code.at(c));
    }
    Planet* myPlanet = &Planet::arr[index];
    return myPlanet;
}

int Planet::count_orbits(int depth) {
    int answer = depth;
    for(auto child : m_children) {
        answer += child->count_orbits(depth+1);
    }
    return answer;
}

int main() {
    Planet::chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (std::string line; std::getline(std::cin, line);) {

        // Get the first object, record the second object as a child
        std::string object1 = line.substr(0,line.find(')'));
        std::string object2 = line.substr(line.find(')') + 1);

        // COM)B ==> B is child of COM
        Planet* p1 = Planet::decode(object1);
        Planet* p2 = Planet::decode(object2);
        p1->m_children.push_back(p2);
    }

    Planet* COM = Planet::decode("COM");
    std::cout << "The answer is " << COM->count_orbits(0) << std::endl;
    return 0;
}

// Gameplan: Decode the objects into static array
// Read each one and give the proper pointers (only need child pointer)
// take the COM object and recursively count
