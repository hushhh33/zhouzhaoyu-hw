#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}
int max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

Matrix yuzishimartrix(Matrix a, int i, int j)
{
    Matrix new = create_matrix(a.rows - 1, a.cols - 1);
    int m = 0, n = 0;
    for (int row = 0; row < a.rows; row++) {
        if (row == i) continue;
        n = 0;
        for (int col = 0; col < a.cols; col++) {
            if (col == j) continue;
            new.data[m][n] = a.data[row][col];
            n++;
        }
        m++;
    }
    return new;
}
//这个写的也是答辩，要保证谁不变直接就从谁开始数数就行了，要变的重新判断，本函数就是从mn来递变，让右边的同时数数，到地方直接跳右边的，不变左边的，这个是不是叫双指针法？
Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.rows!= b.rows || a.cols!= b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");   
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                c.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        
        }
        return c;
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.cols!= b.cols || a.rows!= b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix c = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                c.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        
        }
        return c;
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if(a.cols != b.rows){
    return create_matrix(0, 0);
    printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
    }
    else{
        Matrix c = create_matrix(a.rows, b.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                for (int k = 0; k < a.cols; k++)
                {
                    c.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        
        }
        return c;
    }    
}


Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    if( k==0 )
    return create_matrix(0, 0);
    else{
        Matrix c = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                c.data[i][j] = a.data[i][j] * k;
            }
        
        }
        return c;
    }
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    if(a.rows<=0 || a.cols<=0)
    return create_matrix(0, 0);
    else{
        Matrix c = create_matrix(a.cols, a.rows);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                c.data[j][i] = a.data[i][j];
            }
        
        }
        return c;
    }
}

// double det_matrix(Matrix a)
// {
//     // ToDo
//     if(a.rows != a.cols)
//     return 0;
    
//     else{
//         static double d;
//         int n = a.rows;
//        while(n>2){
           
//             for(int i=0;i<=n-1;i++){
//                 d+=a.data[i][n]* det_matrix(yuzishimartrix(a,i+1,n))*pow(-1,i+n);
               
//        }
//         n--;
       
//     }
//     if(n==2)    
//      return a.data[0][0]*a.data[1][1]-a.data[0][1]*a.data[1][0];
//     else if(n==1)
//      return a.data[0][0];

//     }
// }//我怎么感觉用上三角形直接求tr比用这个简单
//写的真是大芬啊我丢，直接用第一行来算就行了妈妈的


double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
     return 0;
    }
    int n = a.rows;
    if (n == 1) return a.data[0][0];
    if (n == 2) return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];

    double d = 0;
    for (int i = 0; i < n; i++) {
        Matrix sub = yuzishimartrix(a, 0, i);
        d += pow(-1, i) * a.data[0][i] * det_matrix(sub);
    }
    return d;
}

// Matrix inv_matrix(Matrix a)
// {
//     // ToDo
//     if(a.cols!= a.rows||det_matrix(a)==0){
//     printf("Error: The matrix must be a square matrix.\n");
//     return create_matrix(0, 0);
//     }
//     else{
//         Matrix c = create_matrix(a.rows, a.cols);
//         double d = 1/det_matrix(a);
//         for (int i = 0; i < a.rows; i++)
//         {
//             for (int j = 0; j < a.cols; j++)
//             {
//                 c.data[i][j] = d*pow(-1,i+j)*det_matrix(yuzishimartrix(a,i,j));
//             }
        
//         }
//         return c;
//     }
// }
// //直接伴随矩阵
Matrix inv_matrix(Matrix a)
{
    double det = det_matrix(a);
    if (a.cols != a.rows || det == 0) {
        printf("Error: The matrix must be a square matrix and its determinant must not be zero.\n");
        return create_matrix(0, 0);
    }

    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            Matrix sub = yuzishimartrix(a, i, j);
            c.data[j][i] = pow(-1, i + j) * det_matrix(sub) / det; // Note: c.data[j][i] instead of c.data[i][j]。。。全忘了
        }
    }
    return c;
}

