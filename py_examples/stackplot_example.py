import matplotlib.pyplot as plt
import numpy as np

x = np.arange(1, 13)  


solar   = np.array([2, 3, 5, 7, 9, 11, 12, 11, 8, 5, 3, 2], dtype=float)
wind    = np.array([6, 7, 6, 5, 4,  3,  3,  4, 5, 6, 7, 7], dtype=float)
hydro   = np.array([8, 7, 6, 5, 4,  3,  3,  4, 5, 6, 7, 8], dtype=float)
nuclear = np.array([5, 5, 5, 5, 5,  5,  5,  5, 5, 5, 5, 5], dtype=float)

months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
          'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']

fig, axes = plt.subplots(2, 2, figsize=(14, 10))


axes[0, 0].stackplot(x, solar, wind, hydro, nuclear,
                     labels=['Solar', 'Wind', 'Hydro', 'Nuclear'],
                     colors=['gold', 'steelblue', 'mediumseagreen', 'tomato'],
                     alpha=0.8)
axes[0, 0].set_title("Energy Mix — baseline='zero'")
axes[0, 0].set_xticks(x)
axes[0, 0].set_xticklabels(months, rotation=45)
axes[0, 0].set_ylabel("GWh")
axes[0, 0].legend(loc='upper left')
axes[0, 0].grid(True, alpha=0.3)


axes[0, 1].stackplot(x, solar, wind, hydro, nuclear,
                     labels=['Solar', 'Wind', 'Hydro', 'Nuclear'],
                     colors=['gold', 'steelblue', 'mediumseagreen', 'tomato'],
                     baseline='sym',
                     alpha=0.8)
axes[0, 1].set_title("baseline='sym'")
axes[0, 1].set_xticks(x)
axes[0, 1].set_xticklabels(months, rotation=45)
axes[0, 1].set_ylabel("GWh")
axes[0, 1].legend(loc='upper left')
axes[0, 1].grid(True, alpha=0.3)


axes[1, 0].stackplot(x, solar, wind, hydro, nuclear,
                     labels=['Solar', 'Wind', 'Hydro', 'Nuclear'],
                     colors=['gold', 'steelblue', 'mediumseagreen', 'tomato'],
                     baseline='wiggle',
                     alpha=0.8)
axes[1, 0].set_title("baseline='wiggle' (streamgraph)")
axes[1, 0].set_xticks(x)
axes[1, 0].set_xticklabels(months, rotation=45)
axes[1, 0].legend(loc='upper left')
axes[1, 0].grid(True, alpha=0.3)


axes[1, 1].stackplot(x, solar, wind, hydro, nuclear,
                     labels=['Solar', 'Wind', 'Hydro', 'Nuclear'],
                     colors=['gold', 'steelblue', 'mediumseagreen', 'tomato'],
                     baseline='weighted_wiggle',
                     alpha=0.8)
axes[1, 1].set_title("baseline='weighted_wiggle'")
axes[1, 1].set_xticks(x)
axes[1, 1].set_xticklabels(months, rotation=45)
axes[1, 1].legend(loc='upper left')
axes[1, 1].grid(True, alpha=0.3)

fig.suptitle("stackplot — Energy Mix over 12 months", fontsize=14)
fig.tight_layout()
fig.savefig("../pics/stackplot_py_example.png")
plt.show()