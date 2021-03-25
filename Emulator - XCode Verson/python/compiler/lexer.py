class Type:
    def __init__(self, a: str, b: str, c=False):
        self.name = a
        self.values = b
        self.stackable = c

    def isOfType(self, type: str) -> bool:
        return self.values.find(type) >= 0

    name = ""
    values = ""
    stackable: bool

class LexList:
    def add(self, type: str, val: str):
        self.types.append(type)
        self.vals.append(val)
        self.length += 1
    
    # checks if the current token has a newline character in it
    def isCurrentNewLine(self) -> bool:
        # TODO: this
        pass
    
    def expect(self, *types:Type):
        typeFound = False
        for i in types:
            if self.getType() == i.name:
                typeFound = True
                break
        if not typeFound:
            #error
            print("An Error occured")

    def getType(self) -> str:
        return self.types[self.index] if self.canRetrieve() else "EOF"

    def getVal(self) -> str:
        return self.vals[self.index] if self.canRetrieve() else "EOF"

    def stepUp(self, steps: int = 1):
        self.index += steps

    def stepDown(self, steps = 1):
        self.stepUp(-steps)

    # skips whitespace, whitespace must be on top
    def skipSpace(self):
        if not self.canRetrieve() or self.getType() == "EOF":
            return
        if self.getType() == "SPACE":
            self.stepUp()
    
    # print out all of the lexed list
    def printOut(self):
        for i in range(self.length):
            print(self.vals[i] + ": " + self.types[i])
    

    # not sure
    def getVals(self, sep=":") -> list[str]:
        retVal = []
        for i in range(self.length):
            retVal.append(self.types[i] + sep + self.vals[i])
        return retVal

    # checks if you are able to retrieve a token
    def canRetrieve(self) -> bool:
        return self.index < self.length
    
    # checks if the current value is EOF
    def eof(self) -> bool:
        return self.getType() == "EOF"

    index = 0
    length = 0
    types: list[str] = []
    vals: list[str] = []

class Types:
    EQUALS = Type("EQUALS", "=",1)
    ID = Type("ID", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 1)
    STRSEP = Type("STRSEP", "\"`'")
    NUM = Type("NUM", "1234567890", 1)
    SPACE = Type("SPACE", " \n", 1)
    QMARK = Type("QMARK", "?")
    EXPOMARK = Type("EXPOMARK", "!")
    PARENTH = Type("PARENTH", "()")
    CURLY_PAREN = Type("CURLY_PAREN", "{}")
    BRACKET = Type("BRACKET", "[]")
    OPERATOR = Type("OPERATOR", "/*+-")
    PERIOD = Type("PERIOD", ".")
    USCORE = Type("USCORE","_")
    BSLASH = Type("BSLASH","\\")
    SEMICOL = Type("SEMICOL",";")
    TYPEOPER = Type("TYPEOPER","@")
    TILDE = Type("TILDE","~")
    EXPONENT = Type("EXPONENT", "^")
    # this is a special case, not included in list types
    STATEMENT = Type("STATEMENT", "")
    # maybe should add EOF type?]

types = [
    Types.EQUALS,
	Types.ID,
	Types.STRSEP,
	Types.NUM,
	Types.SPACE,
	Types.QMARK,
	Types.EXPOMARK,
	Types.PARENTH,
	Types.CURLY_PAREN,
	Types.BRACKET,
	Types.OPERATOR,
	Types.PERIOD,
	Types.USCORE,
	Types.BSLASH,
	Types.SEMICOL,
	Types.TILDE,
	Types.EXPONENT, 
]

statements = [
    "func",
	"var",
	"if",
	"return",
    "interface",
    "class",
    "include"
]

def lex(text: str, linenum=0) -> LexList:
    index = 0

    lexed = LexList()

    lastType = "NULL"
    lastVal = "NULL"
    first = False

    length = len(text)

    done = False

    for i in range(length):
        c = text[i]

        theType = getCharType(c)
        typ = theType.name

        if typ == lastType and theType.stackable:
            lastVal += c
        else:
            if first:
                for j in range(len(statements)):
                    if statements[j] == lastVal:
                        lastType = "STATEMENT"
                lexed.add(lastType, lastVal)
            else:
                first = True
            
            lastType = typ
            lastVal = c
    for i in range(len(statements)):
        if statements[i] == lastVal:
            lastType = "STATEMENT"
    
    lexed.add(lastType, lastVal)

    lexed.add("EOF", "EOF")

    return lexed

def getCharType(char: str) -> Type:
    for i in range(len(types)):
        if types[i].isOfType(char):
            return types[i]
    return Type("NULL", "^")


if __name__ == "__main__":
    # an example program that i should use for reference when making the syntax tree and parsing through the LexList
    l = lex("""
    ^ primitive Data type, used in emulator
    interface DataSegment {
        func DSET (data@DataSegment, index@int, value@DataSegment);
        func DGET (data@DataSegment, index@int);
        func DCPY (destination@DataSegment, source@DataSegment);


        extern var totalDataSegments;
        ^ extern means that it is not allocated to the variable, but it is like static var in class in c++

        var length@int;

        var values@array;
        ^ values = array of ints
    }

    class array extends DataSegment {
    }

    class Person {
        var name@string;
        var age@int;
        var familyMembers@array<string>;

        func construct(n@string, a@int, familyMembersList@array<string>) {
            this.name = n;
            this.age = a;
            this.familyMembers = familyMembersList;
        }
    }

    func sayHi@string (name@string, age@int) {
        var message@string = "Hi " + name + ". You are " + string(age) + " years old";
        print(message);
        ^ print the string message
    }
    """)

    l.printOut()