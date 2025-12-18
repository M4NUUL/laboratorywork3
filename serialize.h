#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std; 

//бинарный
inline void writeString(ofstream& file, const string& s) {
    size_t len = s.length();
    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
    file.write(s.c_str(), len);
}

inline string readString(ifstream& file) {
    size_t len;
    file.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (file.fail()) return "";
    
    string s(len, '\0');
    file.read(&s[0], len);
    if (file.fail()) return ""; 
    return s;
}

//текстовый
inline void writeStringText(ofstream& file, const string& s) {
    // Записываем строку и перенос
    file << s << "\n";
}

inline string readStringText(ifstream& file) {
    string s;
    if (getline(file, s)) {
        if (!s.empty() && s.back() == '\r') s.pop_back();
        return s;
    }
    return "";
}

#endif