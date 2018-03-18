#ifndef TEST02_SORT_THE_INNER_CONTENT_H
#define TEST02_SORT_THE_INNER_CONTENT_H

//#Srot the inner ctnnoet in dsnnieedcg oredr
//
//You have to sort the inner content of every word of a string in descending order.
//The inner content is the content of a word without first and the last char.
//
//Some examples:
//
//"sort the inner content in descending order" -> "srot the inner ctonnet in dsnnieedcg oredr"
//"wait for me" -> "wiat for me"
//"this kata is easy" -> "tihs ktaa is esay"
//
//The string will never be null and will never be empty.
//It will contain only lowercase-letters and whitespaces.
//
//In C++ the string is always 0-terminated.


#include <cstring>

std::string next_token(const char* words, unsigned int startpos)
{
    unsigned int curpos = startpos;

    //capture possible leading spaces
    while (*(words + curpos) == ' ') {
        ++curpos;
    }
    while (*(words + curpos) && *(words + curpos) != ' ') {
        ++curpos;
    }

    return std::string(words + startpos).substr(0, curpos - startpos);
}

std::string sort_substring(std::string& unsorted_string)
{
    unsigned int startindex = 0;
    while (unsorted_string[startindex] == ' ') {
        ++startindex;
    }
    if (unsorted_string.length() - startindex > 3) {
        std::sort(unsorted_string.begin() + startindex + 1, unsorted_string.end() - 1, [](char c1, char c2) { return c1 > c2; });
    }
    return unsorted_string;
}

char* sortTheInnerContent(const char* words, int length)
{
    // some sanity checking
    if (!length || strlen(words) != length) {
        return nullptr;
    }

    unsigned int startpos = 0;
    std::string  ret;

    std::string token = next_token(words, startpos);
    while (!token.empty()) {
        ret += sort_substring(token);
        startpos += token.length();
        if (startpos >= length) {
            break;
        }
        token = next_token(words, startpos);
    }

    char* caller_has_to_delete_me__why_do_we_have_to_use_raw_pointers_with_cpp14 = new char[length + 1];
    strcpy(caller_has_to_delete_me__why_do_we_have_to_use_raw_pointers_with_cpp14, ret.c_str());

    return caller_has_to_delete_me__why_do_we_have_to_use_raw_pointers_with_cpp14;
}


void sort_the_inner_content()
{
    char const* input    = "sort  the inner  content in descending order";
    char const* expected = "srot  the inner  ctonnet in dsnnieedcg oredr";
    char*       output   = sortTheInnerContent(input, strlen(input));
    std::cout << output << "\n"
              << expected << std::endl;
    delete[] output;

    input    = "wait for me";
    expected = "wiat for me";
    output   = sortTheInnerContent(input, strlen(input));
    std::cout << output << "\n"
              << expected << std::endl;
    delete[] output;

    input    = "this kata is    easy";
    expected = "tihs ktaa is    esay";
    output   = sortTheInnerContent(input, strlen(input));
    std::cout << output << "\n"
              << expected << std::endl;
    delete[] output;
}
#endif //TEST02_SORT_THE_INNER_CONTENT_H
