import matplotlib.pyplot as plt
import numpy as np

x = np.logspace(0, 4, 100)  
y1 = x ** 2                  
y2 = x ** 0.5                
y3 = x                     

fig, axes = plt.subplots(1, 2, figsize=(12, 5))


axes[0].loglog(x, y1, 'b', label='x²')
axes[0].loglog(x, y2, 'r', label='√x')
axes[0].loglog(x, y3, 'g', label='x')
axes[0].set_title("loglog")
axes[0].set_xlabel("x (log scale)")
axes[0].set_ylabel("y (log scale)")
axes[0].legend()
axes[0].grid(True, which='both')  


axes[1].plot(x, y1, 'b', label='x²')
axes[1].plot(x, y2, 'r', label='√x')
axes[1].plot(x, y3, 'g', label='x')
axes[1].set_title("linear (same data)")
axes[1].set_xlabel("x")
axes[1].set_ylabel("y")
axes[1].legend()
axes[1].grid(True)

fig.suptitle("loglog vs linear")
fig.tight_layout()
plt.show()