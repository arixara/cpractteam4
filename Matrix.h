#pragma once
#include <iostream>
#include <sstream>



class SizeException { };

template <typename T>
class Vector;

// Класс матрица
template <typename T>
class Matrix
{
protected:
	T** array_;
	size_t rows_;
	size_t columns_;
public:
	Matrix(); // Конструктор по умолчанию
	Matrix(const Matrix<T>&); // Конструктор копирования
	Matrix(Matrix<T>&&); //  Конструктор перемещения
	Matrix(const std::initializer_list<std::initializer_list<T>>&); // Конструктор от листа инициализаторов
	~Matrix(); // Деструктор

	Matrix<T>& operator= (const Matrix<T>&); // Оператор присваивания с копированием
	Matrix<T>& operator= (Matrix<T>&&); // Оператор присваивания с захватом ресурса

	void resize(size_t, size_t); // Изменение размера матрицы

	inline size_t rows() const; // Количество строк
	inline size_t columns() const; //  И столбцов

	inline T* operator[] (size_t); // Операторы индексации
	inline const T* operator[] (size_t) const;

	Matrix<T>& apply(T(*)(T)); // Применить ко всем
	Matrix<T> map(T(*)(T)) const; // Применить к копии

	Matrix<T>& transpose(); // Транспонирование
	template <typename D>
	friend Matrix<D> transpose_matrix(const Matrix<D>&);
	// Срез
	Matrix<T> slice(int start_row, int stop_row, int step_row, int start_column, int stop_column, int step_column) const;
	// Арифметические операции
	template <typename D>
	friend Matrix<D> operator* (const Matrix<D>&, const Matrix<D>&);
	template <typename D>
	friend Matrix<D> operator+ (const Matrix<D>&, const Matrix<D>&);
	template <typename D>
	friend Matrix<D> operator- (const Matrix<D>&, const Matrix<D>&);
	template <typename D>
	friend Matrix<D> operator* (const Matrix<D>&, D);
	template <typename D>
	friend Matrix<D> operator* (D, const Matrix<D>&);
	template <typename D>
	friend Matrix<D> operator/ (const Matrix<D>&, D);
	// Работа с потоком ввода-вывода
	template <typename D>
	friend std::ostream& operator<< (std::ostream&, const Matrix<T>&);
	template <typename D>
	friend std::istream& operator>> (std::istream&, Matrix<T>&);
};

