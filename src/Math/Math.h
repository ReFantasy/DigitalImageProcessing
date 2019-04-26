#ifndef __MATH_H__
#define __MATH_H__

// 四舍五入
template<typename T>
size_t Round(const T &t)
{
	auto tmp = round(t);
	return static_cast<size_t>(tmp);
}
#endif//__MATH_H__
