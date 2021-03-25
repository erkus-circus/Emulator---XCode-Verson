""""
Creates a data section for a assembly script

Eric Diskin
Created on: 3/11/21
"""

# takes data from a data.txt file in this directory with the following format:

"""
[N|S] [number or string]
  for example for the number 42:
N 42
  or for the string, "Hello World!"
S Hello World!
  strings can be escaped using \\'s. for example:
S hello my name is eric. \n i like eating food.
"""


def bytesFromNumber(number: int): 
    hexString = hex(number)[2:]
    lengthToPad = len(hexString)
    zeros = (8 - lengthToPad) * '0'
    hexString = zeros + hexString
    
    n = 2

    return "0x" + ' 0x'.join([hexString[i:i+n] for i in range(0, len(hexString), n)])

with open("./data.txt", "r") as f:
    text = f.read()
    

output = []

for i in text.splitlines():
    i = i.replace('\\n', '\n').replace('\\t', '\t')
    if i[0] == ";":
      continue
    if i[0] == "S":
        for j in i[2:]:

            output.append((bytesFromNumber(int(ord(j))), ' ; ' + 'Letter: \''  + j.replace('\n', '\\n').replace('\t', '\\t') + '\''))
    else:

        output.append((bytesFromNumber(int(i[2:])),  ' ; Number: ' + i[2:]))



endList = []
numberConstants = bytesFromNumber(len(output))

endList.append(numberConstants + '; ' + str(len(output)) + ' constants\n')

endList.append(output[0][0] + output[0][1] + ', Index: 0')

index = 1
for numbers, comment in output[1:]:
    endList.append('\nCONST_SEPERATOR\n' + numbers + comment + ", Index: " + str(index) + " (" + hex(index) + ")")
    index += 1
endList.append('\nCONST_END')

print(''.join(endList))
with open("outputData.txt", 'w') as fo:
    fo.write(''.join(endList))