#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

namespace console {
    struct InputResult {
        bool succeeded{};
        int value{};
    };

    std::string getString(std::string_view askMessage) {
        std::cout << askMessage;
        std::string input{};
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    class Input {
    private:
        const std::string_view m_stopKey;

    public:
        explicit Input(const std::string_view stopKey) : m_stopKey{stopKey} {
        }

        InputResult getInt(std::string_view askMessage) {
            while (true) {
                const std::string input{getString(askMessage)};

                if (input == m_stopKey) {
                    return {};
                }

                try {
                    return {true, std::stoi(input)};
                } catch (std::exception &exception) {
                    std::cout << "Can't parse to int: " << input << "\r\n";
                }
            }
        }

        std::vector<int> getInts(std::string_view askMessage) {
            std::vector<int> array{};

            while (true) {
                console::InputResult result{getInt(askMessage)};

                if (!result.succeeded) {
                    break;
                }

                array.push_back(result.value);
            }

            return array;
        }
    };
}

int main() {
    console::Input input{console::getString("Please enter stop key:\r\n")};

    std::vector<int> array{input.getInts("Please enter the number:\r\n")};

    array.erase(std::remove_if(
            array.begin(), array.end(),
            [](const int &x) {
                return x == 0;
            }), array.end());

    const int sum{std::accumulate(array.begin(), array.end(), 0)};

    std::cout << "Average of non-zero numbers: " << sum / std::ssize(array);

    return 0;
}