#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

#define LOG(FMT...) fprintf(stderr, FMT)

using namespace std;

typedef long long ll;

struct cd
{
	double re, im;

	cd(double re = 0, double im = 0) : re(re), im(im) {}

	inline double real() const
	{
		return re;
	}
	inline double imag() const
	{
		return im;
	}

	inline void real(double re)
	{
		this->re = re;
	}
	inline void imag(double im)
	{
		this->im = im;
	}

	inline double norm() const
	{
		return re * re + im * im;
	}

	inline cd operator+(const cd& rhs) const
	{
		return cd(re + rhs.re, im + rhs.im);
	}
	inline cd operator-(const cd& rhs) const
	{
		return cd(re - rhs.re, im - rhs.im);
	}
	inline cd operator-() const
	{
		return cd(-re, -im);
	}
	inline cd operator*(const cd& rhs) const
	{
		return cd(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
	}
	inline cd operator/(double x) const
	{
		return cd(re / x, im / x);
	}

	inline void operator+=(const cd& rhs)
	{
		re += rhs.re;
		im += rhs.im;
	}
	inline void operator/=(double x)
	{
		re /= x;
		im /= x;
	}
	inline void operator*=(const cd& rhs)
	{
		*this = *this * rhs;
	}

	inline friend cd conj(const cd& z)
	{
		return cd(z.re, -z.im);
	}

	inline cd operator/(const cd& rhs) const
	{
		return (*this * conj(rhs)) / rhs.norm();
	}
};

#define re register

const int BASE = 4, MOD = 10000, LGM = 17;
const double PI = 3.1415926535897932384626;

class UnsignedDigit;

namespace DivHelper
{
	inline UnsignedDigit quasiInv(const UnsignedDigit& v);
}

class UnsignedDigit
{
	private:
		vector<int> digits;

	public:
		inline UnsignedDigit() : digits(1) {}

		inline UnsignedDigit(const vector<int>& digits);

		inline UnsignedDigit(ll x);

		inline UnsignedDigit(char* str);

		inline void print() const;

		inline bool operator<(const UnsignedDigit& rhs) const;
		inline bool operator<=(const UnsignedDigit& rhs) const;
		inline bool operator==(const UnsignedDigit& rhs) const;

		inline UnsignedDigit operator+(const UnsignedDigit& rhs) const;
		inline UnsignedDigit operator-(const UnsignedDigit& rhs) const;
		inline UnsignedDigit operator*(const UnsignedDigit& rhs) const;
		inline UnsignedDigit operator/(UnsignedDigit rhs) const;

		inline UnsignedDigit operator/(int v) const;

		inline UnsignedDigit move(int k) const;

		inline friend UnsignedDigit DivHelper::quasiInv(const UnsignedDigit& v);

		inline friend void swap(UnsignedDigit& lhs, UnsignedDigit& rhs)
		{
			swap(lhs.digits, rhs.digits);
		}

	private:
		inline void trim();
};

class UnsignedDecimal {};

class Int {};

class Decimal {};

namespace ConvHelper
{

	struct FFT
	{
		int L;
		int brev[1 << 20];
		cd w[1 << 20];

		FFT() {}

		inline void init(int L)
		{
			this->L = L;
			for (re int i = 0; i < (1 << L); ++i) brev[i] = (brev[i >> 1] >> 1) | ((i & 1) << (L - 1));
			for (re int i = 0; i < 1 << L; ++i) w[i] = cd(cos(i * PI * 2 / (1 << L)), sin(i * PI * 2 / (1 << L)));
		}

		inline void dft(cd* a, int lgn, int d)
		{
			int n = 1 << lgn;
			for (re int i = 0; i < n; ++i)
			{
				int rv = brev[i] >> (L - lgn);
				if (rv < i)
					swap(a[rv], a[i]);
			}
			int fa = L;
			for (re int t = 1; t < n; t <<= 1)
			{
				--fa;
				for (re int i = 0; i < n; i += t << 1)
				{
					cd* p = a + i;
					for (re int j = 0; j < t; ++j)
					{
						cd x = p[j + t] * w[j << fa];
						p[j + t] = p[j] - x;
						p[j] += x;
					}
				}
			}
			if (d == -1)
			{
				reverse(a + 1, a + n);
				for (re int i = 0; i < n; ++i) a[i] /= n;
			}
		}

