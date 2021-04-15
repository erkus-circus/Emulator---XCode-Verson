"""
Eric Diskin
Created: 4/3/21
This file takes a parsed AST and turns it into an action tree. 
It also type checks and makes sure that there will be no runtime errors invlolving function calls and all that.
It also creates the indexes for functions, variables, and constants.
After this step is code generation, which takes the action tree and turns it into assembly.
After that the assembly is compiled into bytecode which is then able to be run by my stack machine, and the language is finished
"""

# am i cutting corners making this? it will work but will it actually work in the long run? Oh well i can always remake it
# as long as i comment enough.

from lexer import lex
from syntaxTree import Node, parseBody



# Function is a thing that holds data about the function, like params, return value, and other things like that.
class Function:
    def __init__(self, paramTypes: list[str], returnValue: str):
        self.paramTypes = paramTypes
        self.returnValue = returnValue

# functions is a list of function names, and each one can be found at the respective index
# all the builtin functions can be added later to the start or end. To start i will add print and input functions:
functions: list[str] = [
    "main",
    "print",
    "input"
]
# holds a list in parallel with functions
functionData: list[Function] = [
    # main function:
    Function([], None),
    # print function:
    Function(["string"], None),
    # input function:
    Function(["string"], "string")
]

# a list of all the global variables
globalVars: list[str] = [

]

# constants is the list of all of the constants in the program. at the end it can generate from the constants generator or something.
constants: list[str] = []

# the output of the program:
output = ""

# loop through everything and extract the constants. Then assign the node to be have an index of the actual constant
## TODO: make it so the most prevelant constants are used for C_0 through C_5, then the rest can be C_B, 
## and if needed then C_S, but that should not ever happen i dont think
def parseConstants(node: Node):
    for i in node.children:
        if i.nodeName == "string" or i.nodeName == "int":
            i.nodeName = "constantReference"
            if i.value in constants:
                # the constant is already defined
                i.value = constants.index(i.value)
            else:
                # make the value the current len of constants, then append the new constant to the constants array
                constants.append(i.value)
                i.value = len(constants) - 1
        else:
            parseConstants(i)

    # probably a more efficient method here but since its 12:17am i am just gonna copy paste
    ## TODO make this actually work, IT DOES WORK JUST IS A BIT INEFFICIETN i think 
    # no idea why im using caps lock
    for i in node.arguments:
        if i.nodeName == "string" or i.nodeName == "int":
            i.nodeName = "constantReference"
            if i.value in constants:
                # the constant is already defined
                i.value = constants.index(i.value)
            else:
                # make the value the current len of constants, then append the new constant to the constants array
                constants.append(i.value)
                i.value = len(constants) - 1
        else:
            parseConstants(i)


# extract all function definitions and then assign them to the functions thing.
# include return type and all that stuff somehow in maybe a different list of functions or something
# or functions list is actually a class that contains the data about the function: (argument types, return value...)
def parseFunctions(node: Node) -> None:
    # loop through to get all function definitions. No repeat functions for at least now.
    for i in node.children:
        if i.nodeName == "function":
            paramTypes = []
            if i.name in functions:
                #error: function already defined
                pass
            for argument in i.arguments:
                paramTypes.append(argument.type)
            functions.append(i.name)
            functionData.append(Function(paramTypes=paramTypes, returnValue=i.type))
        parseFunctions(i)

# parse a function call and converting its arguments
def parseFunctionCalls():
    pass



# parse a body for variable definitions. Make sure it is in the correct frame, might make a variable stack thing to do this
# like stack of arrays of variables, then when one body ends its var array gets popped, but a new one appears
# also check for duplicate variables and inconsistant typing when calling other functions. 
# Do this part last, after constants and functions have been done.

class ScopeStack:
    
    def __init__(self) -> None:
        self.scopes: list[list[Node]] = []

    def addScope(self):
        self.scopes.append([])
    
    def popScope(self):
        self.scopes.pop()

    def addVar(self, var):
        self.scopes[-1].append(var)
    
    # check if a variable has already been defined
    def isDefined(self, var: Node):
        for i in self.scopes[-1]:
            if var in i:
                # error: already defined
                print("Variable already defined!")



scopes = ScopeStack()

def parseVariables(node: Node) -> None:
    for i in node.children:
        if i.nodeName == "reference":
            if not scopes.isDefined(i.name):
                # error: variable not defined
                pass
            

        elif i.nodeName == "varDeclaration":
            pass


if __name__ == "__main__":
    inputs = """
    func sayHi@null (name@string) {
        var output@int = (12 + 14) - output;
        print(output);
    }
    sayHi(("Eric Diskin" * 5) + " Is said 5 times." - (22));
    """
    lexed = lex(inputs)
    ast = parseBody(lexed)
    ast.printAll()
    parseConstants(ast)
    parseFunctions(ast)
    print("Constants: ",constants)
    print("Functions: ", functions)
    