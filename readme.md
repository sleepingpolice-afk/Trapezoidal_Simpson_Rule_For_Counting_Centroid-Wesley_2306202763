# Proyek UAS: Penerapan Trapezoidal Rule dan Simpson’s 1/3 Rule Untuk Menghitung Centroid

```text
Nama: Wesley Frederick Oh
NPM: 2306202763
Kelas: Komnum-01
```

## Deskripsi Proyek
- TrapSimp.c
  Deskripsi singkat : 
  Program C untuk mencari centroid sebuah objek 2-dimensi dengan integrasi numerik Newton-Cotes dengan dua cara:
     - Aturan trapesium
     - Aturan 1/3 Simpson
  
  Program bekerja dengan mencari nilai centroid untuk sumbu x dan sumbu y yang direpresentasikan dengan $\bar{x}$ dan $\bar{y}$, serta mencari luas bangun dua dimensi di $A$ dengan menggunakan pendekatan aturan trapesium dan 1/3 simpson, dengan jumlah iterasi sesuai dengan jumlah segment yang diinput ke dalam program. Dalam kasus ini, centroid yang ingin dicari adalah sebagai berikut:

  ![picture 3](https://i.imgur.com/RVvPuH7.png)  

  Alur program:
  - Program meminta input berupa jumlah segment start, step, dan finish untuk jumlah segment awal, jumlah interval segmen, dan jumlah akhir segment.
  - Kemudian program menghitung centroid di $\bar{x}$ dan $\bar{y}$ beserta dengan luas $A$, serta menyimpan hasil perhitungannya ke file output berupa csv. Sebagai tambahan, pada setiap iterasi program juga dapat menghitung deviasi nilai untuk semua nilai, yang disimbolkan dalam $\Delta A$, $\Delta \bar{x}$, $\Delta \bar{y}$


- output.csv dan output.xlsx

  Output.csv berisi tentang output mentah yang dikeluarkan oleh program, agar nantinya dapat lebih mudah untuk diambil datanya dan dianalisis lebih lanjut. Kemudian Output.xlsx adalah file excel berisi tentang analisis data dari file csv sebelumnya, serta menggambarkan beberapa grafik sebagai visualisasi data.

- ProyekUAS_2306202763_Wesley.pdf
  File PDF laporan secara lengkap, dengan template Overleaf LaTeX.
  Dokumen LaTeX diolah dengan MikTeX dan Texmaker di Windows 11

- ProyekUAS_2306202763_Wesley.ppt (file PPT untuk presentasi video)