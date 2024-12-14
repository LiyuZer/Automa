/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

//
//  main.cpp
//  antlr4-cpp-demo
//
//  Created by Mike Lischke on 13.03.16.
//

#include <iostream>

#include "antlr4-runtime.h"
#include "../grammar/AUTOMALexer.h"
#include "../grammar/AUTOMAParser.h"

using namespace std;
using namespace antlr4;
class CustomListener : public AUTOMAParserBaseListener {
public:
    void enterR(AUTOMAParser::RContext *ctx) override {
        std::cout << "Entered rule: " << ctx->getText() << std::endl;
    }

    void exitR(AUTOMAParser::RContext *ctx) override {
        std::cout << "Exited rule: " << ctx->getText() << std::endl;
    }
};
int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    
    ANTLRInputStream input(stream);
    AUTOMALexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    AUTOMAParser parser(&tokens);    
    tree::ParseTree *tree = parser.r();
    CustomListener listener;
    tree::ParseTreeWalker walker;
    walker.walk(&listener, tree); // `tree` is the root node from `parser.r()`
    return 0;
}