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
  InstructionT,
  DirectT,
  IndirectT,
  ImmediateT,
  Comment
};

class Parser {
private:
  list<tuple<Token, string> > tokens_;
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
        tokens_.push_back( tuple<Token, string>(InstructionT,string(pch)));
      pch = strtok(NULL, " ");
    }
  }
}


Program Parser::getProgram(void) {
  /** For tokens → tok
        yield get.format.instruction tok
   */
}
