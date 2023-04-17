import matplotlib.pyplot as plt
x1 = []
y1 = []
x2 = []
y2 = []

x_g1 = []
y_g1 = []
x_r1 = []
y_r1 = []
x_g2 = []
y_g2 = []
x_r2 = []
y_r2 = []

with open('non-heuristic.txt', 'r') as file:
    i = 0;
    for line in file:
        if(i % 5 == 0) : 
            x, y, v = line.strip().split()
            x1.append(float(x))
            y1.append(float(y))
            if v == "0" :
                x_r1.append(float(x))
                y_r1.append(float(y))
            else :
                x_g1.append(float(x))
                y_g1.append(float(y))
        i+=1
with open('heuristic.txt', 'r') as file:
    i = 0;
    for line in file:
        if(i % 5 == 0) : 
            x, y, v = line.strip().split()
            x2.append(float(x))
            y2.append(float(y))
            if v == "0" :
                x_r1.append(float(x))
                y_r1.append(float(y))
            else :
                x_g1.append(float(x))
                y_g1.append(float(y))
        i+=1


plt.plot(x1, y1,'b-',label="Non-Heuristic")
plt.plot(x2,y2,'g-',label="Heuristic")


plt.plot(x_g1, y_g1, 'go', markersize=4, label='Valid Data')
plt.plot(x_r1, y_r1, 'ro', markersize=4, label='Invalid Data')
plt.title('SA')
plt.xlabel('Iteration')
plt.ylabel('Score')
# display plot
plt.legend()

plt.show()

