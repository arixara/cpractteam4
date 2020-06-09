#pragma once
#include "Matrix.h"
#include <cmath>



// Класс с Лотки-Вольтера
class LotkiVoltera
{
private:
	const double alpha_;
	const double gamma_;
	const double betta_;
	const double delta_;
public:
	LotkiVoltera() :
		alpha_(1.0), gamma_(2.0), betta_(1.5), delta_(1.5)
	{ }

	Vector<double> operator() (double time, const Vector<double>& state) const
	{
		Vector<double> res;
		res.resize(2);
		res[0] = (alpha_ - betta_ * state[1]) * state[0];
		res[1] = (delta_ * state[0] - gamma_) * state[1];

		return res;
	}
};

// Класс с двойным маятником
class DoublePendulum
{
private:
	const double m; // Масса груза
	const double L; // Длинна колена
	const double g; // Ускорение свободного падения
public:
	DoublePendulum() :
		m(1.0), L(1.2), g(9.8) // Данный параметры можно менять и получать различные траектории!!!!
	{ }
										// { theta1, theta2, p1, p2 } порядок аргументов
	Vector<double> operator() (double time, const Vector<double>& state) const
	{
		Vector<double> res;
		res.resize(4);
		// Считаем производную по заданным параметрам
		double k = 6.0 / (m * L * L);
		double arg = state[0] - state[1];
		double denominator = (16.0 - 9.0 * std::cos(arg) * std::cos(arg));
		res[0] = k * (2.0 * state[2] - 3.0 * std::cos(arg) * state[3]) / denominator;
		res[1] = k * (8.0 * state[3] - 3.0 * std::cos(arg) * state[2]) / denominator;

		res[2] = (-0.5 * m * L * L) * (res[0] * res[1] * std::sin(arg) + 3 * (g / L) * std::sin(state[0]));
		res[3] = ( -0.5 * m * L * L ) * (-res[0] * res[1] * std::sin(arg) + (g / L) * std::sin(state[1]));

		return res;
	}
};

// RK5(4)7FC from Dorman and Prince
class RKMethodA
{
protected:
	Matrix<double> A;
	Vector<double> c;
	Vector<double> b_subs;
	Vector<double> b_main;
public:
	RKMethodA()
	{
		A = {	{0.0,				0.0,			0.0,				0.0,					0.0,				0.0,			0.0},
				{1.0 / 5,			0.0,			0.0,				0.0,					0.0,				0.0,			0.0},
				{3.0 / 40,			9.0 / 40,		0.0,				0.0,					0.0,				0.0,			0.0},
				{264.0 / 2197,		-90.0 / 2197,	840.0 / 2197,		0.0,					0.0,				0.0,			0.0},
				{932.0 / 3645,		-14.0 / 27,		3256.0 / 5103,		7436.0 / 25515,			0.0,				0.0,			0.0},
				{-367.0 / 513,		30.0 / 19,		9940.0 / 5643,		-29575.0 / 8208,		6615.0 / 3344,		0.0,			0.0},
				{35.0 / 432,		0.0,			8500.0 / 14553,		-28561.0 / 84672,		405.0 / 704,		19.0 / 196,		0.0}};
		c = {	0.0,				1.0 / 5,		3.0 / 10,			6.0 / 13,				2.0 / 3,			1.0,			1.0 };
		b_main = { 35.0 / 432, 0.0, 8500.0 / 14553, -28561.0 / 84672,	405.0 / 704,	19.0 / 196,		0.0 };
		b_subs = { 11.0 / 108, 0.0, 6250.0 / 14553,	2197.0 / 21168,		81.0 / 176,		171.0 / 1960,	1.0 / 40 };
	}
};

// Fehlberg's RK5(6)8
class RKMethodB
{
protected:
	Matrix<double> A;
	Vector<double> c;
	Vector<double> b_subs;
	Vector<double> b_main;
public:
	RKMethodB()
	{
		A = { {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{1.0 / 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{4.0 / 75, 16.0 / 75, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{5.0 / 6, -8.0 / 3, 5.0 / 2, 0.0, 0.0, 0.0, 0.0, 0.0},
		{-8.0 / 5, 144.0 / 25, -4.0, 16.0 / 25, 0.0, 0.0, 0.0, 0.0},
		{361.0 / 320, -18.0 / 5, 407.0 / 128, -11.0 / 80, 55.0 / 128, 0.0, 0.0, 0.0},
		{-11.0 / 640, 0.0, 11.0 / 256, -11.0 / 160, 11.0 / 256, 0.0, 0.0, 0.0},
		{93.0 / 640, -18.0 / 5, 803.0 / 256, -11.0 / 160, 99.0 / 256, 0.0, 1.0, 0.0} };

		c = { 0.0, 1.0 / 6, 4.0 / 15, 2.0 / 3, 4.0 / 5, 1.0, 0.0, 1.0 };
		b_main = { 31.0 / 384, 0.0, 1125.0 / 2816, 9.0 / 32, 125.0 / 768, 5.0 / 66, 0.0, 0.0 };
		b_subs = { 7.0 / 1408, 0.0, 1125.0 / 2816, 9.0 / 32, 125.0 / 768, 0.0, 5.0 / 66, 5.0 / 66 };
	}
};

template <typename ODE, typename RKMETHOD>
class RKIntegrator : public RKMETHOD
{
protected:
	using RKMETHOD::A;
	using RKMETHOD::c;
	using RKMETHOD::b_main;
	using RKMETHOD::b_subs;
	// Система диф уравнений
	ODE ode_;
	// Количество шагов (зависит от метода интегрирования)
	const size_t steps_number_;
public:
	RKIntegrator() : RKMETHOD(), steps_number_(c.size()) // Размер узнаем по длинне вектора с
	{ }
	// сделать шаг:   		начальное время,   временной шаг,   начальное состояние,			 выбор вектора для постройки решениея если true то используется b_main (по умолчанию)
	Vector<double> make_step(double null_time, double timespan, const Vector<double>& null_state, bool isMain = true) const
	{
		Vector<double> a;
		Vector< Vector<double> > k;
		const size_t dimension = null_state.size();
		const Vector<double>& b = (isMain ? b_main : b_subs);
		k.resize(steps_number_);
		a.resize(dimension);
		Vector<double> res;
		res.resize(dimension);
		res.apply([](double) -> double { return 0.0; });
		// В цикле выполняем алгоритм рунге-кутты
		for (size_t i = 0; i < steps_number_; ++i)
		{
			// Вычисляем аргумент
			a.apply([](double) -> double { return 0.0; });
			for (size_t j = 0; j < i; ++j)
				a = a + A[i][j] * k[j];
			// Вычисляем очередной промежуточный вектор состояния
			k[i] = ode_(null_time + timespan * c[i], null_state + (timespan * a));
			// Паралельно суммируя результат
			res = res + b[i] * k[i];
		}

		return null_state + timespan * res;
	}
	// Делает заданное количество шагов
	Vector<Vector<double>> make_N_steps(double null_time, double timespan, Vector<double> null_state, size_t stepCount, bool isMain = true) const
	{
		Vector< Vector<double> > res;

		if (stepCount)
		{
			res.resize(stepCount);
			res[0] = make_step(null_time, timespan, null_state, isMain);
			// Добавляем время
			null_time += timespan;
			// В цикле вызываем интегрирование по одному шагу
			for (size_t i = 1; i < stepCount - 1; ++i)
			{
				res[i] = make_step(null_time, timespan, res[i - 1], isMain);
				null_time += timespan;
			}
		}

		return res;
	}
};