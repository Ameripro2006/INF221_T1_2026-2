import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(BASE_DIR, '../data/measurements/results.csv')
PLOTS_DIR = os.path.join(BASE_DIR, '../data/plots')
os.makedirs(PLOTS_DIR, exist_ok=True)

df = pd.read_csv(CSV_PATH)
df['tipo'] = df['archivo'].apply(lambda x: x.split('_')[1])
df['dominio'] = df['archivo'].apply(lambda x: x.split('_')[2])

print(f"Cargados {len(df)} registros desde {CSV_PATH}")

# Convertir variables a numéricas por seguridad
df['tiempo_ms'] = pd.to_numeric(df['tiempo_ms'], errors='coerce')
df['memoria_kb'] = pd.to_numeric(df['memoria_kb'], errors='coerce')

# --- 1. Gráfico Global: Tiempo ---
prom_tiempo = df.groupby(['tamano', 'algoritmo'])['tiempo_ms'].mean().unstack()

plt.figure(figsize=(8, 5))
plt.plot(prom_tiempo.index, prom_tiempo['naive'], marker='o', label='Naive O(n³)', linewidth=2, color='#1f77b4')
plt.plot(prom_tiempo.index, prom_tiempo['strassen'], marker='s', label='Strassen O(n^2.81)', linewidth=2, color='#d95f02')
plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('Dimensión de la Matriz (N)', fontsize=11)
plt.ylabel('Tiempo Promedio (ms) [Escala Log]', fontsize=11)
plt.title('Comparativa de Tiempo: Naive vs Strassen', fontsize=13, pad=12)
plt.grid(True, which='both', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()
plt.savefig(os.path.join(PLOTS_DIR, 'tiempo_global_matrices.png'), dpi=300)
plt.close()

# --- 2. Gráfico Global: Memoria ---
prom_memoria = df.groupby(['tamano', 'algoritmo'])['memoria_kb'].mean().unstack()

plt.figure(figsize=(8, 5))
plt.plot(prom_memoria.index, prom_memoria['naive'], marker='o', linestyle='--', label='Naive', linewidth=2, color='#1f77b4')
plt.plot(prom_memoria.index, prom_memoria['strassen'], marker='s', linestyle='--', label='Strassen', linewidth=2, color='#d95f02')
plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('Dimensión de la Matriz (N)', fontsize=11)
plt.ylabel('Memoria Promedio (KB) [Escala Log]', fontsize=11)
plt.title('Comparativa de Memoria: Naive vs Strassen', fontsize=13, pad=12)
plt.grid(True, which='both', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()
plt.savefig(os.path.join(PLOTS_DIR, 'memoria_global_matrices.png'), dpi=300)
plt.close()

# --- Gráficos de Impacto en N=256 (Solo Tiempo, para mantener el reporte enfocado) ---
df_256 = df[df['tamano'] == 256]
width = 0.35

# Impacto por Tipo
prom_tipo = df_256.groupby(['tipo', 'algoritmo'])['tiempo_ms'].mean().unstack()
tipos = prom_tipo.index.tolist()
x = np.arange(len(tipos))

plt.figure(figsize=(8, 5))
plt.bar(x - width/2, prom_tipo['naive'], width, label='Naive', color='#1f77b4')
plt.bar(x + width/2, prom_tipo['strassen'], width, label='Strassen', color='#d95f02')
plt.yscale('log')
plt.xlabel('Estructura de la Matriz', fontsize=11)
plt.ylabel('Tiempo Promedio (ms)', fontsize=11)
plt.title('Impacto de la Estructura en N = 256', fontsize=13, pad=12)
plt.xticks(x, tipos, fontsize=11)
plt.grid(axis='y', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()
plt.savefig(os.path.join(PLOTS_DIR, 'impacto_tipo_matrices.png'), dpi=300)
plt.close()

# Impacto por Dominio
prom_dom = df_256.groupby(['dominio', 'algoritmo'])['tiempo_ms'].mean().unstack()
doms = prom_dom.index.tolist()
x = np.arange(len(doms))

plt.figure(figsize=(8, 5))
plt.bar(x - width/2, prom_dom['naive'], width, label='Naive', color='#1f77b4')
plt.bar(x + width/2, prom_dom['strassen'], width, label='Strassen', color='#d95f02')
plt.yscale('log')
plt.xlabel('Dominio de Valores (D0 vs D10)', fontsize=11)
plt.ylabel('Tiempo Promedio (ms)', fontsize=11)
plt.title('Impacto del Dominio de Valores en N = 256', fontsize=13, pad=12)
plt.xticks(x, doms, fontsize=11)
plt.grid(axis='y', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()
plt.savefig(os.path.join(PLOTS_DIR, 'impacto_dominio_matrices.png'), dpi=300)
plt.close()

print("Graficos de Matrices (Tiempo y Memoria) generados correctamente.")