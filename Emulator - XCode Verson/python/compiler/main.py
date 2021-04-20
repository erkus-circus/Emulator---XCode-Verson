import sys
import lexer
import syntaxTree
import codeGeneration
from actionTree import parseConstants, parseFunctions,  parseVariables, parseBody, functions, constants, variables
import actionTree

def build(inputProgram: str) -> str:
    lexed = lexer.lex(inputProgram)
    # create the abstract syntax tree
    ast = parseBody(lexed)
    
    # create the action tree
    parseConstants(ast)
    parseVariables(ast)
    parseFunctions(ast)



    # print the Action Tree
    ast.printAll()

    # make the variable index and constant index constants:
    print("MAX:", max(len(variables), len(constants)))
    for i in range(max(len(variables), len(constants))):
        constants.append(i)
    print("Functions: ", functions)
    print("Constants: ", constants)
    print("Variables: ", variables)


    # crete code generation.
    return (codeGeneration.createCode(ast, actionTree.variables, actionTree.functions, actionTree.functionData, actionTree.constants))

# build("""

# func createName@string (nameParam@string, lastNameParam@string) {
#     var output@string;
#     output = nameParam + lastNameParam;
# }

# func main@int (returnStatus@int) {
#     var myName@string = "Eric";
#     var lastName@string = "Diskin";
#     var fullName@string = myName + lastName;

#     myName = createName(lastName, "Ilana");
#     print(fullName);
# }
# """, 0)

# build("""
# func main@int (param@string) {
#     print("Hello");
# }
# """, 0)

if __name__ == "__main__":
    if len(sys.argv) < 1:
        print("Please input an input file to run.")
    else:
        outputFile = open(sys.argv[1] + ".starpCode", "w")
        with open(sys.argv[1], 'r') as f:
            outputFile.write(build(f.read()))
        outputFile.close()