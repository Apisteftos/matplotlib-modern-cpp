import matplotlib.pyplot as plt

fig1 = plt.figure(1, label="sine_plot")
plt.plot([1, 2, 3], [1, 4, 9])

fig2 = plt.figure(2, label="cosine_plot")
plt.plot([1, 2, 3], [1, 2, 3])

fig3 = plt.figure(3, label="bar_plot")
plt.bar([1, 2, 3], [5, 3, 7])


nums = plt.get_fignums()
print(nums)         


labels = plt.get_figlabels()
print(labels)       


for num, label in zip(plt.get_fignums(), plt.get_figlabels()):
    print(f"Figure {num}: {label}")


for fig in map(plt.figure, plt.get_fignums()):
    if fig.get_label() == "bar_plot":
        plt.close(fig)

plt.show()