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




