import os
import pandas as pd
import matplotlib.pyplot as plt

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(BASE_DIR, "..", "data", "measurements", "results.csv")
PLOTS_DIR = os.path.join(BASE_DIR, "..", "data", "plots")
os.makedirs(PLOTS_DIR, exist_ok=True)

df = pd.read_csv(CSV_PATH)

def extract_type(archivo):
    parts = str(archivo).split('_')
    return parts[1] if len(parts) > 1 else 'desconocido'

df['tipo_orden'] = df['archivo'].apply(extract_type)

# Convertir a numérico, transformando TIMEOUT/CRASH en NaN, y eliminar esos NaN
df['tiempo_ms'] = pd.to_numeric(df['tiempo_ms'], errors='coerce')
df['memoria_kb'] = pd.to_numeric(df['memoria_kb'], errors='coerce')
df = df.dropna(subset=['tiempo_ms', 'memoria_kb'])
df = df[df['tiempo_ms'] > 0]

colores = {
    'mergesort': '#1f77b4',
    'quicksort': '#d62728',
    'sort': '#2ca02c',
    'patiencesort': '#9467bd'
}

for tipo in ['aleatorio', 'ascendente', 'descendente']:
    sub_df = df[df['tipo_orden'] == tipo]
    if sub_df.empty:
        continue

    # Agrupar por algoritmo y tamaño, calculando la media
    grouped = sub_df.groupby(['algoritmo', 'tamano'])[['tiempo_ms', 'memoria_kb']].mean().reset_index()

    # --- GRAFICO DE TIEMPO ---
    plt.figure(figsize=(9, 6))
    for algo in ['mergesort', 'quicksort', 'sort', 'patiencesort']:
        algo_data = grouped[grouped['algoritmo'] == algo].sort_values('tamano')
        if not algo_data.empty:
            plt.plot(algo_data['tamano'], algo_data['tiempo_ms'], marker='o', linewidth=2, label=algo, color=colores.get(algo, None))

    plt.title(f"Rendimiento de Tiempo - Caso {tipo.capitalize()}", fontsize=13, pad=12)
    plt.xlabel("Tamaño del Arreglo (n)", fontsize=11)
    plt.ylabel("Tiempo Promedio (ms)", fontsize=11)
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.legend(title="Algoritmo")
    plt.tight_layout()
    plt.savefig(os.path.join(PLOTS_DIR, f"tiempo_{tipo}.png"), dpi=300)
    plt.close()

    # --- GRAFICO DE MEMORIA ---
    plt.figure(figsize=(9, 6))
    for algo in ['mergesort', 'quicksort', 'sort', 'patiencesort']:
        algo_data = grouped[grouped['algoritmo'] == algo].sort_values('tamano')
        if not algo_data.empty:
            plt.plot(algo_data['tamano'], algo_data['memoria_kb'], marker='s', linewidth=2, linestyle='--', label=algo, color=colores.get(algo, None))

    plt.title(f"Consumo de Memoria - Caso {tipo.capitalize()}", fontsize=13, pad=12)
    plt.xlabel("Tamaño del Arreglo (n)", fontsize=11)
    plt.ylabel("Memoria Máxima (KB)", fontsize=11)
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.legend(title="Algoritmo")
    plt.tight_layout()
    plt.savefig(os.path.join(PLOTS_DIR, f"memoria_{tipo}.png"), dpi=300)
    plt.close()

print("Graficos de Sorting (Tiempo y Memoria) generados correctamente.")