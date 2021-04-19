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
    0,
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
# TODO: make it so the most prevelant constants are used for C_0 through C_5, then the rest can be C_B,
# and if needed then C_S, but that should not ever happen i dont think


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
    # TODO make this actually work, IT DOES WORK JUST IS A BIT INEFFICIETN i think
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
                # error: function already defined
                print("already defined function")
                pass
            elif i.name == "main":
                # the main function, treat this special
                functions[0] = "main"
            else:
                functions.append(i.name)
            for argument in i.arguments:
                paramTypes.append(argument.type)
            # treat this main function special too
            if not i.name == "main":
                functionData.append(
                    Function(paramTypes=paramTypes, returnValue=i.type))
            else:
                # here is for the main function
                functionData[0] = Function(paramTypes=paramTypes, returnValue=i.type)
            # give the function an index
            i.name = len(functions) - 1
        # parse a call node 
        elif i.nodeName == "call":
            if not i.name in functions:
                print("undefined function call")
            else:
                i.name = functions.index(i.name)
        parseFunctions(i)




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


# scopes = ScopeStack()

# def parseVariables(node: Node) -> None:
#     for i in node.children:
#         if i.nodeName == "reference":
#             if not scopes.isDefined(i.name):
#                 # error: variable not defined
#                 pass


#         elif i.nodeName == "varDeclaration":
#             pass


"""
To make results come faster, i am going to inneficiently make variable indexes not recycle and prob screw this up. So anyways i hope this goes slightly well.
anything after this is prob half-assed
"""

variables: list[str] = []



#### varDeclaration if is being executed when it should not be. I dont know why. I am gojing to reboot the server right now to maybe get python stuff.
def parseVariables(node: Node):
    # do variable declarations first, then references after because otherwise it does not work.
    for i in node.children:
        if i.nodeName == "varDeclaration":
            if i.name in variables:
                # error already defined:
                print("ALREADY DEFINED")
            
            # makeshift fix, works but i should not need to add this here.
            if type(i.name) == int:
                continue
            placeholderName = i.name
            i.name = len(variables)
            variables.append(placeholderName)
        parseVariables(i)
    
    # do the same but with arguments.
    for i in node.arguments:
        if i.nodeName == "varDeclaration":
            if i.name in variables:
                # error already defined:
                print("ALREADY DEFINED")
            
            # makeshift fix, works but i should not need to add this here.
            if type(i.name) == int:
                continue
            placeholderName = i.name
            i.name = len(variables)
            variables.append(placeholderName)
        parseVariables(i)

    for i in node.children:
        if i.nodeName == "reference":
            # variable name is a number when it should be a string.
            if not i.name in variables:
                # error not defined
                print("NOT DEFINED!")
                pass
            else:
                i.nodeName = "variableReference"
                i.name = variables.index(i.name)
        parseVariables(i)

if __name__ == "__main__":
    inputs = """
    func main@int ( unknown@void) {
        var zero@int = 0;
        var one@int = 1;
        var two@int = 2;
        var three@int = 3;
        var four@int = 4;
    }
    main(1000);
    """
    lexed = lex(inputs)
    ast = parseBody(lexed)
    parseConstants(ast)
    parseVariables(ast)
    parseFunctions(ast)
    ast.printAll()
    print("Constants: ", constants)
    print("Functions: ", functions)
    print("Variables: ", variables)
