import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Rutas absolutas/relativas segun estructura del proyecto
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(BASE_DIR, '../data/measurements/results.csv')
PLOTS_DIR = os.path.join(BASE_DIR, '../data/plots')

os.makedirs(PLOTS_DIR, exist_ok=True)

# Carga y parseo de datos
df = pd.read_csv(CSV_PATH)
df['tipo'] = df['archivo'].apply(lambda x: x.split('_')[1])
df['dominio'] = df['archivo'].apply(lambda x: x.split('_')[2])

print(f"Cargados {len(df)} registros desde {CSV_PATH}")

# -------------------------------------------------------------
# 1. Grafico Global: Escala de N vs Tiempo (Naive vs Strassen)
# -------------------------------------------------------------
prom_global = df.groupby(['tamano', 'algoritmo'])['tiempo_ms'].mean().unstack()

plt.figure(figsize=(8, 5))
plt.plot(prom_global.index, prom_global['naive'], marker='o', label='Naive O(n³)', linewidth=2, color='#1f77b4')
plt.plot(prom_global.index, prom_global['strassen'], marker='s', label='Strassen O(n^2.81)', linewidth=2, color='#d95f02')

plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('Dimensión de la Matriz (N)', fontsize=11)
plt.ylabel('Tiempo Promedio (ms) [Escala Log]', fontsize=11)
plt.title('Comparativa General: Naive vs Strassen', fontsize=13, pad=12)
plt.grid(True, which='both', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()

plot1_path = os.path.join(PLOTS_DIR, 'comparativa_global_matrices.png')
plt.savefig(plot1_path, dpi=300)
plt.close()
print(f"Guardado: {plot1_path}")

# -------------------------------------------------------------
# 2. Grafico de Impacto por Tipo de Matriz (en N = 256)
# -------------------------------------------------------------
df_256 = df[df['tamano'] == 256]
prom_tipo = df_256.groupby(['tipo', 'algoritmo'])['tiempo_ms'].mean().unstack()

tipos = prom_tipo.index.tolist()
x = np.arange(len(tipos))
width = 0.35

plt.figure(figsize=(8, 5))
plt.bar(x - width/2, prom_tipo['naive'], width, label='Naive', color='#1f77b4')
plt.bar(x + width/2, prom_tipo['strassen'], width, label='Strassen', color='#d95f02')

plt.yscale('log')
plt.xlabel('Estructura de la Matriz', fontsize=11)
plt.ylabel('Tiempo Promedio (ms) [Escala Log]', fontsize=11)
plt.title('Impacto de la Estructura Matricial en N = 256', fontsize=13, pad=12)
plt.xticks(x, tipos, fontsize=11)
plt.grid(axis='y', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()

plot2_path = os.path.join(PLOTS_DIR, 'impacto_tipo_matrices.png')
plt.savefig(plot2_path, dpi=300)
plt.close()
print(f"Guardado: {plot2_path}")

# -------------------------------------------------------------
# 3. Grafico de Impacto por Dominio (D0 vs D10 en N = 256)
# -------------------------------------------------------------
prom_dom = df_256.groupby(['dominio', 'algoritmo'])['tiempo_ms'].mean().unstack()

doms = prom_dom.index.tolist()
x = np.arange(len(doms))

plt.figure(figsize=(8, 5))
plt.bar(x - width/2, prom_dom['naive'], width, label='Naive', color='#1f77b4')
plt.bar(x + width/2, prom_dom['strassen'], width, label='Strassen', color='#d95f02')

plt.yscale('log')
plt.xlabel('Dominio de Valores (D0: {0,1} vs D10: {0..10})', fontsize=11)
plt.ylabel('Tiempo Promedio (ms) [Escala Log]', fontsize=11)
plt.title('Impacto del Dominio de Valores en N = 256', fontsize=13, pad=12)
plt.xticks(x, doms, fontsize=11)
plt.grid(axis='y', ls='--', alpha=0.5)
plt.legend(fontsize=11)
plt.tight_layout()

plot3_path = os.path.join(PLOTS_DIR, 'impacto_dominio_matrices.png')
plt.savefig(plot3_path, dpi=300)
plt.close()
print(f"Guardado: {plot3_path}")