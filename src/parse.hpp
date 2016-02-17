#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <regex>
#include <map>


#include "program.hpp"

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

  void parserParam(string str);

  void parserInstructions(string str);

  void parserComments(string str);
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
    if (match_regex(line, regex("^\\s*;.*"))) // comments
      tokens_.push_back(tuple<Token, string>(CommentT,line));
    else {
      smatch results;
      if (match_regex(line, results, regex("^\\s*(\\w)\\s*:\\s*(.*)"))) {
        tokens_.push_back(tuple<Token, string>(TagT, results[1]));

        if (result[2].size()>0 && !parserComments(results[2]))
          parserInstructions(results[2]);
      }
      else
        parserInstructions(line);
    }
  }
}

bool Parser::parserComments(string str) {
  bool temp = match_regex(str, regex("^\\s*;.*"));
  if (temp)
    tokens_.push_back(tuple<Token, string>(CommentT,str));
  return temp;
}

void Parser::parserParam(string str) {
  smatch results;
  if (match_regex(str, results, regex("^=(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(ImmediateT, results[1]));
    parserComments(results[2]);
  }
  else if (match_regex(str, results, regex("^(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(DirectT, result[1]));
    parserComments(results[2]);
  }
  else if (match_regex(str, results, regex("^\\*(\\d+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(IndirectT, result[1]));
    parserComments(results[2]);
  }
  else if (match_regex(str, results, regex("^(\\w)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(TagT, results[1]));
    parserComments(result[2]);
  }
  else
    parserComments(str);
}

void Parser::parserInstructions(string str) {
  smatch results;

  auto helper = [=](string name) { return match_regex(str, results, regex("^"+name+"\\s+(.*)"));};

  auto instructionsPairs =
    { {"LOAD", LoadT}
      , {"STORE", StoreT}
      , {"READ", ReadT}
      , {"WRITE", WriteT}
      , {"ADD", AddT}
      , {"SUB", Sub}
      , {"MUL", MulT}
      , {"DIV", DivT}
      , {"HALT", HaltT}
      , {"JUMP", JumpT}
      , {"JGZT", JgztT}
      , {"JZERO", JzeroT}
    };


  for (auto i : instructionsPairs) { // TODO usar iteradores con un while
    if (helper(i.get<0>())) {
      tokens_.push_back(tuple<Token,string>(i.get<1>(),i.get<0>()));
      parserParam(results[1]);
      break;
    }
  }// si no se ninguna ver si es comemtario si no es un error de compilacion
}


Program Parser::getProgram(void) {

  while (!tokens_.empty()) {
    switch (tokens_front()) {
        TagT
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

        DirectT,
        IndirectT,
        ImmediateT,
        CommentT,

    case
    }
  }
    /** For tokens → tok
        yield get.format.instruction tok
    */
}
