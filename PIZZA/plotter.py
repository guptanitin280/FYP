import matplotlib.pyplot as plt

# read file and extract data into lists
x_values = []
y_values = []
with open('ip.txt', 'r') as file:
    for line in file:
        x, y = line.strip().split()
        x_values.append(float(x))
        y_values.append(float(y))

# create and customize plot
plt.plot(x_values, y_values)
plt.title('ACO')
plt.xlabel('Iteration')
plt.ylabel('Number of clients')

# display plot
plt.show()