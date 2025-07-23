def receptor_hamming(trama):
    bits = list(map(int, list(trama)))
    p1 = bits[0]
    p2 = bits[1]
    d3 = bits[2]
    p4 = bits[3]
    d5 = bits[4]
    d6 = bits[5]
    d7 = bits[6]
    s1 = p1 ^ d3 ^ d5 ^ d7
    s2 = p2 ^ d3 ^ d6 ^ d7
    s4 = p4 ^ d5 ^ d6 ^ d7

    syndrome = s4 * 4 + s2 * 2 + s1 * 1

    if syndrome == 0:
        print("No se detectaron errores.")
    elif syndrome > 0 and syndrome <= 7:
        print(f"Se detectó un error en la posición: {syndrome}")
        bits[syndrome - 1] ^= 1  
        print(f"Trama corregida: {''.join(map(str, bits))}")
    else:
        print("Error -> fuera del alcance de corrección")

    datos = [bits[2], bits[4], bits[5], bits[6]]
    mensaje_original = ''.join(map(str, datos))
    print(f"Mensaje original extraído: {mensaje_original}")

if __name__ == "__main__":
    trama = input("Ingrese la trama recibida (7 bits): ")
    receptor_hamming(trama)
