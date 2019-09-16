# UBCO-Aerospace-Club
This is a program to simulate the launch, and landing of a model rocket for the UBCO Aerospace Club.

We take into account drag, gravity, and motor thrust for this model:
$$\Sigma F=F_{Drag}+F_{Thrust}+F_{g}$$

We vary mass with thrust:
Assume $$m_{discrete loss rate}=\frac{\Sigma_{i=0}^{t} F_{Thrust}(t) }{m_{loss}}$$