#pragma once
#include <exception>
#include <string>

using namespace std;

class AdditionalInfo
{
protected:
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

class TokenUnknow : public exception, AdditionalInfo
{
public:
    TokenUnknow(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
      return ("No se reconoce el token: " + info()).c_str();
    }
};


class UnexpectedToken : public exception, AdditionalInfo
{
public:
    UnexpectedToken(string str):
        AdditionalInfo(str) {}
    virtual const char* what() const throw() {
        return ("No se esperaba ese token: " + info()).c_str();;
    }
};

class TagNotFound : public exception, AdditionalInfo
{
public:
  TagNotFound(string str):
    AdditionalInfo(str) {}
  TagNotFound(const TagNotFound & tag):
    AdditionalInfo(tag.addInfo) {}
  virtual const char* what() const throw() {
    return ("No ha sido declarada la siguiente etiqueta: " + info()).c_str();;
  }
};

class ProgramError : public exception, AdditionalInfo
{
public:
  ProgramError(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("Se " + info()).c_str();;
  }
};

class TapeNoInput : public exception, AdditionalInfo
{
public:
  TapeNoInput(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("No hay valores de entrada " + info()).c_str();;
  }
};



class ParseError : public exception, AdditionalInfo
{
public:
  ParseError(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("Error Parseando: " + info()).c_str();;
  }
};

class MemoryAccess : public exception, AdditionalInfo
{
public:
  MemoryAccess(string str):
    AdditionalInfo(str) {}
  virtual const char* what() const throw() {
    return ("Error accediendo a la memoria: " + info()).c_str();;
  }
};

