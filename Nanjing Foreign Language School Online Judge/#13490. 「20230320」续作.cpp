#include <iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    switch (t)
    {
    case 1:
        cout << R"(
ab=
ba=
a=(return)a
b=(return)b
		)";
		break;
	case 2:
		std::cout << R"(
O0=0O
O1=1O
I0=0I
I1=1I
0O=o
1O=l
0I=l
1I=do
O=o
I=l
od=l
ld=do
0+=+O
1+=+I
0d=1
1d=d0
d=1
o=0
l=1
+=
		)";
        break;
    default:
        cout << R"(S=XY
aX=Xa
bX=Xb
cX=Xc
X=ZP
PA=dp
PB=ep
PC=fp
pa=aP
pb=bP
pc=cP
p=(return)0
aA=Aa
bB=Bb
cC=Cc
aB=Ba
bC=Cb
cA=Ac
aC=Ca
bA=Ab
cB=Bc
Ya=AY
Yb=BY
Yc=CY
P=

Z=T1
1da=ad1
1eb=be1
1fc=cf1
1a=(return)1
1b=(return)1
1c=(return)1
1Y=(return)1
1=0
0da=ad0
0db=bd0
0dc=cd0
0ea=ae0
0eb=be0
0ec=ce0
0fa=af0
0fb=bf0
0fc=cf0
0=
Ta=Z
Tb=Z
Tc=Z
T=(return)0
		)";
    }
    return 0;
}