#pragma once
#include <exception>
#include <string>

using namespace std;

class AdditionalInfo
{
private:
    string addInfo;
public:
    AdditionalInfo(string str) {
        addInfo = str;
    };
    string info(void) const {
        return addInfo;
    };
    virtual ~AdditionalInfo() {};
};

class TokenUnknow : exception, AdditionalInfo
{
public:
    TokenUnknow(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("No se reconoce el token: " + info()).c_str();
    }
};


class UnexpectedToken : exception, AdditionalInfo
{
public:
    UnexpectedToken(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("No se esperaba ese token: " + info()).c_str();;
    }
};

class TagNotFound : exception, AdditionalInfo
{
public:
  TagNotFound(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("No ha sido declarada la siguiente etiqueta: " + info()).c_str();;
  }
};

class ProgramError : exception, AdditionalInfo
{
public:
  ProgramError(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("Se " + info()).c_str();;
  }
};


class ParseError : exception, AdditionalInfo
{
public:
  ParseError(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("Error Parseando: " + info()).c_str();;
  }
};
