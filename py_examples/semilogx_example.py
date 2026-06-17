import matplotlib.pyplot as plt
import numpy as np

x = np.logspace(0, 4, 100)  
y1 = np.log(x)               
y2 = np.sqrt(x)              
y3 = x * 0.01               

fig, axes = plt.subplots(1, 2, figsize=(12, 5))


axes[0].semilogx(x, y1, 'b', label='log(x)')
axes[0].semilogx(x, y2, 'r', label='√x')
axes[0].semilogx(x, y3, 'g', label='x * 0.01')
axes[0].set_title("semilogx")
axes[0].set_xlabel("x (log scale)")
axes[0].set_ylabel("y (linear scale)")
axes[0].legend()
axes[0].grid(True, which='both')


axes[1].plot(x, y1, 'b', label='log(x)')
axes[1].plot(x, y2, 'r', label='√x')
axes[1].plot(x, y3, 'g', label='x * 0.01')
axes[1].set_title("linear (same data)")
axes[1].set_xlabel("x")
axes[1].set_ylabel("y")
axes[1].legend()
axes[1].grid(True)

fig.suptitle("semilogx vs linear")
fig.tight_layout()
plt.show()