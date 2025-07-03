# Colliding Pendulum Simulation - C++

The simulation contains two pendulums and renders their motion physically accurate, taking in account the energy loss from the collision. The outcome is modifiable via 'adatok.txt' and runnable with 'Main.exe'. The program outputs 3 graphs. The first graph is the $\phi(t)$ function of the first pendulum without collisions. The second shows the same function of the first pendulum when the collisions are taken into account, and the third shows it for the second pendulum in the same system. 

The first line is datas of the first pendulum, meanwhile the second one holds the values for the second pendulum. The parameteres in 'adatok.txt' are the following:

- `phi0`: initial angular displacement  
- `L`: the length of the pendulum  
- `m`: the mass of the pendulum  
- `k`: a coefficient including the drag factor, the cross-sectional area, and the density  

