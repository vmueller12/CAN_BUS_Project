f = open("can_msg_short.txt", "w")

# CAN BUS SIGNALS FROM 0x000 to 0x999
## 999 different cases to identify the can bus signal
for i in range(270,281):

    if i < 100:
        f.write("\t\tCAN.sendMsgBuf(0x0" + str(i) + ", 0, 8, stmp);\n")
    else:
        f.write("\t\tCAN.sendMsgBuf(0x" + str(i) + ", 0, 8, stmp);\n")
  
f.close()
