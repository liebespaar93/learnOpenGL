#ifndef CMDLINEARGS_HPP
#define CMDLINEARGS_HPP

#include <iostream>
#include <vector>
#include <variant>
#include <stdexcept>

class CmdLineArgs
{
public:
    using ArgType = std::variant<int, float, std::string>;

    CmdLineArgs(int argc, char *argv[]);
    ~CmdLineArgs();

    const std::vector<ArgType> &getArgs() const { return args; }

    void printArgs() const;

    template <typename T>
    T get(size_t index) const;

    template <typename T>
    bool holds(size_t index) const;

private:
    std::vector<ArgType> args;
    void parseArgs(int argc, char *argv[]);
};

template <typename T>
T CmdLineArgs::get(size_t index) const
{
    try
    {
        if (index > args.size())
            throw std::out_of_range("Invalid argument index.");
        return std::get<T>(args[index]);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return false;
}

template <typename T>
bool CmdLineArgs::holds(size_t index) const
{
    try
    {
        if (index > args.size())
            throw std::out_of_range("Invalid argument index.");
        return std::holds_alternative<T>(args[index]);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Caught exception: " << e.what() << args.size() << "???" << index << std::endl;
    }
    return false;
}

#endif
