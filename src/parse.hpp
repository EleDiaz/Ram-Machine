#pragma once
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <regex>
#include <map>


#include "program.hpp"
#include "instruction.hpp"

/**
   TODO: llevar este codigo al repo de haskell
   tokenizer :: Stream Char → [Tokens]
   tokenizer stream = join (runParser tokenizer') . lines . stream
   where
   tokenizer' :: Parser [Token]
   tokenizer' = skipWhiteSpace $ do
   choice
   [ TagT <$> (word >> char ':')
   , IntructionT <$> (choice $ map string ["write", "read", "store"....])
   , DirectT <$> many1 digit
   , Indirect <$> char '*' >> many1 digit
   , Indirect <$> char '=' >> many1 digit
   ]
*/

using namespace std;

enum Token {
  TagT,
  RefTagT,
  // Instructions
  LoadT,
  StoreT,
  ReadT,
  WriteT,
  AddT,
  SubT,
  MulT,
  DivT,
  HaltT,
  JumpT,
  JgztT,
  JzeroT,
  // Direcionamiento
  DirectT,
  IndirectT,
  ImmediateT,
  CommentT,
};

class Parser {
private:
  list<tuple<Token, string> > tokens_;

  map<string, int> context_;

  int lineOfCode;

  void parserParam(string str);

  void parserInstructions(string str);

  bool parserComments(string str);

  tuple<int, Memory::DirectionMode> getParams(void);

public:
  Parser(ifstream & file);

  Program getProgram(void);
};

// INFO: Se esta usando \s como si fuese un \b debido a que nunca se da el caso de encontrar un \n
Parser::Parser(ifstream & file) {
  if (!file.is_open())
    throw (-1);

  string line;
  while (getline(file, line)) {
    if (regex_match(line, regex("^\\s*;.*"))) // comments
      tokens_.push_back(tuple<Token, string>(CommentT,line));
    else {
      smatch results;
      if (regex_match(line, results, regex("^\\s*(\\w)\\s*:\\s*(.*)"))) {
        tokens_.push_back(tuple<Token, string>(TagT, results[1]));
        context_.insert(pair<string, int>(results[1], lineOfCode+1)); // Adding tag to context

        if (results[2].length()>0 && !parserComments(results[2]))
          parserInstructions(results[2]);
      }
      else
        parserInstructions(line);
    }
  }
}

Program Parser::getProgram(void) {
  vector<Instruction> aux;
  tuple<int,Memory::DirectionMode> auxParams;
  while (!tokens_.empty()) {
    switch (get<0>(tokens_.front())) {
    case TagT:
      tokens_.pop_front();
      break;
    case LoadT:
      tokens_.pop_front();
      auxParams = getParams(); // param and mode
      aux.push_back(Instruction(Instruction::Load, get<0>(auxParams), get<1>(auxParams)));
      break;
    case StoreT:
      ;
    case ReadT:
    case WriteT:
    case AddT:
    case SubT:
    case MulT:
    case DivT:
    case HaltT:
    case JumpT:
    case JgztT:
    case JzeroT:
    case DirectT:
    case IndirectT:
    case ImmediateT:
    case CommentT:
      break;
    default:
      // TODO: no se soporta tal situacion exponer caso "error"
      break;
    }
  }

  // case RefTagT:
  //   auto it = context_.find(get<1>(tokens_.front()));
  //   if (context_.end() == it)
  //     ; // TODO: Error tag sin definir llamada desde el jump tal
  // }
  /** For tokens → tok
      yield get.format.instruction tok
  */
}

tuple<int, Memory::DirectionMode> Parser::getParams(void) {
}


bool Parser::parserComments(string str) {
  bool temp = regex_match(str, regex("^\\s*;.*"));
  if (temp)
    tokens_.push_back(tuple<Token, string>(CommentT,str));
  return temp;
}

void Parser::parserParam(string str) {
  smatch results;
  if (regex_match(str, results, regex("^=(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(ImmediateT, results[1]));
    parserComments(results[2]);
    lineOfCode++;
  }
  else if (regex_match(str, results, regex("^(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(DirectT, results[1]));
    parserComments(results[2]);
    lineOfCode++;
  }
  else if (regex_match(str, results, regex("^\\*(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(IndirectT, results[1]));
    parserComments(results[2]);
    lineOfCode++;
  }
  else if (regex_match(str, results, regex("^(\\w)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(RefTagT, results[1])); // TODO
    parserComments(results[2]);
    lineOfCode++;
  }
  else
    parserComments(str);
}

void Parser::parserInstructions(string str) {
  smatch results;

  auto helper = [&](string name) { return regex_match(str, results, regex("^"+name+"\\s+(.*)"));};

  map<string, Token> instructionsPairs
    { {"LOAD", LoadT}
      , {"STORE", StoreT}
      , {"READ", ReadT}
      , {"WRITE", WriteT}
      , {"ADD", AddT}
      , {"SUB", SubT}
      , {"MUL", MulT}
      , {"DIV", DivT}
      , {"HALT", HaltT}
      , {"JUMP", JumpT}
      , {"JGZT", JgztT}
      , {"JZERO", JzeroT}
    };

  map<string, Token>::iterator it = instructionsPairs.begin();
  bool found = false;
  while (!found && it != instructionsPairs.end()) {
    if (helper(it->first)) {
      tokens_.push_back(tuple<Token,string>(it->second,it->first));
      parserParam(results[1]);
    }
    it++;
  }
}


