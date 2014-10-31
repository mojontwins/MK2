' generador de passwords

Function pex (va as uByte, dummy as uByte) as String
	pex = Chr (va + 65)
End Function

Dim As Integer level, p_life, coins, checksum

Print "Generador de passwords para Ninjajar!"
Input "Nivel (0 es el primero) "; level
Input "Vidas"; p_life
Input "Monedas"; coins

if level > 99 or p_life > 99 or coins > 99 then 
	? "No te cuele coone"
	System
End If

checksum = ((p_life Shl 2) + (level Shl 1) + coins) Mod 256

Print pex (p_life And 15, 1);
Print pex (level Shr 4, 1);
Print pex (coins And 15, 1);
Print pex (checksum Shr 4, 1);
Print pex (checksum And 15, 1);
Print pex (coins Shr 4, 1);
Print pex (level And 15, 1);
Print pex (p_life Shr 4, 1);
Print
sleep
