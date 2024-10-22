// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);			// по умолчанию вектор длиной 10	
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  const ValType& operator[](int pos) const;	// доступ для констанстных значений ///////////////////////////

  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение


  // инициализация вектора (строка матрицы)
  void InitInt(int a)			
  {
	  for (int i = StartIndex; i < Size; i++)
	  {
		  pVector[i] = a;
	  }
  }


  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }


  friend ostream& operator<<(ostream& out, const TVector& v)
  {
	  for (int i = 0; i < v.Size; i++)
	  {
		  out << v.pVector[i] << ' ';
		  //out << '\n';
	  }
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 1) || (s > MAX_VECTOR_SIZE) || (si < 0) || (si > MAX_MATRIX_SIZE - 1))
	{
		throw - 1;
	}
	Size = s;
	StartIndex = si;
	pVector = new ValType[Size];

}  


template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
}  



template <class ValType>
TVector<ValType>::~TVector()	// деструктор
{
	delete[] pVector;	
}  



template <class ValType> // доступ к элементу по индексу
ValType& TVector<ValType>::operator[](int pos)
{
	
	pos -= StartIndex;		// чтобы сдвиг индексов вектора начинался с StartIndex
	if ((pos < 0) || (pos >= Size))
	{
		throw - 1;
	}
	return pVector[pos];
}  

template <class ValType>
const ValType& TVector<ValType>::operator[](int pos) const {
	pos -= StartIndex;
	if ((pos < 0) || (pos >= Size)) {
		throw - 1; // Обработка ошибки при некорректном индексе
	}
	return pVector[pos];
}




template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (this == &v)
	{
		return true;
	}
	if (Size != v.Size)
	{
		return false;
	}

	if (StartIndex != v.StartIndex)
	{
		return false;
	}
	
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i])
		{
			return false;
		}
	}
	return true;
}  



template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
}  



template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
	{
		return *this;
	}
	if (Size != v.Size)
	{
		delete[] pVector;
		Size = v.Size;
		pVector = new ValType[v.Size];
	}

	StartIndex = v.StartIndex;
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
	return *this;
}  



template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)	
	{
		res.pVector[i] = pVector[i] + val;
	}
	return res;
}  



template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - val;
	}
	return res;
}  



template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] * val;
	}
	return res;
}  



template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
	{
		throw - 1;
	}

	TVector <ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] + v.pVector[i];
	}
	return res;
}  



template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
	{
		throw - 1;
	}

	TVector <ValType> res(Size, StartIndex);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - v.pVector[i];
	}
	return res;
}  



template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
	{
		throw - 1;
	}

	ValType res = 0;
	for (int i = 0; i < Size; i++)
	{
		res += (pVector[i] * v.pVector[i]);
	}
	return res;
}  




///////////////////////////////////////////////////////////////////////////////////////////////////



// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание
	TMatrix operator* (const TMatrix& mt);         // умножение 

	TVector<ValType>& operator[](int i);             // Для неконстантных объектов
	const TVector<ValType>& operator[](int i) const; // Для константных объектов


	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
		
	}


	void InitMat(int a)			// инициализация нулями
	{
		for (int i = 0; i < Size; i++)
		{
			pVector[i].InitInt(0);
		}
	}
};


template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s < 0) || (s > MAX_MATRIX_SIZE))
		throw - 1;

	for (int i = 0; i < s; i++)
	{
		pVector[i] = TVector<ValType>(s - i, i);  // Здесь мы убираем смещение i
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) /*:
	TVector<TVector<ValType>>(mt) {}*/
{
	Size = mt.Size;
	pVector = new TVector<ValType>[Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = mt.pVector[i];
	}
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}


template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const

{
	if (Size != mt.Size)
	{
		return false;
	}
	for (int i = 0; i < Size; i++)
	{
		if (pVector[i] != mt.pVector[i]) 
		{
			return false;
		}
	}
	return true;

	//return TVector<TVector<ValType>>::operator==(mt);
}


template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);	
}


template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this == &mt)
	{
		return *this;
	}

	if (this->Size != mt.Size)
	{
		delete[] pVector;  // корректно освобождаем память
		this->Size = mt.Size;
		this->pVector = new TVector<ValType>[Size];
		
	}

	for (int i = 0; i < Size; i++)
	{
		this->pVector[i] = mt.pVector[i];
	}
	return *this;
}


template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	
	//return TVector<TVector<ValType>>::operator+(mt);

	if (this->Size != mt.Size)
	{
		throw - 1;
	}
	TMatrix res(Size);
	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = pVector[i] + mt.pVector[i];
	}
	return res;

}


template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
	{
		return false;
	}
	TMatrix res(Size);
	for (int i = 0; i < Size; i++)
	{
		res[i] = pVector[i] - mt.pVector[i];
	}
	return res;
	 
	//return TVector<TVector<ValType>>::operator-(mt);

}


template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& mt)
{
	if (this->Size != mt.Size) 
	{
		throw - 1; // Проверка на совместимость матриц по размеру
	}

	TMatrix<ValType> res(this->Size); // Создаем результирующую матрицу

	// умножаем элементы соответствующим образом для верхнеугольной матрицы
	for (int i = 0; i < this->Size; i++) 
	{
		for (int j = i; j < this->Size; j++) 
		{												// j начинается с i, так как это верхнетреугольная матрица
			res[i][j] = ValType();						// Инициализируем элемент результирующей матрицы нулем
			for (int k = i; k <= j; k++) 
			{											// Ограничиваем суммирование
				res[i][j] += (*this)[i][k] * mt[k][j];
			}
		}
	}
	return res;
}


// Для неконстантных объектов
template <class ValType>
TVector<ValType>& TMatrix<ValType>::operator[](int i)
{
	return TVector<TVector<ValType>>::operator[](i);
}

// Для константных объектов
template <class ValType>
const TVector<ValType>& TMatrix<ValType>::operator[](int i) const
{
	return TVector<TVector<ValType>>::operator[](i);
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3

#endif
