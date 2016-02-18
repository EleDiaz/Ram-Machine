#pragma once
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <regex>
#include <map>


#include "instruction.hpp"
#include "commonExceptions.hpp"

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

   TODO: Problema grande!!
   <<<
   hola:
        instr dd
        instr next
   next: // me salta a un lugar no comtemplado he estupido > error
   >>>

// Nota de milagro funciona bien el line of code
*/

using namespace std;

typedef vector<Instruction> Program;

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

  tuple<int, Memory::DirectionMode, bool> getParams(void);

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
  tuple<int, Memory::DirectionMode, bool> auxParams;
  auto helper = [&] (Instruction::IOpcode inst){
    tokens_.pop_front();
    auxParams = getParams(); // param and mode
    if (!(get<0>(auxParams) > 0 && get<2>(auxParams)))
      ; // throw UnexpectedToken("`" + get<1>(auxParams) + "` sino =int,*int o int");
    aux.push_back(Instruction(inst, get<0>(auxParams), get<1>(auxParams)));
  };

  while (!tokens_.empty()) {
    switch (get<0>(tokens_.front())){
    case TagT:
      tokens_.pop_front();
      break;

    case LoadT:
      helper(Instruction::Load);
      break;

    case StoreT:
      tokens_.pop_front();
      auxParams = getParams();
      if (!(get<0>(auxParams) > 0 && get<2>(auxParams) && get<1>(auxParams) == Memory::Immediate))
        ; // TODO: no se espera el siguiente token
      aux.push_back(Instruction(Instruction::Store, get<0>(auxParams), get<1>(auxParams)));
      break;

    case ReadT:
      tokens_.pop_front();
      auxParams = getParams();
      if (!(get<0>(auxParams) > 0 && get<2>(auxParams) && get<1>(auxParams) == Memory::Immediate))
        ; // TODO: no se espera el siguiente token
      aux.push_back(Instruction(Instruction::Read, get<0>(auxParams), get<1>(auxParams)));
      break;

    case WriteT:
      helper(Instruction::Write);
      break;

    case AddT:
      helper(Instruction::Add);
      break;

    case SubT:
      helper(Instruction::Sub);
      break;

    case MulT:
      helper(Instruction::Mul);
      break;

    case DivT:
      helper(Instruction::Div);
      break;

    case HaltT:
      tokens_.pop_front();
      aux.push_back(Instruction(Instruction::Halt));
      break;

    case JumpT:
      tokens_.pop_front();
      auxParams = getParams();
      if (get<2>(auxParams))
        throw UnexpectedToken(get<1>(tokens_.front()) + "  Expected Token: Tag Name");
      aux.push_back(Instruction(Instruction::Jump,get<0>(auxParams)));
      break;

    case JgztT:
      tokens_.pop_front();
      auxParams = getParams();
      if (get<2>(auxParams))
        throw UnexpectedToken(get<1>(tokens_.front()) + "  Expected Token: Tag Name");
      aux.push_back(Instruction(Instruction::Jgzt,get<0>(auxParams)));
      break;

    case JzeroT:
      tokens_.pop_front();
      auxParams = getParams();
      if (get<2>(auxParams))
        throw UnexpectedToken(get<1>(tokens_.front()) + "  Expected Token: Tag Name");
      aux.push_back(Instruction(Instruction::Jzero,get<0>(auxParams)));
      break;

    case CommentT:
      break;

    default:
      throw UnexpectedToken(get<1>(tokens_.front()));
      break;
    }
  }
  return aux;
}

tuple<int, Memory::DirectionMode, bool> Parser::getParams(void) {
  int aux;
  switch (get<0>(tokens_.front())){
  case DirectT:
    aux = stoi(get<1>(tokens_.front()));
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Direct, true);

  case IndirectT:
    aux = stoi(get<1>(tokens_.front()));
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Indirect, true);

  case ImmediateT:
    aux = stoi(get<1>(tokens_.front()));
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Immediate, true);

  case RefTagT:
    if (context_.end() == context_.find(get<1>(tokens_.front())))
      throw TagNotFound(get<1>(tokens_.front()));
    aux = context_[get<1>(tokens_.front())];
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Immediate, false);

  default:
    throw UnexpectedToken(get<1>(tokens_.front())); // FIXME: Token type to text
  }
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
  }
  else if (regex_match(str, results, regex("^(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(DirectT, results[1]));
    parserComments(results[2]);
  }
  else if (regex_match(str, results, regex("^\\*(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(IndirectT, results[1]));
    parserComments(results[2]);
  }
  else if (regex_match(str, results, regex("^(\\w)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(RefTagT, results[1]));
    parserComments(results[2]);
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
      lineOfCode++; // nueva instrucción a establecer la siguiente linea de codigo
    }
    it++;
  }
}


