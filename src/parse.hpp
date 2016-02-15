#include <fstream>
#include <list>
#include <string>
#include <cstring>
#include <utility>

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

  Token parserInstructions(string str);

public:
  Parser(ifstream & file);

  Program getProgram(void);
};


Parser::Parser(ifstream & file) {
  if (!file.is_open())
    throw (-1);

  string line;
  while (getline(file, line)) {
    switch (line[0]) {
    case ';':

      tokens_.push_back(tuple<Token, string>(Comment, line));
      break;
    default:
      break;
    }
    char * pch = strtok(line, " "); // La peor funcion que existe
    while (pch != nullptr) {
      if (pch[0] == '=')
        tokens_.push_back( tuple<Token, string>(ImmediateT,string(pch)));
      else if (pch[0] == '*')
        tokens_.push_back( tuple<Token, string>(DirectT,string(pch)));
      else if (pch[strlen(pch)])
        tokens_.push_back( tuple<Token, string>(TagT,string(pch)));
      else
        tokens_.push_back( tuple<Token, string>(parserInstructions(string(pch)),string(pch)));
      pch = strtok(NULL, " ");
    }
  }
}



Token Parser::parserInstructions(string str) {
    if (str.compare("load"))
        return LoadT;
    if (str.compare("store"))
        return StoreT;
    if (str.compare("read"))
        return ReadT;
    if (str.compare("write"))
        return WriteT;
    if (str.compare("add"))
        return AddT;
    if (str.compare("sub"))
        return SubT;
    if (str.compare("mul"))
        return MulT;
    if (str.compare("div"))
        return DivT;
    if (str.compare("halt"))
        return HaltT;
    if (str.compare("jump"))
        return JumpT;
    if (str.compare("jgzt"))
        return JgztT;
    if (str.compare("jzero"))
        return JzeroT;
    else
        return ; // throws a error
}


Program Parser::getProgram(void) {
  /** For tokens → tok
        yield get.format.instruction tok
   */
}
