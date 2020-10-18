// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len <= 0)
		 throw logic_error("Negative bit length");

	BitLen = len;
	MemLen = (BitLen / BITS_IN_ONE_MEM);
	if (BitLen % BITS_IN_ONE_MEM != 0)
		MemLen += 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > BitLen)
		throw logic_error("Index out of array");
	if (n < 0)
		throw logic_error("Negative index");
	int temp;
	temp = n / BITS_IN_ONE_MEM;
	return temp;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n > BitLen)
		throw logic_error("Index out of array");
	if (n < 0)
		throw logic_error ("Negative index");
	TELEM temp = 1 << (n % BITS_IN_ONE_MEM);
	return temp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{	
	if (n > BitLen)
		throw logic_error("Index out of array");
	if (n < 0)
		throw logic_error("Negative index");
	int k = GetMemIndex(n);
	pMem[k] = pMem[k] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen)
		throw logic_error("Index out of array");
	if (n < 0)
		throw logic_error("Negative index");
	TELEM mask = GetMemMask(n);
	int k = GetMemIndex(n);
	pMem[k] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{{
	if (n < 0) throw logic_error("Negative bit length");
	if (n >= BitLen) throw logic_error("Too large index");
	
	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	if ((pMem[i] & (1 << j)) == 0) return 0;
	else return 1;
}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		throw logic_error("BitFields are not equal size");
	else if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int min = (MemLen > bf.MemLen) ? bf.MemLen : MemLen;
	int max = (BitLen < bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(max);
	if (bf.GetLength() == max)
	{
		res = bf;
	}
	else
	{ 
		res = *this;
	}
	for (int i = 0; i < min; i++) 
		res.pMem[i] = pMem[i] | bf.pMem[i]; 
	
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;
	for (int i = 0; i < temp.BitLen; i++) {
		if (temp.GetBit(i))		
			temp.ClrBit(i);
		else
			temp.SetBit(i);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	 int i = 0;
  char string;

  for (int a = 0; a < bf.GetLength(); a++)
  {
    istr >> string;
    if (string == '1') bf.SetBit(i);
    i++;
  };
	
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
		int len = bf.GetLength();
	
	for (int i = 0; i < len; i++)
	{
		if (bf.GetBit(i)) ostr << 1;
		else ostr << 0;
	}
	
	return ostr;
}
