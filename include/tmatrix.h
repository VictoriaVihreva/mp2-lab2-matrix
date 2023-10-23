﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if ((sz <= 0)||(sz>MAX_VECTOR_SIZE))
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz];// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[]pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          sz = v.sz;
          delete[] pMem;
          pMem = new T[sz];
          for (int i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
}
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if ((ind >= sz) || (ind < 0))
          throw out_of_range("index of element is more than a len of vector");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if ((ind >= sz) || (ind < 0))
          throw out_of_range("index of element is more than a len of vector");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind >= sz) || (ind < 0))
          throw out_of_range("index of element is more than a len of vector");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind >= sz) || (ind < 0))
          throw out_of_range("index of element is more than a len of vector");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const 
  {
      if (sz == v.sz)
          for (int i = 0; i < sz; i++)
              if (pMem[i] != v.pMem[i])
                  return false;
      if (sz != v.sz)
          return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const 
  {
      return !(v==*this);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < tmp.sz; i++)
          tmp.pMem[i] = pMem[i] + val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < tmp.sz; i++)
          tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (int i = 0; i < tmp.sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw exception("the length of the vectors must be the same");
      TDynamicVector tmp(sz);;
      for (int i = 0; i < tmp.sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw exception("the length of the vectors must be the same");
      TDynamicVector tmp(sz);
      for (int i = 0; i < tmp.sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz != v.sz)
          throw exception("the length of the vectors must be the same");
      T tmp=0;
      for (int i = 0; i < sz; i++)
          tmp += pMem[i] * v.pMem[i];
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if ((s <= 0) || (s > MAX_MATRIX_SIZE))
        throw out_of_range("matrix size should be greater than zero");
    for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const 
  {
      if (sz == m.sz)
          for (int i = 0; i < sz; i++)
              if (pMem[i] != m.pMem[i])
                  return false;
      if (sz!=m.sz)
          return false;
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }
  

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) {
          throw exception("matrix's sizes should be the same");
      }

      TDynamicVector<T> tmp(sz);

      for (int i = 0; i < sz; i++) {
          T sum = 0;
          for (int j = 0; i < sz; i++) {
              sum += pMem[i][j] * v[j]
          }

          tmp[i] = sum;
      }

      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) 
          throw exception("matrix's sizes should be the same");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw exception("matrix's sizes should be the same");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != v.sz)
          throw exception("matrix's sizes should be the same");
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              T sum = 0;
              for (int k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m[k][j];
              }
              tmp[i][j] = sum;
          }
      }
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v[i] << endl; // требуется оператор>> для типа T
      return ostr;
  }
};
#endif
