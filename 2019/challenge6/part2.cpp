#include <iostream>
#include <string>
#include <vector>
#include <map>

class Planet {
public:
    static std::string chars;
    static Planet arr[50653];

    void add_child(Planet* c);
    int count_orbits(int depth);
    static Planet* get_planet_from_string(std::string planet_code);
    int jumps(Planet* other);

    std::vector<Planet*> m_children;
    Planet* m_parent = nullptr;
};
std::string Planet::chars;
Planet Planet::arr[];

Planet* Planet::get_planet_from_string(std::string planet_code) {
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

int Planet::jumps(Planet* other) {
    // List all the ancestors for this planet up to COM
    // Traverse through parents until we find something we see
    std::map<Planet*, int> this_ancestors;
    int this_jumps = 0;
    for (Planet* head = this->m_parent; head != nullptr; head = head->m_parent) {
        this_jumps++;
        this_ancestors.insert({head, this_jumps});
    }

    Planet* common_ancestor;
    int other_jumps = 0;
    for (Planet* head = other->m_parent; head != nullptr; head = head->m_parent) {
        other_jumps++;

        auto common_ancestor = this_ancestors.find(head);
        if (common_ancestor == this_ancestors.end()) continue;

        this_jumps = common_ancestor->second;
        return this_jumps + other_jumps - 2;
    }
    return -1;
}

int main() {
    Planet::chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (std::string line; std::getline(std::cin, line);) {

        // Get the first object, record the second object as a child
        std::string object1 = line.substr(0,line.find(')'));
        std::string object2 = line.substr(line.find(')') + 1);

        // COM)B ==> B is child of COM
        Planet* p1 = Planet::get_planet_from_string(object1);
        Planet* p2 = Planet::get_planet_from_string(object2);
        p1->m_children.push_back(p2);
        p2->m_parent = p1;
    }

    Planet* SAN = Planet::get_planet_from_string("SAN");
    Planet* YOU = Planet::get_planet_from_string("YOU");
    std::cout << "The answer is " << SAN->jumps(YOU) << std::endl;
    return 0;
}

// Gameplan: Decode the objects into static array
// Read each one and give the proper pointers (only need child pointer)
// take the COM object and recursively count
