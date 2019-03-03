#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <list>
#include <utility>

class QuackInterpreter {
public:
    explicit QuackInterpreter();

    void loadCommand(const std::string &command);

    bool doOneCycle(std::string &output, bool &output_flag);

private:
    std::map<char, uint16_t> registers;
    std::list<uint16_t> queue;

    std::vector<std::string> command_list;
    std::map<std::string, int> label_indexes;

    int run_index = -1;

    uint16_t get();

    void put(uint16_t value);

    void getIntoReg(char reg);

    void putFromReg(char reg);

    void calcSum();

    void calcSub();

    void calcProd();

    void calcQuotient();

    void calcMod();

    void printGet(std::string &value);

    void printReg(char reg, std::string &value);

    void printCharGet(std::string &value);

    void printCharReg(char reg, std::string &value);

    void gotoLabel(const std::string &label);

    void gotoIfZeroReg(char reg, const std::string &label);

    void gotoIfRegsValEqual(char reg1, char reg2, const std::string &label);

    void gotoIfReg1valGreaterReg2val(char reg1, char reg2, const std::string &label);

};

QuackInterpreter::QuackInterpreter() {
    for (int i = 0; i < 26; ++i)
        registers.insert(std::make_pair('a' + i, 0));
}

void QuackInterpreter::loadCommand(const std::string &command) {
    if (command.empty())
        return;

    command_list.push_back(command);
    if (command[0] == ':') {
        std::string jump_label_name = command.substr(1, command.length() - 1);
        int jump_label_index = command_list.size() - 1;
        label_indexes.insert(std::make_pair(jump_label_name, jump_label_index));
    }
}

bool QuackInterpreter::doOneCycle(std::string &output, bool &output_flag) {
    output_flag = false;
    output.clear();

    ++run_index;
    if (run_index == command_list.size())
        return false;

    char command_begin = command_list[run_index][0];

    char reg1;
    char reg2;
    std::string label;
    uint16_t value = 0;

    switch (command_begin) {
        case '+':
            calcSum();
            break;

        case '-':
            calcSub();
            break;

        case '*':
            calcProd();
            break;

        case '/':
            calcQuotient();
            break;

        case '%':
            calcMod();
            break;

        case '>':
            getIntoReg(command_list[run_index][1]);
            break;

        case '<':
            putFromReg(command_list[run_index][1]);
            break;

        case 'P':
            output_flag = true;
            if (command_list[run_index].length() == 1)
                printGet(output);
            else
                printReg(command_list[run_index][1], output);
            break;

        case 'C':
            output_flag = true;
            if (command_list[run_index].length() == 1)
                printCharGet(output);
            else
                printCharReg(command_list[run_index][1], output);
            break;

        case 'J':
            label = command_list[run_index].substr(1, command_list[run_index].length() - 1);
            gotoLabel(label);
            break;

        case 'Z':
            reg1 = command_list[run_index][1];
            label = command_list[run_index].substr(2, command_list[run_index].length() - 2);
            gotoIfZeroReg(reg1, label);
            break;

        case 'E':
            reg1 = command_list[run_index][1];
            reg2 = command_list[run_index][2];
            label = command_list[run_index].substr(3, command_list[run_index].length() - 3);
            gotoIfRegsValEqual(reg1, reg2, label);
            break;

        case 'G':
            reg1 = command_list[run_index][1];
            reg2 = command_list[run_index][2];
            label = command_list[run_index].substr(3, command_list[run_index].length() - 3);
            gotoIfReg1valGreaterReg2val(reg1, reg2, label);
            break;

        case 'Q':
            run_index = command_list.size();
            break;

        case ':':
            break;

        default:
            if (!command_list[run_index].empty()) {
                value = (uint16_t) std::stoi(command_list[run_index]);
                put(value);
            }
    }

    return run_index != command_list.size();
}

uint16_t QuackInterpreter::get() {
    uint16_t value = queue.back();
    queue.pop_back();
    return value;
}

void QuackInterpreter::put(uint16_t value) {
    queue.emplace_front(value);
}

void QuackInterpreter::getIntoReg(char reg) {
    registers[reg] = get();
}

void QuackInterpreter::putFromReg(char reg) {
    put(registers[reg]);
}

void QuackInterpreter::calcSum() {
    uint16_t value1 = get();
    uint16_t value2 = get();
    put(value1 + value2);
}

void QuackInterpreter::calcSub() {
    uint16_t value1 = get();
    uint16_t value2 = get();
    put(value1 - value2);
}

void QuackInterpreter::calcProd() {
    uint16_t value1 = get();
    uint16_t value2 = get();
    put(value1 * value2);
}

void QuackInterpreter::calcQuotient() {
    uint16_t value1 = get();
    uint16_t value2 = get();

    if (value2)
        put(value1 / value2);
    else
        put(0);
}

void QuackInterpreter::calcMod() {
    uint16_t value1 = get();
    uint16_t value2 = get();

    if (value2)
        put(value1 % value2);
    else
        put(0);
}

void QuackInterpreter::printGet(std::string &value) {
    value = std::to_string(get()) + '\n';
}

void QuackInterpreter::printReg(char reg, std::string &value) {
    value = std::to_string(registers[reg]) + '\n';
}

void QuackInterpreter::printCharGet(std::string &value) {
    value = (char) get();
}

void QuackInterpreter::printCharReg(char reg, std::string &value) {
    value = (char) registers[reg];
}

void QuackInterpreter::gotoLabel(const std::string &label) {
    run_index = label_indexes[label];
}

void QuackInterpreter::gotoIfZeroReg(char reg, const std::string &label) {
    if (!registers[reg])
        gotoLabel(label);
}

void QuackInterpreter::gotoIfRegsValEqual(char reg1, char reg2, const std::string &label) {
    if (registers[reg1] == registers[reg2])
        gotoLabel(label);
}

void QuackInterpreter::gotoIfReg1valGreaterReg2val(char reg1, char reg2, const std::string &label) {
    if (registers[reg1] > registers[reg2])
        gotoLabel(label);
}


#define IN_FILE_NAME "quack.in"
#define OUT_FILE_NAME "quack.out"

int main() {
    std::ifstream fin(IN_FILE_NAME);
    if (!fin.is_open()) {
        std::cerr << "Couldn't open input file\n";
        return -2;
    }

    QuackInterpreter quack_interpreter;
    while (true) {
        if (fin.eof())
            break;

        std::string command;
        fin >> command;
        quack_interpreter.loadCommand(command);
    }
    fin.close();

    std::ofstream fout("CON");//OUT_FILE_NAME);
    if (!fout.is_open()) {
        std::cerr << "Couldn't open output file\n";
        return -2;
    }

    bool run_flag = true;
    while (run_flag) {
        std::string output;
        bool output_flag = false;

        run_flag = quack_interpreter.doOneCycle(output, output_flag);
        if (output_flag)
            fout << output;
    }

    fout.close();
    return 0;
}