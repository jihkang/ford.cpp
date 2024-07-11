#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#define ipair std::pair<int, int>

std::size_t jacob[54] = {
    0u,
   1u,
   3u,
   5u,
   11u,
   21u,
   43u,
   85u,
   171u,
   341u,
   683u,
   1365u,
   2731u,
   5461u,
   10923u,
   21845u,
   43691u,
   87381u,
   174763u,
   349525u,
   699051u,
   1398101u,
   2796203u,
   5592405u,
   11184811u,
   22369621u,
   44739243u,
   89478485u,
   178956971u,
   357913941u,
   715827883u,
   1431655765u,
   2863311531u,
   5726623061u,
   11453246123u,
   22906492245u,
   45812984491u,
   91625968981u,
   183251937963u,
   366503875925u,
   733007751851u,
   1466015503701u,
   2932031007403u,
   5864062014805u,
   11728124029611u,
   23456248059221u,
   46912496118443u,
   93824992236885u,
   187649984473771u,
   375299968947541u,
   750599937895083u,
   1501199875790165u,
   3002399751580331u
};

int find_pair(std::vector<ipair>& pairs, int v) {
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].second == v) {
            return pairs[i].first;
        }
    }
    return v;
}


void print_vec(std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

std::vector<int> sorted(std::vector<int>& v) {
    int mid = v.size() / 2;
    std::vector<int> _cv;
    std::vector<int> lv(mid);
    std::vector<int> sv(mid);
    std::vector<ipair> pair_vector;
    int odd = -1;
    if (v.size() % 2) {
        odd = v[v.size() - 1];
    }
    if (v.size() < 2) {
        _cv.push_back(v[0]);
        return _cv;
    }
    for (int i = 0; i < mid; i++) {
        lv[i] = v[i];
        sv[i] = v[i + mid];
        if (lv[i] < sv[i]) {
            std::swap(lv[i], sv[i]);
        }
        pair_vector.push_back(std::make_pair(sv[i], lv[i]));
    }
    _cv = sorted(lv);
    if (_cv.size() == 1) {
        _cv.insert(_cv.begin(), sv[0]);
        return _cv;
    }
    std::vector<int> _sv(sv.size());
    for (int i = 0; i < sv.size(); ++i) {
        _sv[i] = (find_pair(pair_vector, lv[i]));
    }   
    if (odd != -1) {
        _sv.push_back(odd);
    }
    for(int i = 1; jacob[i] <= _cv.size(); i++) {
        int end = std::pow(2, i) - 2 > _cv.size() ? _cv.size() : std::pow(2, i) - 2;
        if (i == 1) {
            _cv.insert(
                std::lower_bound(
                    _cv.begin(),
                    _cv.begin() + end + 1,
                    _sv[0]
                ),
                _sv[0]
            );
            continue ;
        }
        for (int j = jacob[i + 1] - 1; j > jacob[i]; j--) { 
            _cv.insert(
                std::lower_bound(
                    _cv.begin(),
                    _cv.begin() + end + 1,
                    _sv[j - 1]
                )
                ,_sv[j - 1]
            );
        }
    }
    std::cout << "\n";
    print_vec(_sv);
    std::cout<< "\n ================= \n";

    return _cv;
}

                 
int main()
{
    int arr[] = {1,2,4,5,6,3,8,7,9,10};
    std::vector<int> v(arr, arr + (sizeof(arr) / sizeof(int)));

    std::vector<int> _res = sorted(v);
    for (int i = 0; i < _res.size(); ++i) {
        std::cout << _res[i] << " ";
    }
    return 0;
}
