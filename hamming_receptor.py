def receptor_hamming(trama):
    if len(trama) != 15 or any(c not in '01' for c in trama):
        print("Error: Debes ingresar exactamente 15 bits binarios.")
        return

    bits = [' '] + list(map(int, trama)) 
    error_pos = 0

    print("Verificando bits de paridad:")

    for p in [1, 2, 4, 8]:
        suma = 0
        for i in range(1, 16):
            if i & p:
                suma ^= bits[i]
        print(f"  R{p} = {suma}")
        if suma == 1:
            error_pos += p

    if error_pos == 0:
        print("No se detectaron errores.")
    elif error_pos >= 1 and error_pos <= 15:
        print(f"Se detectó y se puede corregir 1 error en la posición {error_pos}.")
        bits[error_pos] ^= 1  
    else:
        print("Error fuera del rango de corrección.")

    datos = [bits[i] for i in range(1, 16) if (i & (i - 1)) != 0]
    mensaje = ''.join(map(str, datos))
    print(f"Mensaje original extraído: {mensaje}")

if __name__ == "__main__":
    trama = input("Ingrese la trama recibida (15 bits): ")
    receptor_hamming(trama)
