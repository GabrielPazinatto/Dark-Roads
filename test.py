correct_out = open("./output_trabalho_grafos_cont.txt")
my_out = open("./output3.txt")

correct_lines = correct_out.read().splitlines()
my_lines = my_out.read().splitlines()

i = 1
correct= True

for correct_line, my_line in zip(correct_lines, my_lines):
    if(correct_line != my_line):
        correct = False
        print("Error found at line: " + i)
    i = i +1
    
if not correct:
    print("A problem was found.")
else:
    print("All answers are correct.")