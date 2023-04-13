import matplotlib.pyplot as plt

# read file and extract data into lists
x_values = []
y_values = []

# x_values2 = []
# y_values2 = []
#
x_values3 = []
y_values3 = []

itr=200
i=0

with open('ip.txt', 'r') as file:
    for line in file:
        x, y = line.strip().split()
        if i//itr == 0:
            x_values.append(float(x))
            y_values.append(float(y))
        else:
            x_values3.append(float(x))
            y_values3.append(float(y))
        i+=1



# create and customize plot
plt.plot(x_values, y_values,'r',label="Non-Heuristic")
# plt.plot(x_values2, y_values2,'b',label="randomGreedy")
plt.plot(x_values3,y_values3,'g',label="Heuristic")
plt.title('ACO')
plt.xlabel('Iteration')
plt.ylabel('Score')
# display plot
plt.show()

