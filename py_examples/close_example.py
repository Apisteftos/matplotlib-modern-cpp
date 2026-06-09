import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [10, 24, 36, 48, 55]


fig1 = plt.figure(1)
plt.plot(x, y, 'b')
plt.title("Figure 1")


fig2 = plt.figure(2)
plt.plot(x, y, 'r')
plt.title("Figure 2")

plt.show()

plt.close(fig1)        

plt.close(1)           

plt.close('all')
plt.close()             