		// realSeq FFT
		inline void dft(cd* a, cd* b, int lgn, int d)
		{
			int n = 1 << lgn;
			for (re int i = 0; i < n; ++i) a[i].imag(b[i].real());
			dft(a, lgn, d);
			b[0] = conj(a[0]);
			for (re int i = 1; i < n; ++i) b[i] = conj(a[n - i]);
			for (re int i = 0; i < n; ++i)
			{
				cd x = a[i], y = b[i];
				a[i] = (x + y) / 2.;
				b[i] = (x - y) / cd(0, 2);
			}
		}

	} fft;

	inline vector<ll> conv(const vector<int>& a, const vector<int>& b)
	{
		int n = a.size() - 1, m = b.size() - 1;
		if (n < 100 / (m + 1) || n < 3 || m < 3)
		{
			vector<ll> ret(n + m + 1);
			for (re int i = 0; i <= n; ++i)
				for (re int j = 0; j <= m; ++j) ret[i + j] += a[i] * (ll)b[j];
			return ret;
		}
		int lgn = 0;
		while ((1 << lgn) <= n + m) ++lgn;
		vector<cd> ta(a.begin(), a.end()), tb(b.begin(), b.end());
		ta.resize(1 << lgn);
		tb.resize(1 << lgn);

		if (a == b)
		{
			fft.dft(ta.begin().base(), lgn, 1);
			tb = ta;
		}
		else
			fft.dft(ta.begin().base(), tb.begin().base(), lgn, 1);
		for (re int i = 0; i < (1 << lgn); ++i) ta[i] *= tb[i];
		fft.dft(ta.begin().base(), lgn, -1);
		vector<ll> ret(n + m + 1);
		for (re int i = 0; i <= n + m; ++i) ret[i] = ta[i].real() + 0.5;
		return ret;
	}

}  // namespace ConvHelper

namespace DivHelper
{

