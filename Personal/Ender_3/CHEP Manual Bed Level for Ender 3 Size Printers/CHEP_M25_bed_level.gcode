; *** This version is for 32 Bit Ender 3 using M25 Pause  **** 
Bed leveling Ender 3 by ingenioso3D
; Modified by elproducts CHEP FilamentFriday.com
; Version 2.0 Replaced G10 with G25 per Cobberton suggestion
; Version 3.0 Fixed missing 1st step
; Version 4.0 Added F3000 to speed up movement

G90

G28 ; Home all axis
M25 ; 
G1 Z5 ; Lift Z axis
G1 X32 Y36 F3000; Move to Position 1
G1 Z0
M25 ; Pause print
G1 Z10 ; Lift Z axis
G1 X32 Y206 F3000; Move to Position 2
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X202 Y206 F3000; Move to Position 3
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X202 Y36 F3000; Move to Position 4
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X117 Y121 F3000; Move to Position 5
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X32 Y206 F3000; Move to Position 2
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X202 Y206 F3000; Move to Position 3
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X202 Y36 F3000; Move to Position 4
G1 Z0
M25 ; Pause print
G1 Z5 ; Lift Z axis
G1 X32 Y36 F3000; Move to Position 1
G1 Z0
M25 ; Pause print

G28;
M84 ; disable motors



