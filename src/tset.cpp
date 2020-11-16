// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()// преобразование типа к битовому полю
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	

	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	
	return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	if (BitField != s.BitField) return 0;
	else return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if (BitField != s.BitField) return 1;
	else return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	TSet temp(BitField | s.BitField);
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem > MaxPower)
  {
    TSet set(Elem);
    set.InsElem(Elem);
    TSet upd(BitField | set.BitField);
    return upd;
  }
  else
  {
    TSet set = *this;
    set.InsElem(Elem);
    return set;
  }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
	{
		throw logic_error("more then maxpower");
	}
	else
	{
     TSet set = *this;
     set.DelElem(Elem);
     return set;
	}
}

TSet TSet::operator*(const TSet& s) // пересечение
{

	TSet temp(BitField & s.BitField);
	return temp;
}


TSet TSet::operator~(void) // дополнение
{
	TSet temp(*this);
	temp.BitField = ~(this->BitField);
	return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int integ;
    char ch;

    istr >> ch;
    while (ch != '}')
    {
        istr >> integ;
        s.InsElem(integ);
        istr >> ch;
    }

    return istr;
}
ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    int len = s.GetMaxPower();
    int ind = 0, check_len = 0;

    ostr << "{";
    while (check_len < len)
    {
        if (s.IsMember(ind) == 1)
        {
            ostr << ind;
            break;
        }
        ind++;
        check_len++;
    }
    for (int i = check_len + 1; i < len; i++)
        if (s.IsMember(i))
            ostr << "," << i;
    ostr << "}";

    return ostr;
}
