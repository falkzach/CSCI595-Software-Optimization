import matplotlib.pyplot as plt


n = [4,16,64,256,1024,4096,16348,65536,262144,1048576]
c = [0.000559/4,0.000438/16,0.000398/64,0.000561/256,0.000386/1024,0.000468/4096,0.000589/16348,0.001195/65536,0.003389/262144,0.020226/1048576]
d = [0,0,0,0,0,0,0.000119/16384, 0.000724/65536, 0.002274/262144, 0.01319/1048576]

fig, ax1 = plt.subplots()
ax1.plot(n, c, 'b-')
ax1.set_xlabel('nxn')
ax1.set_ylabel('nxn naieve')

# ax1.annotate('L1 Data 2x32KBytes\nL1 Inst. 2x32KBytes\nL2 2x256KBytes\nL3 3MBytes', xy=(3, 1))

ax2 = ax1.twinx()
ax2.plot(n, d, 'r-')
ax2.set_ylabel('nxn recursive')

fig.tight_layout()
plt.show()
