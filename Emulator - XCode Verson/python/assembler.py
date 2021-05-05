
# get binKeys.h and set binary keys:
binKeysStr = ''

binKeys = {}

with open("/Users/ericdiskin/Documents/code/code/c/Emulator - XCode Verson/Emulator - XCode Verson/BinKeys.h", "r") as binKeysFile:
    binKeysStr = binKeysFile.read()

for i in binKeysStr.splitlines():
    if i.strip().startswith("//") or i.strip() == "":
        continue
    if i.strip().startswith("#define") and not '//' in i:
        binKeys[i.split()[1]] = bytes.fromhex(i.split()[2].strip().replace("\\", "").replace("x", "").replace("'", ""))

file = ""

with open("/Users/ericdiskin/Documents/code/code/c/Emulator - XCode Verson/Emulator - XCode Verson/python/compiler/testProgram.starp.starpCode","r") as f:
    file = f.read()

file = file.split("\n")
noCommentsFile = []
for i in file:
    noCommentsFile.append(i.split(";")[0])

noCommentsFile = " ".join(noCommentsFile)

with open("/Users/ericdiskin/Library/Developer/Xcode/DerivedData/Emulator_-_XCode_Verson-bgutdxdelmtmxqdfbharumjtmmjp/Build/Products/Debug/out.emulate", "wb") as out:
    for i in noCommentsFile.split():
        if not i.startswith("0x"):
            out.write(binKeys[i])
        else:
            # the string is actually 0x6 or something, does not work, so pad it.
            if len(i) == 3:
                i = "0x0" + i[2:]
            numberString = int.from_bytes(bytearray.fromhex(i[2:]), byteorder='big', signed=True)
            out.write(bytearray.fromhex(i[2:]))
