#include <vector>
#include <string>
#include <algorithm>

class InputParser
{
public:
    InputParser(int &argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }

    const std::string &getArgument(const std::string &option) const
    {
        std::vector<std::string>::const_iterator it;
        it = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (it != this->tokens.end() && ++it != this->tokens.end())
        {
            return *it;
        }
        static const std::string emptyString("");
        return emptyString;
    }

private:
    std::vector<std::string> tokens;
};
