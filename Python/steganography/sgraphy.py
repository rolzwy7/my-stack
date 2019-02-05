from PIL import Image
import argparse
import hashlib
import time
import sys
import pdb
import argparse

parser = argparse.ArgumentParser('Sgraphy - simple steganography module')

parser.add_argument('--base', help='PNG image (path)')
parser.add_argument('--hide', help='File to hide (path)')

parser.add_argument('--encode', help='Output file (path)')
parser.add_argument('--decode', help='Output file (path)')

args = parser.parse_args()

class Steganography():
         
    def __init__(self, base, hide=None):
        self.end_flag = "$END$"

        # Base - parameter init
        self.base_filename = base
        self.base_extension = self.base_filename.split(".")[-1]
        if self.base_extension != "png":
            print("[+] It's highly recommended use to PNG format. Convert your image.")
            exit(0)
        self.base_handle = Image.open(self.base_filename)
        # Check how many bits Base file can fit inside itself
        self.base_can_fit = self.base_handle.size[0] * self.base_handle.size[1] * 3
        kb = self.base_can_fit/8/1024
        mb = kb/1024
        print("[*] Base image can fit: %.4fKB | %.4fMB" % (kb, mb) )
        self.base_matrix = self.create_matrix(self.base_handle)

        # Hide - parameter init
        if hide != None:
            self.hide_filename = hide
            # Get required space for Hide file. Hide length * 8 to get number of bits
            with open(hide, "rb") as hide_:
                # Create Hide content holder
                self.hide_content = hide_.read()
                self.hide_required_space = len(self.hide_content) * 8
                hide_.close()
                
            if self.base_can_fit < self.hide_required_space + len(self.end_flag):
                print("[-] Hide file is too big for Base to fit in")
                exit()
    
    def create_matrix(self, handle):
        # Turn pixels into int array
        ret = []
        pixels = handle.load()
        for h in range(0, handle.size[0]):
            for w in range(0, handle.size[1]):
                ret.append(pixels[h, w][0])
                ret.append(pixels[h, w][1])
                ret.append(pixels[h, w][2])
        return ret

    def encode_check(self, original_binary_string, encoded_base_matrix_copy):
        # check if original Hide and encoded Hide are the same
        buffor = ""
        for element in encoded_base_matrix_copy:
            buffor += str(element % 2)

        print("[*] Sample original :", original_binary_string[0:25])
        print("[*] Sample decoded  :", buffor[0:25])

        print("[*] Precentage of pixels taken: %.2f%%" % (len(original_binary_string)/len(buffor)*100) )
            
        if buffor[0:len(original_binary_string)] == original_binary_string:
            print("[+] Encoded successfully")
        else:
            print("[-] Error. That really shouldn't happen")
            
    def encode(self, destination):
        base_matrix_copy = self.base_matrix
        # Add end flag string
        #base_matrix_copy += self.end_flag.encode("utf8")
        # Load Hide content as very long string of zeros and ones
        binary_string = ""
        for ch in self.hide_content:
            holder = str(bin(ch))[2:]
            holder = (8-len(holder))*'0' + holder
            binary_string += holder

        # Encode Hide in Base matrix
        for it in range(0, len(base_matrix_copy)):
            # break if iterator gets out of binary_string's range
            if it >= len(binary_string):
                break
            
            # if 1 in binary_string
            if int(binary_string[it]):
                if base_matrix_copy[it] % 2 != 1:
                    base_matrix_copy[it] = base_matrix_copy[it] + 1 if base_matrix_copy[it] < 255 else base_matrix_copy[it] - 1    
            # if 0 in binary_string 
            else:
                if base_matrix_copy[it] % 2 != 0:
                    base_matrix_copy[it] = base_matrix_copy[it] + 1 if base_matrix_copy[it] < 255 else base_matrix_copy[it] - 1
                    
        # final check
        self.encode_check(binary_string, base_matrix_copy)

        # Replace original pixels with encoded pixels
        base_handle_copy = self.base_handle
        pixels = base_handle_copy.load()
        it = 0
        for h in range(0, base_handle_copy.size[0]):
            for w in range(0, base_handle_copy.size[1]):
                pixels[h, w] = tuple(base_matrix_copy[3*it:3*(it+1)])
                it += 1

        print("[*] Saving encoded image: %s" % destination)     
        base_handle_copy.save(destination, format='PNG', subsampling=0, quality=100)

    def decode(self, destination):
        decimal_array = []
        buffor = ""
        arr = self.create_matrix(self.base_handle)

        flag_search = "0" * len(self.end_flag)
        for a in arr:
            buffor += "1" if a % 2 == 1 else "0"
            if len(buffor) == 8:
                decimal_array.append(int(buffor, 2))

                # Search for finishing flag
                flag_search = flag_search[1:] + chr(int(buffor, 2))
                if flag_search == self.end_flag:
                    decimal_array = decimal_array[0:-1*len(self.end_flag)]
                    break
                
                buffor = ""

        with open(destination, "wb") as file_:
            file_.write(bytes(decimal_array))
            file_.close()
        
# Single file
if args.base and not args.hide:
    object_ = Steganography(args.base)
    if args.decode:
        object_.decode(args.decode)
        exit()
    
# Two files
if args.base and args.hide:
    object_ = Steganography(args.base, args.hide)
    if args.encode:
        object_.encode(args.encode)
    exit()

parser.print_help()
