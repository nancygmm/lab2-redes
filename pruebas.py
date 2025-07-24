import subprocess
import os

def extraer_trama_del_emisor(mensaje):
    try:
        result = subprocess.run(["./hamming_emisor"],
                              input=mensaje + "\n",
                              capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"Error ejecutando emisor: {result.stderr}")
            return None
        
        for line in result.stdout.split('\n'):
            if "Trama Hamming extendida generada" in line:
                parts = line.split(": ")
                if len(parts) >= 3:  
                    trama = parts[-1].strip()  
                    
                    if len(trama) == 16 and all(c in '01' for c in trama):
                        return trama
                    else:
                        print(f"Trama extraída inválida: '{trama}' (longitud: {len(trama)})")
                        return None
        
        print(" No se pudo encontrar trama en la salida del emisor")
        return None
        
    except Exception as e:
        print(f"Error: {e}")
        return None

def ejecutar_receptor(trama):
    try:
        result = subprocess.run(["python3", "hamming_receptor.py"],
                              input=trama + "\n",
                              capture_output=True, text=True)
        return result.stdout.strip()
    except Exception as e:
        return f"Error ejecutando receptor: {e}"

def introducir_error(trama, posicion):
    if 0 <= posicion < len(trama):
        trama_lista = list(trama)
        trama_lista[posicion] = '1' if trama_lista[posicion] == '0' else '0'
        return ''.join(trama_lista)
    return trama

def main():
    print("PRUEBAS HAMMING")
    print("="*60)
    
    print("Compilando emisor...")
    result = subprocess.run(["g++", "-o", "hamming_emisor", "hamming_emisor.cpp"],
                          capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error compilando: {result.stderr}")
        return
    print("Emisor compilado exitosamente")
    
    mensajes = ["10110101001", "11111111111", "00000000000"]
    
    print(f"\n{'='*60}")
    print("CASO 1: SIN ERRORES")
    print("="*60)
    
    for i, mensaje in enumerate(mensajes, 1):
        print(f"\n--- Prueba {i} ---")
        print(f"Mensaje: {mensaje}")
        
        trama = extraer_trama_del_emisor(mensaje)
        if not trama:
            print("No se pudo generar trama")
            continue
        
        print(f"Trama:   {trama}")
        
        resultado = ejecutar_receptor(trama)
        print(f"Receptor dice:")
        print(resultado)
    

    print(f"\n{'='*60}")
    print("CASO 2: UN ERROR")
    print("="*60)
    
    for i, mensaje in enumerate(mensajes, 1):
        print(f"\n--- Prueba {i} ---")
        print(f"Mensaje: {mensaje}")
        
        trama = extraer_trama_del_emisor(mensaje)
        if not trama:
            print("No se pudo generar trama")
            continue
        
        print(f"Trama original: {trama}")
        
        pos_error = (i + 2) % 16  
        trama_con_error = introducir_error(trama, pos_error)
        
        print(f"Error en posición {pos_error + 1}: {trama_con_error}")
        print(f"Comparación:")
        print(f"    Original: {trama}")
        print(f"    Con error: {trama_con_error}")
        
        diferencia = "           "
        for j, (a, b) in enumerate(zip(trama, trama_con_error)):
            if a != b:
                diferencia += "!"
            else:
                diferencia += " "
        print(f"    {diferencia}")
        
        resultado = ejecutar_receptor(trama_con_error)
        print(f"🔍 Receptor dice:")
        print(resultado)
    
    print(f"\n{'='*60}")
    print("CASO 3: MÚLTIPLES ERRORES")
    print("="*60)
    
    for i, mensaje in enumerate(mensajes, 1):
        print(f"\n--- Prueba {i} ---")
        print(f"Mensaje: {mensaje}")
        
        trama = extraer_trama_del_emisor(mensaje)
        if not trama:
            print("No se pudo generar trama")
            continue
        
        print(f"Trama original: {trama}")
        
        pos1, pos2 = i % 16, (i + 7) % 16
        trama_con_errores = introducir_error(trama, pos1)
        trama_con_errores = introducir_error(trama_con_errores, pos2)
        
        print(f"Errores en posiciones {pos1 + 1} y {pos2 + 1}: {trama_con_errores}")
        print(f"Comparación:")
        print(f"    Original:   {trama}")
        print(f"    Con errores: {trama_con_errores}")
        
        diferencia = "                "
        for j, (a, b) in enumerate(zip(trama, trama_con_errores)):
            if a != b:
                diferencia += "!"
            else:
                diferencia += " "
        print(f"    {diferencia}")
        
        resultado = ejecutar_receptor(trama_con_errores)
        print(f"Receptor dice:")
        print(resultado)
    
    if os.path.exists("hamming_emisor"):
        os.remove("hamming_emisor")
    

if __name__ == "__main__":
    main()