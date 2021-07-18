#include <cstdint>
#include <cassert>

#include "map.h"

namespace ZJVL
{
    namespace Core
    {
        static const char map[] = "0000222222220000"
                                  "1              0"
                                  "1      11111   0"
                                  "1     4        0"
                                  "0     0  1114444"
                                  "5     3        0"
                                  "5   30000      0"
                                  "5   0   11100  0"
                                  "5   0   0      0"
                                  "5   0   1  00000"
                                  "5       1      0"
                                  "2       1      0"
                                  "0       0      0"
                                  "0 0000000      0"
                                  "0              0"
                                  "0002222222200000";

        Map::Map() : w(16), h(16)
        {
            assert(sizeof(map) == w * h + 1); // + 1 for null terminated string
        }

        int Map::get(const std::size_t row, const std::size_t col)
        {
            assert(row < h && col < w && sizeof(map) == w * h + 1);

            // https://stackoverflow.com/questions/15598698/why-does-subtracting-0-in-c-result-in-the-number-that-the-char-is-representing
            // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            // This is kinda like char to int conversion. '0' is 48 and '9' is 57. 57 - 48 is 9. So it's kinda like '9' - 48
            return map[col + row * w] - '0';
        }

        bool Map::is_empty(const std::size_t row, const std::size_t col)
        {
            assert(row < h && col < w && sizeof(map) == w * h + 1);
            return map[col + row * w] == ' ';
        }
    }
}