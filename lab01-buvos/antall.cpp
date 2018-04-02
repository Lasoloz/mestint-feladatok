#include <iostream>
#include <cstdio>

using namespace std;

const int n = 4;
const int n_square = n * n;
const int n_min = n - 2;
const int L = n * (n_square + 1) / 2;

bool elhasznalt[n*n];
int matrix[n][n];

int db = 0;

FILE *f;

void kiir(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
       //     cout << matrix[i][j] << " ";
            fprintf(f, "%d ", matrix[i][j]);
        }
    //    cout << endl;
        fprintf(f, "\n");
    }
  //  cout<<endl;
    fprintf(f, "\n");
}
void ellenorzes(){
    int sum1 = 0, sum2 = 0;

    for(int i = 0; i < n; i++){
        sum1 += matrix[i][i];
        sum2 += matrix[i][n-i-1];
    }

    if(sum1 == L && sum2 == L){
        kiir();
 //       system("pause");
        db++;
    }
}

void megold(int i, int j, int sum){
    if(i < n_min){ // ha utolsoelotti elotti sorokban vagyunk
        if(j < n_min){ // ha utolsoelotti elotti oszlopokban vagyunk
            for(int k = 0; k < n_square; k++){
                if(!elhasznalt[k]){
                    elhasznalt[k] = 1;
                    sum += (k + 1);

                    matrix[i][j] = k + 1;
                    megold(i, j + 1, sum);

                    sum -= (k + 1);
                    elhasznalt[k] = 0;
                }
            }
        }
        else{ // utolso elotti oszlop
            int min_val = L - n_square - sum;
            if(min_val <= 0) min_val = 1;
                for(int k = min_val; k <= n_square; k++){
                    if(k + sum >=  L) break;

                    if(!elhasznalt[k-1]){
                        elhasznalt[k-1] = 1;

                        matrix[i][j] = k;

                        int last_val = L - sum - k - 1;
                        if(!elhasznalt[last_val]){
                            elhasznalt[last_val] = 1;

                            matrix[i][j+1] = last_val + 1;

                            megold(i + 1, 0, 0);

                            elhasznalt[last_val] = 0;
                        }

                        elhasznalt[k-1] = 0;
                    }
                }
        }
    } // eddig jo
    else{ // utolso elotti sor
        int col_sum = 0;
        for(int k = 0; k < n_min; k++){
            col_sum += matrix[k][j];
        }
        int min_val = L - n_square - col_sum;

        if(min_val <= 0) min_val = 1;
            for(int k = min_val; k <= n_square; k++){
                if(k + col_sum >= L) break;

                if(!elhasznalt[k-1]){
                    elhasznalt[k-1] = 1;
                    sum +=  k;

                    matrix[i][j] = k;

                    int last_value = L - col_sum - k - 1;
                    if(!elhasznalt[last_value]){
                        elhasznalt[last_value] = 1;

                        matrix[i+1][j] = last_value + 1;

                        if(j < n_min){
                            megold(i, j + 1, sum);
                        }
                        else{
                            int last_val = L - sum - 1;
                            if(!elhasznalt[last_val] && last_val >= 0 && last_val < n_square){
                                elhasznalt[last_val] = 1;

                                matrix[i][j+1] = last_val + 1;

                                for(int p = 0; p < n_square; p++){
                                    if(!elhasznalt[p]){
                                        matrix[n-1][n-1] = p + 1;
                                        ellenorzes();
                                        break;
                                    }
                                }

                                elhasznalt[last_val] = 0;
                            }
                        }

                        elhasznalt[last_value] = 0;
                    }

                    sum -= k;
                    elhasznalt[k-1] = 0;
                }
            }
    }
}

int main()
{
    f = fopen("buvosnegyzetek.txt", "w");
    megold(0, 0, 0);

  //  fprintf(f, "\n%d\n", db);
    printf("%d\n", db);
    return 0;
}
