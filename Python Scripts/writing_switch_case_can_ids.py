
f = open("can_msg.txt", "w")

# CAN BUS SIGNALS FROM 0x000 to 0x999
## 999 different cases to identify the can bus signal

f.write("switch(i){\n\n")

for i in range(275,282):
    f.write("\tcase " + str(i) + ":\n")
    f.write('\t\tSerial.println("Thats CAN ID 0x' + str(i) + '");\n')
    f.write("\t\tCAN.sendMsgBuf(0x" + str(i) + ", 0, 8, stmp);\n")
    f.write('\t\tbreak;\n\n')


f.write("\tdefault:\n")
f.write("\t\tbreak;\n\n")


f.write("}")
f.close()
