"""
Parses the LexedList into a tree consisting of Nodes
Eric Diskin
3/22/21 Created, things copied from older projects from 2019
"""



"""

Each Parse function takes in a lexedList and returns a Node

"""

from lexer import LexList, lex, Types

class Node:
    def __init__(self, name) -> None:
        self.nodeName = name
    
    def addChild(self, child) -> None:
        self.children.append(child)
    
    # print all children and itself
    def printAll(self, tabs=0):
        output = tabs * '\t' + "Name: %s, value: %s, children:" % (self.name, self.value)
        print(output)
        for i in range(len(self.children)):
            self.children[i].printAll(tabs + 1)

    # children of the node, for bodys
    children = []
    # arguments, for parameters or arrays or if statements
    arguments = []
    # the name of node: string, body, if, func declaration, like statements
    nodeName = ""

    # the name of the node
    name = ""

    # the value of the node, for values like strings and numbers
    value = ""

# parse a body
def parseBody(lexed: LexList) -> Node:
    # init a body node
    tree = Node("Body")
    while lexed.canRetrieve() and lexed.eof():
        
        # expect only ID's and STATEMENTS
        lexed.expect(Types.ID, Types.STATEMENT)

        # inside body funcs expect only statements and word tokens like for assinging and calling functions
        if lexed.getType() == "STATEMENT":
            # each function call here lexed index is pointing on top of STATEMENT
            if lexed.getVal() == "var":
                # parse a variable declaration
                tree.addChild(parseVarDeclaration(lexed))
            if lexed.getVal() == "func":
                # parse a function declaration
                tree.addChild(parseFunctionDeclaration(lexed))
            if lexed.getVal() == "if":
                # parse an if statement
                tree.addChild(parseIf(lexed))
            if lexed.getVal() == "return":
                # parse a return statement
                tree.addChild(parseReturn(lexed))


        elif lexed.getType() == "ID":
            # lexed index is pointing on top of ID
            tree.addChild(parseID(lexed))
        else: 
            # error
            pass
        
        # will probably need to stepUp here, but we will see
    return tree

def parseVarDeclaration(lexed: LexList) -> Node:
    pass

# parse an ID into a function call or an assignment
def parseID(lexed: LexList) -> Node:
    # expect an ID on top
    lexed.expect(Types.ID)

    # step and skip
    lexed.stepUp()
    lexed.skipSpace()

    # expect ID followed by (), =, or []
    lexed.expect(Types.PARENTH, Types.EQUALS, Types.BRACKET)

    # parse a function call
    if lexed.getVal == "(":
        pass

    # parse an assignment
    elif lexed.getVal() == "=":
        pass

    # parse a bracket
    # followed by assignment or call: array[index]();
    elif lexed.getVal() == "[":
        pass

    else:
        # error
        pass

    # TODO: return a Node


def parseCall(lexed: LexList) -> Node:
    tree = Node("call")

    # expect an ID, for function name
    lexed.expect(Types.ID)

    # get the name of the function
    tree.name = lexed.getVal()

    # step and skip
    lexed.stepUp()
    lexed.skipSpace()

    # now pointing to (
    parseArguments(lexed)


def parseAssignment(lexed: LexList) -> Node:
    pass

def parseArguments(lexed: LexList, openingClosingTypes=Types.PARENTH, seperator: str=",", requiresType=True, expression=False) -> Node:
    # expect (
    lexed.expect(openingClosingTypes)
    



# ending is when to expect the ending of the expression, ie. ) or , or ;
def parseExpression(lexed: LexList, ending: str, depth:int=0) -> Node:  

    # if expecting an operator after an ID or const
    expectingOperator = False
    expressionTree = Node("expression")

    while lexed.canRetrieve() and not lexed.eof() and lexed.getVal() != ending:
        # expects to be pointing to the token before the start of the expression
        lexed.stepUp()
        lexed.skipSpace()

        if lexed.getVal() == ending:
            # the end of the expression
            if not expectingOperator:
                # error, cannot end an expression with like: (a + b =) or (b=c%)
                pass
            break

        if expectingOperator:
            # expect an operator
            lexed.expect(Types.OPERATOR)
            # create a node for the operator
            operatorNode = Node("operator")
            operatorNode.value = lexed.getVal()

            # push the node into expression
            expressionTree.addChild(operatorNode)

            # no longer expecting operator
            expectingOperator = False
            continue
            

        # expect a variable name, string, or number
        lexed.expect(Types.ID, Types.STRSEP, Types.NUM)

        if lexed.getType() == "ID":
            expressionTree.addChild(parseID(lexed))
            # what does this leave lexed pointing to?
        
        elif lexed.getType() == "STRSEP":
            # parse a string
            expressionTree.addChild(parseString(lexed))
            # leaves lexed on top of last STRSEP token
        
        elif lexed.getType() == "NUM":
            # parse a number
            expressionTree.addChild(parseNumber(lexed))
            # leaves lexed on top of NUM token
        # in an expression following a symbol you need an operator
        expectingOperator = True
    
    # ends pointing to ending param
    return expressionTree

def parseIf(lexed:LexList) -> Node:
    pass

def parseNumber(lexed: LexList) -> Node:
    # floats are not yet supported. I should support them eventually i will probably 
    # give them their own special stack or something
    number = ""

    # expect a number since we are getting a number
    lexed.expect(Types.NUM)

    node = Node("int")
    node.value = lexed.getVal()

    # stops with lexed pointing to int
    return node

def parseString(lexed: LexList) -> Node:
    #expects lexed to point on top of first "
    lexed.expect(Types.STRSEP)
    # to check if the current string is terminated or not. ie \n \t
    terminated = False
    output = ""
    while not lexed.eof() and lexed.canRetrieve():
        # move up
        lexed.stepUp()

        # chars could be a whole token so loop through everything
        chars = lexed.getVal()

        if lexed.getType() == "SPACE" and not terminated:
            # this could have more space
            if '\n' in chars:
                #error
                pass
            
        if terminated:
            output += chars
        
        elif lexed.getVal() == "\\":
            # an escape sequence
            terminated = True
            continue

        elif lexed.getType() == "STRSEP":
            # the string has ended
            break
        terminated = False
    # wrap up output in node and return
    node = Node("string")
    # stops with lexer on top of STRSEP
    node.value = output
    return node
        
        

        
        

def parseFunctionDeclaration(lexed: LexList) -> Node:
    pass

def parseReturn(lexed: LexList) -> Node:
    pass


if __name__ == "__main__":
    parsed = parseExpression(lex("(12 + 15)"), ")")
    parsed.printAll()