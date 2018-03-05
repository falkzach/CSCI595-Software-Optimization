import matplotlib.pyplot as plt


l = [1.3, 1.35, 1.4, 1.45, 1.5, 1.55, 1.6, 1.61]
c = [13, 13, 12, 12, 12, 11, 11, 11]
d = [101348, 124868, 67564, 80732, 109044, 52028, 61264, 63040]

fig, ax1 = plt.subplots()
ax1.plot(l, c, 'b-')
ax1.set_xlabel('lambda')
ax1.set_ylabel('copies')

ax2 = ax1.twinx()
ax2.plot(l, d, 'r-')
ax2.set_ylabel('max mem diff')

fig.tight_layout()
plt.show()