template <typename T>
Matrix<T>::Matrix() : array_(nullptr), rows_(0), columns_(0)
{ }

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& arg) : rows_(arg.rows_), columns_(arg.columns_)
{
	if (arg.array_)
	{
		array_ = new T*[rows_];
		for (register size_t i = 0; i < rows_; ++i)
		{
			array_[i] = new T[columns_];
			for (register size_t j = 0; j < columns_; ++j)
				array_[i][j] = arg.array_[i][j];
		}
	}
	else
	{
		array_ = nullptr;
	}
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& arg) :
array_(arg.array_), rows_(arg.rows_), columns_(arg.columns_)
{
	// Захватываем данные и зануляем источник
	arg.array_ = nullptr;
	arg.rows_ = 0;
	arg.columns_ = 0;
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list< std::initializer_list<T> >& arg)
{
	size_t newColumns;
	size_t newRows;

	newRows = arg.size();
	if (newRows && (newColumns = arg.begin()->size()))
	{
		// Проходим по массивам и копируем объекты
		array_ = new T*[newRows];
		for (size_t i = 0; i < newRows; ++i)
			array_[i] = new T[newColumns];
		rows_ = newRows;
		columns_ = newColumns;

		size_t copyI, copyJ;
		auto i = arg.begin();
		for (copyI = 0; i != arg.end(); ++i, ++copyI)
		{
			auto j = i->begin();
			for (copyJ = 0; j != i->end(); ++j, ++copyJ)
				array_[copyI][copyJ] = *j;
		}
	}
	else
	{
		array_ = nullptr;
		rows_ = 0;
		columns_ = 0;
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	if (array_)
	{
		// Отпускаем выделенную память
		for (register size_t i = 0; i < rows_; ++i)
			delete[] array_[i];
		delete[] array_;
		array_ = nullptr;
		rows_ = 0;
		columns_ = 0;
	}
}

template <typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& arg)
{
	if (this != &arg)
	{
		// Удаляем матрицу
		this->~Matrix();
		if (arg.array_)
		{
			// Создаем новую и копируем
			rows_ = arg.rows_;
			columns_ = arg.columns_;
			resize(arg.rows_, arg.columns_);
			for (register size_t i = 0; i < rows_; ++i)
				for (register size_t j = 0; j < columns_; ++j)
					array_[i][j] = arg.array_[i][j];
		}
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& arg)
{
	if (this != &arg)
	{
		// Обмениваемся ресурсами
		std::swap(array_, arg.array_);
		std::swap(rows_, arg.rows_);
		std::swap(columns_, arg.columns_);
	}

	return *this;
}

template <typename T>
void Matrix<T>::resize(size_t newRows, size_t newColumns)
{
	if (!newRows || !newColumns)
	{
		// Если размер нулевой
		for (register size_t i = 0; i < rows_; ++i)
			delete[] array_[i];
		delete[] array_;
		array_ = nullptr;
		rows_ = 0;
		columns_ = 0;
	}
	else if (!array_)
	{
		array_ = new T*[newRows];
		for (register size_t i = 0; i < newRows; ++i)
			array_[i] = new T[newColumns];

		rows_ = newRows;
		columns_ = newColumns;
	}
	else
	{
		// Выделяем новую память и копируем туда содержимое
		T** newArray;
		newArray = new T*[newRows];
		for (register size_t i = 0; i < newRows; ++i)
			newArray[i] = new T[newColumns];

		size_t copyRows;
		size_t copyColumns;
		copyRows = (newRows < rows_ ? newRows : rows_);
		copyColumns = (newColumns < columns_ ? newColumns : columns_);
		for (register size_t i = 0; i < copyRows; ++i)
			for (register size_t j = 0; j < copyColumns; ++j)
				newArray[i][j] = array_[i][j];

		for (register size_t i = 0; i < rows_; ++i)
			delete[] array_[i];
		delete[] array_;

		array_ = newArray;
		rows_ = newRows;
		columns_ = newColumns;
	}
}

template <typename T>
inline size_t Matrix<T>::rows() const
{
	return rows_;
}

template <typename T>
inline size_t Matrix<T>::columns() const
{
	return columns_;
}

template <typename T>
inline T* Matrix<T>::operator[] (size_t index)
{
	return array_[index];
}

template <typename T>
inline const T* Matrix<T>::operator[] (size_t index) const
{
	return array_[index];
}

template <typename T>
Matrix<T>& Matrix<T>::apply(T(*f)(T))
{
	// Применяем ко всем
	for (size_t i = 0; i < rows_; ++i)
		for (size_t j = 0; j < columns_; ++j)
			array_[i][j] = f(array_[i][j]);

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::map(T(*f)(T)) const
{
	Matrix<T> res;
	res.resize(rows_, columns_);
	for (size_t i = 0; i < rows_; ++i)
		for (size_t j = 0; j < columns_; ++j)
			res.array_[i][j] = f(array_[i][j]);

	return res;
}

template <typename T>
Matrix<T>& Matrix<T>::transpose()
{
	Matrix<T> res;

	if (array_)
	{
		res.resize(columns_, rows_);
		for (size_t i = 0; i < columns_; ++i)
			for (size_t j = 0; j < rows_; ++j)
				res.array_[i][j] = array_[j][i];
		// Присваиваем самому себе
		operator=(res);
	}

	return *this;
}

template <typename T>
Matrix<T> transpose_matrix(const Matrix<T>& a)
{
	Matrix<T> res;
	size_t resRows;
	size_t resColumns;

	resRows = a.columns_;
	resColumns = a.rows_;
	res.resize(resRows, resColumns);
	for (register size_t i = 0; i < resRows; ++i)
		for (register size_t j = 0; j < resColumns; ++j)
			res.array_[i][j] = a.array_[j][i];

	return res;
}

// Длинная функция использована ради того чтобы не выходить за рамки общей композиции
template <typename T>
Matrix<T> Matrix<T>::slice(int a_start, int a_stop, int a_step, int start, int stop, int step) const
{
	Matrix<size_t> indexes;
	// Slice by rows

	indexes.resize(1, rows_);
	for (size_t i = 0; i < rows_; ++i)
		indexes[0][i] = i;
	// Отдельный блок для локальных переменных
	{
		Matrix<size_t> a_res;
		size_t a_resSize = 0;
		int a_index = a_start;
		int a_resWall;
		size_t a_copyIndex = 0;

		if (a_start >= 0 && a_start < indexes.columns())
		{
			if (a_step > 0)
			{
				if (a_start < a_stop)
				{
					a_resWall = (a_stop < indexes.columns() ? a_stop : indexes.columns());
					while (1)
					{
						if (a_index >= a_resWall) break;
						++a_resSize;
						a_index += a_step;
					}
				}
				else ++a_resSize;
			}
			else if (a_step < 0)
			{
				if (a_stop < a_start)
				{
					a_resWall = (a_stop > -1 ? a_stop : -1);
					while (1)
					{
						if (a_index <= a_resWall) break;
						++a_resSize;
						a_index += a_step;
					}
				}
				else ++a_resSize;
			}
			a_res.resize(1, a_resSize);
			for (a_index = a_start; a_copyIndex < a_resSize; a_index += a_step, ++a_copyIndex)
				a_res[0][a_copyIndex] = indexes[0][a_index];
		}

		indexes = a_res;
	}

	Matrix<T> res;
	size_t resRows;
	size_t resColumns = 0;
	int stopIndex;
	register int index = start;

	// Slice by columns
	resRows = indexes.columns();
	if (resRows)
	{
		if (start >= 0 && start < columns_)
		{
			if (step > 0)
			{
				if (start < stop)
				{
					stopIndex = (stop < columns_ ? stop : columns_);
					while (index < stopIndex)
					{
						index += step;
						++resColumns;
					}
				}
				else ++resColumns;

			}
			else if (step < 0)
			{
				if (start > stop)
				{
					stopIndex = (stop > -1 ? stop : -1);
					while (index > stopIndex)
					{
						index += step;
						++resColumns;
					}
				}
				else ++resColumns;
			}
		}
		res.resize(resRows, resColumns);
		for (size_t i = 0; i < resRows; ++i)
		{
			index = indexes[0][i];
			for (size_t copyIndex = 0, j = start; copyIndex < resColumns; ++copyIndex, j += step)
				res[i][copyIndex] = array_[index][j];
		}
	}

	return res;
}

template <typename T>
Matrix<T> operator* (const Matrix<T>& a, const Matrix<T>& b)
{
	Matrix<T> res;
	if (a.columns_ == b.rows_ && a.array_)
	{
		res.resize(a.rows_, b.columns_);
		for (size_t i = 0; i < a.rows_; ++i)
		{
			for (size_t j = 0; j < b.columns_; ++j)
			{
				res[i][j] = 0;
				for (size_t s = 0; s < a.columns_; ++s)
					res[i][j] += a[i][s] * b[s][j];
			}
		}
	}
	else throw SizeException(); // Если размеры недопустимые то вызываем исключение

	return res;
}

template <typename T>
Matrix<T> operator+ (const Matrix<T>& a, const Matrix<T>& b)
{
	Matrix<T> res;

	if (a.rows_ == b.rows_ && a.columns_ == b.columns_)
	{
		res.resize(a.rows_, a.columns_);
		for (register size_t i = 0; i < a.rows_; ++i)
			for (register size_t j = 0; j < a.columns_; ++j)
				res.array_[i][j] = a.array_[i][j] + b.array_[i][j];
	}
	else throw SizeException();

	return res;
}

template <typename T>
Matrix<T> operator- (const Matrix<T>& a, const Matrix<T>& b)
{
	Matrix<T> res;

	if (a.rows_ == b.rows_ && a.columns_ == b.columns_)
	{
		res.resize(a.rows_, a.columns_);
		for (register size_t i = 0; i < a.rows_; ++i)
			for (register size_t j = 0; j < a.columns_; ++j)
				res.array_[i][j] = a.array_[i][j] - b.array_[i][j];
	}
	else throw SizeException();

	return res;
}

template <typename T>
Matrix<T> operator* (const Matrix<T>& a, T b)
{
	Matrix<T> res;
	size_t newRows;
	size_t newColumns;

	newRows = a.rows_;
	newColumns = a.columns_;

	res.resize(newRows, newColumns);
	for (size_t i = 0; i < newRows; ++i)
		for (size_t j = 0; j < newColumns; ++j)
			res[i][j] = a[i][j] * b;

	return res;
}

template <typename T>
Matrix<T> operator* (T b, const Matrix<T>& a)
{
	Matrix<T> res;
	size_t newRows;
	size_t newColumns;

	newRows = a.rows_;
	newColumns = a.columns_;

	res.resize(newRows, newColumns);
	for (size_t i = 0; i < newRows; ++i)
		for (size_t j = 0; j < newColumns; ++j)
			res[i][j] = a[i][j] * b;

	return res;
}

// Деление на константу
template <typename T>
Matrix<T> operator/ (const Matrix<T>& a, T b)
{
	Matrix<T> res;
	size_t newRows;
	size_t newColumns;

	newRows = a.rows_;
	newColumns = a.columns_;

	res.resize(newRows, newColumns);
	for (size_t i = 0; i < newRows; ++i)
		for (size_t j = 0; j < newColumns; ++j)
			res[i][j] = a[i][j] / b;

	return res;
}

template <typename T>
std::istream& operator>> (std::istream& stream, Matrix<T>& arg)
{
	std::stringstream ss;
	char symbol;
	char previous_symbol;
	// Доходим до место считывания
	while ((symbol = stream.get()) == '\n');
	if (!stream.good())
	{
		arg.resize(0, 0);
		return stream;
	}
	// Считываем блок данных
	while (1)
	{
		if (symbol != ',')
			ss << symbol;
		previous_symbol = symbol;
		symbol = stream.get();
		if (symbol == '\n' && previous_symbol == symbol) break;
		if (!stream.good())
		{
			if (previous_symbol != '\n')
				ss << '\n';
			break;
		}
	}
	stream.clear();
	// Блок заканчиватеся на '\n'
	size_t resColumns = 0;
	size_t resRows;
	T element;
	// Считаем количество столбцов
	ss.seekg(0);
	while (1)
	{
		ss >> element;
		if (!ss.good())
		{
			arg.resize(0, 0);
			stream.clear(std::ios::failbit);
			return stream;
		}
		++resColumns;
		symbol = ss.get();
		if (symbol == '\n') break;
	}
	// Считаем количество строк
	resRows = 1;
	while (1)
	{
		symbol = ss.get();
		if (symbol == '\n')
			++resRows;
		if (!ss.good()) break;
	}
	// Считываем матрицу
	ss.clear();
	ss.seekg(0);
	if (resRows && resColumns)
	{
		arg.resize(resRows, resColumns);
		for (size_t i = 0; i < resRows; ++i)
		{
			for (size_t j = 0; j < resColumns; ++j)
			{
				ss >> arg[i][j];
				if (!ss.good())
				{
					stream.clear(std::ios::failbit);
					arg.resize(0, 0);
					return stream;
				}
			}
		}
	}
	else
	{
		stream.clear(std::ios::failbit);
		arg.resize(0, 0);
	}

	return stream;
}

template <typename T>
std::ostream& operator<< (std::ostream& stream, const Matrix<T>& arg)
{
	for (size_t i = 0; i < arg.rows(); ++i)
	{
		for (size_t j = 0; j < arg.columns(); ++j)
		{
			stream << arg[i][j];
			if (j != arg.columns() - 1) // Если символ не последний
				stream << ", ";
		}
		if (i != arg.rows() - 1)
			stream << '\n';
	}
	
	return stream;
}

template <typename T>
class Vector : public Matrix<T>
{
protected:
	using Matrix<T>::array_;
	using Matrix<T>::rows_;
	using Matrix<T>::columns_;
	size_t columns() = delete; // Увектора этих методов нет
	size_t rows() = delete;
public:
	Vector();
	Vector(const std::initializer_list<T>&);
	Vector(const Vector<T>&);
	Vector(const Matrix<T>&); // Конструктор от класса предка
	Vector(Vector<T>&&);
	~Vector();

	Vector<T>& operator= (const Vector<T>&);
	Vector<T>& operator= (Vector<T>&&);
	Vector<T>& operator= (const Matrix<T>&); // Дополнительный оператор для удобства

	void resize(size_t);
	inline size_t size() const;

	inline T& operator[] (size_t);
	inline const T& operator[] (size_t) const;

	Vector<T>& apply(T(*)(T));
	Vector<T> map(T(*)(T)) const;
	// Срез для вектора
	Vector<T> slice(int start, int stop, int step) const;

	static Vector<T> linspace(T start, T stop, size_t number);

	template <typename D>
	friend D operator, (const Vector<D>&, const Vector<D>&);
////////////////
	// Арифметические операции для удобства
	template <typename D>
	friend Vector<D> operator+ (const Vector<D>&, const Vector<D>&);
	template <typename D>
	friend Vector<D> operator- (const Vector<D>&, const Vector<D>&);
	template <typename D>
	friend Vector<D> operator* (const Vector<D>&, D);
	template <typename D>
	friend Vector<D> operator* (D, const Vector<D>&);
	template <typename D>
	friend Vector<D> operator/ (const Vector<D>&, D);
////////////////
	template <typename D>
	friend std::ostream& operator<< (std::ostream&, const Vector<D>&);
	template <typename D>
	friend std::istream& operator>> (std::istream&, Vector<D>&);
};

template <typename T>
Vector<T>::Vector() : Matrix<T>()
{ }

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& arg)
{
	size_t newRows;
	size_t index = 0;

	newRows = arg.size();
	if (newRows)
	{
		array_ = new T*[newRows];
		for (size_t i = 0; i < newRows; ++i)
			array_[i] = new T[1];
		
		for (auto element = arg.begin(); element != arg.end(); ++element, ++index)
			array_[index][0] = *element;
		rows_ = newRows;
		columns_ = 1;
	}
	else
	{
		array_ = nullptr;
		rows_ = 0;
		columns_ = 0;
	}
}

template <typename T>
Vector<T>::Vector(const Vector<T>& arg) : Matrix<T>(arg) // Просто пользуемся ранее описанным конструктором матрицы
{ }

template <typename T>
Vector<T>::Vector(Vector&& arg) : Matrix<T>(arg) // Просто пользуемся ранее описанным конструктором матрицы
{ }

template <typename T>
Vector<T>::Vector(const Matrix<T>& arg) : Matrix<T>(arg)  // Просто пользуемся ранее описанным конструктором матрицы
{ }

template <typename T>
Vector<T>::~Vector()
{ }

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector& arg)
{
	size_t newRows;

	if (&arg != this)
	{
		newRows = arg.rows_;
		Matrix<T>::resize(newRows, 1);
		for (size_t i = 0; i < newRows; ++i)
			array_[i][0] = arg.array_[i][0];
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& arg)
{
	if (&arg != this)
	{
		std::swap(array_, arg.array_);
		std::swap(rows_, arg.rows_);
		std::swap(columns_, arg.columns_);
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Matrix<T>& arg)
{
	size_t newRows;

	if (&arg != this)
	{
		if (arg.columns() == 1)
		{
			newRows = arg.rows();
			Matrix<T>::resize(newRows, 1);
			for (size_t i = 0; i < newRows; ++i)
				array_[i][0] = arg[i][0];
		}
		else throw SizeException();
	}

	return *this;
}

// Перегружаем матричный метод
template <typename T>
void Vector<T>::resize(size_t newSize)
{
	Matrix<T>::resize(newSize, 1);
}

template <typename T>
size_t Vector<T>::size() const
{
	return rows_;
}

template <typename T>
T& Vector<T>::operator[] (size_t index)
{
	return array_[index][0];
}

template <typename T>
const T& Vector<T>::operator[] (size_t index) const
{
	return array_[index][0];
}

template <typename T>
Vector<T>& Vector<T>::apply(T(*f)(T))
{
	for (register size_t i = 0; i < rows_; ++i)
		array_[i][0] = f(array_[i][0]);

	return *this;
}

template <typename T>
Vector<T> Vector<T>::map(T(*f)(T)) const
{
	Vector<T> res;
	res.resize(rows_);
	for (register size_t i = 0; i < rows_; ++i)
		res[i] = f(array_[i][0]);

	return res;
}

// Перегружаем метод срез для вектора
template <typename T>
Vector<T> Vector<T>::slice(int start, int stop, int step) const
{
	Vector<T> res;
	size_t resSize = 0;
	int index = start;
	int resWall;
	int copyIndex = 0;

	if (start >= 0 && start < rows_)
	{
		if (step > 0)
		{
			if (start < stop)
			{
				resWall = (stop < rows_ ? stop : rows_);
				while (1)
				{
					if (index >= resWall) break;
					++resSize;
					index += step;
				}
			}
			else ++resSize;
		}
		else if (step < 0)
		{
			if (stop < start)
			{
				resWall = (stop > -1 ? stop : -1);
				while (1)
				{
					if (index <= resWall) break;
					++resSize;
					index += step;
				}
			}
			else ++resSize;
		}
		res.resize(resSize);
		for (index = start; copyIndex < resSize; index += step, ++copyIndex)
			res[copyIndex] = array_[index][0];
	}

	return res;
}

// Определение статического метода
template <typename T>
Vector<T> Vector<T>::linspace(T start, T stop, size_t number)
{
	Vector<T> res;
	T stepSize;

	if (start < stop && number > 1)
	{
		res.resize(number);
		stepSize = (stop - start) / static_cast<T>(number - 1);
		for (size_t i = 0; i < number; ++i)
		{
			res[i] = start;
			start += stepSize;
		}
	}

	return res;
}

// Скалярное произведение
template <typename T>
T operator, (const Vector<T>& a, const Vector<T>& b)
{
	T res = static_cast<T>(0);
	size_t resSize;

	if (a.size() == b.size())
	{
		resSize = a.size();
		for (size_t i = 0; i < resSize; ++i)
			res += a[i] * b[i];
	}
	else throw SizeException();

	return res;
}

template <typename T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& arg)
{
	for (register size_t i = 0; i < arg.size(); ++i)
	{
		stream << arg[i];
		if (i != arg.size() - 1)
			stream << ", ";
	}

	return stream;
}

template <typename T>
std::istream& operator>> (std::istream& stream, Vector<T>& arg)
{
	char symbol;
	const char delimiter = ',';
	size_t resSize = 0;
	std::stringstream ss;
	T element;
	// Заполняем буффер
	while (1)
	{
		stream >> element;
		if (!stream.good()) break;
		ss << element;
		++resSize;
		symbol = stream.get();
		if (symbol != delimiter) break;
		ss << ' ';
	}

	arg.resize(resSize);
	ss.seekg(0);
	// В цикле считываем
	for (size_t i = 0; i < resSize; ++i)
		ss >> arg[i];

	return stream;
}
//////////////////// Additions //////////////////////

template <typename T>
Vector<T> operator+ (const Vector<T>& a, const Vector<T>& b)
{
	Vector<T> res;
	size_t resSize;
	
	resSize = a.size();
	if (resSize == b.size())
	{
		res.resize(resSize);
		for (size_t i = 0; i < resSize; ++i)
			res[i] = a[i] + b[i];
	}
	else throw SizeException();

	return res;
}

template <typename T>
Vector<T> operator- (const Vector<T>& a, const Vector<T>& b)
{
	Vector<T> res;
	size_t resSize;

	resSize = a.size();
	if (resSize == b.size())
	{
		res.resize(resSize);
		for (size_t i = 0; i < resSize; ++i)
			res[i] = a[i] - b[i];
	}
	else throw SizeException();

	return res;
}

template <typename T>
Vector<T> operator* (const Vector<T>& a, T b)
{
	Vector<T> res;
	size_t resSize;

	resSize = a.size();
	res.resize(resSize);
	for (size_t i = 0; i < resSize; ++i)
		res[i] = a[i] * b;

	return res;
}

template <typename T>
Vector<T> operator* (T b, const Vector<T>& a)
{
	return operator* (a, b);
}

template <typename T>
Vector<T> operator/ (const Vector<T>& a, T b)
{
	Vector<T> res;
	size_t resSize;

	resSize = a.size();
	res.resize(resSize);
	for (size_t i = 0; i < resSize; ++i)
		res[i] = a[i] / b;

	return res;
}
