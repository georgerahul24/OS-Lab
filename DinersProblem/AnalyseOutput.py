# This program is to tabulate the output file

philosopherData = {
    "0": [0, 0, 0, 0],  # Alive, Think,Hungry,Eat,
    "1": [0, 0, 0, 0],
    "2": [0, 0, 0, 0],
    "3": [0, 0, 0, 0],
    "4": [0, 0, 0, 0]

}

with open("output.txt") as f:
    for line in f:
        if line[4] == "a":
            philosopherData[line[1]][0] += 1
        elif line[4] == "t":
            philosopherData[line[1]][1] += 1
        elif line[4] == "h":
            philosopherData[line[1]][2] += 1
        elif line[4] == "e":
            philosopherData[line[1]][3] += 1

for philosopher in philosopherData:
    print("Philosopher Number: ", philosopher)
    print("Philosopher Alive: ", philosopherData[philosopher][0])
    print("Philosopher Thinking: ", philosopherData[philosopher][1])
    print("Philosopher Hungry: ", philosopherData[philosopher][2])
    print("Philosopher Eating: ", philosopherData[philosopher][3])
    print("----"*10)
