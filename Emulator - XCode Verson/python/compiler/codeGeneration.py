"""
Takes a Node tree, from actionTree.py
Then converts it into a string containing the bytecode and data to be transpiled into actual bytecode
Eric Diskin
Created: 4-19-21, in TLP class
"""

from syntaxTree import Node
from createData import createData

constantsData = ""
output = ""

def createExpression():
    pass

def createFunction():
    pass

def createCall():
    pass

def createVariableAssignment():
    pass

# create a higher level constants string, then output it
def createConstants(constants: list):
    global constantsData
    for i in constants:
        if type(i) == int:
            # int
            constantsData += "\nN " + str(i)
        else:
            # string uses less bits to hold values
            constantsData += "\nS " + i
    return createData(constantsData.strip())


def createCode(node: Node, variables: list[str], functions: list[str], functionData: list[str], constants: list):
    constants = createConstants(constants)
    print(constantsData)
    print(constants)