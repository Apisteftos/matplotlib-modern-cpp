import matplotlib.pyplot as plt
import numpy as np

x = np.arange(1, 8)
y = np.array([2.3, 3.1, 4.5, 3.8, 5.2, 4.9, 6.1])


y_err = np.array([0.3, 0.5, 0.4, 0.6, 0.3, 0.5, 0.4])


y_err_asym = np.array([[0.2, 0.4, 0.3, 0.5, 0.2, 0.4, 0.3],
                        [0.4, 0.6, 0.5, 0.7, 0.4, 0.6, 0.5]])

x_err = np.array([0.1, 0.2, 0.1, 0.3, 0.1, 0.2, 0.1])

fig, axes = plt.subplots(2, 2, figsize=(12, 8))


axes[0, 0].errorbar(x, y, yerr=y_err, fmt='bo-', capsize=5)
axes[0, 0].set_title("Basic errorbar")
axes[0, 0].grid(True)

axes[0, 1].errorbar(x, y, yerr=y_err_asym, fmt='rs-', capsize=5)
axes[0, 1].set_title("Asymmetric errors")
axes[0, 1].grid(True)


axes[1, 0].errorbar(x, y, yerr=y_err, xerr=x_err,
                    fmt='g^-', capsize=5, ecolor='red',
                    elinewidth=2, capthick=2)
axes[1, 0].set_title("X and Y errors")
axes[1, 0].grid(True)


axes[1, 1].errorbar(x, y, yerr=y_err, fmt='none',
                    ecolor='purple', elinewidth=2, capsize=8, capthick=2)
axes[1, 1].plot(x, y, 'o', color='purple')
axes[1, 1].set_title("Error bars only")
axes[1, 1].grid(True)

fig.suptitle("errorbar examples")
fig.tight_layout()
plt.show()