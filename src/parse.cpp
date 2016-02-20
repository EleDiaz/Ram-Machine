#include "parse.hpp"

#include <iostream>

// INFO: Se esta usando \s como si fuese un \b debido a que nunca se da el caso de encontrar un \n
Parser::Parser(ifstream & file):
  tokens_(),
  context_(),
  lineOfCode(0)
{
  if (!file.is_open())
    throw (-1);

  string line;
  while (getline(file, line)) {
    if (regex_match(line, regex("^\\s*;.*"))) {// comments
      tokens_.push_back(tuple<Token, string>(CommentT,line));
    }
    else {
      smatch results;
      if (regex_match(line, results, regex("^\\s*(\\w+)\\s*:\\s*(.*)"))) {
        tokens_.push_back(tuple<Token, string>(TagT, results[1]));

        if (results[2].length()>0 && !parserComments(results[2])) {
          context_.insert(pair<string, int>(results[1], lineOfCode)); // Adding tag to context same line
          parserInstructions(results[2]);

        } else {
          context_.insert(pair<string, int>(results[1], lineOfCode+1)); // Adding tag to context only line
        }
      }
      else {
        parserInstructions(line);
      }
    }
  }
}

Program Parser::getProgram(void) {
  vector<Instruction> aux;
  tuple<int, Memory::DirectionMode, bool> auxParams;
  auto helper = [&] (Instruction::IOpcode inst){
    tokens_.pop_front();
    string temp = get<1>(tokens_.front());
    auxParams = getParams(); // param and mode
    if ((!get<0>(auxParams) > 0 && !get<2>(auxParams))) {
      throw UnexpectedToken("`" + temp + "` sino =int,*int o int");
    }
    aux.push_back(Instruction(inst, get<0>(auxParams), get<1>(auxParams)));
  };

  while (!tokens_.empty()) {
    cout << get<1>(tokens_.front()) << endl;
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
        ;//throw UnexpectedToken("Invalid parameter");
      aux.push_back(Instruction(Instruction::Store, get<0>(auxParams), get<1>(auxParams)));
      break;

    case ReadT:
      tokens_.pop_front();
      auxParams = getParams();
      if (!(get<0>(auxParams) > 0 && get<2>(auxParams) && get<1>(auxParams) == Memory::Immediate))
        ;//throw UnexpectedToken("Invalid parameter");
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
      tokens_.pop_front();
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
    tokens_.pop_front();
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Direct, true);

  case IndirectT:
    aux = stoi(get<1>(tokens_.front()));
    tokens_.pop_front();
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Indirect, true);

  case ImmediateT:
    aux = stoi(get<1>(tokens_.front()));
    tokens_.pop_front();
    return tuple<int, Memory::DirectionMode, bool> (aux, Memory::Immediate, true);

  case RefTagT:
    for (auto i : context_) /// HERE
      cout << get<0>(i) << " : " << get<1>(i) << endl;
    if (context_.end() == context_.find(get<1>(tokens_.front())))
      throw TagNotFound(get<1>(tokens_.front()));
    aux = context_[get<1>(tokens_.front())];
    tokens_.pop_front();
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
  else if (regex_match(str, results, regex("^(\\w+)\\s*(.*)"))) {
    tokens_.push_back(tuple<Token, string>(RefTagT, results[1]));
    parserComments(results[2]);
  }
  else
    parserComments(str);
}

void Parser::parserInstructions(string str) {
  smatch results;

  auto helper = [&](string name) {
    return regex_match(str, results, regex("^\\s*"+name+"\\s*(.*)", regex_constants::icase));};

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
      found = true;
    }
    it++;
  }
}
