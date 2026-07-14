import matplotlib.pyplot as plt
import numpy as np

categories = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun']
values1    = [4, 7, 3, 8, 5, 9]
values2    = [3, 5, 6, 4, 7, 6]
values3    = [2, 4, 5, 3, 6, 4]

x = np.arange(len(categories))
width = 0.25 

fig, axes = plt.subplots(2, 2, figsize=(12, 8), dpi=160)


axes[0, 0].bar(x, values1, color='blue', alpha=0.7)
axes[0, 0].set_title("Basic bar")
axes[0, 0].set_xticks(x)
axes[0, 0].set_xticklabels(categories)
axes[0, 0].grid(True, axis='y')


axes[0, 1].bar(x - width, values1, width, color='blue',  alpha=0.7, label='2022')
axes[0, 1].bar(x,         values2, width, color='red',   alpha=0.7, label='2023')
axes[0, 1].bar(x + width, values3, width, color='green', alpha=0.7, label='2024')
axes[0, 1].set_title("Grouped bar")
axes[0, 1].set_xticks(x)
axes[0, 1].set_xticklabels(categories)
axes[0, 1].legend()
axes[0, 1].grid(True, axis='y')


axes[1, 0].bar(x, values1, color='blue',  alpha=0.7, label='2022')
axes[1, 0].bar(x, values2, color='red',   alpha=0.7, label='2023', bottom=values1)
axes[1, 0].bar(x, values3, color='green', alpha=0.7, label='2024',
               bottom=np.array(values1) + np.array(values2))
axes[1, 0].set_title("Stacked bar")
axes[1, 0].set_xticks(x)
axes[1, 0].set_xticklabels(categories)
axes[1, 0].legend()
axes[1, 0].grid(True, axis='y')


axes[1, 1].barh(x, values1, color='purple', alpha=0.7)
axes[1, 1].set_title("Horizontal bar")
axes[1, 1].set_yticks(x)
axes[1, 1].set_yticklabels(categories)
axes[1, 1].grid(True, axis='x')

fig.suptitle("bar examples")
fig.tight_layout()
plt.show()