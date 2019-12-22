

//最大公約数を求める
template<class T>
T gcd(T a, T b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

//素数判定
template<class T>
bool isPrime(T n){
    if(n < 2) return false;
    for(T i = 2; i*i < n; ++i) if(n % i == 0) return false;
    return true;
}

//素因数分解


//関数名：pow
//概要：modつき指数関数
//第一引数a：指数の底
//第二引数b：指数
//第三引数mod：法となる値
//戻り値：a^b(m mod)
template<class T>
T pow(T a, int b){
    if(b == 0) return 1;
    if(b%2){
        T ret = pow(a,(b-1)/2); 
        return ret*ret*a;
    }else{
        T ret = pow(a,b/2);
        return ret*ret;
    }
}

template<class T>
T pow(long long a, long long b, T mod){
    if(b == 0) return 1;
    if(b % 2 == 0){
        T d = pow(a,b/2,mod);
        return (d*d)%mod;
    }else return a%mod*pow(a,b-1,mod)%mod;
}

//関数名：comb
//概要：二項係数
//第一引数n：組み合わせの全体
//第二引数r：何個取り出すか
//第三引数mod：法となる値
//戻り値：nCr(m mod)
template<class T>
T comb(T n, T r){
    if(r > n) return 0;
    if(n == r || r == 0) return 1;
    T ret = 1;
    for(T i = 1; i <= r; ++i){
        ret *= n--;
        ret /= i;
    }
    return ret;
}
template<class T>
T comb(long long n,long long r,T mod){
    if(r > n) return 0;
    if(n == r || r == 0) return 1;
    long long fact1 = 1,fact2 = 1;
    for(long long i = n; i >= n-r+1; --i) fact1 = fact1*i%mod;
    for(long long i = r; i >= 1; --i) fact2 = fact2*i%mod;
    return fact1*pow(fact2,mod-2,mod)%mod;
}