	inline UnsignedDigit quasiInv(const UnsignedDigit& v)
	{
		if (v.digits.size() == 1)
		{
			UnsignedDigit tmp;
			tmp.digits.resize(3);
			tmp.digits[2] = 1;
			return tmp / v.digits[0];
		}
		if (v.digits.size() == 2)
		{
			UnsignedDigit sum = 0LL, go = 1;
			vector<int> tmp(4);
			go = go.move(4);
			vector<UnsignedDigit> db(LGM);
			db[0] = v;
			for (re int i = 1; i < LGM; ++i) db[i] = db[i - 1] + db[i - 1];
			for (re int i = 3; i >= 0; --i)
			{
				for (re int k = LGM - 1; k >= 0; --k)
					if (sum + db[k].move(i) <= go)
					{
						sum = sum + db[k].move(i);
						tmp[i] |= 1 << k;
					}
			}
			return tmp;
		}
		int n = v.digits.size(), k = (n + 2) / 2;
		UnsignedDigit tmp = quasiInv(vector<int>(v.digits.end().base() - k, v.digits.end().base()));
		return (UnsignedDigit(2) * tmp).move(n - k) - (v * (tmp * tmp)).move(-2 * k);
	}

}  // namespace DivHelper

inline UnsignedDigit::UnsignedDigit(ll x)
{
	while (x)
	{
		digits.push_back(x % MOD);
		x /= MOD;
	}
	if (digits.empty())
		digits.push_back(0);
}

inline UnsignedDigit UnsignedDigit::move(int k) const
{
	if (k == 0)
		return *this;
	if (k < 0)
	{
		if (-k >= digits.size())
			return UnsignedDigit();
		return vector<int>(digits.begin().base() + (-k), digits.end().base());
	}
	if (digits.size() == 1 && digits[0] == 0)
		return UnsignedDigit();
	UnsignedDigit ret;
	ret.digits.resize(k, 0);
	ret.digits.insert(ret.digits.end(), digits.begin(), digits.end());
	return ret;
}

inline bool UnsignedDigit::operator<(const UnsignedDigit& rhs) const
{
	int n = digits.size(), m = rhs.digits.size();
	if (n != m)
		return n < m;
	for (re int i = n - 1; i >= 0; --i)
		if (digits[i] != rhs.digits[i])
			return digits[i] < rhs.digits[i];
	return false;
}

inline bool UnsignedDigit::operator<=(const UnsignedDigit& rhs) const
{
	int n = digits.size(), m = rhs.digits.size();
	if (n != m)
		return n < m;
	for (re int i = n - 1; i >= 0; --i)
		if (digits[i] != rhs.digits[i])
			return digits[i] < rhs.digits[i];
	return true;
}

inline bool UnsignedDigit::operator==(const UnsignedDigit& rhs) const
{
	int n = digits.size(), m = rhs.digits.size();
	if (n != m)
		return false;
	return memcmp(digits.begin().base(), rhs.digits.begin().base(), n) == 0;
}

inline UnsignedDigit UnsignedDigit::operator+(const UnsignedDigit& rhs) const
{
	int n = digits.size(), m = rhs.digits.size();
	vector<int> tmp = digits;
	if (m > n)
	{
		tmp.resize(m + 1);
		for (re int i = 0; i < m; ++i)
			if ((tmp[i] += rhs.digits[i]) >= MOD)
			{
				tmp[i] -= MOD;
				++tmp[i + 1];
			}
	}
	else
	{
		tmp.resize(n + 1);
		for (re int i = 0; i < m; ++i)
			if ((tmp[i] += rhs.digits[i]) >= MOD)
			{
				tmp[i] -= MOD;
				++tmp[i + 1];
			}
		for (re int i = m; i < n; ++i)
			if (tmp[i] == MOD)
			{
				tmp[i] = 0;
				++tmp[i + 1];
			}
	}
	return tmp;
}

inline UnsignedDigit UnsignedDigit::operator*(const UnsignedDigit& rhs) const
{
	vector<ll> tmp = ConvHelper::conv(digits, rhs.digits);
	for (re int i = 0; i + 1 < tmp.size(); ++i)
	{
		tmp[i + 1] += tmp[i] / MOD;
		tmp[i] %= MOD;
	}
	while (tmp.back() >= MOD)
	{
		ll remain = tmp.back() / MOD;
		tmp.back() %= MOD;
		tmp.push_back(remain);
	}
	return vector<int>(tmp.begin(), tmp.end());
}

inline UnsignedDigit UnsignedDigit::operator/(UnsignedDigit rhs) const
{
	int m = digits.size(), n = rhs.digits.size(), t = 0;
	if (m < n)
		return 0LL;
	if (m > n * 2)
		t = m - 2 * n;
	rhs = DivHelper::quasiInv(rhs.move(t));
	UnsignedDigit ret = move(t) * rhs;
	return ret.move(-2 * (n + t));
}

inline UnsignedDigit UnsignedDigit::operator/(int k) const
{
	UnsignedDigit ret;
	int n = digits.size();
	ret.digits.resize(n);
	ll r = 0;
	for (re int i = n - 1; i >= 0; --i)
	{
		r = r * MOD + digits[i];
		ret.digits[i] = r / k;
		r %= k;
	}
	ret.trim();
	return ret;
}

inline UnsignedDigit UnsignedDigit::operator-(const UnsignedDigit& rhs) const
{
	UnsignedDigit ret(*this);
	int n = rhs.digits.size();
	for (re int i = 0; i < n; ++i)
		if ((ret.digits[i] -= rhs.digits[i]) < 0)
		{
			ret.digits[i] += MOD;
			--ret.digits[i + 1];
		}
	ret.trim();
	return ret;
}

inline UnsignedDigit::UnsignedDigit(const vector<int>& digits) : digits(digits)
{
	if (this->digits.empty())
		this->digits.resize(1);
	trim();
}

inline void UnsignedDigit::trim()
{
	while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
}

inline void UnsignedDigit::print() const
{
	printf("%d", digits.back());
	int j = 0;
	for (re int i = (int)digits.size() - 2; i >= 0; --i)
	{
		printf("%04d", digits[i]);
		++j;
	}
}

inline UnsignedDigit::UnsignedDigit(char* str)
{
	int n = strlen(str);
	reverse(str, str + n);
	digits.resize((n + BASE - 1) / BASE);
	int cur = 1;
	for (re int i = 0; i < n; ++i)
	{
		if (i % BASE == 0)
			cur = 1;
		digits[i / BASE] += cur * (str[i] - '0');
		cur *= 10;
	}
	trim();
}

#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>

#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

char s[1000010];

int main()
{
#ifdef LBT
	freopen("test.in", "r", stdin);
	int nol_cl = clock();
#endif

	scanf("%s", s);
	UnsignedDigit a(s);
	int l = ceil(log2(strlen(s)));
	ConvHelper::fft.init(l + 2);
	scanf("%s", s);
	UnsignedDigit b(s);
	UnsignedDigit res = a / b;
	while ((res + 1) * b <= a) res = res + 1;
	while (a < res * b) res = res - 1;
	res.print();

#ifdef LBT
	LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
	return 0;
}
