import sys
import lexer
import syntaxTree
import codeGeneration
from actionTree import parseConstants, parseFunctions,  parseVariables, parseBody
import actionTree
def build(inFile: str, outFile: str):
    lexed = lexer.lex(inFile)
    # create the abstract syntax tree
    ast = parseBody(lexed)
    
    # create the action tree
    parseConstants(ast)
    parseVariables(ast)
    parseFunctions(ast)

    # print the Action Tree
    ast.printAll()

    print("Constants: ", actionTree.constants)

    # crete code generation.
    codeGeneration.createCode(ast, actionTree.variables, actionTree.functions, actionTree.functionData, actionTree.constants)

build("""
func main@int (returnStatus@int) {
    returnStatus = 1;
    var myName@string = "Eric";
    var lastName@string = "Diskin";
    var fullName@string = myName + lastName;
}
""", 0)