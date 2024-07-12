#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

#define ipair std::pair<int, int>
#define iv std::vector<int>
#define vpair std::pair<iv, iv>
/**
    분할은 제대로 동작함.
    insertion 이 제대로 동작하지 않는 현상을 발견함.
 */
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

vpair set_pair(std::vector<int>& v) {
    int mid = v.size() / 2;
    std::vector<int> lv(mid);
    std::vector<int> sv(mid);
    for (int i = 0; i < mid; i++) {
        lv[i] = v[i];
        sv[i] = v[i + mid];
        if (lv[i] < sv[i]) {
            std::swap(lv[i], sv[i]);
        }
    }
    return std::make_pair(lv, sv);
}

std::vector<int> insertion(std::vector<int>& cv, std::vector<int> sv, int idx) {
    // 1 -> 3 -> 2 -> 5 -> 4 -> 11 -> 10 -> 9 -> 8 -> 7 -> 6
    if (jacob[idx - 1] >= cv.size()) {
        return cv;
    }
    std::size_t start = sv.size() > jacob[idx] ? jacob[idx] : sv.size(); 
    for (std::size_t i = start - 1; i >= jacob[idx - 1]; --i) {
        cv.insert(
            std::lower_bound(
                cv.begin(), 
                cv.end(),
                sv[i]
            ), sv[i]);
        if (i == 0) {
            break ;
        }
    }
    std::cout << "\n";
    // if (sv.size() >= 1) {
    //     cv.insert(
    //         std::lower_bound(cv.begin(), 
    //         cv.end(), sv[sv.size() - 1]), sv[sv.size() - 1]);
    //     sv.pop_back();
    //     return insertion(cv, sv, idx + 1); 
    // }
    return insertion(cv, sv, idx + 1);
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
    std::vector<int> _sv(sv.size());
    for (int i = 0; i < _sv.size(); ++i) {
        _sv[i] = find_pair(pair_vector, _cv[i]);
    }
    if (odd != -1) {
        _sv.push_back(odd);
    }
    std::cout << "_sv: ";    
    print_vec(_sv);
    insertion(_cv, _sv, 1);
    std::cout << "_cv: ";
    print_vec(_cv);
    return _cv;
}

int main()
{
    int arr[] = {85 , 26 , 67 ,
    31 , 36 , 24 , 56 , 39 , 14 , 94 , 6 , 83 ,
    62 , 23 , 7 , 81 , 49 , 99 , 55 , 92 ,
    74 , 76 , 50 , 87 , 73 , 77 , 72 , 47 ,
  37 , 52 , 8 , 79 , 20 , 27 , 4 , 61 , 
  30 , 9 , 16 , 57 , 59 , 44 , 53 , 1 ,
  82 , 84 , 22 , 41 , 43 , 68 , 88 , 75 ,
  21 , 33 , 46 , 35 , 95 , 19 , 13 ,
  10 , 11 , 89 , 54 , 38 , 66 , 48 , 91 , 0 , 18 , 3 , 71 , 12 , 78 , 80 , 51 , 93 , 40 , 69 , 63 , 29 , 90 , 98 , 34 , 65 , 28 , 45 , 58 , 86 , 42 , 60 , 70 , 32 , 97 , 17 , 2 , 15 , 64 , 25 , 96 , 5};
    std::vector<int> v(arr, arr + (sizeof(arr) / sizeof(int)));

    std::vector<int> _res = sorted(v);
    for (int i = 0; i < _res.size(); ++i) {
        std::cout << _res[i] << " ";
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); ++i) {
        if (v[i] != _res[i]) {
            std::cout << "failed\n";
            return 1;
        }
    }
    return 0;
}
