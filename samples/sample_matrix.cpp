// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (20.04.2015)
//
// ������������ ����������������� �������

#include <iostream>
#include "utmatrix.h"


int main()
{
    try
    {
        // ������� ������� 3x3 (�����������������)
        TMatrix<int> matrix(3);
        cout << "Matrix created with size 3" << endl;

        // �������� �������� ��������� �������
        for (int i = 0; i < 3; i++)
        {
            for (int j = i; j < 3; j++)
            {
                cout << "Assigning value to matrix[" << i << "][" << j << "]" << endl;
                matrix[i][j] = i + j;  // ������ ������������ ��������
            }
        }

        // ������� �������
        cout << "Matrix:" << endl;
        cout << matrix;
    }
    catch (const std::out_of_range& e)
    {
        cout << "Out of range exception: " << e.what() << endl;
    }
    catch (const std::bad_alloc& e)
    {
        cout << "Bad allocation exception: " << e.what() << endl;
    }
    catch (const std::exception& e)
    {
        cout << "Standard exception: " << e.what() << endl;
    }
    catch (int e)
    {
        cout << "Caught int exception: " << e << endl;
    }
    catch (...)
    {
        cout << "Unknown exception occurred." << endl;
    }

    return 0;
}
