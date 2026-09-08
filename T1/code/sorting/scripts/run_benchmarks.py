import subprocess
import glob
import os


BIN_DIR = "bin"
INPUT_DIR = "data/array_input"
MEASUREMENTS_DIR = "data/measurements"
CSV_FILE = os.path.join(MEASUREMENTS_DIR, "results.csv")
TIMEOUT_SEC = 60  # 1 minuto máximo por prueba


os.makedirs(MEASUREMENTS_DIR, exist_ok=True)


if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, "w") as f:
        f.write("algoritmo,archivo,tamano,tiempo_ms,memoria_kb,ordenado\n")

algoritmos = ["mergesort", "quicksort", "sort", "patiencesort"]
archivos_txt = sorted(glob.glob(os.path.join(INPUT_DIR, "*.txt")))

print(f"Se encontraron {len(archivos_txt)} archivos para procesar.")

for algo in algoritmos:
    bin_path = os.path.join(BIN_DIR, algo)
    if not os.path.exists(bin_path):
        print(f"ADVERTENCIA: No se encontro el binario {bin_path}. Ejecuta 'make' primero.")
        continue

    for archivo in archivos_txt:
        archivo_name = os.path.basename(archivo).replace('.txt', '')
        try:
            tamano = archivo_name.split('_')[0]
        except:
            tamano = "0"

        print(f"[{algo}] Evaluando {archivo_name}...", end=" ", flush=True)

        try:
            result = subprocess.run(
                [f"./{bin_path}", archivo],
                timeout=TIMEOUT_SEC,
                capture_output=True
            )
            
            if result.returncode == 0:
                print("OK")
            elif result.returncode < 0:
                print(f"CRASH (Señal {-result.returncode} - Posible Stack Overflow)")
                
                with open(CSV_FILE, "a") as f:
                    f.write(f"{algo},{archivo_name},{tamano},CRASH,CRASH,no\n")
            else:
                print(f"ERROR (Código {result.returncode})")
                
        except subprocess.TimeoutExpired:
            print(f"TIMEOUT (Superó los {TIMEOUT_SEC}s)")
            
            with open(CSV_FILE, "a") as f:cd code/sorting/
                f.write(f"{algo},{archivo_name},{tamano},TIMEOUT,TIMEOUT,no\n")

print("\n¡Benchmarks finalizados! Revisa data/measurements/results.csv")