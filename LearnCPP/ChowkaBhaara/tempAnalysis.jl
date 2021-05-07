



###### Calculating q -> amount of heat transferred by 1 person to the surroundings
## assuming 100% convection

h = 3.3 #W/m^2K heat transfer co-efficient
A_exposed = 1.5 #metre # area of body exposed to ambient
δT = 33 - 21.5 #Kelvin;
time = 3*60 # time since lunch break,  current time 16.42
q = h*A_exposed*δT*time 

Q_total = 7*q ;


rho = 1.1839 ; #kg/m^3
Cp = 1.005*10^3 ; #J/KgK
area =  10.6*13; #m^2
height = 3 ; #m
volume = area*height ;
mass = rho*volume ;
 
dt = Q_total/(mass*Cp)