// int rank_matrix(Matrix a)
// {
//    
//     if(a.cols==0 || a.rows==0){
//     return 0;
//     }
//     else{
//         for(int i=1;i<=a.rows;i++){
//             for(int j=1;j<=a.cols;j++){
//             Matrix b = yuzishimartrix(a,i,1);
//         if(det_matrix(b)!=0)
//         return max(a.rows,a.cols);
//         }
//     }  
//             //实现递归重新判断
//         for(int k=1;k<=a.rows;k++){
//                 for(int l=1;l<=a.cols;l++){               
//                     return rank_matrix(yuzishimartrix(a,k,l));
//         }
//     }
//     }
// }
//还是有问题，不一定为square matrix，要判断det是否为0，然后再判断rank，最后返回最大的rank
//只能用上三角来做

int min(int a, int b) {
    return (a < b) ? a : b;
}
void swap_rows(Matrix *a, int row1, int row2) {
    for (int j = 0; j < a->cols; j++) {
        double temp = a->data[row1][j];
        a->data[row1][j] = a->data[row2][j];
        a->data[row2][j] = temp;
    }
}
//这个有问题，没法观察到最好的情况，1 2 1/0 3 0/ 0 2 0
int rank_matrix(Matrix a) {
    if (a.cols > a.rows) {
        a = transpose_matrix(a);
    }

    int rank = a.cols;
    int m = a.rows;
    int n = a.cols;
    
    for (int col = 0; col < a.cols; col++) {
        // 找主元
        int count =0;
        for (int row = col; row < m; row++) {
            count++;
            if (a.data[row][col] != 0) {
                // 交换两行
                
                swap_rows(&a, row, col);
                break;

            }
            else if(count==m-col){
                rank--;        
             }       
    }
    if(count==m-col)
    continue;
     for (int i = 0; i < m - 1; i++) {
        if(i!=col){
            double factor = a.data[i][col] / a.data[col][col];
            for (int j = 0; j < n; j++) {
                a.data[i][j] -= factor * a.data[col][j];
            }
            }

        }
    }

    return rank;
}
// int rank_matrix(Matrix a)
// {
//     int rank = min(a.rows, a.cols);
//     int m = a.rows;
//     int n = a.cols;
    
//     // 转化为上三角形式
//     for (int row = 0; row < rank; row++) {
//         // 如果主对角线上的元素为0，需要与下面的行交换
//         if (a.data[row][row] == 0) {
//             int reduce = 1;

//             // 尝试寻找下面的非零元素
//             for (int i = row + 1; i < m; i++) {
//                 if (a.data[i][row] != 0) {
//                     // 交换两行
//                     for (int j = 0; j < n; j++) {
//                         double temp = a.data[row][j];
//                         a.data[row][j] = a.data[i][j];
//                         a.data[i][j] = temp;
//                     }
//                     reduce = 0;
//                     break;
//                 }
//             }

//             // 如果不能找到非零元素，则减少秩
//             if (reduce) {
//                 rank--;

//                 // 将该列的元素设为最后一列对应位置的元素
//                 for (int i = 0; i < m; i++) {
//                     a.data[i][row] = a.data[i][rank];
//                 }
//             }

//             // 继续处理当前列
//             row--;
//             continue;
//         }

//         // 消去当前列下面的元素
//         for (int i = row + 1; i < m; i++) {
//             double factor = a.data[i][row] / a.data[row][row];
//             for (int j = row; j < n; j++) {
//                 a.data[i][j] -= factor * a.data[row][j];
//             }
//         }
//     }

//     return rank;
// }

double trace_matrix(Matrix a)
{
    // ToDo
    if(a.rows!=a.cols){
    printf("Error: The matrix must be a square matrix.\n");
    return 0;
    }
    else{
        double d=0;
        for(int i=0;i<a.rows;i++){
            d+=a.data[i][i];
        }
        return d;
    }
    
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}


//写完之后再写一个上三角版本，是在感觉是简单很多
