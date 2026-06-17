import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 10, 100)
y1 = np.exp(x)        
y2 = np.exp(x * 0.5)  
y3 = np.exp(x * 0.2)  

fig, axes = plt.subplots(1, 2, figsize=(12, 5))


axes[0].semilogy(x, y1, 'b', label='e^x')
axes[0].semilogy(x, y2, 'r', label='e^0.5x')
axes[0].semilogy(x, y3, 'g', label='e^0.2x')
axes[0].set_title("semilogy")
axes[0].set_xlabel("x (linear scale)")
axes[0].set_ylabel("y (log scale)")
axes[0].legend()
axes[0].grid(True, which='both')


axes[1].plot(x, y1, 'b', label='e^x')
axes[1].plot(x, y2, 'r', label='e^0.5x')
axes[1].plot(x, y3, 'g', label='e^0.2x')
axes[1].set_title("linear (same data)")
axes[1].set_xlabel("x")
axes[1].set_ylabel("y")
axes[1].legend()
axes[1].grid(True)

fig.suptitle("semilogy vs linear")
fig.tight_layout()
plt.show()