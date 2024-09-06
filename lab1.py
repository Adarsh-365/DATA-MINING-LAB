#1. Creation of Transaction Database in a file using only file operations Create td.txt file and store transactions 
#
with open("Td1.txt","w")as f:
    f.write("T1 a b c e\n") 
    f.write("T2 b d f\n")
    f.write("T3 a c d f\n") 
    f.write("T4 d f\n")
    f.write("T5 c d e")