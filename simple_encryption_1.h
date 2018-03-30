#ifndef TEST02_SIMPLE_ENCRYPTION_1_H
#define TEST02_SIMPLE_ENCRYPTION_1_H

//For building the encrypted string:
//Take every 2nd char from the string, then the other chars,
//that are not every 2nd char, and concat them as new String.
//Do this n times!
//
//Examples:
//
//"This is a test!", 1 -> "hsi  etTi sats!"
//"This is a test!", 2 -> "hsi  etTi sats!" -> "s eT ashi tist!"
//Write two methods:
//
//std::string encrypt(std::string text, int n)
//std::string decrypt(std::string encryptedText, int n)
//For both methods:
//If the input-string is null or empty return exactly this value!
//If n is <= 0 then return the input text.
//
//This kata is part of the Simple Encryption Series:
//Simple Encryption #1 - Alternating Split
//Simple Encryption #2 - Index-Difference
//Simple Encryption #3 - Turn The Bits Around
//Simple Encryption #4 - Qwerty

std::string extract_crypt_result(const std::string& in, int n)
{
    std::string first, second;
    int         current_pos = 0;

    for (const auto c : in) {
        if (current_pos++ % 2) {
            first += c;
        } else {
            second += c;
        }
    }
    return first + second;
};


std::string extract_decrypt_result(std::string first, std::string second, int n)
{
    std::string res;
    size_t      pos = 0;
    while (pos < first.length()) {
        res = res + second[pos] + first[pos];
        ++pos;
    }

    if (first.length() != second.length()) {
        res = res + second[pos];
    }

    return res;
}

std::string encrypt(std::string text, int n)
{
    if (n <= 0) {
        return text;
    }

    int counter = n;
    while (counter--) {
        text = extract_crypt_result(text, n);
    }
    return text;
}

std::string decrypt(std::string encryptedText, int n)
{
    if (n <= 0 || encryptedText.length() < 2) {
        return encryptedText;
    }

    int    counter    = n;
    size_t splitindex = encryptedText.length() / 2;
    while (counter--) {
        encryptedText = extract_decrypt_result(encryptedText.substr(0, splitindex), encryptedText.substr(splitindex, encryptedText.length() - 1), n);
    }
    return encryptedText;
}

void simple_encryption_1()
{
    cout << decrypt("D", 1).c_str();
    cout << encrypt("E", 1).c_str();
    return;
    cout << decrypt("hsi  etTi sats!", 1).c_str() << '\n'
         << "This is a test!" << '\n';
    cout << decrypt("s eT ashi tist!", 2).c_str() << '\n'
         << "This is a test!" << '\n';

    cout << encrypt("This is a test!", 0).c_str() << '\n'
         << "This is a test!" << '\n';
    cout << encrypt("This is a test!", 1).c_str() << '\n'
         << "hsi  etTi sats!" << '\n';
    cout << encrypt("This is a test!", 2).c_str() << '\n'
         << "s eT ashi tist!" << '\n';
    cout << encrypt("This is a test!", 3).c_str() << '\n'
         << " Tah itse sits!" << '\n';
    cout << encrypt("This is a test!", 4).c_str() << '\n'
         << "This is a test!" << '\n';
    cout << encrypt("This is a test!", -1).c_str() << '\n'
         << "This is a test!" << '\n';
    cout << encrypt("This kata is very interesting!", 1).c_str() << '\n'
         << "hskt svr neetn!Ti aai eyitrsig" << '\n';
}

#endif //TEST02_SIMPLE_ENCRYPTION_1_H
