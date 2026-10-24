#include <iostream>
#include <cstdlib>
#include <ctime>

int randint(int min, int max)
{
    return min+(rand()%(max-min+1));
}

int**matrix(int rows, int cols)
{
    int min=0;
    int max=0;
    std::cout<<"input min, max:\n";
    std::cin>>min;
    std::cin>>max;
    int**arr= new int*[rows];
    for(int i=0; i<rows;++i)
    {
        arr[i]=new int[cols];
    }
    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols;++j)
        {
            arr[i][j]=randint(min, max);
        }
    }
    return arr;
}

void printmatrix(int**arr, int rows, int cols)
{
    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols;++j)
        {
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}


void deletematr(int**arr, int rows, int cols)
{
    for(int i=0; i<rows; ++i)
    {
        delete[]arr[i];
    }
    delete[]arr;

}




// =============== ФУНКЦИИИ ДЛЯ ОПРЕДЕЛИТЕЛЯ =======================


int**getMinor(int**arr, int row, int col, int n)
{
    int**minor=new int*[n-1];
    {
        for(int i=0; i<n-1;++i)
        {
            minor[i]=new int[n-1];
        }
    }
    int minorRow=0;
    for(int i=0; i<n;++i)
    {
        if(i==row)continue;
        int minorCol=0;
        for(int j=0; j<n; ++j)
        {
            if(j==col) continue;
            minor[minorRow][minorCol]= arr[i][j];
            minorCol++;
        }
        minorRow++;
    }
    return minor;

}

void deleteminor(int**minor,int n)
{
    for(int i=0; i< n ; ++i)
    {
        delete[]minor[i];
    }
    delete[]minor;
}


int determinantRecursive(int** matrix, int n)
{
    if(n == 1)
    {
        return matrix[0][0];
    }
    if(n == 2)
    {
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    
    int det = 0;
    int sign = 1;
    for(int j=0; j<n; ++j)
    {
        int** minor = getMinor(matrix, n, 0, j);
        det += sign * matrix[0][j] * determinantRecursive(minor, n-1);
        deleteminor(minor, n-1);
        sign = -sign;
    }
    return det;
}




int main()
{
    srand(time(0));
    int**A=nullptr;
    int rows=4;
    int cols=4;
    int n=4;
    int det=0;


    std::cout<<"matrix:\n";
    A=matrix(rows,cols);
    printmatrix(A,rows,cols);

    det=determinantRecursive(A,n);
    std::cout<<det;
    deletematr(A,rows,cols);

    return 0;
}