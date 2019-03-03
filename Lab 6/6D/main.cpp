#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <utility>
#include <list>

class QA {
private:
    std::list<uint16_t > value;
    std::map<char , uint16_t > quack_reg;
    std::vector<std::string> commands;
    std::map<std::string, int> tag;
public:

    uint16_t addition();

    uint16_t sub();

    uint16_t multiplication();

    void division();

    void module();

    void read(std::vector<std::string>&, std::ofstream&);

    void queueToRegistr(const char&);

    void registrToQueue(const char&);

    void read_commands();
};

uint16_t QA::addition() {
    uint16_t temp_value = 0;
    temp_value = value.back();
    value.pop_back();
    temp_value += value.back();
    value.pop_back();
    value.emplace_front(temp_value);
    return temp_value;
}

uint16_t QA::sub(){
    uint16_t temp_value;
    temp_value = value.back();
    value.pop_back();
    temp_value -= value.back();
    value.pop_back();
    value.emplace_front(temp_value);
    return temp_value;
}

uint16_t QA::multiplication() {
    uint16_t temp_value;
    temp_value = value.back();
    value.pop_back();
    temp_value *= value.back();
    value.pop_back();
    value.emplace_front(temp_value);
    return temp_value;
}

void QA::division() {
    uint16_t temp_value_1;
    uint16_t temp_value_2;
    temp_value_1 = value.back();
    value.pop_back();
    temp_value_2 = value.back();
    value.pop_back();
    if(temp_value_2) {
        value.emplace_front(temp_value_1/temp_value_2);
    } else {
        value.emplace_front(0);
    }
}

void QA::module() {
    uint16_t temp_value_1;
    uint16_t temp_value_2;
    temp_value_1 = value.back();
    value.pop_back();
    temp_value_2 = value.back();
    value.pop_back();
    if (temp_value_2) {
        value.emplace_front(temp_value_1 % temp_value_2);
    } else {
        value.emplace_front(0);
    }
}

void QA::read(std::vector<std::string>& line, std::ofstream &outFile) {
    int iter = 0;
    while (line[iter][0] != 'Q') {
        if (line[iter][0] == '+') {
            addition();
            ++iter;
        } else if (line[iter][0] == '-') {
            sub();
            ++iter;
        } else if (line[iter][0] == '*') {
            multiplication();
            ++iter;
        } else if (line[iter][0] == '/') {
            division();
            ++iter;
        } else if (line[iter][0] == '%') {
            module();
            ++iter;
        } else if (line[iter][0] == '>') {
            queueToRegistr(line[iter][1]);
            ++iter;
        } else if (line[iter][0] == '<') {
            registrToQueue(line[iter][1]);
            ++iter;
        } else if (line[iter][0] == 'P') {
            if (line[iter].size() == 1) {
                outFile << value.back() << "\n";
                value.pop_back();
            } else {
                outFile << quack_reg[line[iter][1]] << "\n";
            }
            ++iter;
        } else if (line[iter][0] == 'C') {
            if (line[iter].size() == 1) {
                outFile << (char) (value.back());
                value.pop_back();
            } else {
                outFile << (char) (quack_reg[line[iter][1]]);
            }
            ++iter;
        } else if (line[iter][0] == ':') {
            ++iter;
        } else if (line[iter][0] == 'J') {
            iter = tag[line[iter].substr(1, line[iter].size() - 1)];
            ++iter;
        } else if (line[iter][0] == 'Z') {
            if (quack_reg[line[iter][1]] == 0) {
                iter = tag[line[iter].substr(2, line[iter].size() - 2)];
            }
            ++iter;
        } else if (line[iter][0] == 'E') {
            if ( quack_reg[line[iter][1]] == quack_reg[line[iter][2]]) {
                iter = tag[line[iter].substr(3, line[iter].size() - 3)];
            }
            ++iter;
        } else if ( line[iter][0] == 'G') {
            if (quack_reg[line[iter][1]] > quack_reg[line[iter][2]]){
                iter = tag[line[iter].substr(3, line[iter].size() - 3)];
            }
            ++iter;
        } else {
            value.emplace_front((uint16_t)std::stoi(line[iter]));
            ++iter;
        }
        if (iter == line.size() )
            break;
    }
    outFile.close();
}


void QA::queueToRegistr(const char& get_registr) {
    quack_reg[get_registr] = value.back();
    value.pop_back();
}

void QA::registrToQueue(const char & get_registr) {
    value.emplace_front(quack_reg[get_registr]);

}

void QA::read_commands() {
    std::ifstream inFile("quack.in");
    std::string line;
    int counter = 0;
    while (inFile >> line) {
        if (line[0] == ':'){
            std::string temp_line = line.substr(1, line.size() - 1);
            tag.insert(std::make_pair(temp_line, counter));
        }
        ++counter;
        commands.push_back(line);
    }
    std::ofstream outFile("quack.out");
    if(!commands.empty())
        read(commands, outFile) ;
}


int main() {
    QA program;
    program.read_commands();
    return 0;
}