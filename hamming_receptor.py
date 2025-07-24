def receptor_hamming(trama):
    if len(trama) != 16 or any(c not in '01' for c in trama):
        print("Error: La trama debe tener exactamente 16 bits binarios.")
        return

    bits = [' '] + list(map(int, trama))
    syndrome = 0

    for p in [1, 2, 4, 8]:
        suma = 0
        for i in range(1, 16):
            if i & p:
                suma ^= bits[i]
        if suma == 1:
            syndrome += p

    paridad_total = sum(bits[1:16]) % 2
    paridad_correcta = (paridad_total == bits[16])

    if syndrome == 0 and paridad_correcta:
        print("Trama sin errores detectados.")
    elif syndrome != 0 and not paridad_correcta:
        print("Se detectaron 2 errores. Trama descartada.")
        return
    elif syndrome != 0 and paridad_correcta:
        print(f"Error de 1 bit detectado en posición {syndrome}. Corrigiendo...")
        bits[syndrome] ^= 1
    elif syndrome == 0 and not paridad_correcta:
        print("Error en el bit de paridad general. Trama descartada.")
        return

    datos = [bits[i] for i in range(1, 16) if (i & (i - 1)) != 0]
    mensaje = ''.join(map(str, datos))
    print(f"Mensaje original extraído: {mensaje}")

if __name__ == "__main__":
    trama = input("Ingrese la trama recibida (16 bits): ")
    receptor_hamming(trama)
