import sys
import lexer
import syntaxTree

def build(inFile: str, outFile: str):
    lexed = lexer.lex(inFile)

    