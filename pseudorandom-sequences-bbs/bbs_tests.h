#ifndef BBS_TESTS_H
#define BBS_TESTS_H
#include <string>

bool numbers_test(std::string sequence);
bool numbers_test(std::string sequence, bool msg);
bool series_test(std::string sequence);
bool series_test(std::string sequence, bool msg);
bool long_series_test(std::string sequence);
bool long_series_test(std::string sequence, bool msg);
bool poker_test(std::string sequence);
bool poker_test(std::string sequence, bool msg);

void bbs_test_menu();

#endif // BBS_TEST_H