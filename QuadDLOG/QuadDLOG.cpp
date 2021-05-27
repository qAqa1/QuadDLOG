// QuadDLOG.cpp : Defines the entry point for the application.

#include "TonelliShanks.h"
#include "QuadraticResidueDLOG.h"

#include <chrono>
#include <tuple>

using namespace std;
using namespace boost::multiprecision;

optional<tuple<cpp_int, cpp_int, cpp_int>> InputDiscreteLogarithm(vector<string> commandLineArgs)
{
    cpp_int a, b, c;

    if (commandLineArgs.empty())
    {
        cout << "a^x = b(mod c)" << endl;
        cout << "a=";
        cin >> a;
        cout << "b=";
        cin >> b;
        cout << "c=";
        cin >> c;

        return make_optional(make_tuple(a, b, c));
    }

    if (commandLineArgs.size() == 3)
    {
        a = cpp_int(commandLineArgs[0]);
        b = cpp_int(commandLineArgs[1]);
        c = cpp_int(commandLineArgs[2]);
        return make_optional(make_tuple(a, b, c));
    }

    cout << "error args count, must 3: a b c; a^x = b(mod c)";
    return std::nullopt;
}

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    vector<string> commandLineArgs;
    for (int i = 1; i < argc; i++) commandLineArgs.emplace_back(argv[i]);

    auto input = InputDiscreteLogarithm(commandLineArgs);
    if (!input) exit(1);
    const auto& [a, b, c] = *input;

    auto starTimer = chrono::steady_clock::now();

    auto root = FindRoot(a, b, c);
    auto endTimer = chrono::steady_clock::now();
    if (root)
        std::cout << std::endl << "Корень: " << *root;
    cout << endl << endl << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>((endTimer - starTimer)).count() << "ms";

	return 0;
}
