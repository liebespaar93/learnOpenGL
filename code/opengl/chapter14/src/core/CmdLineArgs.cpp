#include "CmdLineArgs.hpp"

CmdLineArgs::CmdLineArgs(int argc, char *argv[])
{
    parseArgs(argc, argv);
    printArgs();
}

CmdLineArgs::~CmdLineArgs() {}

void CmdLineArgs::parseArgs(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        try
        {
            if (arg.find('.') != std::string::npos)
                args.emplace_back(std::stof(arg)); // 실수로 변환
            else
                args.emplace_back(std::stoi(arg)); // 정수로 변환
        }
        catch (const std::exception &)
        {
            args.emplace_back(arg); // 변환 실패 시 문자열로 저장
        }
    }
}

void CmdLineArgs::printArgs() const
{
    std::cout << "Command Line Arguments:\n";
    for (size_t i = 0; i < args.size(); ++i)
    {
        std::cout << "  [" << i << "] ";
        std::visit([](auto &&arg) { std::cout << arg; }, args[i]);
        std::cout << "\n";
    }
}
