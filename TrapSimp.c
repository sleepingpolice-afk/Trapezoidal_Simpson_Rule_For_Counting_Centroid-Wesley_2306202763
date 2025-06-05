/*----------------------------------------------------------------------------*
 * Tugas Komputasi Numerik
 * Nama program : TrapSimp.c
 * Deskripsi    : Program C untuk mencari centroid sebuah objek 2-dimensi
 *                dengan integrasi numerik Newton-Cotes dengan dua cara:
 *                - Aturan trapesium
 *                - Aturan 1/3 Simpson
 *
 * Nama : Wesley Frederick Oh
 * NPM  : 2306202763
 *----------------------------------------------------------------------------*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI                3.14159265358979323846 // 20 decimal places
#define CONST_NAMA_FILE   "output.csv"


//-------------- FUNGSI-FUNGSI DASAR --------------
// Definisi fungsi f(x) dan g(x)
//-------------------------------------------------

// F(x) = x
double fungsi_Fx (double x) {
    return x;
}

// G(x) = -3.sin(pi.x/6).exp(-0.01*x^1.5) 
double fungsi_Gx (double x) {
    return -3.0 * sin(PI*x/6.0) * exp(-0.01*pow(x,1.50));
}


//-------------------------- FUNGSI-FUNGSI TAMBAHAN -------------------------
// Fungsi-fungsi di bawah ini dibuat berdasarkan definisi
// dari fungsi-fungsi dasar di atas.
// Fungsi-fungsi ini diperlukan untuk integrasi dalam menghitung centroid
//---------------------------------------------------------------------------

// Fungsi f(x)-g(x)
double fungsi_Fx_minus_Gx (double x) {
    return fungsi_Fx(x) - fungsi_Gx(x);
}

// Fungsi x[f(x)-g[(x)]
double fungsi_x_Fx_minus_Gx (double x) {
    return x * (fungsi_Fx(x) - fungsi_Gx(x));
}

// Fungsi f(x)^2 - g(x)^2
double fungsi_Fx_kuadrat_minus_Gx_kuadrat (double x) {
    return fungsi_Fx(x) * fungsi_Fx(x) - fungsi_Gx(x) * fungsi_Gx(x);
}


// Function untuk menghitung integral secara numerik dengan aturan trapesium
// n: jumlah titik, minimal = 2
// f: pointer ke fungsi f(x)
// a: batas bawah integrasi
// b: batas atas integrasi
double integral_trapesium_multiple (int n, double (*f)(double), double a, double b)
{
    double h, sum;
    int i;
    
	h = (b - a) / n;
    sum = f(a);

    for (i = 1; i < n; i++) {
        sum += 2 * f(a + i * h);
    }

    sum += f(b);
    
    return (h / 2) * sum;
}


// Fungsi untuk menghitung integral secara numerik dengan aturan 1/3 Simpson
// n: jumlah interval (HARUS GENAP)
// f: pointer ke fungsi f(x)
// a: batas bawah integrasi
// b: batas atas integrasi
double Simp13multi(int n, double (*f)(double), double a, double b) {
	int i;
	double h, sum, x;
	
    if (n % 2 != 0) {
        printf("Error: Jumlah interval (n) harus genap.\n");
        return 0.0;
    }

    h = (b - a) / n;
    sum = f(a);

    for (i = 1; i < n; i++) {
        x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        } else {
            sum += 4 * f(x);
        }
    }

    sum += f(b);

    return h * sum / 3.0;
}


// Fungsi ini akan menghitung A, dan centroid(xbar,ybar) untuk
// metode trapezoidal rule & Simpson's 1/3 Rule
// Hasilnya akan dituliskan ke layar dan juga dituliskan ke file CSV
// sebagai bahan analisis lebih lanjut.
//
// Keterangan:
// A = area = luas daerah = integral (f(x)-g(x)) dx
// xbar = center of gravity x = 1/A  [integral x(f(x)-g(x)) dx]
// ybar = center of gravity y = 1/2A [integral (f(x)^2 - g(x)^2) dx]
void hitung_centroid (int n_start, int n_step, int n_finish,
                      double (*   Fx_minus_Gx                )(double), 
					  double (* x_Fx_minus_Gx                )(double),
                      double (*   Fx_kuadrat_minus_Gx_kuadrat)(double),
                      double a, double b, 
					  FILE *file_hasil)
{
	int i;
	double A_trap, x_trap, y_trap;  // A, xbar, dan ybar untuk trapezoidal rule
	double A_simp, x_simp, y_simp;  // A, xbar, dan ybar untuk Simpson's 1/3 rule
	double moment_x, moment_y;      // temp variable untuk menampung hitungan momen-x dan momen-y
	
	//------------------------------------------------------
	// Iterasi untuk A, xbar, dan ybar
	// untuk metode trapezoial rule & Simpson's 1/3 Rule
	//------------------------------------------------------
	i = n_start;
	if (i > n_finish)
	    i = n_finish;
	    
	// Print ke layar + tulis ke file CSV
    printf("n\tA_trap\t\tA_simp\t\tx_trap\t\tx_simp\t\ty_trap\t\ty_simp\n");
    fprintf(file_hasil, "n,A_trap,A_simp,x_trap,x_simp,y_trap,y_simp\n");

    while (i<=n_finish)
	{
	    // Untuk trapezoidal rule
		A_trap   = integral_trapesium_multiple (i, Fx_minus_Gx, a, b);
	    moment_x = integral_trapesium_multiple (i, x_Fx_minus_Gx, a, b);
	    moment_y = 0.5 * integral_trapesium_multiple (i, Fx_kuadrat_minus_Gx_kuadrat, a, b);
	    x_trap   = moment_x / A_trap;
	    y_trap   = moment_y / A_trap;
	    
	    // Untuk Simpson's 1/3 rule
        A_simp   = Simp13multi (i, Fx_minus_Gx, a, b);
	    moment_x = Simp13multi (i, x_Fx_minus_Gx, a, b);
	    moment_y = 0.5 * Simp13multi (i, Fx_kuadrat_minus_Gx_kuadrat, a, b);
	    x_simp   = moment_x / A_simp;
	    y_simp   = moment_y / A_simp;
        
        // Print ke layar + tulis ke file CSV
		printf ("%d\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\t%.8f\n", i, A_trap, A_simp, x_trap, x_simp, y_trap, y_simp);
        fprintf (file_hasil, "%d,%.8f,%.8f,%.8f,%.8f,%.8f,%.8f\n", i, A_trap, A_simp, x_trap, x_simp, y_trap, y_simp);

        i = i + n_step;
    }
    printf ("\n");
    
	return;
}


int main() {
    int n_start, n_step, n_finish;  // Jumlah segmen awal, step, dan segmen akhir
    int result;
    double a = 0.0;       // Batas bawah
    double b = 6.0;       // Batas atas
    double x, temp;
    double A;             // luas
    double moment_x, moment_y;
    double centroid_x, centroid_y;
    double exact_centroid_x, exact_centroid_y;
    FILE   *file_hasil;

    // Input nilai dari user
    printf("Masukkan nilai n_start (bilangan bulat positif): ");
    result = scanf("%d", &n_start);
    if (result != 1 || n_start < 0) {
        printf("Input tidak valid untuk n_start. Program dihentikan.\n");
        exit(1);
    }

    printf("Masukkan nilai n_step (bilangan bulat positif): ");
    result = scanf("%d", &n_step);
    if (result != 1 || n_step <= 0) {  // langkah harus positif dan tidak nol
        printf("Input tidak valid untuk n_step. Program dihentikan.\n");
        exit(1);
    }

    printf("Masukkan nilai n_finish (bilangan bulat positif): ");
    result = scanf("%d", &n_finish);
    if (result != 1 || n_finish < 0) {
        printf("Input tidak valid untuk n_finish. Program dihentikan.\n");
        exit(1);
    }

    // Menampilkan hasil input jika semua valid
    printf("\nNilai yang dimasukkan:\n");
    printf("n_start = %d\n", n_start);
    printf("n_step  = %d\n", n_step);
    printf("n_finish= %d\n", n_finish);

    // Buka file CSV
    file_hasil = fopen(CONST_NAMA_FILE, "w");
    
    hitung_centroid (n_start, n_step, n_finish,
	                 fungsi_Fx_minus_Gx, 
					 fungsi_x_Fx_minus_Gx,
					 fungsi_Fx_kuadrat_minus_Gx_kuadrat,
                     a, b,
					 file_hasil);
    
    // Tutup file CSV
    fclose (file_hasil);
    
    return 0;
}


