"""Plots strong and weak scaling speedup and efficiency.

@author Akash Pallath
"""
import numpy as np
import matplotlib.pyplot as plt

procs = [1, 2, 4, 8, 12, 16]
times = []

for proc in procs:
    f = open("time_{}.txt".format(proc))

    for line in f:
        toks = line.strip().split()
        if len(toks) == 2 and toks[0] == "real":
            mmss = toks[1].split("m")
            min = int(mmss[0])
            sec = float(mmss[1][:-1])
            tp = min * 60 + sec
            times.append(tp)

    f.close()

procs = np.array(procs)
times = np.array(times)

# Strong scaling
speedup = times[0] / times
efficiency = times[0] / (procs * times)

print(speedup, efficiency)

# Plot
fig, ax = plt.subplots(1, 2, figsize=(12, 6), dpi=150)
ax[0].plot(procs, speedup, 'x-')
ax[0].plot(procs, procs, '--')
ax[0].set_xlabel(r"Number of processors, $p$")
ax[0].set_ylabel(r"Strong speedup, $S_p$")
ax[0].set_xlim([1, procs[-1]])
ax[0].set_ylim([1, procs[-1]])

ax[1].plot(procs, efficiency, 'x-')
ax[1].plot(procs, np.ones(len(procs)), '--')
ax[1].set_xlabel(r"Number of processors, $p$")
ax[1].set_ylabel(r"Strong scaling efficiency, $E_s$")
ax[1].set_xlim([1, procs[-1]])
ax[1].set_ylim([0, 1])

fig.suptitle("Intel Core i7 10700K @ 3.80 GHz, 8 cores, 16 threads")

fig.savefig("strong_scaling.png")
